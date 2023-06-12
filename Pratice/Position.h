#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Position
{
public:
	int x;
	int y;

	Position();
	Position(int x, int y);
	Position(sf::Vector2i pos);
	~Position();

	bool operator==(const Position& pos) const;
	bool operator!=(const Position& pos) const;
	bool operator<(const Position& pos) const;

	Position operator+(const Position& pos) const;
	Position operator-(const Position& pos) const;
	Position operator*(int a) const;
	Position operator/(int a) const;
	


	Position& operator=(const Position& pos);
	friend std::ostream& operator<<(std::ostream& os, const Position& pos);


};

