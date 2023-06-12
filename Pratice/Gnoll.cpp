#include "Gnoll.h"

// Intent: Constructor
//		The rat has been created with 
//		----------------------------
//		Position: sPos
//		MaxHp: 12
//		Attak: from 1 to 6
//		Defence: 2
//		Dodge: 4
//		Hit: 10
//		Exp: 2
//		canMoveTime: 1
//		--------------------------
//Post: The rat has been created
Gnoll::Gnoll(sf::Vector2i sPos) : Monster(sPos, 12, 1, 6, 2, 4, 10, 2, 1)
{
	loadImage();
}

void Gnoll::loadImage()
{
	RandomNum random;
	imageWidth = 12;
	imageHeight = 16;
	animator = Animator(this);

	auto size = sf::Vector2i(imageWidth, imageHeight);
	auto& idleAnimation = animator.CreateAnimation("Idle", GNOLL_IMAGE, sf::seconds(2), true);
	int randomStyle = random.getRandomBool();
	idleAnimation.addFrames(sf::Vector2i(0, randomStyle * 16), size, 2);

	auto& deadAnimation = animator.CreateAnimation("Dead", GNOLL_IMAGE, sf::seconds(0.4), false);
	deadAnimation.addFrames(sf::Vector2i(7 * imageWidth, randomStyle * 16), size, 3);

	auto& chaseAnimation = animator.CreateAnimation("Chase", GNOLL_IMAGE, sf::seconds(0.8), true);
	chaseAnimation.addFrames(sf::Vector2i(4 * imageWidth, randomStyle * 16), size, 4);

	auto& attackAnimation = animator.CreateAnimation("Attack", GNOLL_IMAGE, sf::seconds(0.2), false);
	attackAnimation.addFrames(sf::Vector2i(2 * imageWidth, randomStyle * 16), size, 2);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / imageWidth, BLOCK_SIZE / imageHeight));
	this->setPosition(sf::Vector2f(sPos.x * pixelSize, sPos.y * pixelSize));
}

Gnoll::~Gnoll()
{
}

istream& operator>>(istream& in, Gnoll& gnoll)
{
	in >> gnoll.sPos.x >> gnoll.sPos.y >>  gnoll.sHp;
	return in;
}

ostream& operator<<(ostream& out, const Gnoll& gnoll)
{
	out << "Gnoll" << " " << gnoll.sPos.x << " " << gnoll.sPos.y << " " << gnoll.sHp;
	return out;
}
