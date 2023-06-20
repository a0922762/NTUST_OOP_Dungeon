#include "Board.h"
#include <cmath>

// Intent: 根據不同的樓層產生不同的地圖
Board::Board(FloorInfo floor) : width(floor.width), height(floor.height)
{
	RandomDungeon d(floor.width, floor.height);

	d.generate(30);
	d.print();

	loadDungeon(d);

}

Board::Board(int width, int height) : width(width), height(height)
{
	
}

// Intent: load be created random dungeon to board
// Pre: RandomDungeon d has been created
// Post: board has been loaded
void Board::loadDungeon(RandomDungeon d) {
	allBoard.clear();
	allBoard.resize(width);

	for (int i = 0; i < width; i++) {
		allBoard[i].resize(height);
		for (int j = 0; j < height; j++) {
			switch (d.getTile(i, j)) {
			case '.':
				allBoard[i][j] = Block(BLOCK_TYPE::EMPTY);
				break;
			case ' ': case ',':
				allBoard[i][j] = Block(BLOCK_TYPE::ROAD);
				break;
			case '#':
				allBoard[i][j] = Block(BLOCK_TYPE::WALL);
				break;
			case '+': case '-':
				allBoard[i][j] = Block(BLOCK_TYPE::DOOR);
				break;
			case '<':
				allBoard[i][j] = Block(BLOCK_TYPE::ROAD);
				downStairPos = sf::Vector2i(i, j);
				break;
			case '>':
				allBoard[i][j] = Block(BLOCK_TYPE::ROAD);
				upStairPos = sf::Vector2i(i, j);
				break;
			default:
				allBoard[i][j] = Block(BLOCK_TYPE::EMPTY);
				break;
			}
			allBoard[i][j].setPosition(i * float(BLOCK_SIZE), j * float(BLOCK_SIZE));
		}
	}
}

void Board::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			window->draw(allBoard[i][j]);
		}
	}
}


// Inten: check if the block at (x, y) can be walked
// Post: return true if the block at (x, y) can be walked, false otherwise
bool Board::canGo(const Position& pos) const
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= this->height || pos.x >= this->width || allBoard[pos.x][pos.y].canWalk() == false) {
		return false;
	}
	return true;
}

bool Board::isRoad(const Position& pos) const
{
	if (allBoard[pos.x][pos.y].getType() == BLOCK_TYPE::ROAD) {
		return true;
	}
	return false;
}

Position Board::getDownStairPos() const
{
	return downStairPos;
}

Position Board::getUpStairPos() const
{
	return upStairPos;
}

int Board::getHeight() const
{
	return height;
}

int Board::getWidth() const
{
	return width;
}

std::vector<sf::Vector2i> Board::getCanPlaceBlock() const
{
	std::vector<sf::Vector2i> retVec;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (allBoard[j][i].getType() == BLOCK_TYPE::ROAD || allBoard[j][i].getType() == BLOCK_TYPE::DOOR) {

				retVec.push_back({ j, i });
			}
		}
	}

	return retVec;
}

// Intent: destructor, delete all block in board
// Post: all block in board has been deleted
Board::~Board() {
}

ostream& operator<<(ostream& os, const Board& board)
{
	for (int i = 0; i < board.height; i++) {
		for (int j = 0; j < board.width; j++) {
			if (board.allBoard[j][i].getType() == BLOCK_TYPE::EMPTY) {
				os << "." << " ";
			}
			else if (board.allBoard[j][i].getType() == BLOCK_TYPE::WALL) {
				os << "#" << " ";
			}
			else if (board.allBoard[j][i].getType() == BLOCK_TYPE::ROAD) {
				os << "," << " ";
			}
			else if (board.allBoard[j][i].getType() == BLOCK_TYPE::DOOR) {
				os << "+" << " ";
			}
		}
		os << endl;
	}
	return os;
}
