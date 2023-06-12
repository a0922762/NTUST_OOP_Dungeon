/*****************************************************************//**
 * File: Astar.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: The astar algorithm, can find the short road 
 *********************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Common.h"

using namespace std;

struct Node {
    int x;
    int y;
    double g;
    double h;
    double f;
    Node* parent;

    Node(int x, int y, double g, double h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
};

class AStar {
private:
    vector<vector<bool>> obstacleMap;
    vector<Node*> openList;
    vector<Node*> closedList;
    int width;
    int height;
    int startX;
    int startY;
    int goalX;
    int goalY;

private:
    double calculateHeuristic(int x, int y);

public:
    AStar(vector<vector<bool>> obstacleMap, int startX, int startY, int goalX, int goalY);

    vector<sf::Vector2i> getPath();
};