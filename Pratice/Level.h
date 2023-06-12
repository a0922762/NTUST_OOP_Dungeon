#pragma once
#include <iostream>

using namespace std;
class Level
{
private:
	int level;
	int nowExp;
	int maxExp;

	bool newLevel;

public:
	Level();
	~Level() = default;
	void gainLevel(int level);
	bool gainExp(int points);
	void clearewLevel();
	int getLevel() const;
	int getExp() const;
	int getMaxExp() const;
	bool isNewLevel() const;

	friend ostream& operator<<(ostream& out, const Level& level);
	friend istream& operator>>(istream& in, Level& level);
};

