#pragma once

#include <vector>
#include <list>
#include "Node.h"

// forward declaring some Poly2Tri objects
namespace p2t {
	class CDT;
	struct Point;
}

class NavMesh {
public:

	// creates the base walkable area
	NavMesh(float width, float height);
	~NavMesh();

	struct Obstacle {
		float x, y, w, h, padding;
	};

	// returns true if the obstacle was added safely (does not overlap)
	bool addObstacle(float x, float y, float width, float height, float padding);

	// triangulates the walkable area and builds the nav mesh nodes
	void build();

	// given a list of pathfinding nodes from a pathfinding search,
	// treat them as NavMesh::Node's and smooth the path using a
	// funneling algorithm from (http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html)
	// we must build a list of portals first
	static int smoothPath(const std::list<Node*>& path, std::list<Vector2>& smoothPath);

	// access nodes
	
	unsigned int getNodeCount() const { return m_nodes.size(); }
	const std::vector<Node*>& getNodes() const { return m_nodes; }

	// access random node or closest node to a coordinate
	Node* getRandomNode() const;
	Node* findClosest(float x, float y) const;

	// access osbatcles
	unsigned int getObstacleCount() const { return m_obstacles.size(); }
	const std::vector<Obstacle>& getObstacles() const { return m_obstacles; }


protected:

	// funneling algorithm from (http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html)
	inline static float triarea2(const Vector2& a, const Vector2& b, const Vector2& c) {
		const float ax = b.x - a.x;
		const float ay = b.y - a.y;
		const float bx = c.x - a.x;
		const float by = c.y - a.y;
		return bx*ay - ax*by;
	}
	inline static float vdistsqr(const Vector2& a, const Vector2& b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return (dx*dx) + (dy*dy);
	}
	inline static bool vequal(const Vector2& a, const Vector2& b) {
		static const float eq = 0.001f*0.001f;
		return vdistsqr(a, b) < eq;
	}
	static int stringPull(const Vector2* portals, int portalCount, Vector2* points, const int maxPoints);

	// store obstacles and nav nodes
	std::vector<Obstacle> m_obstacles;
	std::vector<Node*> m_nodes;

	// this is used for building the mesh
	// uses Poly2Tri (https://github.com/greenm01/poly2tri)
	p2t::CDT* m_cdt;
	std::vector<std::vector<p2t::Point*>> m_polygons;
};