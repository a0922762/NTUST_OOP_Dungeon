#pragma once
#include "Item.h"
#include "Position.h"

enum class STAIR_TYPE {
	UP,
	DOWN,
};

class Stair : public Item
{
public:
	Stair(GameControl* gameControl, Position pos, STAIR_TYPE stairType);
	~Stair();
private:
	// private function
	void loadImage();
	void use() override;

	// private variable
	STAIR_TYPE stairType;
	sf::IntRect intRect;
};

