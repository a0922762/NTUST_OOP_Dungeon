#pragma once

#include <random>

class RandomNum {
public:
    RandomNum();

    // 生成介於min和max之間（包括min和max）的亂數整數
    int getRandomInt(int min, int max);
    int getRandomInt(int max);

    // 生成介於min和max之間（包括min，不包括max）的亂數浮點數
    float getRandomFloat(float min, float max);

    bool getRandomBool(double probability = 0.5);
private:
    std::mt19937 generator;  // 亂數生成器
};