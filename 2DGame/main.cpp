#include "_2DGameApp.h"

int main() {
	
	// allocation
	auto app = new _2DGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}