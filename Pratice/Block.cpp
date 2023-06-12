#include "Block.h"

Block::Block()
{
	type = BLOCK_TYPE::EMPTY;

	texture = TextureCache::getTexture(BLOCK_IMAGE_PATH); 

	int indexX = 0;
	int indexY = 0;

	scalar = sf::Vector2f(BLOCK_SIZE / BLOCK_IMAGE_SIZE, BLOCK_SIZE / BLOCK_IMAGE_SIZE);
	intRect = new sf::IntRect(indexX * BLOCK_IMAGE_SIZE, indexY * BLOCK_IMAGE_SIZE, BLOCK_IMAGE_SIZE, BLOCK_IMAGE_SIZE);

	this->setTexture(texture);
	this->setTextureRect(*intRect);
	this->setScale(scalar);
}

Block::Block(BLOCK_TYPE type)
{
	int indexX = 0;
	int indexY = 0;

	this->texture = TextureCache::getTexture(BLOCK_IMAGE_PATH); // 避免重複load
	this->type = type;

	// 根據不同type來設定不同的圖形
	switch (type) {
	case BLOCK_TYPE::EMPTY:
		indexY = 0;
		indexX = 0;
		break;
	case BLOCK_TYPE::WALL:
		indexY = 1;
		indexX = 0;
		break;
	case BLOCK_TYPE::ROAD:
		indexY = 0;
		indexX = 1;
		break;
	case BLOCK_TYPE::CORRIDOR:
		indexY = 0;
		indexX = 15;
		break;
	case BLOCK_TYPE::UP_STARIRS:
		indexY = 0;
		indexX = 7;
		break;
	case BLOCK_TYPE::DOWN_STARIRS:
		indexY = 0;
		indexX = 8;
		break;
	case BLOCK_TYPE::DOOR:
		indexY = 0;
		indexX = 5;
		break;
	}


	scalar = sf::Vector2f(BLOCK_SIZE / BLOCK_IMAGE_SIZE, BLOCK_SIZE / BLOCK_IMAGE_SIZE);
	intRect = new sf::IntRect(indexX * BLOCK_IMAGE_SIZE, indexY * BLOCK_IMAGE_SIZE, BLOCK_IMAGE_SIZE, BLOCK_IMAGE_SIZE);

	this->setTexture(texture);
	this->setTextureRect(*intRect);
	this->setScale(scalar);
	this->setOrigin(8, 8);

}

bool Block::canWalk() const
{
	if (type == BLOCK_TYPE::WALL || type == BLOCK_TYPE::EMPTY) {
		return false;
	}
	else {
		return true;
	}
}

Block& Block::operator=(const Block& b)
{
	this->type = b.type;
	this->texture = b.texture;
	this->intRect = b.intRect;
	this->scalar = b.scalar;
	this->setTexture(texture);
	this->setTextureRect(*intRect);
	this->setScale(scalar);
	this->setOrigin(8, 8);
	return *this;
}


BLOCK_TYPE Block::getType() const
{
	return type;
}
