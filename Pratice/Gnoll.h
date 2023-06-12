#pragma once
#include "Monster.h"
#include "RandomNum.h"

class Gnoll : public Monster
{
private:
	void loadImage() override;

public:
	Gnoll(sf::Vector2i sPos);

	~Gnoll();

	friend istream& operator>>(istream& in, Gnoll& gnoll);
	friend ostream& operator<<(ostream& out, const Gnoll& gnoll);

	void print(ostream& out) const override { out << *this; };
	void input(istream& in) override { in >> *this; };



};


