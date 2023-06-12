#include "Rat.h"

// Intent: Constructor
//		The rat has been created with 
//		----------------------------
//		Position: sPos
//		MaxHp: 8
//		Attak: from 1 to 4
//		Defence: 1
//		Dodge: 2
//		Hit: 8
//		Exp: 1
//		canMoveTime: 1
//		--------------------------
//Post: The rat has been created
Rat::Rat(sf::Vector2i sPos) : Monster(sPos, 8, 1, 4, 1, 2, 8, 1, 1)
{
	loadImage();
}

Rat::~Rat()
{
}

void Rat::loadImage()
{
	imageWidth = 16;
	imageHeight = 16;
	animator = Animator(this);
	auto size = sf::Vector2i(IMAGE_SIZE, IMAGE_SIZE);
	auto& idleAnimation = animator.CreateAnimation("Idle", RAT_IMAGE, sf::seconds(3), true);
	idleAnimation.addFrames(sf::Vector2i(0, 0), size, 2);

	auto& deadAnimation = animator.CreateAnimation("Dead", RAT_IMAGE, sf::seconds(0.5), false);
	deadAnimation.addFrames(sf::Vector2i(11 * 16, 0), size, 4);

	auto& chaseAnimation = animator.CreateAnimation("Chase", RAT_IMAGE, sf::seconds(1), true);
	chaseAnimation.addFrames(sf::Vector2i(6 * 16, 0), size, 5);

	auto& attackAnimation = animator.CreateAnimation("Attack", RAT_IMAGE, sf::seconds(0.3), false);
	attackAnimation.addFrames(sf::Vector2i(2 * 16, 0), size, 4);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / 16.0f, BLOCK_SIZE / 16.0f));
	this->setPosition(sf::Vector2f(sPos.x * pixelSize, sPos.y * pixelSize));
}

istream& operator>>(istream& in, Rat& rat)
{
	in >> rat.sPos.x >> rat.sPos.y >> rat.sHp;
	return in;
}

ostream& operator<<(ostream& out, const Rat& rat)
{
	out << "Rat" << " " << rat.sPos.x << " " << rat.sPos.y << " "  << rat.sHp;
	return out;
}
