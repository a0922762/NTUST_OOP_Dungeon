#pragma once
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "Player.h"

/*
	畫面中左上角玩家介紹欄的class
	
	待做:
	1.click顯示詳細資料
	2.血量數字
	3.腳色icon
*/
class PlayerStatusInfo
{
public:
	// Constructor
	PlayerStatusInfo();

	// Functions
	void draw(sf::RenderWindow* window);
	void setPlayerHp(int hp);
	void setPlayerLevel(int level);
	void update(const sf::View &view, Player& player);

	~PlayerStatusInfo();

private:
	// Attributes
	sf::Texture statusImage;
	sf::Texture playerImage;
	sf::Sprite mainBody;
	sf::Sprite hpImage;
	sf::Sprite playerIcon;

	sf::Texture buffImage;
	vector<sf::Sprite> buffSprites;


	sf::Font font;
	sf::Text hpNum;
	sf::Text levelNum;

	int playerHp;
	int playerMaxHp;
	int playerLevel;

	double sizeRate;
};

