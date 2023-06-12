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
	sf::Vector2i downStairPos;
	sf::Vector2i upStairPos;


public:
	Board(FloorInfo floor);
	Board(int width, int height);

	void draw(sf::RenderWindow* window);

	bool canGo(sf::Vector2i pos) const;
	bool isRoad(Position pos) const;
	
	sf::Vector2i getDownStairPos() const;
	sf::Vector2i getUpStairPos() const;

	int getHeight() const;
	int getWidth() const;

	std::vector<sf::Vector2i> getCanPlaceBlock() const;

	void loadDungeon(RandomDungeon d);

	friend ostream& operator<<(ostream& os, const Board& board);

	~Board();

};


