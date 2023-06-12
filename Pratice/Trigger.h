#pragma once
#include "Item.h"


class Trigger : public Item {
public:
	Trigger(GameControl* gameControl, Position pos, bool canSee = true, bool needOperate = false, bool isDead = false);

	virtual void update(Player& player);

	sf::IntRect deadInRect;

public:
	virtual void loadImage();
	virtual void use();
	virtual void toDead() override;
};
