#include "DownStair.h"

DownStair::DownStair(GameControl* gameControl, sf::Vector2i pos) : Item(gameControl)
{
	sPos = pos;
	needOperate = true;
	loadImage();
	name = "DownStair";
}

DownStair::~DownStair()
{
	// Do nothing
}

void DownStair::loadImage()
{
	sizeRate = 50 / 16;
	texture = TextureCache::getTexture(BLOCK_IMAGE_PATH);
	intRect = sf::IntRect(8 * 16, 0, 16, 16);

	this->setTexture(texture);
	this->setTextureRect(intRect);

	this->setPosition(sPos.x * 50, sPos.y * 50);
	this->setScale(sf::Vector2f(sizeRate, sizeRate));
	this->setOrigin(8, 8);
}

void DownStair::use()
{
	gameControl->goDownstairs();
}
