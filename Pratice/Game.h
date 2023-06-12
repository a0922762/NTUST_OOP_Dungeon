#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Item.h"
#include "Board.h"

#include "Floor.h"
#include "Common.h"
#include "Rat.h"
#include "Snake.h"
#include "Gnoll.h"
#include "PlayerStatusInfo.h"
#include "DownStair.h"
#include "UpStair.h"
#include "Position.h"
#include "GameOverWindow.h"
#include "GameControl.h"
#include "RandomNum.h"

#include "Trigger.h"
#include "DamageTrigger.h"
#include "BleedTrigger.h"

#include "TextManager.h"
#include "EffectMananger.h"

#include "MusicPlayer.h"
using namespace std;

class Game : GameControl
{
private:
	// Window attributes
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::View view;
	double windowWidth;
	double windowHeight;
	

	// Mouse positions
	sf::Vector2i mousePosWindow;

	// Game objects
	Player *player; // player
	vector<Monster*> monsters; // all monster
	vector<Item*> items;
	Board *board;
	Floor floor;
	vector<vector<bool>> obstacleMap; // map of obstacle
	EffectMananger effectMananger;

	// Text
	// TextManager *textManager;

	// Music
	MusicPlayer musicPlayer;
	float musicVolume;

	// functional
	RandomNum randomNum;
	
	// player info
	PlayerStatusInfo playerStatusInfo;

	// initalize functions
	void initializeVariables();
	void initializeWindow();
	void initializePlayer();
	void initializeEnemy(Floor floor);
	void initializeBoard();
	void initializeView();
	void initializePlayerStatusInfo();
	void initializeItem();
	void initMusic();

	// initalize functions
	void showEnemy() const;
	void showItem() const;

	// operate functions
	void MonsterOperate();
	void playerOperate();

	// update functions
	void updateItem();
	void updateMonster(sf::Time dt);
	void updateView();
	void updateObstacle();
	void updateAnimation(sf::Time dt);


	// interface functions
	void goDownstairs() override;
	void gameOver() override;
	Player* getPlayer() override;
	void addEffect(EFFECT_TYPE type, Creature* target, int count = 1, int atk = 0) override;
	void saveGame();
	void loadGame();
public:
	// Constructor / Destructor
	Game();
	~Game();

	const bool running() const;

	// Functions
	void pollEvents();
	void update(sf::Time dt);
	void run();
	void render();
};

