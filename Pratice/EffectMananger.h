/*****************************************************************//**
 * File: EffectMananger.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-11
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-11
 * Description: 這個class負責處理effect效果。
 *********************************************************************/
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Common.h"


class Creature;

enum EFFECT_TYPE {
	FIRE,
	BLEED,
	INVISIBLE,
};

struct Effect {
	EFFECT_TYPE type; // 效果種類
	int count; // 效果持續回合
	int atk; // 效果攻擊力
	Creature* target; // 效果目標

	Effect(EFFECT_TYPE type, Creature* target, int count = 1, int atk = 0) {
		this->type = type;
		this->target = target;
		this->count = count;
		this->atk = atk;
	};

};

class EffectMananger
{
public:
private:
	static std::vector<Effect> effects;


public:
	EffectMananger() = default;
	~EffectMananger() = default;
	static void addEffect(EFFECT_TYPE type, int count, int atk, Creature *target);
	void update();
	void draw(sf::RenderWindow* window);
	void use();

	static std::vector<Effect>& getEffects();
};

