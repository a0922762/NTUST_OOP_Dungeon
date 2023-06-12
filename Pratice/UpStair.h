#pragma once
#include "Item.h"
class UpStair : public Item
{
public:
	UpStair(GameControl* gameControl, sf::Vector2i pos);
	~UpStair();
private:
	void loadImage();

	void use() override;

	sf::IntRect intRect;
};

