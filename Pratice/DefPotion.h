#pragma once
#include "Item.h"
#include "GameControl.h"
#include "TextureCache.h"

class DefPotion : public Item
{
public:
	DefPotion(GameControl* gameControl, Position pos);
	void use();
private:
	void loadImage();
};

