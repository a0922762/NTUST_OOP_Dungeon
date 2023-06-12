/*****************************************************************//**
 * File: Trigger.cpp
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: The main trigger 
 *********************************************************************/
#include "Trigger.h"

// Intent: Constructor
// Post: constructor trigger and load image.
Trigger::Trigger(GameControl* gameControl, Position pos, bool canSee, bool needOperate, bool isDead) : Item(gameControl, pos, canSee, needOperate, isDead)
{
}

void Trigger::update(Player& player)
{
	if (dead) {
		return;
	}
	if (player.getCoridnate().x == sPos.x && player.getCoridnate().y == sPos.y) {
		player.beDamage(5);
		dead = true;
		this->setTextureRect(deadInRect);
	}
}

void Trigger::loadImage()
{
	sizeRate = 50 / 16;
	texture = TextureCache::getTexture(TRAP_IMAGE_PATH);
	inRect = sf::IntRect(7 * 16, 5 * 16, 16, 16);
	deadInRect = sf::IntRect(8 * 16, 5 * 16, 16, 16);

	this->setTexture(texture);
	this->setTextureRect(inRect);

	this->setPosition(sPos.x * 50, sPos.y * 50);
	this->setScale(sf::Vector2f(sizeRate, sizeRate));
	this->setOrigin(8, 8);

}

void Trigger::use()
{
}

void Trigger::toDead()
{
	dead = true;
	this->setTextureRect(deadInRect);
}


