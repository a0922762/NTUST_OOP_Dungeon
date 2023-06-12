#include "Level.h"
#include <iostream>

Level::Level()
{
	level = 1;
	nowExp = 0;
	maxExp = 10;
	newLevel = false;
}

void Level::gainLevel(int level)
{
	this->level += level;
}

bool Level::gainExp(int points)
{
	nowExp += points;
	if (nowExp >= maxExp) {
		nowExp -= maxExp;
		gainLevel(1);
		maxExp += 5;

		std::cout << "Player is level up!" << std::endl;

		return true;
	}
	return false;
}

void Level::clearewLevel()
{
	newLevel = false;
}

int Level::getLevel() const
{
	return level;
}

int Level::getExp() const
{
	return nowExp;
}

int Level::getMaxExp() const
{
	return maxExp;
}

bool Level::isNewLevel() const
{
	return newLevel;
}

ostream& operator<<(ostream& out, const Level& level)
{	
	out << level.level << " " << level.nowExp << " " << level.maxExp << " " << level.newLevel;
	return out;
}

istream& operator>>(istream& in, Level& level)
{
	in >> level.level >> level.nowExp >> level.maxExp >> level.newLevel;
	return in;
}
