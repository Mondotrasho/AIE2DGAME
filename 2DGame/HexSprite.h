#pragma once
#include "SpriteObject.h"
#include "Plane.h"

class HexSprite:public SpriteObject{
public:
	HexSprite();

	// load sprites and attach Hex
	HexSprite(const char* HexImage);
	virtual ~HexSprite();

	// OTHER load sprites and attach Hex
	void setup(const char* HexImage);


	int Hex_states{};
	bool done{}; //is the Hex setup
private:

	SpriteObject sprite;

	// add speed variables
};

