#pragma once
#include "Block.h"
#include "Common.h"
#include <vector>
#include <random>
#include "RandomDungeon.h"
#include "Floor.h"
#include "Item.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Board
{
private:
	int height;
	int width;

	vector<vector<Block>> allBoard;
	Position downStairPos;
	Position upStairPos;


public:
	Board(FloorInfo floor);
	Board(int width, int height);

	void draw(sf::RenderWindow* window);

	bool canGo(const Position& pos) const;
	bool isRoad(const Position& pos) const;
	
	Position getDownStairPos() const;
	Position getUpStairPos() const;

	int getHeight() const;
	int getWidth() const;

	std::vector<sf::Vector2i> getCanPlaceBlock() const;

	void loadDungeon(RandomDungeon d);

	friend ostream& operator<<(ostream& os, const Board& board);

	~Board();

};


