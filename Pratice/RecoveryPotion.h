#pragma once
#include "Item.h"
#include "GameControl.h"
#include "TextureCache.h"
#include "TextManager.h"

class RecoveryPotion : public Item
{
public:
	RecoveryPotion(GameControl* gameControl, Position pos);
	void use();

private:
	void loadImage();
};

