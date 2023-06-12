#include "UpStair.h"

UpStair::UpStair(GameControl* gameControl, sf::Vector2i pos) : Item(gameControl)
{
	sPos = pos;
	loadImage();
	name = "UpStair";
}


UpStair::~UpStair()
{
	// Do nothing
}

void UpStair::loadImage()
{
	sizeRate = float(50) / 16;
	texture = TextureCache::getTexture(BLOCK_IMAGE_PATH);
	intRect = sf::IntRect(7 * 16, 0, 16, 16);
	this->setTexture(texture);
	this->setTextureRect(intRect);
	this->setOrigin(8, 8);
	this->setPosition(sPos.x * float(BLOCK_SIZE), sPos.y * float(BLOCK_SIZE));
	this->setScale(sf::Vector2f(sizeRate, sizeRate));

	cout << getPosition().x << " " << getPosition().y << endl;
}

void UpStair::use()
{
}
