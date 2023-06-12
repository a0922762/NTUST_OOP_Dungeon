#include "GameOverWindow.h"
#include "TextureCache.h"
#include "Common.h"

GameOverWindow::GameOverWindow()
{ 
	musicPlayer.play(MUSIC_TYPE::ED);
	musicPlayer.setLoop(MUSIC_TYPE::ED, true);

	create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Over", sf::Style::Close);

	deadImage = TextureCache::getTexture(ED_IMAGE_PATH);

	deadSprite.setTexture(deadImage);

	double scale = WINDOW_WIDTH / deadSprite.getGlobalBounds().width;

	deadSprite.setScale(scale, scale);
	deadSprite.setPosition(0, 0);


	font.loadFromFile(FONT_PATH);

	controlText.setFont(font);
	controlText.setCharacterSize(24);
	controlText.setFillColor(sf::Color::White);
	controlText.setString("Press [Q] to quit the game		/		Press [R] to restart the game");
	controlText.setPosition(WINDOW_WIDTH / 2 - controlText.getLocalBounds().width / 2, WINDOW_HEIGHT - controlText.getLocalBounds().height * 2);

	loseText.setFont(font);
	loseText.setCharacterSize(24);
	loseText.setFillColor(sf::Color::Red);
	loseText.setString("You are a loser");
	loseText.setPosition(WINDOW_WIDTH / 2 - loseText.getLocalBounds().width / 2, controlText.getPosition().y - loseText.getLocalBounds().height * 2);

}

GameOverWindow::~GameOverWindow()
{
	musicPlayer.stop(MUSIC_TYPE::ED);
}

const bool GameOverWindow::running() const
{
	return isOpen();
}

void GameOverWindow::pollEvents()
{
	sf::Event event;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);

	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Q) {
				close();
			}
			else if (event.key.code == sf::Keyboard::R) {
				// TODO: Restart the game
				close();
			}
		}
	}
}

void GameOverWindow::update()
{
	
}

void GameOverWindow::render()
{
	clear();
	draw(deadSprite);
	draw(controlText);
	draw(loseText);
	display();
}
