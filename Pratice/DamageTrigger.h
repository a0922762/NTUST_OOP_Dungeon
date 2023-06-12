/*****************************************************************//**
 * File: DamageTrigger.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-11
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-11
 * Description: 這是一個直接造成傷害的陷阱 
 *********************************************************************/
#pragma once
#include "Trigger.h"
#include "Floor.h"
class DamageTrigger : public Trigger
{
private:
	int atk;

	void loadImage() override;
public:
	DamageTrigger(GameControl* gameControl, Position pos, Floor floor, bool canSee = true, bool needOperate = false, bool isDead = false);
	~DamageTrigger() = default;
	virtual void update(Player& player) override;
};

