/*****************************************************************//**
 * File: Player.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: The player class 
 *********************************************************************/
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <utility>
#include "Common.h"
#include "Creature.h"
#include "Level.h"

class Monster;

using namespace std;

class Player : public Creature
{
private:
	// Game attributes

	Level level;
	sf::Music attackMusic;

private:
	void loadAnimation() override;
public:
	// Constructor / Destructor
	Player(sf::Vector2i Pos);
	virtual ~Player();

	// Functions
	pair<sf::Vector2i, sf::Vector2i> getCanSee() const;
	void setExp(int exp);
	void gainExp(int points);
	void attack(Monster& target);

	void update();


	// Accessors
	Level getLevel() const;
	Position getPos() const { return {sPos.x, sPos.y}; }

	// IOstream
	friend ostream& operator<<(ostream& out, const Player& player);
	friend istream& operator>>(istream& in, Player& player);

};

