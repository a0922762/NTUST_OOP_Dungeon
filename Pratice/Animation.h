#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Animation{
public:
	string name; // file name
	string textureName;
	vector<sf::IntRect> frames; // store all frames of animation
	sf::Time durationTime;
	bool isLooping;
	bool isEnd;

	Animation(const string& name, const string& textureName, const sf::Time& durationTime, bool isLooping = true);
	void addFrames(sf::Vector2i from, sf::Vector2i size, int count);

};
