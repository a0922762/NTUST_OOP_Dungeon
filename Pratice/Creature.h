#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Animator.h"
#include "RandomNum.h"
#include <vector>

using namespace std;


class Creature : public sf::Sprite
{
protected:
	sf::Vector2i sPos; // the position of creature
	int		sHp; // the current hp of creature
	int		sMaxHp; // the max hp of creature
	int		sMaxAtk; // the max attack of creature
	int		sMinAtk; // the min attack of creature
	int		sDef; // the defense of creature
	int		sDodge; // the dodge value of creature
	int		sHit; // the hit value of creature
	int     canSee; // can see how many blocks


	// 處理動畫效果
	Animator animator;
	DIRECTION sDir; // the direction of creature look
	sf::Time idleTime;
	float imageWidth; // 圖案原本的寬
	float imageHeight; // 圖案原本的高
	float pixelSize; // 轉換後的長寬
	bool inAttack; // 是否在攻擊狀態
	bool inChase; // 是否在追逐
	bool inDead; // 是否死亡
	sf::Text text;
	sf::Font font;
	double maxUpDis;
	double upDis;


	RandomNum randomNum;
	string name;

protected:


public:
	Creature();
	Creature(sf::Vector2i pos, int sMaxHp, int sMinAtk, int sMaxAtk, int sDef, int sDodge, int sHit);


	virtual bool moveCoridnate(DIRECTION dir, vector<vector<bool>> obstacleMap);
	virtual void moveCoridnate(sf::Vector2i pos);
	virtual void attack(Creature& target);
	virtual void beDamage(int points);
	virtual void dodge();
	virtual void loadAnimation();
	virtual void updateAnimation(sf::Time dt);

	virtual bool isIdle() const;

	void turnLeft();
	void turnRight();
	
	virtual bool isDead() const;
	// Accesser
	int getHp() const;
	int getMaxHp() const;
	int getDodge() const;
	int getMaxAtk() const;
	int getMinAtk() const;
	int getDef() const;

	void setHp(int hp) { sHp = hp; };
	void setMaxAtk(int atk) { sMaxAtk = atk; }
	void setMinAtk(int atk) { sMinAtk = atk; }
	void setDef(int def) { sDef = def; }

	sf::Text getText() const { return text; }

	sf::Vector2i getCoridnate() const;
};

