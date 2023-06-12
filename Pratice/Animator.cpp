#include "Animator.h"

Animator::Animator(sf::Sprite* sprite) : sprite(sprite), currentTime(), currentAnimation(nullptr)
{

}

Animation& Animator::CreateAnimation(const std::string& name, const std::string &textureName, const sf::Time& duration, bool loop)
{
	Animation animation = Animation(name, textureName, duration, loop);

	animations.push_back(animation);

	// 如果目前沒有任何動畫，就把這個動畫設為目前的動畫
	if (currentAnimation == nullptr) {
		SwitchAnimation(&animations.back());
	}

	return animations.back();
}

bool Animator::SwitchAnimation(const std::string& name)
{
	auto findAnimation = FindAnimation(name);

	if (findAnimation != nullptr) {
		SwitchAnimation(findAnimation);
		currentAnimation->isEnd = false;
		return true;
	}
	else {
		return false;
	}
}

std::string Animator::GetCurrentAnimationName() const
{
	if (currentAnimation == nullptr) {
		return "";
	} 
	else {
		return currentAnimation->name;
	}
}

bool Animator::IsCurrentAnimationFinished() const
{
	return currentAnimation->isEnd;
}

Animation* Animator::FindAnimation(const std::string& name)
{
	for (auto it = animations.begin(); it != animations.end(); it++) {
		if (it->name == name) {
			return &*it;
		}
	}

	return nullptr;
}

void Animator::SwitchAnimation(Animation* animation) {
	// 改变精灵的纹理
	if (currentAnimation == animation) {
		return;
	}

	if (animation != nullptr) {
		if (animation->textureName != "") {
			sprite->setTexture(TextureCache::getTexture(animation->textureName));
		}

	}
	currentAnimation = animation;
	currentTime = sf::Time::Zero; // 重置时间
}


void Animator::Update(const sf::Time& dt) {
	// 現在沒有動畫，沒辦法update
	if (currentAnimation == nullptr) return;

	currentTime += dt;

	// 獲取當前frame
	float scaledTime = currentTime.asSeconds() / currentAnimation->durationTime.asSeconds();
	int numFrames = currentAnimation->frames.size();
	int currentFrame = static_cast<int>(scaledTime * numFrames);

	if (currentAnimation->isLooping) {
		currentFrame %= numFrames;
	}
	else if (currentFrame >= numFrames) {
		currentFrame = numFrames - 1;
		currentAnimation->isEnd = true; // 如果到最後
	}

	sprite->setTextureRect(currentAnimation->frames[currentFrame]);

}

void Animator::play(const string& name)
{
	auto orinAnimation = currentAnimation;
	int currentFrame = 0;
	int numFrames = currentAnimation->frames.size();
	float scaledTime = 0;

	currentAnimation = FindAnimation(name);

	// 如果動畫沒辦法播放
	if (currentAnimation == nullptr) return;

	sf::Time time = sf::seconds(0);
	sf::Clock clock;

	while (currentFrame < numFrames) {
		sprite->setTextureRect(currentAnimation->frames[currentFrame]);
		time += clock.restart();
		scaledTime = time.asSeconds() / currentAnimation->durationTime.asSeconds();
		currentFrame = static_cast<int>(scaledTime * numFrames);
	}
	
}



