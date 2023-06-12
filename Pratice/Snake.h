#pragma once
#include "Monster.h"
class Snake : public Monster
{
private:
	void loadImage() override;

public:
	Snake(sf::Vector2i sPos);

	~Snake();

	// IOstream
	friend ostream& operator<<(ostream& os, const Snake& snake);
	friend istream& operator>>(istream& in, Snake& snake);

	void print(ostream& out) const override { out << *this; };
	void input(istream& in) override { in >> *this; };
};

