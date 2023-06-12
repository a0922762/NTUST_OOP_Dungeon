#include "RecoveryPotion.h"

RecoveryPotion::RecoveryPotion(GameControl* gameControl, Position pos) : Item(gameControl, pos, true, true, false)
{
	name = "RecoveryPotion";
	loadImage();
}

void RecoveryPotion::use()
{
	if (dead) {
		return;
	}
	gameControl->getPlayer()->setHp(gameControl->getPlayer()->getMaxHp());
	dead = true;

	this->setScale(0, 0);
}

void RecoveryPotion::loadImage()
{
	texture = TextureCache::getTexture(ITEMS_IMAGE_PATH);
	inRect = sf::IntRect(0, 336, 16, 16);
	sizeRate = 50 / 16.0f;
	setTexture(texture);
	setTextureRect(inRect);
	setScale(sizeRate, sizeRate);
	setOrigin(8, 8);

	setPosition(sPos.x * 50, sPos.y * 50);
}
