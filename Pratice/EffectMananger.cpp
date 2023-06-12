#include "EffectMananger.h"
#include "Creature.h"

std::vector<Effect> EffectMananger::effects;

void EffectMananger::addEffect(EFFECT_TYPE type, int count, int atk, Creature* target)
{
	Effect newEffect(type, target, count, atk);

	effects.push_back(newEffect);
}

void EffectMananger::update()
{
	for (auto i = effects.begin(); i != effects.end(); i++) {
		switch (i->type) {
		case FIRE:
			i->target->beDamage(i->atk + 10);
			i->atk -= 5;
			break;
		case BLEED:
			i->target->beDamage(i->atk + 5);
			break;

		}
		i->count--;
	}

	auto it = partition(effects.begin(), effects.end(), [](Effect& e) {return e.count > 0; });
	effects.erase(it, effects.end());
}

void EffectMananger::draw(sf::RenderWindow* window)
{
}

std::vector<Effect>& EffectMananger::getEffects()
{
	return effects;
}


