#include "Position.h"

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::Position(sf::Vector2i pos)
{
	x = pos.x;
	y = pos.y;
}

Position::~Position()
{
}

bool Position::operator==(const Position& pos) const
{
	return (x == pos.x && y == pos.y);
}

bool Position::operator!=(const Position& pos) const
{
	return (x != pos.x || y != pos.y);
}

bool Position::operator<(const Position& pos) const
{
	if (x < pos.x) {
		return true;
	}
	else if (x == pos.x) {
		if (y < pos.y) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

Position Position::operator+(const Position& pos) const
{
	return Position(x + pos.x, y + pos.y);
}

Position Position::operator-(const Position& pos) const
{
	return Position(x - pos.x, y - pos.y);
}

Position Position::operator*(int a) const
{
	return Position(x * a, y * a);
}

Position Position::operator/(int a) const
{
	return Position(x / a, y / a);
}

Position& Position::operator=(const Position& pos)
{
	x = pos.x;
	y = pos.y;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	os << "(" << pos.x << ", " << pos.y << ")";
	return os;
}


