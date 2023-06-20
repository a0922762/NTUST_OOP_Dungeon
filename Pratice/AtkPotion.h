#pragma once
#include "Item.h"
#include "GameControl.h"
#include "TextureCache.h"
#include "TextManager.h"

class AtkPotion : public Item
{
public:
	AtkPotion(GameControl* gameControl, Position pos);
	void use();
private:
	TextManager textManager;
	void loadImage();
};

