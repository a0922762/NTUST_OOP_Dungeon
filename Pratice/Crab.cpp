#include "Crab.h"

// Intent: Constructor
//		The rat has been created with 
//		----------------------------
//		Position: sPos
//		MaxHp: 15
//		Attak: from 3 to 6
//		Defence: 4
//		Dodge: 5
//		Hit: 12
//		Exp: 3
//		canMoveTime: 2
//		--------------------------
Crab::Crab(sf::Vector2i sPos) : Monster(sPos, 15, 3, 6, 4, 5, 12, 3, 2)
{
	loadImage();
}

Crab::~Crab()
{
}

void Crab::loadImage()
{
	imageWidth = 16;
	imageHeight = 16;
	animator = Animator(this);
	auto size = sf::Vector2i(IMAGE_SIZE, IMAGE_SIZE);
	auto& idleAnimation = animator.CreateAnimation("Idle", CRAB_IMAGE, sf::seconds(3), true);
	idleAnimation.addFrames(sf::Vector2i(0, 0), size, 3);

	auto& deadAnimation = animator.CreateAnimation("Dead", CRAB_IMAGE, sf::seconds(0.5), false);
	deadAnimation.addFrames(sf::Vector2i(10 * 16, 0), size, 4);

	auto& chaseAnimation = animator.CreateAnimation("Chase", CRAB_IMAGE, sf::seconds(1), true);
	chaseAnimation.addFrames(sf::Vector2i(3 * 16, 0), size, 4);

	auto& attackAnimation = animator.CreateAnimation("Attack", CRAB_IMAGE, sf::seconds(0.3), false);
	attackAnimation.addFrames(sf::Vector2i(7 * 16, 0), size, 3);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / 16.0f, BLOCK_SIZE / 16.0f));
	this->setPosition(sf::Vector2f(sPos.x * pixelSize, sPos.y * pixelSize));
}

istream& operator>>(istream& in, Crab& crab)
{
	in >> crab.sPos.x >> crab.sPos.y >> crab.sHp;
	return in;
}

ostream& operator<<(ostream& out, const Crab& crab)
{
	out << "Crab" << " " << crab.sPos.x << " " << crab.sPos.y << " " << crab.sHp;
	return out;
}
