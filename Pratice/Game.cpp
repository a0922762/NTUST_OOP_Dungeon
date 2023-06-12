/*****************************************************************//**
 * File: Game.cpp
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This is a game class, this is can control game. 
 *********************************************************************/
#include "Game.h"

#include <algorithm>
#include <random>
#include <fstream>

#include "Crab.h"
#include "RecoveryPotion.h"
#include "AtkPotion.h"
#include "DefPotion.h"


Game::Game() {
	initializeVariables(); // 初始化變數
	initializeWindow(); // 初始化視窗
	initializeBoard(); // 初始化地圖並設置障礙 (此時障礙為牆壁以及空的地方)
	initializePlayer(); // 初始化玩家
	initializeEnemy(floor); // 初始化敵人 此時障礙為敵人位置及牆壁
	initializeItem(); // 初始化道具
	initializeView();
	initializePlayerStatusInfo();
	initMusic();

	// textManager = new TextManager(window);
}

Game::~Game() {
	delete this->window;
	delete this->board;
	delete this->player;
	// delete textManager;
	for (auto& monster : monsters) {
		delete monster;
	}
	for (auto& item : items) {
		delete item;
	}
	musicPlayer.stop(MUSIC_TYPE::BACKGROUND);
}

// Post: init all variables
void Game::initializeVariables()
{
	cout << "init Variables..." << endl;
	this->window = nullptr;
}

// Post: init the game window
void Game::initializeWindow()
{
	cout << "init Window..." << endl;
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;

	this->window = new sf::RenderWindow(this->videoMode, "My dungeon game", sf::Style::Default);

	this->window->setFramerateLimit(144);
}

// Post: init the emeny by floor
void Game::initializeEnemy(Floor floor)
{
	auto floorInfo = floor.getFloorInfo(); // get floor info
	vector<sf::Vector2i> canPlace;

	cout << "init Enemy..." << endl;

	monsters.clear(); // 先清除monster固有資料

	for (int i = 0; i < board->getWidth(); i++) {
		for (int j = 0; j < board->getHeight(); j++) {
			// 如果是道路且不是障礙物
			if (!obstacleMap[i][j] && board->isRoad({ i, j })) {
				canPlace.push_back({ i, j });
			}
		}
	}

	auto pos = reservoirSampling(canPlace, floorInfo.monsterNumber);

	// 將敵人設定成障礙
	for (auto i : pos) {
		obstacleMap[i.x][i.y] = true;
	}

	// 依照比例產生怪物
	int i = 0;

	while (i < floorInfo.monsterNumber) {
		for (int j = 0; j < floorInfo.monsterType[0] && i + j < floorInfo.monsterNumber; j++) {
			monsters.push_back(new Rat(pos[i + j]));
		}
		i += floorInfo.monsterType[0];
		for (int j = 0; j < floorInfo.monsterType[1] && i + j < floorInfo.monsterNumber; j++) {
			monsters.push_back(new Snake(pos[i + j]));
		}
		i += floorInfo.monsterType[1];
		for (int j = 0; j < floorInfo.monsterType[2] && i + j < floorInfo.monsterNumber; j++) {
			monsters.push_back(new Gnoll(pos[i + j]));
		}
		i += floorInfo.monsterType[2];
		for (int j = 0; j < floorInfo.monsterType[3] && i + j < floorInfo.monsterNumber; j++) {
			monsters.push_back(new Crab(pos[i + j]));
		}
		i += floorInfo.monsterType[3];
	}
	
}

// Post: init Player Status Info
void Game::initializePlayer()
{
	
	cout << "init Player..." << endl;
	cout << "------------------------------------------------------------------------" << endl;

	// 先清除player固有資料
	if (player != nullptr) {
		delete player;
	}

	player = new Player(board->getUpStairPos());
}

// Post: init Board
void Game::initializeBoard()
{
	cout << "init Board..." << endl;

	// 先清除board固有資料
	if (board != nullptr) {
		delete board;
	}

	board = new Board(floor.getFloorInfo());

	cout << "init Obstacle Map..." << endl;

	obstacleMap.clear();

	obstacleMap = vector<vector<bool>>(board->getWidth(), vector<bool>(board->getHeight(), false));

	for (int i = 0; i < board->getWidth(); i++) {
		for (int j = 0; j < board->getHeight(); j++) {
			if (!board->canGo({ i, j })) {
				obstacleMap[i][j] = true;
			}
		}
	}

	for (int y = 0; y < board->getHeight(); y++) {
		for (int x = 0; x < board->getWidth(); x++) {
			if (obstacleMap[x][y]) {
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

}

// Pre: need init player
// Post: init View
void Game::initializeView()
{
	cout << "init View..." << endl;
	view.setSize(WINDOW_SIZE, WINDOW_SIZE);
	view.setCenter(player->getPosition().x, player->getPosition().y);
}

// Pre: need init player
// Post: init Player Status Info
void Game::initializePlayerStatusInfo()
{
	playerStatusInfo.setPlayerHp(player->getMaxHp());
	playerStatusInfo.setPlayerLevel(1);
}

// Post: init Item
void Game::initializeItem()
{
	auto floorInfo = floor.getFloorInfo(); // get floor info
	vector<sf::Vector2i> canPlace;

	cout << "init Item..." << endl;
	cout << "------------------------------------------------------------------------" << endl;

	items.clear(); // 先清除item固有資料

	// 先初始化stair
	items.push_back(new DownStair(this, board->getDownStairPos()));
	items.push_back(new UpStair(this, board->getUpStairPos()));

	for (int i = 0; i < board->getWidth(); i++) {
		for (int j = 0; j < board->getHeight(); j++) {
			// 如果是道路(不是門)且不是障礙物且不是上下樓梯
			if (!obstacleMap[i][j] && board->isRoad({ i, j }) && !(i == board->getUpStairPos().x && j == board->getUpStairPos().y) && !(i == board->getDownStairPos().x && j == board->getDownStairPos().y)) {
				canPlace.push_back({ i, j });
			}
		}
	}

	board->getCanPlaceBlock();

	auto pos = reservoirSampling(canPlace, floorInfo.triggerNumber);

	// 依照比例產生陷阱
	for (int i = 0; i < floorInfo.triggerNumber; i++) {
		int index = randomNum.getRandomInt(0, TRIGGER_NUM - 1);
		switch (index) {
		case 0:
			items.push_back(new DamageTrigger(this, pos[i], floor));
			break;
		case 1:
			items.push_back(new BleedTrigger(this, pos[i], floor));
			break;
		}
	}

	pos = reservoirSampling(canPlace, 2);

	if (randomNum.getRandomBool()) {
		items.push_back(new RecoveryPotion(this, pos[0]));
		items.push_back(new AtkPotion(this, pos[1]));
	}
	else {
		items.push_back(new RecoveryPotion(this, pos[0]));
		items.push_back(new DefPotion(this, pos[1]));
	}

}

void Game::initMusic()
{
	musicPlayer.setLoop(MUSIC_TYPE::BACKGROUND, true);
	musicPlayer.play(MUSIC_TYPE::BACKGROUND);
	musicVolume = 100.0f;
}

/**
 * ***********************
 * Show info.
 * ****************************
 */

void Game::showEnemy() const
{
	for (auto& monster : monsters) {
		if (monster->isDead() == false) {
			this->window->draw(*monster);
		}
	}
}

void Game::showItem() const
{
	for (const auto& i : items) {
		window->draw(*i);
	}
}

void Game::MonsterOperate()
{
	for (auto i : monsters) {
		i->control(player, obstacleMap);
	}
}

void Game::playerOperate()
{
	auto pos = player->getCoridnate();

	for (const auto& i : items) {
		if (i->getPos().x == pos.x && i->getPos().y == pos.y && i->isNeedOperate()) {
			i->use();
			return;
		}
	}

	sf::Vector2i delta[9] = {
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, 0} };

	for (int i = 0; i < 9; i++) {
		auto newPos = pos + delta[i];
		for (auto j : monsters) {
			if (j->isDead() == false && j->getCoridnate() == newPos) {
				player->attack(*j);
				return;
			}
		}
	}
	
}



void Game::updateItem()
{
	for (auto it : items) {
		it->update(*player);
	}
}

void Game::updateMonster(sf::Time dt)
{
	try {
		auto it = partition(monsters.begin(), monsters.end(), [](Monster* monster) {
			return !monster->isDead();
			});

		monsters.erase(it, monsters.end());
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << endl;
	}


}

void Game::updateView()
{
	view.setCenter(player->getPosition().x, player->getPosition().y);
}

void Game::updateObstacle()
{
	for (int i = 0; i < board->getHeight(); i++) {
		for (int j = 0; j < board->getWidth(); j++) {
			obstacleMap[j][i] = false;
		}
	}
	// Let wall be obstacle
	for (int i = 0; i < board->getHeight(); i++) {
		for (int j = 0; j < board->getWidth(); j++) {
			if (board->canGo({j, i}) == false) {
				obstacleMap[j][i] = true;
			}
		}
	}
	// Let monster be obstacle
	for (auto i : monsters) {
		if (i->isDead() == false) {
			obstacleMap[i->getCoridnate().x][i->getCoridnate().y] = true;
		}
	}

	//玩家不可以是阻礙

}

void Game::updateAnimation(sf::Time dt)
{
	player->updateAnimation(dt);

	for (int i = 0; i < monsters.size(); i++) {
		monsters[i]->updateAnimation(dt);
	}

}

void Game::goDownstairs()
{
	floor.goDown();
	initializeBoard();
	initializeEnemy(floor);
	initializeView();
	initializePlayerStatusInfo();
	initializeItem();


	player->moveCoridnate(board->getUpStairPos());
}

void Game::gameOver()
{
	musicPlayer.stop(MUSIC_TYPE::BACKGROUND);
	GameOverWindow gameOverWindow;

	while (gameOverWindow.running()) {
		gameOverWindow.update();
		gameOverWindow.render();
		gameOverWindow.pollEvents();
	}

	this->window->close();
}

Player* Game::getPlayer()
{
	return player;
}

void Game::addEffect(EFFECT_TYPE type, Creature* target, int count, int atk)
{
	effectMananger.addEffect(type, count, atk, target);
}

void Game::saveGame()
{
	ofstream out(SAVE_PATH);

	out << board->getWidth() << " " << board->getHeight() << endl;
	out << *board;
	out << floor << endl;
	out << *player << endl;

	out << monsters.size() << endl;
	for (auto i : monsters) {
		i->print(out);
		out << endl;
	}

	out << items.size() << endl;
	for (auto i : items) {
		out << *i << endl;
	}
	out.close();


}

void Game::loadGame()
{
	ifstream in(SAVE_PATH);

	int width, height;

	in >> width >> height;

	RandomDungeon randomDungeon(width, height);

	in >> randomDungeon;

	if (board != nullptr) {
		delete board;
	}

	board = new Board(width, height);

	board->loadDungeon(randomDungeon);

	in >> floor;

	in >> *player;

	int monsterSize;

	in >> monsterSize;
	monsters.clear();

	for (int i = 0; i < monsterSize; i++) {
		string monsterType;
		int x, y, hp;

		in >> monsterType;
		in >> x >> y >> hp;

		if (monsterType == "Rat") {
			monsters.push_back(new Rat({ x, y }));
			monsters[monsters.size() - 1]->setHp(hp);
		}
		else if (monsterType == "Snake") {
			monsters.push_back(new Snake({ x, y }));
			monsters[monsters.size() - 1]->setHp(hp);
		}
		else if (monsterType == "Gnoll") {
			monsters.push_back(new Gnoll({ x, y }));
			monsters[monsters.size() - 1]->setHp(hp);
		}
		else if (monsterType == "Crab") {
			monsters.push_back(new Crab({ x, y }));
			monsters[monsters.size() - 1]->setHp(hp);
		}
		else {
			cout << "Load failure: unknow monster name" << endl;
		}
	}

	int itemSize;
	in >> itemSize;
	items.clear();

	for (int i = 0; i < itemSize; i++) {
		string itemType;
		int x, y;
		bool canSee, dead, needOperate;

		in >> itemType;

		in >> x >> y >> canSee >> needOperate >> dead;

		if (itemType == "AtkPotion") {
			if (dead) {
				continue;
			}
			items.push_back(new AtkPotion(this, { x, y }));
		}
		else if (itemType == "RecoveryPotion") {
			if (dead) {
				continue;
			}
			items.push_back(new RecoveryPotion(this, { x, y }));
		}
		else if (itemType == "DefPotion") {
			if (dead) {
				continue;
			}
			items.push_back(new DefPotion(this, { x, y }));
		}
		else if (itemType == "UpStair") {
			if (dead) {
				continue;
			}
			items.push_back(new UpStair(this, { x, y }));
		}
		else if (itemType == "DownStair") {
			if (dead) {
				continue;
			}
			items.push_back(new DownStair(this, { x, y }));
		}
		else if (itemType == "BleedTrigger") {
			items.push_back(new BleedTrigger(this, { x, y }, floor));
			items[items.size() - 1]->toDead();
		}
		else if (itemType == "DamageTrigger") {
			items.push_back(new DamageTrigger(this, { x, y }, floor));
			items[items.size() - 1]->toDead();
		}
		else {
			cout << "Unknow item: " << itemType << endl;
		}

	}



}




const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		bool canGo = true;
		switch (ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			// textManager->addText("Key Pressed", player->getPosition());
			if (ev.key.code == sf::Keyboard::Escape) {
				window->close();
			}
			else if (ev.key.control && ev.key.code == sf::Keyboard::Z) {
				view.zoom(1.1f);
			}
			else if (ev.key.control && ev.key.code == sf::Keyboard::S) {
				saveGame();
			}
			else if (ev.key.control && ev.key.code == sf::Keyboard::L) {
				loadGame();
			}
			else if (ev.key.control && ev.key.code == sf::Keyboard::Down) {
				musicVolume -= 10;

				if (musicVolume < 0) {
					musicVolume = 0;
				}
				musicPlayer.setVolume(musicVolume);
			}
			else if (ev.key.control && ev.key.code == sf::Keyboard::Up) {
				musicVolume += 10;

				if (musicVolume > 100) {
					musicVolume = 100;
				}
				musicPlayer.setVolume(musicVolume);
			}
			else if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up) {
				canGo = player->moveCoridnate(DIRECTION::UP, obstacleMap);
				MonsterOperate();
				effectMananger.update();
			}
			else if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Left) {
				canGo = player->moveCoridnate(DIRECTION::LEFT, obstacleMap);
				MonsterOperate();
				effectMananger.update();
			}
			else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down) {
				canGo = player->moveCoridnate(DIRECTION::DOWN, obstacleMap);
				MonsterOperate();
				effectMananger.update();
			}
			else if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Right) {
				canGo = player->moveCoridnate(DIRECTION::RIGHT, obstacleMap);
				MonsterOperate();
				effectMananger.update();
			}
			else if (ev.key.code == sf::Keyboard::Space) {
				playerOperate();
				MonsterOperate();
				effectMananger.update();
			}
			else if (ev.key.code == sf::Keyboard::E) {
				if (board->canGo(player->getCoridnate())) {
					goDownstairs();
				}
			}
		}
	}
}

void Game::update(sf::Time dt) {
	this->pollEvents();
	updateObstacle();
	updateView();
	updateAnimation(dt);
	playerStatusInfo.update(view, *player);
	updateItem();
	updateMonster(dt);
	player->update();
	// textManager->update();
}

void Game::run()
{
	if (player->isDead()) {
		gameOver();
	}
}

void Game::render() {

	this->window->clear();

	this->window->setView(view);

	board->draw(window);

	showItem();

	showEnemy();



	effectMananger.draw(window);

	this->window->draw(*player);
	playerStatusInfo.draw(window);
	// textManager->draw();

	for (const auto& i : monsters) {
		this->window->draw(i->getText());
	}

	this->window->display();
}
