#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Common.h"

class TextManager {
private:
    sf::RenderWindow* window;
    std::vector<sf::Text> texts;

public:
    TextManager(sf::RenderWindow* window) : window(window) {}

    void addText(const std::string& content, const sf::Vector2f& position) {
        sf::Font font;
        if (!font.loadFromFile(FONT_PATH)) {
            std::cout << "Failed to load font." << std::endl;
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);

        texts.push_back(text);
    }

    void update() {
        for (auto it = texts.begin(); it != texts.end();) {
            it->move(0, -1);  // 向上移动文字
            if (it->getPosition().y < 0) {
                it = texts.erase(it);  // 当文字移出屏幕后，从列表中删除
            }
            else {
                ++it;
            }
        }
    }

    void draw() {
        for (int i = 0; i < texts.size(); i++) {
            window->draw(texts[i]);
        }
    }
};

