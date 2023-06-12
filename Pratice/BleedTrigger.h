#pragma once
#include "Trigger.h"
#include "Floor.h"

class BleedTrigger : public Trigger
{
private:
	int atk;
	int count;
	void loadImage() override;

public:
	BleedTrigger(GameControl* gameControl, Position pos, Floor floor, bool canSee = true, bool needOperate = false, bool isDead = false);
	~BleedTrigger() = default;
	virtual void update(Player& player) override;
};

