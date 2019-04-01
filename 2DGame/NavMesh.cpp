#include "NavMesh.h"

#include "poly2tri/poly2tri.h"
#include "GameObject.h"

NavMesh::NavMesh(float width, float height) {

	m_polygons.push_back({});
	m_polygons[0].push_back(new p2t::Point(0, 0));
	m_polygons[0].push_back(new p2t::Point(0, height));
	m_polygons[0].push_back(new p2t::Point(width, height));
	m_polygons[0].push_back(new p2t::Point(width, 0));

	m_cdt = new p2t::CDT(m_polygons[0]);
}

NavMesh::~NavMesh() {
	for (auto node : m_nodes)
		delete node;
}

Node* NavMesh::getRandomNode() const {
	if (m_nodes.empty())
		return nullptr;

	return m_nodes[rand() % m_nodes.size()];
}

Node* NavMesh::findClosest(float x, float y) const {

	Node* closest = nullptr;
	float closestDist = 2000 * 2000;

	for (auto node : m_nodes) {

		float dist = (node->Pos.x - x) * (node->Pos.x - x) + (node->Pos.y - y) * (node->Pos.y - y);

		if (dist < closestDist) {
			closest = node;
			closestDist = dist;
		}
	}

	return closest;
}

bool NavMesh::addObstacle(float x, float y, float width, float height, float padding) {

	for (auto& ob : m_obstacles) {
		if (((ob.x + ob.w + ob.padding) < x - padding ||
			 (ob.y + ob.h + ob.padding) < y - padding ||
			 (x + width + padding) < ob.x - ob.padding ||
			 (y + height + padding) < ob.y - ob.padding) == false)
			return false;
	}

	Obstacle o = { x, y, width, height, padding };
	m_obstacles.push_back(o);

	m_polygons.push_back({});
	m_polygons.back().push_back(new p2t::Point(o.x - padding, o.y - padding));
	m_polygons.back().push_back(new p2t::Point(o.x - padding, o.y + o.h + padding));
	m_polygons.back().push_back(new p2t::Point(o.x + o.w + padding, o.y + o.h + padding));
	m_polygons.back().push_back(new p2t::Point(o.x + o.w + padding, o.y - padding));
	m_cdt->AddHole(m_polygons.back());

	return true;
}

void NavMesh::build() {

	m_cdt->Triangulate();

	// first convert triangles to Node's
	std::vector<p2t::Triangle*> triangles = m_cdt->GetTriangles();
	for (auto tri : triangles) {
		Node* n = new Node();
		n->vertices.push_back({ (float)tri->GetPoint(0)->x,
			(float)tri->GetPoint(0)->y });
		n->vertices.push_back({ (float)tri->GetPoint(1)->x,
			(float)tri->GetPoint(1)->y });
		n->vertices.push_back({ (float)tri->GetPoint(2)->x,
			(float)tri->GetPoint(2)->y });
		n->Pos.x = (n->vertices[0].x + n->vertices[1].x +
			n->vertices[2].x) / 3;
		n->Pos.y = (n->vertices[0].y + n->vertices[1].y +
			n->vertices[2].y) / 3;
		m_nodes.push_back(n);
	}
	// then link nodes that share triangle edges
	for (auto node : m_nodes) {
		for (auto node2 : m_nodes) {
			// ignore same node
			if (node == node2)
				continue;
			// share verts?
			int sharedVerts = 0;
			for (auto& v : node->vertices) {
				for (auto& v2 : node2->vertices) {
					if (v.x == v2.x &&
						v.y == v2.y)
						sharedVerts++;
				}
			}
			// link if two verts shared (should only ever be 0, 1 or 2)
			if (sharedVerts == 2) {
				float mag = node2->Pos.distance(node->Pos);
				// add links to both nodes //todo watch out for me I added the 2 &
				node->Connections.push_back(new Edge(node2, 0));//mag));
				//node2->Connections.push_back(new Edge(node, mag));
			}
		}
	}
	// cleanup polygons
	for (auto& p : m_polygons)
		for (auto ptr : p)
			delete ptr;
	m_polygons.clear();

	// close up Poly2Tri
	delete m_cdt;
	m_cdt = nullptr;
}


// funneling algorithm taken from
// http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html
int NavMesh::stringPull(const Vector2* portals, int portalCount,
						Vector2* points, const int maxPoints) {

	// Find straight path
	int npts = 0;

	// Init scan state
	Vector2 portalApex, portalLeft, portalRight;
	int apexIndex = 0, leftIndex = 0, rightIndex = 0;
	portalApex = portals[0];
	portalLeft = portals[0];
	portalRight = portals[1];

	// Add start point
	points[npts] = portalApex;
	npts++;

	for (int i = 1; i < portalCount && npts < maxPoints; ++i) {
		Vector2 left = portals[i * 2 + 0];
		Vector2 right = portals[i * 2 + 1];

		// Update right vertex
		if (triarea2(portalApex, portalRight, right) <= 0.0f) {
			if (vequal(portalApex, portalRight) || triarea2(portalApex, portalLeft, right) > 0.0f) {

				// Tighten the funnel
				portalRight = right;
				rightIndex = i;
			}
			else {
				// Right over left, insert left to path and restart scan from portal left point
				points[npts] = portalLeft;
				npts++;

				// Make current left the new apex
				portalApex = portalLeft;
				apexIndex = leftIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}

		// Update left vertex
		if (triarea2(portalApex, portalLeft, left) >= 0.0f) {
			if (vequal(portalApex, portalLeft) || triarea2(portalApex, portalRight, left) < 0.0f) {

				// Tighten the funnel
				portalLeft = left;
				leftIndex = i;
			}
			else {
				// Left over right, insert right to path and restart scan from portal right point
				points[npts] = portalRight;
				npts++;

				// Make current right the new apex
				portalApex = portalRight;
				apexIndex = rightIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}
	}

	// Append last point to path
	if (npts < maxPoints) {
		points[npts] = portals[(portalCount - 1) * 2 + 0];
		npts++;
	}

	return npts;
}

int NavMesh::smoothPath(const std::list<Node*>& path, std::list<Vector2>& smoothPath) {

	if (path.size() == 0)
		return 0;
	smoothPath.clear();
	// build portal list
	int index = 0;
	Vector2* portals = new Vector2[(path.size() + 1) * 2];
	// add start node as first portal
	portals[index++] = ((Node*)path.front())->Pos;
	portals[index++] = ((Node*)path.front())->Pos;
	// LOOP TO GO HERE! //done
	Node* prev = nullptr;
	for (auto it = path.begin(); it != path.end(); ++it) {
		if (it != path.begin()) {
			Node* node = (Node*)*it;
			// MORE TO GO HERE done 
			// find vertices they share to make a portal from
			Vector2 adjacent[2];
			if (prev != nullptr) {
				prev->getAdjacentVertices(node, adjacent);
			
			// get a vector going from previous node to this one
			float mag = (node->Pos.x - prev->Pos.x) *
				(node->Pos.x - prev->Pos.x) +
				(node->Pos.y - prev->Pos.y) *
				(node->Pos.y - prev->Pos.y);
			Vector2 fromPrev = {};
			if (mag > 0) {
				mag = sqrt(mag);
				fromPrev.x = (node->Pos.x - prev->Pos.x) / mag;
				fromPrev.y = (node->Pos.y - prev->Pos.y) / mag;
			}
			// now get a vector going to the first adjacent vertex on the edge
			mag = (adjacent[0].x - prev->Pos.x) *
				(adjacent[0].x - prev->Pos.x) +
				(adjacent[0].y - prev->Pos.y) *
				(adjacent[0].y - prev->Pos.y);
			Vector2 toAdj0 = {};
			if (mag > 0) {
				mag = sqrt(mag);
				toAdj0.x = (adjacent[0].x - prev->Pos.x) / mag;
				toAdj0.y = (adjacent[0].y - prev->Pos.y) / mag;
			}
			if ((fromPrev.x * toAdj0.y - toAdj0.x * fromPrev.y) > 0) {
				portals[index++] = adjacent[0];
				portals[index++] = adjacent[1];
			}
			else {
				portals[index++] = adjacent[1];
				portals[index++] = adjacent[0];
			}
			}
			prev = (Node*)*it;
		}
	}

	// add last node as end portal
	portals[index++] = ((Node*)path.back())->Pos;
	portals[index++] = ((Node*)path.back())->Pos;
	// run funnelling algorithm
	Vector2 out[100];
	int count = stringPull(portals, index / 2, out, 100);
	// gather up shortest path
	for (int i = 0; i < count; i++) {
		smoothPath.push_back(out[i]);
	}
	// cleanup and return length of path
	delete[] portals;
	return smoothPath.size();

}