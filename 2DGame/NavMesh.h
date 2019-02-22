#pragma once

#include <vector>
#include <list>
#include "Vector2.h"
#include "Node.h"


// the nav mesh node
class NavNode : public Node {
public:

	NavNode(std::string label, Vector2 pos) : Node(label, pos)
	{
	}

	NavNode() = default;

	virtual ~NavNode() {}

	// edges
	std::vector<Vector2> vertices;

	// finds any vertices that are shared with the other node
	int getAdjacentVertices(NavNode* other, Vector2* adjacent) {
		int count = 0;
		for (auto v : vertices) {
			for (auto v2 : other->vertices) {
				if (v.x == v2.x &&
					v.y == v2.y) {
					adjacent[count++] = v;
					break;
				}
			}
		}
		return count;
	}

	// simple distance squared
	static float heuristic(Node* a, Node* b) {
		NavNode* s = (NavNode*)a;
		NavNode* e = (NavNode*)b;
		float x = e->Pos.x - s->Pos.x;
		float y = e->Pos.y - s->Pos.y;
		return x * x + y * y;
	}
};
///////////////////////////////////////////////////////////
// NOTE: This is included just for reference
// TODO: Replace with your own implementations!!


//struct Vector2 {
//	float x, y;
//};

struct GameObject {
	Vector2 position = Vector2(0,0);
	float speed = 50;

	// these are used by the NavMesh behaviours
	std::list<Vector2> smoothPath;
	std::list<NavNode*> path;
};

class Behaviourtute {
public:

	// empty constructors and destructors for base class
	Behaviourtute() {}
	virtual ~Behaviourtute() {}

	// pure virtual function for executing the behaviour
	virtual bool execute(GameObject* gameObject, float deltaTime) = 0;
};

class followpath : public Behaviourtute
{
public:
	followpath(Vector2 Destination):destination(Destination){}
	Vector2 destination;
	bool execute(GameObject* gameObject, float deltaTime) override
	{
		if (destination.distance(gameObject->position) < 0.5) {
			destination = gameObject->smoothPath.back();
			gameObject->smoothPath.pop_back();
		}
	}
};

///////////////////////////////////////////////////////////

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
	static int smoothPath(const std::list<NavNode*>& path, std::list<Vector2>& smoothPath);

	// access nodes
	unsigned int getNodeCount() const { return m_nodes.size(); }
	const std::vector<NavNode*>& getNodes() const { return m_nodes; }

	// access random node or closest node to a coordinate
	NavNode* getRandomNode() const;
	NavNode* findClosest(float x, float y) const;

	// access osbatcles
	unsigned int getObstacleCount() const { return m_obstacles.size(); }
	const std::vector<Obstacle>& getObstacles() const { return m_obstacles; }

public:

	

	// a behaviour that follows a path
	class FollowPathBehaviour : public Behaviourtute {
	public:

		FollowPathBehaviour() {}
		virtual ~FollowPathBehaviour() {}

		virtual bool execute(GameObject* gameObject, float deltaTime);
	};

	// a behaviour that finds a new path and smooths it
	class NewPathBehaviour : public Behaviourtute {
	public:

		NewPathBehaviour(NavMesh* navMesh, std::list<Vector2>& smoothPath) : m_navMesh(navMesh), m_smoothPath(smoothPath) {}
		virtual ~NewPathBehaviour() {}

		virtual bool execute(GameObject* gameObject, float deltaTime);

	protected:

		NavMesh* m_navMesh;
		std::list<Vector2>& m_smoothPath;
	};

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
	std::vector<NavNode*> m_nodes;

	// this is used for building the mesh
	// uses Poly2Tri (https://github.com/greenm01/poly2tri)
	p2t::CDT* m_cdt;
	std::vector<std::vector<p2t::Point*>> m_polygons;
};

