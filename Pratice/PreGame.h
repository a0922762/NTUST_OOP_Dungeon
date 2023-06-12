#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Common.h"
#include "MusicPlayer.h" 
class PreGame : public sf::RenderWindow
{
private:
	sf::Texture startImage;
	sf::Sprite startSprite;
	sf::Text controlText;
	sf::Text loseText;
	sf::Font font;
	MusicPlayer musicPlayer;

public:
	bool quit;
	// Constructor
	PreGame();
	~PreGame();

	const bool running() const;

	// Functions
	void pollEvents();
	void update();
	void render();
};

