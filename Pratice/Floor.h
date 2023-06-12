#pragma once
#include "Common.h"
#include <iostream>

using namespace std;

constexpr int maxFloor = 5; // 目前最多有五層

struct FloorInfo {
	int width;
	int height;
	int monsterNumber;
	int triggerNumber;
	std::vector<int> monsterType;
};

class Floor
{
public:
	Floor();
	~Floor();

	FloorInfo getFloorInfo() const;
	void goUp();
	void goDown();

	// Accessors
	int getNowFloor() const { return nowFloor; }

	friend ostream& operator<<(ostream& os, const Floor& floor);
	friend istream& operator>>(istream& is, Floor& floor);

private:
	int nowFloor;
	int width[maxFloor];
	int height[maxFloor];

	int monsterNumber[maxFloor];
	int triggerNumber[maxFloor];
	std::vector<int> monsterType[maxFloor];
};

