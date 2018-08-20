#include "_2DGameApp.h"
#include <iostream>
#include "RandomXY.h"


int main() {

	RandomXY hi;

	Vector2 boop = hi.random_in_range(100, 500, 100, 500);

	// allocation
	auto app = new _2DGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
