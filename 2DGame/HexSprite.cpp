#include "HexSprite.h"

HexSprite::HexSprite()
{
	
		done = false;
	
}

HexSprite::HexSprite(const char * HexImage)
{
	//shrink
	scale(0.5, 0.5);
	//load textures
	load(HexImage);
	sprite.load(HexImage);

}

HexSprite::~HexSprite()
{
}

void HexSprite::setup(const char * HexImage)
{
	//shrink
	scale(0.2075 / 2,0.2075 / 2);
	//load textures
	load(HexImage);
	sprite.load(HexImage);
}
