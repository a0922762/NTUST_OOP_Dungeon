#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Animation.h"
#include "TextureCache.h"

using namespace std;

class Animator {
public:
    Animator(sf::Sprite* sprite);

    Animation& CreateAnimation(const std::string & name,
        const std::string & textureName, const sf::Time& duration, bool loop = false);

    void Update(const sf::Time& dt);
    void play(const string& name);

    // 是否切换成功
    bool SwitchAnimation(const std::string& name);

    std::string GetCurrentAnimationName() const;
    bool IsCurrentAnimationFinished() const;

private:
    Animation* FindAnimation(const std::string& name);

    void SwitchAnimation(Animation* animation);

    sf::Sprite* sprite;
    sf::Time currentTime;
    std::list<Animation> animations;
    Animation* currentAnimation;

};