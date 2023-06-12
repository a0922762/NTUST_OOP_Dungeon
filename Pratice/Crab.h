#pragma once
#include "Monster.h"
#include "RandomNum.h"

class Crab : public Monster
{
private:
	void loadImage() override;

public:
	Crab(sf::Vector2i sPos);

	~Crab();

	friend istream& operator>>(istream& in, Crab& rat);
	friend ostream& operator<<(ostream& out, const Crab& rat);

	void print(ostream& out) const override { out << *this; };
	void input(istream& in) override { in >> *this; };
};

