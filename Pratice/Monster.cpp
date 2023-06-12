#include "Monster.h"
#include <math.h>
#include "Player.h"


// Intent: Constructor
Monster::Monster(sf::Vector2i pos, int sMaxHp, int sMinAtk, int sMaxAtk, int sDef, int sDodge, int sHit, int getExp, int moveNum)
	: Creature(pos, sMaxHp, sMinAtk, sMaxAtk, sDef, sDodge, sHit), sExp(getExp), moveNum(moveNum)
{
	loadImage();
}

void Monster::loadImage()
{
	animator = Animator(this);
	auto size = sf::Vector2i(IMAGE_SIZE, IMAGE_SIZE);
	auto& idleAnimation = animator.CreateAnimation("Idle", RAT_IMAGE, sf::seconds(3), true);
	idleAnimation.addFrames(sf::Vector2i(0, 0), size, 2);

	auto& deadAnimation = animator.CreateAnimation("Dead", RAT_IMAGE, sf::seconds(0.5), false);
	deadAnimation.addFrames(sf::Vector2i(11 * 16, 0), size, 4);

	auto& chaseAnimation = animator.CreateAnimation("Chase", RAT_IMAGE, sf::seconds(1), true);
	chaseAnimation.addFrames(sf::Vector2i(6 * 16, 0), size, 5);

	auto& attackAnimation = animator.CreateAnimation("Attack", RAT_IMAGE, sf::seconds(0.3), false);
	attackAnimation.addFrames(sf::Vector2i(2 * 16, 0), size, 4);

	animator.SwitchAnimation("Idle");


	this->setScale(sf::Vector2f(BLOCK_SIZE / 16.0f, BLOCK_SIZE / 16.0f));
	this->setPosition(sf::Vector2f(sPos.x * pixelSize, sPos.y * pixelSize));
}


void Monster::attack(Player& player)
{
	inAttack = true;

	int attack = randomNum.getRandomInt(sMinAtk, sMaxAtk + 1);

	int lucky = randomNum.getRandomInt(0, 50);

	if (lucky + sHit > player.getDodge()) {
		player.beDamage(attack);
	}
	else {
		cout << "玩家閃避" << endl;
	}

	cout << "Monster attack player, player hp: " << player.getHp() << " / " << player.getMaxHp() << endl;

}

void Monster::control(Player* player, vector<vector<bool>>& obstacleMap)
{

	int playerX = player->getPos().x;
	int playerY = player->getPos().y;

	if (isDead()) {
		return;
	}
	else if (canAttack(*player)) {
		attack(*player);
	}
	else if (findPlayer(*player)) {

		AStar astar(obstacleMap, sPos.x, sPos.y, playerX, playerY);

		auto go = astar.getPath();

		for (int i = 0; i < go.size() && i <= moveNum; i++) {
			// 不讓怪物走到玩家的位置
			if (go[i].x == playerX && go[i].y == playerY) break;
			obstacleMap[sPos.x][sPos.y] = false;
			moveCoridnate(go[i]);
			obstacleMap[sPos.x][sPos.y] = true;
		}
	}
}

int Monster::getExp() const
{
	return sExp;
}

bool Monster::findPlayer(const Player& player)
{
	// 計算玩家和怪物之間的距離
	double d = getDistance(player.getCoridnate(), sPos);

	// 如果距離小於等於可以看到的範圍，return true
	if (d <= canSee) {
		if (inChase == false) {
			cout << "Monster find player" << endl;
		}
		inChase = true;
		return true;
	}
	else {
		inChase = false;
		return false;
	}
}

bool Monster::canAttack(const Player& player) const
{
	// 計算玩家和怪物之間的距離
	double d = getDistance(player.getCoridnate(), sPos);

	if (d <= sqrt(2)) {
		return true;
	}
	return false;
}

bool Monster::isIdle() const
{
	return !inChase;
}

Monster::~Monster()
{
	
}


