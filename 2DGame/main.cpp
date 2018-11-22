#include "App2D.h"
#include "PathFindingDjikstra.h"
#include "Edge.h"
#include "AStar.h"

int main() {

	
	//temp.dijkstrasSearch();



	// allocation
	auto app = new App2D();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
