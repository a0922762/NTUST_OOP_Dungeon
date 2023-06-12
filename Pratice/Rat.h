#pragma once
#include "Monster.h"
#include "RandomNum.h"


class Rat : public Monster
{
private:
	void loadImage() override;

public:
	Rat(sf::Vector2i sPos);

	~Rat();

	friend istream& operator>>(istream& in, Rat& rat);
	friend ostream& operator<<(ostream& out, const Rat& rat);

	void print(ostream& out) const override { out << *this; };
	void input(istream& in) override { in >> *this; };
};

