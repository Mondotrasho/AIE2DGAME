#include "_2DGameApp.h"
#include "Application2D.h"

int main() {

	// allocation
	auto app = new Application2D; //_2DGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
