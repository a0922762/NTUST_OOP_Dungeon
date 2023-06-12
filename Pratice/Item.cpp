/*****************************************************************//**
 * File: Item.cpp
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This is a Item class
 *********************************************************************/
#include "Item.h"

Item::Item(GameControl* gameControl)
{
	this->gameControl = gameControl;
	canSee = true;
	needOperate = false;
	dead = false;
	sizeRate = 1.0f;
}

Item::Item(GameControl* gameControl, Position pos, bool canSee, bool needOperate, bool isDead)
{
	this->gameControl = gameControl;
	this->sPos = pos;
	this->canSee = canSee;
	this->needOperate = needOperate;
	this->dead = isDead;
	sizeRate = 1.0f;
}



void Item::draw(sf::RenderWindow* window)
{
	if (canSee && !dead) {
		window->draw(*this);
	}
}

void Item::update(Player& player)
{
	if (needOperate == false && sPos == player.getCoridnate()) {
		player.beDamage(1);
		dead = true;
	}
}

ostream& operator<<(ostream& out, const Item& item)
{
	out << item.name << " " << item.sPos.x << " " << item.sPos.y << " " << item.canSee << " " << item.needOperate << " " << item.dead;

	return out;
}
