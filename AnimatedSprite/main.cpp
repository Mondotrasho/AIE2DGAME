#include "AnimatedSpriteApp.h"
#include <iostream>
#include <exception>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main() {
	
	// allocation
	auto app = new AnimatedSpriteApp();
	try {
	// initialise and loop
	app->run("AIE", 1280, 720, false);
}
catch (std::exception e) {
	std::cout << e.what() << std::endl;
}
	// deallocation
//delete app;

	_CrtDumpMemoryLeaks();
	return 0;
}