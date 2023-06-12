#include "Animation.h"

Animation::Animation(const string& name, const string& textureName, const sf::Time& durationTime, bool isLooping)
	: name(name), textureName(textureName), frames(frames), durationTime(durationTime), isLooping(isLooping), isEnd(false)
{

}


// 把count幀都加入進去frames裡面
// Intent: add count frames into frames
// Pre: from and size are valid, else the result is undefined
// Post: all count frames are added into frames vector
void Animation::addFrames(sf::Vector2i from, sf::Vector2i size, int count)
{
	for (int i = 0; i < count; i++) {
		frames.push_back(sf::IntRect(from.x + i * size.x, from.y, size.x, size.y));
	}

}
