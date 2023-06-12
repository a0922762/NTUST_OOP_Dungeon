#include <iostream>
#include "Game.h"
#include "PreGame.h"
using namespace std;


int main() {
	PreGame preGame;

	while (preGame.running()) {
		preGame.pollEvents();
		preGame.update();
		preGame.render();
	}

	if (preGame.quit) {
		return 0;
	}

	Game game;

	sf::Clock clock;

	while (game.running()) {

		sf::Time dt = clock.restart();
		//	update
		game.update(dt);
		//	render
		game.render();
		game.run();
	}

	return 0;
}

