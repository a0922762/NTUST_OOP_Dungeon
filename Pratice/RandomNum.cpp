#include "RandomNum.h"

// Intent: Constructor
// Pre: None
// Post: generator is initialized with a random seed
RandomNum::RandomNum() {
    generator.seed(std::random_device()());
}

// Intent: generate a random integer between min and max
// Pre: generator is initialized
// Post: return a random integer between min and max
int RandomNum::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Intent: generate a random integer between 0 and max
// Pre: generator is initialized
// Post: return a random integer between 0 and max
int RandomNum::getRandomInt(int max) {
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(generator);
}

// Intent: generate a random float between min and max
// Pre: generator is initialized
// Post: return a random float between min and max
float RandomNum::getRandomFloat(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

bool RandomNum::getRandomBool(double probability)
{
    std::bernoulli_distribution distribution(probability);
	return distribution(generator);
}
