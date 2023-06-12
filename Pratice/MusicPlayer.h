#pragma once
#include <vector>
#include <map>
#include <SFML/Audio.hpp>
#include "Config.h"

using namespace std;

enum class MUSIC_TYPE {
	BACKGROUND,
	ED,
	OP,

};

class MusicPlayer
{
private:
	static sf::Music edMusic;
	static sf::Music opMusic;
	static sf::Music backGroundMusic;
	static sf::Music stabMusic;

public:
	MusicPlayer();
	~MusicPlayer();

	static void play(MUSIC_TYPE type);
	static void stop(MUSIC_TYPE type);
	static void pause(MUSIC_TYPE type);
	static void setVolume(float volume);
	static void setLoop(MUSIC_TYPE type, bool isLooping);
};

