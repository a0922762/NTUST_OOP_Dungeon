#include "Common.h"

// Intent: choose k point from data
// Pre: data has been created
// Post: return k point from data
std::vector<sf::Vector2i> reservoirSampling(const std::vector<sf::Vector2i>& data, int k) {
    std::vector<sf::Vector2i> reservoir(k);
    size_t n = data.size();

    // 将前 k 个元素放入鱼塘
    for (int i = 0; i < k; i++) {
        reservoir[i] = data[i];
    }


    for (int i = k; i < n; ++i)
    {
        // 以 k/i 的概率选择是否替换鱼塘中的元素
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double r = distribution(generator);

        if (r < (double)k / (double)(i + 1))
        {
            std::uniform_int_distribution<int> indexDistribution(0, k - 1);
            int j = indexDistribution(generator);
            reservoir[j] = data[i];
        }
    }

    return reservoir;

}

// Intent: Calulate the distance between two point
// Post: return the distance between two point
double getDistance(sf::Vector2i from, sf::Vector2i to) {
    return sqrt(pow(double(from.x - to.x), 2) + pow(double(from.y - to.y), 2));
}

