#include "Snake.h"

// Intent: Constructor
//		The Snake has been created with 
//		----------------------------
//		Position: sPos
//		MaxHp: 4
//		Attak: from 1 to 4
//		Defence: 0
//		Dodge: 25
//		Hit: 10
//		Exp: 7
//		canMoveTime: 1
//		--------------------------
//Post: The rat has been created
Snake::Snake(sf::Vector2i sPos) : Monster(sPos, 4, 1, 4, 0, 60, 10, 7, 1)
{
	loadImage();
}

Snake::~Snake()
{
}


void Snake::loadImage()
{
	imageWidth = 12;
	imageHeight = 16;
	animator = Animator(this);
	auto size = sf::Vector2i(imageWidth, imageHeight);
	auto& idleAnimation = animator.CreateAnimation("Idle", SNAKE_IMAGE, sf::seconds(3), true);
	idleAnimation.addFrames(sf::Vector2i(0, 0), size, 4);

	auto& deadAnimation = animator.CreateAnimation("Dead", SNAKE_IMAGE, sf::seconds(0.5), false);
	deadAnimation.addFrames(sf::Vector2i(11 * imageWidth, 0), size, 3);

	auto& chaseAnimation = animator.CreateAnimation("Chase", SNAKE_IMAGE, sf::seconds(1), true);
	chaseAnimation.addFrames(sf::Vector2i(4 * imageWidth, 0), size, 4);

	auto& attackAnimation = animator.CreateAnimation("Attack", SNAKE_IMAGE, sf::seconds(0.3), false);
	attackAnimation.addFrames(sf::Vector2i(6 * imageWidth, 0), size, 3);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / imageWidth, BLOCK_SIZE / 16.0f));
	this->setPosition(sf::Vector2f(sPos.x * 50, sPos.y * 50));
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

ostream& operator<<(ostream& os, const Snake& snake)
{
	os << "Snake" << " " << snake.sPos.x << " " << snake.sPos.y << " " << snake.sHp << endl;
	return os;
}

istream& operator>>(istream& in, Snake& snake)
{
	in >> snake.sPos.x >> snake.sPos.y >> snake.sHp;
	return in;
}


