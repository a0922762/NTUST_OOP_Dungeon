#include "DamageTrigger.h"

DamageTrigger::DamageTrigger(GameControl* gameControl, Position pos, Floor floor, bool canSee, bool needOperate, bool isDead) : Trigger(gameControl, pos, canSee, needOperate, isDead)
{
	atk = floor.getNowFloor() * 5 + 15;
	loadImage();
	name = "DamageTrigger";
}

void DamageTrigger::loadImage()
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


void DamageTrigger::update(Player& player)
{
	if (dead) {
		return;
	}
	if (player.getCoridnate().x == sPos.x && player.getCoridnate().y == sPos.y) {
		player.beDamage(5);
		toDead();
	}
}

