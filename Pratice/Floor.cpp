#include "Floor.h"
#include "RandomNum.h"

Floor::Floor()
{
	RandomNum ranDomNum;
	for (int i = 0; i < maxFloor; i++) {
		width[i] = ranDomNum.getRandomInt(20, 50);
	}
	for (int i = 0; i < maxFloor; i++) {
		height[i] = ranDomNum.getRandomInt(20, 50);
	}
	for (int i = 0; i < maxFloor; i++) {
		monsterNumber[i] = ranDomNum.getRandomInt(5 + i, 5 + i * 2);
	}
	for (int i = 0; i < maxFloor; i++) {
		triggerNumber[i] = ranDomNum.getRandomInt(5 + i, 5 + i * 2);
	}

	nowFloor = 0;

	monsterType[0] = { 10, 0, 0, 0, 0 };
	monsterType[1] = { 6, 4, 0, 0, 0};
	monsterType[2] = { 1, 4, 6, 0, 0};
	monsterType[3] = { 0, 3, 3, 4, 0};
	monsterType[4] = { 0, 0, 5, 10, 0};

}

Floor::~Floor()
{
}

FloorInfo Floor::getFloorInfo() const
{
	FloorInfo ret;

	ret.height = height[nowFloor];
	ret.width = width[nowFloor];
	ret.monsterNumber = monsterNumber[nowFloor];
	ret.monsterType = monsterType[nowFloor];
	ret.triggerNumber = triggerNumber[nowFloor];

	return ret;
}

void Floor::goUp()
{
	if (nowFloor == 0) {
		return;
	}
	nowFloor--;
}

void Floor::goDown()
{
	if (nowFloor == maxFloor - 1) {
		return;
	}
	nowFloor++;
}

ostream& operator<<(ostream& os, const Floor& floor)
{
	os << floor.nowFloor;
	return os;
}

istream& operator>>(istream& is, Floor& floor)
{
	is >> floor.nowFloor;
	return is;
}
