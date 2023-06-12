#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Common.h"
#include "MusicPlayer.h"

class GameOverWindow : public sf::RenderWindow
{
private:
	sf::Texture deadImage;
	sf::Sprite deadSprite;
	sf::Text controlText;
	sf::Text loseText;
	sf::Font font;
	MusicPlayer musicPlayer;


	// Mouse positions
	sf::Vector2i mousePosWindow;

public:
	// Constructor
	GameOverWindow();
	~GameOverWindow();

	const bool running() const;

	// Functions
	void pollEvents();
	void update();
	void render();
};

