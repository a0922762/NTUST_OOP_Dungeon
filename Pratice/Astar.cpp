/*****************************************************************//**
 * File: Astar.cpp
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This is a implention of Astar
 *********************************************************************/
#include "Astar.h"

// Post: Consturct Astar with obstacleMap, start x y, goal x y
AStar::AStar(vector<vector<bool>> obstacleMap, int startX, int startY, int goalX, int goalY) 
    : obstacleMap(obstacleMap), startX(startX), startY(startY), goalX(goalX), goalY(goalY) 
{
    width = obstacleMap.size();
    height = obstacleMap[0].size();
}

// Post: return the path from start to goal
vector<sf::Vector2i> AStar::getPath()
{

    Node* startNode = new Node(startX, startY, 0.0, calculateHeuristic(startX, startY));
    openList.push_back(startNode);

    while (!openList.empty()) {
        // Find the node with the lowest f value in the open list
        Node* currentNode = openList[0];
        int currentIndex = 0;

        for (int i = 1; i < openList.size(); i++) {
            if (openList[i]->f < currentNode->f) {
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        // Remove the current node from the open list and add it to the closed list
        openList.erase(openList.begin() + currentIndex);
        closedList.push_back(currentNode);

        // Check if the current node is the goal node
        if (currentNode->x == goalX && currentNode->y == goalY) {
            // Path found, construct the path by following the parent pointers
            vector<sf::Vector2i> path;
            Node* node = currentNode;

            while (node != nullptr) {
                path.insert(path.begin(), sf::Vector2i(node->x, node->y));
                node = node->parent;
            }

            // Cleanup memory
            for (Node* n : openList) {
                delete n;
            }
            for (Node* n : closedList) {
                delete n;
            }

            return path;
        }

        // Generate neighboring nodes
        vector<pair<int, int>> neighbors = {
            {currentNode->x - 1, currentNode->y},
            {currentNode->x + 1, currentNode->y},
            {currentNode->x, currentNode->y - 1},
            {currentNode->x, currentNode->y + 1}
        };

        for (pair<int, int> neighbor : neighbors) {
            int neighborX = neighbor.first;
            int neighborY = neighbor.second;

            // Check if the neighbor is valid
            if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height && !obstacleMap[neighborX][neighborY]) {
                // Calculate the tentative g score for the neighbor
                double tentativeG = currentNode->g + 1.0;

                // Check if the neighbor is already in the closed list with a lower g score
                bool inClosedList = false;

                for (Node* n : closedList) {
                    if (n->x == neighborX && n->y == neighborY && tentativeG >= n->g) {
                        inClosedList = true;
                        break;
                    }
                }

                if (inClosedList) {
                    continue;
                }

                // Check if the neighbor is already in the open list
                bool inOpenList = false;
                int openIndex = -1;

                for (int i = 0; i < openList.size(); i++) {
                    if (openList[i]->x == neighborX && openList[i]->y == neighborY) {
                        inOpenList = true;
                        openIndex = i;
                        break;
                    }
                }

                if (inOpenList) {
                    Node* existingNode = openList[openIndex];

                    // Check if the tentative g score is lower than the current g score
                    if (tentativeG < existingNode->g) {
                        existingNode->g = tentativeG;
                        existingNode->f = existingNode->g + existingNode->h;
                        existingNode->parent = currentNode;
                    }
                }
                else {
                    // Add the neighbor to the open list
                    Node* neighborNode = new Node(neighborX, neighborY, tentativeG, calculateHeuristic(neighborX, neighborY), currentNode);
                    openList.push_back(neighborNode);
                }
            }
        }
    }

    // No path found
    std::cout << "No path found!" << endl;
    return vector<sf::Vector2i>();
}

// Post: return distance between two point x y and goal x y
double AStar::calculateHeuristic(int x, int y)
{
    return getDistance({ x, y }, { goalX, goalY });
}




