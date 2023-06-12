#pragma once
#include "Creature.h"
#include "Common.h"
#include "Item.h"
#include "TextureCache.h"
#include "Animator.h"
#include "Astar.h"
#include "Board.h"

class Player;


class Monster : public Creature
{
protected:
	int sExp;
	int moveNum;

	virtual void loadImage();

public:
	Monster(sf::Vector2i pos, int sMaxHp, int sMinAtk, int sMaxAtk, int sDef, int sDodge, int sHit, int getExp, int moveNum);

	virtual ~Monster();
	void attack(Player& player);
	void control(Player* player, vector<vector<bool>> &obstacleMap);

	virtual int getExp() const;
	virtual bool findPlayer(const Player& player);
	virtual bool canAttack(const Player& player) const;
	virtual bool isIdle() const override;

	virtual void print(ostream& out) const = 0;
	virtual void input(istream& in) = 0;
};

