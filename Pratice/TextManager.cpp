#include "TextManager.h"
#include "Creature.h"

std::vector<TextType> TextManager::texts;
sf::Font TextManager::font;

TextManager::TextManager()
{
	font.loadFromFile(FONT_PATH);
}

void TextManager::addRiseText(Creature* creature, const std::string& content, const sf::Vector2f& orinPos, const float maxCount, const float riseSpeed, const unsigned int size, sf::Color color)
{
	sf::Text tempText;
	tempText.setString(content);
	tempText.setFont(font);
	tempText.setCharacterSize(size);
	tempText.setPosition(orinPos);
	tempText.setFillColor(color);

	texts.push_back(TextType(creature, tempText, 0, maxCount, riseSpeed, TEXT_TYPE::RISE_TEXT, false));
}

void TextManager::update()
{
	for (auto& text : texts) {
		if (text.type == RISE_TEXT) {
			text.count += text.riseSpeed;
			if (text.count >= text.maxCount) {
				text.isDead = true;
			}
			else {
				text.text.setPosition(text.creature->getPosition().x - text.text.getLocalBounds().width, text.creature->getPosition().y - text.count - text.creature->getLocalBounds().height / 2 - text.text.getLocalBounds().height);
			}
		}
	}


	// 刪除掉已經沒用的text
	auto it = partition(texts.begin(), texts.end(), [](TextType& text) {return text.isDead == false; });
	texts.erase(it, texts.end());
}

void TextManager::draw(sf::RenderWindow* window)
{
	for (const auto& text : texts) {
		window->draw(text.text);
	}
}

TextManager::~TextManager()
{

}
