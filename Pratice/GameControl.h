/*****************************************************************//**
 * File: GameControl.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-05
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-05
 * Description: 用來控制Game的界面
 *********************************************************************/
#pragma once
#include "EffectMananger.h"

class Player;

class GameControl
{
public:
	virtual void goDownstairs() = 0;
	virtual void gameOver() = 0;
	virtual Player* getPlayer() = 0;
	virtual void addEffect(EFFECT_TYPE type, Creature* target, int count = 1, int atk = 0) = 0;
};

