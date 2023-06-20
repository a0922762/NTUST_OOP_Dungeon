#include "Creature.h"
#include "TextManager.h"

Creature::Creature(Position pos, int sMaxHp, int sMinAtk, int sMaxAtk, int sDef, int sDodge, int sHit)
	: sPos(pos), sMaxHp(sMaxHp), sHp(sMaxHp), sMinAtk(sMinAtk), sMaxAtk(sMaxAtk), sDef(sDef), sDodge(sDodge), sHit(sHit), animator(this)
	, inAttack(false), inDead(false), inChase(false), pixelSize(50), canSee(3), sDir(DIRECTION::RIGHT)
{
}


bool Creature::moveCoridnate(DIRECTION dir, vector<vector<bool>> obstacleMap)
{
	int newX = sPos.x;
	int newY = sPos.y;

	idleTime = sf::seconds(0);

	switch (dir) {
		case DIRECTION::UP:
			newY -= 1;
			break;
		case DIRECTION::DOWN:
			newY += 1;
			break;
		case DIRECTION::LEFT:
			turnLeft();
			newX -= 1;
			break;
		case DIRECTION::RIGHT:
			turnRight();
			newX += 1;
			break;
	}
	if (newX >= 0 && newX < obstacleMap.size() && newY >= 0 && newY < obstacleMap[0].size() && obstacleMap[newX][newY] == false) {
		this->move(float(newX - sPos.x) * BLOCK_SIZE, float(newY - sPos.y) * BLOCK_SIZE);
		sPos.x = newX;
		sPos.y = newY;
		inChase = true;
		return true;
	}
	else {
		return false;
	}

}

// Post: from orinal position to new position
void Creature::moveCoridnate(const Position& pos) {

	idleTime = sf::seconds(0);

	if (pos.x <= sPos.x) {
		turnLeft();
	}
	else if (pos.x >= sPos.x) {
		turnRight();
	}


	this->move((pos.x - sPos.x) * BLOCK_SIZE, (pos.y - sPos.y) * BLOCK_SIZE);
	sPos = pos; 

	inChase = true;
}

// Post: attack target
void Creature::attack(Creature& target) {

	idleTime = sf::seconds(0);
	inAttack = true;

	target.beDamage(sMaxAtk);
}

// Post: be damage
void Creature::beDamage(int points) {
	int damage = points - sDef;

	// 如果防禦>傷害，則一樣造成0傷害
	if (damage < 0) {
		damage = 0;
	}

	sHp -= damage;

	// 如果血量<0，則血量=0，並且死亡
	if (sHp <= 0) {
		sHp = 0;
		inDead = true;
	}
	TextManager::addRiseText(this, to_string(damage), getPosition(), 60, 1, 25, sf::Color::White);
}


void Creature::updateAnimation(sf::Time dt)
{
	idleTime += dt;

	if (inAttack && animator.IsCurrentAnimationFinished()) {
		inAttack = false;
	}
	if (isIdle()) {
		inChase = false;
	}


	if (inDead) {
		animator.SwitchAnimation("Dead");
	}
	else if (inAttack) {
		animator.SwitchAnimation("Attack");
	}
	else if (inChase) {
		animator.SwitchAnimation("Chase");
	}
	else {
		animator.SwitchAnimation("Idle"); 
	}

	if (sDir == DIRECTION::LEFT) {
		this->setScale(-50 / imageWidth, 50 / imageHeight);
		this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
	}
	else if (sDir == DIRECTION::RIGHT) {
		this->setScale(50 / imageWidth, 50 / imageHeight);
		this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
	}


	animator.Update(dt);

}

void Creature::dodge()
{
	TextManager::addRiseText(this, "Dodge", getPosition(), 60, 1, 25, sf::Color::Yellow);
}

bool Creature::isIdle() const
{
	if (idleTime >= sf::seconds(0.5)) {
		return true;
	}
	else {
		return false;
	}
}

void Creature::turnLeft()
{
	sDir = DIRECTION::LEFT;
}

void Creature::turnRight()
{
	sDir = DIRECTION::RIGHT;
}

bool Creature::isDead() const
{
	if (inDead && animator.IsCurrentAnimationFinished()) {
		return true;
	}
	else {
		return false;
	}
}

int Creature::getHp() const
{
	return sHp;
}

int Creature::getMaxHp() const
{
	return sMaxHp;
}

int Creature::getDodge() const
{
	return sDodge;
}

int Creature::getMaxAtk() const
{
	return sMaxAtk;
}

int Creature::getMinAtk() const
{
	return sMinAtk;
}

int Creature::getDef() const
{
	return sDef;
}

const Position Creature::getPos() const
{
	return sPos;
}



const Position& Creature::getCoridnate() const {
	return sPos;
}



