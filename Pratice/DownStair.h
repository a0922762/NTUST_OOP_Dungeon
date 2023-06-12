#pragma once
#include "Item.h"
class DownStair : public Item
{
public:
	DownStair(GameControl * gameControl, sf::Vector2i pos);
	~DownStair();
private:
	void loadImage();

	void use() override;

	sf::IntRect intRect;
};

