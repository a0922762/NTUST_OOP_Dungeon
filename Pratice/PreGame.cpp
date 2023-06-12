#include "PreGame.h"
#include "TextureCache.h"
#include "Config.h"

PreGame::PreGame()
{
	musicPlayer.play(MUSIC_TYPE::OP);
	musicPlayer.setLoop(MUSIC_TYPE::OP, true);

	create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PreGame", sf::Style::Close);

	startImage = TextureCache::getTexture(START_IMAGE_PATH);

	startSprite.setTexture(startImage);

	double scale = WINDOW_WIDTH / startSprite.getGlobalBounds().width;

	startSprite.setScale(scale, scale);
	startSprite.setPosition(0, 0);


	font.loadFromFile(FONT_PATH);

	controlText.setFont(font);
	controlText.setCharacterSize(24);
	controlText.setFillColor(sf::Color::White);
	controlText.setString("Press the [Space] to enter the dungeon, or press [Q] to leave like a weakling.");
	controlText.setPosition(WINDOW_WIDTH / 2 - controlText.getLocalBounds().width / 2, WINDOW_HEIGHT - controlText.getLocalBounds().height * 2);

	loseText.setFont(font);
	loseText.setCharacterSize(24);
	loseText.setFillColor(sf::Color::Red);
	loseText.setString("Welcome to the dungeon. Are you a coward ? ");
	loseText.setPosition(WINDOW_WIDTH / 2 - loseText.getLocalBounds().width / 2, controlText.getPosition().y - loseText.getLocalBounds().height * 2);

	quit = true;
}

PreGame::~PreGame()
{
	musicPlayer.stop(MUSIC_TYPE::OP);
}

const bool PreGame::running() const
{
	return isOpen();
}

void PreGame::pollEvents()
{
	sf::Event event;

	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Q) {
				quit = true;
				close();
			}
			else if (event.key.code == sf::Keyboard::Space) {
				// TODO: Restart the game
				quit = false;
				close();
			}
		}
	}
}

void PreGame::update()
{
}

void PreGame::render()
{
	clear();
	draw(startSprite);
	draw(controlText);
	draw(loseText);
	display();
}
