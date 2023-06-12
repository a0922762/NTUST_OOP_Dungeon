#pragma once
#include "Item.h"
#include "GameControl.h"
#include "TextureCache.h"

class AtkPotion : public Item
{
public:
	AtkPotion(GameControl* gameControl, Position pos);
	void use();
private:
	void loadImage();
};

