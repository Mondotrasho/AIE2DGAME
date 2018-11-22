#include "App2D.h"
#include "PathFindingDjikstra.h"
#include "Edge.h"

int main() {
	PathFindingDjikstra Djiki;

	std::vector<Node> nodes;

	//setup nodes with no connections
	Node node0 = { "0" , Vector2{ 150,200 } };
	Node node1 = { "1" , Vector2{ 250,200 } };
	Node node2 = { "2" , Vector2{250,300 } };
	Node node3 = { "3" , Vector2{ 250,250 } };
	Node node4 = { "4" , Vector2{ 200,200 } };
	Node node5 = { "5" , Vector2{ 150,250 } };
	//pushback Nodes
	nodes.push_back(node0);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);
	nodes.push_back(node5);
	//setup edges to attach
	std::vector<Edge> node0Edges;
	Edge node0Edge1 = { &node5, 5.0f };
	node0Edges.push_back(node0Edge1);
	Edge node0Edge2 = { &node1, 2.0f };
	node0Edges.push_back(node0Edge2);

	std::vector<Edge> node1Edges;
	Edge node1Edge1 = { &node2, 3.0f };
	node1Edges.push_back(node1Edge1);

	std::vector<Edge> node2Edges;
	Edge node2Edge1 = { &node0, 3.0f };
	node2Edges.push_back(node2Edge1);
	Edge node2Edge2 = { &node3, 1.0f };
	node2Edges.push_back(node2Edge2);

	std::vector<Edge> node3Edges;
	Edge node3Edge1 = { &node4, 4.0f };
	node3Edges.push_back(node3Edge1);
	Edge node3Edge2 = { &node5, 4.0f };
	node3Edges.push_back(node3Edge2);

	//node 4 is empty

	std::vector<Edge> node5Edges;
	Edge node5Edge1 = { &node4, 6.0f };
	node5Edges.push_back(node5Edge1);

	//attach edges
	node0.Connections = node0Edges;
	node1.Connections = node1Edges;
	node2.Connections = node2Edges;
	node3.Connections = node3Edges;
	//nodes[4].Connections = node4Edges;
	node5.Connections = node5Edges;

	auto endpos = Djiki.dijkstrasSearch(&node0  , &node4);
	
	endpos;
	
	//temp.dijkstrasSearch();



	// allocation
	auto app = new App2D();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
