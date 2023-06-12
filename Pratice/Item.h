/*****************************************************************//**
 * File: Item.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This is a item class 
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Player.h"
#include "GameControl.h"

using namespace std;

class Game;

class Item : public sf::Sprite 
{
protected:
	string name;
	bool canSee;
	bool needOperate;
	bool dead;
	Position sPos;

	sf::Texture texture;
	sf::IntRect inRect;
	float sizeRate;

	GameControl* gameControl;
public:
	Item(GameControl* gameControl);
	Item(GameControl* gameControl, Position pos, bool canSee = true, bool needOperate = false, bool isDead = false);

	// main function
	virtual void draw(sf::RenderWindow* window);
	virtual void update(Player& player);
	virtual void use() = 0;
	virtual void toDead() { dead = true; };

	// Accessors
	Position getPos() const { return sPos; };
	bool isNeedOperate() const { return needOperate; };
	bool isDead() const { return dead; };


	friend ostream& operator<<(ostream& out, const Item& item);
};


