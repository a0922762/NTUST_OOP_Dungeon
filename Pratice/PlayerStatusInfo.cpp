#include "PlayerStatusInfo.h"
#include "TextureCache.h"
#include "EffectMananger.h"

// Intent: Constructor
// Pre: None
// Post: init all attributes
PlayerStatusInfo::PlayerStatusInfo()
{
	playerLevel = 0; // 未設定
	playerHp = 0; // 未設定
	playerMaxHp = 0; // 未設定
	sizeRate = 3; // 3倍大
	statusImage.loadFromFile(PLAYER_STATUS_IMAGE);
	playerImage.loadFromFile(PLAYER_IMAGE);

	// 設定mainBody
	mainBody.setTexture(statusImage);
	mainBody.setTextureRect(sf::IntRect(0, 0, 128, 36));
	mainBody.setScale(sizeRate, sizeRate);
	mainBody.setPosition(0, 0);

	// 設定hpImage
	hpImage.setTexture(statusImage);
	hpImage.setTextureRect(sf::IntRect(0, 36, 50, 4));
	hpImage.setScale(sizeRate, sizeRate);
	hpImage.setPosition(30 * sizeRate, 3 * sizeRate);

	// 設定playerIcon
	playerIcon.setTexture(playerImage);
	playerIcon.setTextureRect(sf::IntRect(0, 90, 12, 16));
	playerIcon.setScale(sizeRate, sizeRate);
	playerIcon.setPosition(8 * sizeRate, 8 * sizeRate);

	// 設定hpNum
	font.loadFromFile(FONT_PATH);
	hpNum.setFont(font);
	hpNum.setCharacterSize(11);
	hpNum.setFillColor(sf::Color::White);
	hpNum.setPosition(30 * sizeRate, 3 * sizeRate);
	hpNum.setString("100/100");

	// 設定levelNum
	levelNum.setFont(font);
	levelNum.setCharacterSize(11);
	levelNum.setFillColor(sf::Color::Yellow);
	levelNum.setPosition(25 * sizeRate, 25 * sizeRate);
	levelNum.setString("1");


	// 設定buffImage
	const auto& effects = EffectMananger::getEffects();
	int offect = 0;
	int imageW = 7;
	int imageH = 7;
	buffImage = TextureCache::getTexture(BUFF_IMAGE_PATH);
	for (const auto& effect : effects) {
		sf::Sprite sprite;
		sprite.setTexture(buffImage);

		cout << "asf" << endl;

		switch (effect.type) {
		case EFFECT_TYPE::BLEED:
			sprite.setTextureRect(sf::IntRect(8 * imageW, 1 * imageH, imageW, imageH));
			break;


		}
		sprite.setScale(sizeRate, sizeRate);
		sprite.setPosition(50 * sizeRate + offect * sizeRate, 5 * sizeRate);
		buffSprites.push_back(sprite);
		offect++;
	}



}

// Intent: show the player status info on the window
// Pre: window is not null
// Post: draw all the sprites on the window
void PlayerStatusInfo::draw(sf::RenderWindow* window)
{
	window->draw(mainBody);
	window->draw(hpImage);
	window->draw(playerIcon);
	window->draw(hpNum);
	window->draw(levelNum);
	for (const auto& sprite : buffSprites) {
		window->draw(sprite);
	}
}

// Intent: set the player hp
// Pre: hp is not null
// Post: set the player hp
void PlayerStatusInfo::setPlayerHp(int hp)
{
	playerHp = playerMaxHp = hp;
}

void PlayerStatusInfo::setPlayerLevel(int level)
{
	playerLevel = level;
}

void PlayerStatusInfo::update(const sf::View& view, Player& player)
{
	// 根據視角移動而跟著移動資訊欄
	mainBody.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	hpImage.setPosition(mainBody.getPosition().x + 30 * sizeRate, mainBody.getPosition().y + 3 * sizeRate);
	playerIcon.setPosition(mainBody.getPosition().x + 8 * sizeRate, mainBody.getPosition().y + 8 * sizeRate);
	hpNum.setPosition(mainBody.getPosition().x + 30 * sizeRate, mainBody.getPosition().y + 3 * sizeRate);
	levelNum.setPosition(mainBody.getPosition().x + 27 * sizeRate - levelNum.getLocalBounds().width / 2, mainBody.getPosition().y + 28 * sizeRate - levelNum.getLocalBounds().height / 2);

	// 更新玩家資訊
	playerHp = player.getHp();
	playerMaxHp = player.getMaxHp();
	playerLevel = player.getLevel().getLevel();

	// 根據現在血量調整血量條
	float hpPercent = float(playerHp) / float(playerMaxHp);
	string hpPercentStr = std::to_string(playerHp) + "/" + std::to_string(playerMaxHp);
	string levelStr = std::to_string(playerLevel);

	hpImage.setScale(sizeRate * hpPercent, sizeRate);
	hpNum.setString(hpPercentStr);
	levelNum.setString(levelStr);

	// 更新buff
	const auto& effects = EffectMananger::getEffects();
	int offect = 0;
	int imageW = 7;
	int imageH = 7;

	buffSprites.clear();
	buffImage = TextureCache::getTexture(BUFF_IMAGE_PATH);
	for (const auto& effect : effects) {
		sf::Sprite sprite;
		sprite.setTexture(buffImage);

		switch (effect.type) {
		case EFFECT_TYPE::BLEED:
			sprite.setTextureRect(sf::IntRect(8 * imageW, 1 * imageH, imageW, imageH));
			break;


		}
		sprite.setScale(sizeRate, sizeRate);
		sprite.setPosition(mainBody.getPosition().x + 31 * sizeRate + offect * sizeRate, mainBody.getPosition().y + 10 * sizeRate);
		buffSprites.push_back(sprite);
		offect++;
	}

}

// Intent: Destructor
// Pre: None
// Post: None
PlayerStatusInfo::~PlayerStatusInfo()
{
	// Nothing to do here
}
