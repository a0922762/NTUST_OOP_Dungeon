#include "AtkPotion.h"

AtkPotion::AtkPotion(GameControl* gameControl, Position pos) : Item(gameControl, pos, true, true, false)
{
	name = "AtkPotion";
	loadImage();
}

void AtkPotion::use()
{
	if (dead) {
		return;
	}
	gameControl->getPlayer()->setMinAtk(gameControl->getPlayer()->getMinAtk() + 1);
	gameControl->getPlayer()->setMaxAtk(gameControl->getPlayer()->getMaxAtk() + 1);
	dead = true;
	this->setScale(0, 0);
}

void AtkPotion::loadImage()
{
	texture = TextureCache::getTexture(ITEMS_IMAGE_PATH);
	inRect = sf::IntRect(16, 336, 16, 16);
	sizeRate = 50 / 16.0f;
	setTexture(texture);
	setTextureRect(inRect);
	setScale(sizeRate, sizeRate);
	setOrigin(8, 8);

	setPosition(sPos.x * 50, sPos.y * 50);
}
