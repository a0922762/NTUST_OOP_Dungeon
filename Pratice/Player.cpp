/*****************************************************************//**
 * File: Player.cpp
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This is a player class. 
 *********************************************************************/
#include <iostream>
#include "Common.h"
#include "RandomNum.h"
#include "Monster.h"
#include "Player.h"

Player::Player(sf::Vector2i sPos) : Creature(sPos, 50, 3, 6, 2, 2, 2)
{
	animator = Animator(this);

	loadAnimation();
}

Player::~Player()
{
}


void Player::setExp(int exp)
{
}

pair<sf::Vector2i, sf::Vector2i> Player::getCanSee() const
{
	return make_pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(sPos.x - canSee, sPos.y - canSee), sf::Vector2i(sPos.x + canSee, sPos.y + canSee));
}

void Player::attack(Monster& target)
{
	RandomNum randomNum;
	int attack = randomNum.getRandomInt(sMinAtk, sMaxAtk);
	int lucky = randomNum.getRandomInt(0, 100);

	// if lucky enough, attack success
	if (lucky + this->sHit >= target.getDodge()) {
		target.beDamage(attack);
	}
	else {
		target.dodge();
	}
	
	inAttack = true;

	

	// if target is dead, gain exp
	if (target.getHp() == 0) {
		gainExp(target.getExp());
	}

	attackMusic.play();

	cout << "Player attack, target hp = " << target.getHp() << " / " << target.getMaxHp() << std::endl;
}

void Player::update()
{
	this->setPosition(sPos.x * 50, sPos.y * 50);
}

void Player::loadAnimation()
{
	imageWidth = 12;
	imageHeight = 16;
	animator = Animator(this);
	auto size = sf::Vector2i(12, IMAGE_SIZE);
	auto& idleAnimation = animator.CreateAnimation("Idle", PLAYER_IMAGE, sf::seconds(3), true);
	idleAnimation.addFrames(sf::Vector2i(0, 90), size, 2);

	auto& chaseAnimation = animator.CreateAnimation("Chase", PLAYER_IMAGE, sf::seconds(1), true);
	chaseAnimation.addFrames(sf::Vector2i(2 * 12, 90), size, 6);

	auto& deadAnimation = animator.CreateAnimation("Dead", PLAYER_IMAGE, sf::seconds(0.5), false);
	deadAnimation.addFrames(sf::Vector2i(8 * 12, 90), size, 5);

	auto& attackAnimation = animator.CreateAnimation("Attack", PLAYER_IMAGE, sf::seconds(0.3), false);
	attackAnimation.addFrames(sf::Vector2i(13 * 12, 90), size, 3);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / 12.0f, BLOCK_SIZE / 16.0f));
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
	this->setPosition(sf::Vector2f(sPos.x * 50, sPos.y * 50));
}

Level Player::getLevel() const
{
	return level;
}



void Player::gainExp(int points)
{
	if (level.gainExp(points)) {
		sMaxHp += 10;
	}


}

ostream& operator<<(ostream& out, const Player& player)
{
	out << player.sPos.x << " " << player.sPos.y << " " << player.sMaxHp << " " << player.sHp << " " << player.sHit << " " << player.sDef << " " << player.sDodge << " " << player.sMinAtk << " " << player.sMaxAtk << " " << player.level;
	return out;
}

istream& operator>>(istream& in, Player& player)
{
	in >> player.sPos.x >> player.sPos.y >> player.sMaxHp >> player.sHp >> player.sHit >> player.sDef >> player.sDodge >> player.sMinAtk >> player.sMaxAtk >> player.level;
	return in;
}
