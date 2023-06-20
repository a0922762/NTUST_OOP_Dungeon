#include "BleedTrigger.h"
#include "EffectMananger.h"
#include "TextManager.h"

BleedTrigger::BleedTrigger(GameControl* gameControl, Position pos, Floor floor, bool canSee, bool needOperate, bool isDead) : Trigger(gameControl, pos, canSee, needOperate, isDead)
{
	atk = floor.getNowFloor() * 2 + 2;
	count = floor.getNowFloor() + 5;
	loadImage();

	name = "BleedTrigger";
}

void BleedTrigger::loadImage()
{
	sizeRate = 50 / 16;
	texture = TextureCache::getTexture(TRAP_IMAGE_PATH);
	inRect = sf::IntRect(2 * 16, 5 * 16, 16, 16);
	deadInRect = sf::IntRect(8 * 16, 5 * 16, 16, 16);

	this->setTexture(texture);
	this->setTextureRect(inRect);

	this->setPosition(sPos.x * 50, sPos.y * 50);
	this->setScale(sf::Vector2f(sizeRate, sizeRate));
	this->setOrigin(8, 8);
}


void BleedTrigger::update(Player& player)
{
	if (dead) {
		return;
	}
	if (sPos == player.getPos()) {
		gameControl->addEffect(BLEED, &player, count, atk);
		TextManager::addRiseText(gameControl->getPlayer(), "Bleeding", gameControl->getPlayer()->getPosition(), 60, 1, 18, sf::Color::Red);
		toDead();
	}
}
