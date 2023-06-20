/*****************************************************************//**
 * File: TextManager.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-20
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-20
 * Description: 這個類別負責管理各種文字，並且統一對文字進行更新、顯示。 
 *********************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Common.h"
#include "Creature.h"

enum TEXT_TYPE {
	RISE_TEXT,
};

struct TextType {
    sf::Text text;
    float count;
    float maxCount;
    float riseSpeed;
    TEXT_TYPE type;
    bool isDead;
    Creature* creature;

    TextType(Creature* creature, sf::Text text, float count, float maxCount, float riseSpeed, TEXT_TYPE type, bool isDead) {
		this->text = text;
		this->count = count;
		this->maxCount = maxCount;
		this->riseSpeed = riseSpeed;
		this->type = type;
		this->isDead = isDead;
        this->creature = creature;
	}
};

class TextManager {
private:
    static std::vector<TextType> texts;
    static sf::Font font;

public:
    TextManager();
    static void addRiseText(Creature* creature, const std::string& content, const sf::Vector2f& orinPos, const float maxCount, const float riseSpeed, const unsigned int size, sf::Color color);

    static void update();
    static void draw(sf::RenderWindow* window);

    ~TextManager();
};

