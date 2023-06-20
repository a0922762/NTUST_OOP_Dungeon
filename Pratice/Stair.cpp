#include "Stair.h"

Stair::Stair(GameControl* gameControl, Position pos, STAIR_TYPE stairType) : Item(gameControl)
{
	sPos = pos;
	needOperate = true;
	name = stairType == STAIR_TYPE::UP ? "UpStair" : "DownStair";
	this->stairType = stairType;
	
	loadImage();
}


Stair::~Stair()
{
	// Do nothing
}

void Stair::loadImage()
{
	sizeRate = float(50) / 16;
	texture = TextureCache::getTexture(BLOCK_IMAGE_PATH);

	// 根據不同的type選擇不同圖形
	if (stairType == STAIR_TYPE::UP) {
		intRect = sf::IntRect(7 * 16, 0, 16, 16);
	}
	else {
		intRect = sf::IntRect(8 * 16, 0, 16, 16);
	}

	this->setTexture(texture);
	this->setTextureRect(intRect);
	this->setOrigin(8, 8);
	this->setPosition(sPos.x * float(BLOCK_SIZE), sPos.y * float(BLOCK_SIZE));
	this->setScale(sf::Vector2f(sizeRate, sizeRate));
}

void Stair::use()
{
	if (stairType == STAIR_TYPE::UP) {
		// gameControl->goUpstairs();
	}
	else {
		gameControl->goDownstairs();
	}
}
