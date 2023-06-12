#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "TextureCache.h"

class Block : public sf::Sprite
{
private:
	BLOCK_TYPE type;
	sf::Texture texture;
	sf::IntRect* intRect;
	sf::Vector2f scalar;
public:
	Block();
	Block(BLOCK_TYPE type);
	bool canWalk() const;

	Block& operator=(const Block& b);


	BLOCK_TYPE getType() const;
};
