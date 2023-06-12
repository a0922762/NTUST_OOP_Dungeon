#include "Creature.h"

// Intent: default constructor
// Post: set default value to all attributes
Creature::Creature() 
	: sPos({ 1, 1 }), sHp(100), sMaxHp(100), sMaxAtk(10), sDef(10), sDodge(10), sHit(5), sDir(DIRECTION::RIGHT), pixelSize(50), canSee(5), animator(this) {
}


Creature::Creature(sf::Vector2i pos, int sMaxHp, int sMinAtk, int sMaxAtk, int sDef, int sDodge, int sHit)
	: sPos(pos), sMaxHp(sMaxHp), sHp(sMaxHp), sMinAtk(sMinAtk), sMaxAtk(sMaxAtk), sDef(sDef), sDodge(sDodge), sHit(sHit), animator(this), inAttack(false), inDead(false), inChase(false), pixelSize(50), canSee(3), sDir(DIRECTION::RIGHT)
{
	font.loadFromFile(FONT_PATH);
	text = sf::Text("", font, 15);
	text.setFillColor(sf::Color::Red);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	maxUpDis = 50;
	upDis = 0;

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
		this->move(double(newX - sPos.x) * BLOCK_SIZE, double(newY - sPos.y) * BLOCK_SIZE);
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
void Creature::moveCoridnate(sf::Vector2i pos) {

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

	if (damage < 0) {
		damage = 0;
	}

	sHp -= damage;

	if (sHp <= 0) {
		sHp = 0;
		inDead = true;
	}

	text = sf::Text(to_string(points), font, 20);
	text.setFillColor(sf::Color::Black);
	sf::Vector2f midTopPos = this->getPosition() - sf::Vector2f(0, this->getLocalBounds().height / 2);
	upDis = 0;
	text.setPosition(midTopPos.x - text.getLocalBounds().width / 2, midTopPos.y - upDis - text.getLocalBounds().height);
}

void Creature::loadAnimation()
{
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

	if (text.getString() != "") {
		if (upDis <= maxUpDis) {
			sf::Vector2f midTopPos = this->getPosition() - sf::Vector2f(0, this->getLocalBounds().height / 2);
			upDis += 0.4;
			text.setPosition(midTopPos.x - text.getLocalBounds().width / 2, midTopPos.y - upDis - text.getLocalBounds().height);
		}
		else {
			text.setString("");
			upDis = 0;
		}

	}


	animator.Update(dt);


}

void Creature::dodge()
{
	if (text.getString() != "") {
		upDis = 0;
		text.setString("Dodge");
	}
	else {
		upDis = 0;
		text.setString("Dodge");
	}



}

bool Creature::isIdle() const
{
	if (idleTime >= sf::seconds(1.5)) {
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

sf::Vector2i Creature::getCoridnate() const {
	return sPos;
}



