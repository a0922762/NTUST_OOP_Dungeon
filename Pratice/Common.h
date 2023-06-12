#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "Config.h"
#include "Position.h"

constexpr int BLOCK_SIZE = 50;
constexpr int BLOCK_IMAGE_SIZE = 16;
constexpr int WINDOW_SIZE = 800;
constexpr int IMAGE_SIZE = 16;


enum class BLOCK_TYPE {
	EMPTY,
	WALL,
	ROAD,
	CORRIDOR,
	UP_STARIRS,
	DOWN_STARIRS,
	DOOR,
};

enum class DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


std::vector<sf::Vector2i> reservoirSampling(const std::vector<sf::Vector2i>& data, int k);

// Intent: Find the shortest path from start to end
// Pre: start and end are valid positions in the map
// Post: return a vector of positions from start to end
double getDistance(sf::Vector2i from, sf::Vector2i to);

