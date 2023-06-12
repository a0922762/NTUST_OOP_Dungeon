#include "RandomDungeon.h"

bool RandomDungeon::createFeature()

{
	for (int i = 0; i < 1000; ++i)
	{
		if (_exits.empty())
			break;

		// choose a random side of a random room or corridor
		int r = randomInt(_exits.size());
		int x = randomInt(_exits[r].x, _exits[r].x + _exits[r].width - 1);
		int y = randomInt(_exits[r].y, _exits[r].y + _exits[r].height - 1);

		// north, south, west, east
		for (int j = 0; j < DirectionCount; ++j)
		{
			if (createFeature(x, y, static_cast<Direction>(j)))
			{
				_exits.erase(_exits.begin() + r);
				return true;
			}
		}
	}

	return false;
}

bool RandomDungeon::createFeature(int x, int y, Direction dir)

{
	static const int roomChance = 50; // corridorChance = 100 - roomChance

	int dx = 0;
	int dy = 0;

	if (dir == North)
		dy = 1;
	else if (dir == South)
		dy = -1;
	else if (dir == West)
		dx = 1;
	else if (dir == East)
		dx = -1;

	if (getTile(x + dx, y + dy) != Floor && getTile(x + dx, y + dy) != Corridor)
		return false;

	if (randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			setTile(x, y, ClosedDoor);

			return true;
		}
	}

	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (getTile(x + dx, y + dy) == Floor)
				setTile(x, y, ClosedDoor);
			else // don't place a door between corridors
				setTile(x, y, Corridor);

			return true;
		}
	}

	return false;
}

bool RandomDungeon::makeRoom(int x, int y, Direction dir, bool firstRoom)

{
	static const int minRoomSize = 3;
	static const int maxRoomSize = 6;

	Rect room;
	room.width = randomInt(minRoomSize, maxRoomSize);
	room.height = randomInt(minRoomSize, maxRoomSize);

	if (dir == North)
	{
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}

	else if (dir == South)
	{
		room.x = x - room.width / 2;
		room.y = y + 1;
	}

	else if (dir == West)
	{
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}

	else if (dir == East)
	{
		room.x = x + 1;
		room.y = y - room.height / 2;
	}

	if (placeRect(room, Floor))
	{
		_rooms.emplace_back(room);

		if (dir != South || firstRoom) // north side
			_exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
		if (dir != North || firstRoom) // south side
			_exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
		if (dir != East || firstRoom) // west side
			_exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
		if (dir != West || firstRoom) // east side
			_exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

		return true;
	}

	return false;
}

bool RandomDungeon::makeCorridor(int x, int y, Direction dir)

{
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (randomBool()) // horizontal corridor
	{
		corridor.width = randomInt(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North)
		{
			corridor.y = y - 1;

			if (randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == South)
		{
			corridor.y = y + 1;

			if (randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == West)
			corridor.x = x - corridor.width;

		else if (dir == East)
			corridor.x = x + 1;
	}

	else // vertical corridor
	{
		corridor.width = 1;
		corridor.height = randomInt(minCorridorLength, maxCorridorLength);

		if (dir == North)
			corridor.y = y - corridor.height;

		else if (dir == South)
			corridor.y = y + 1;

		else if (dir == West)
		{
			corridor.x = x - 1;

			if (randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}

		else if (dir == East)
		{
			corridor.x = x + 1;

			if (randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}
	}

	if (placeRect(corridor, Corridor))
	{
		if (dir != South && corridor.width != 1) // north side
			_exits.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
		if (dir != North && corridor.width != 1) // south side
			_exits.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
		if (dir != East && corridor.height != 1) // west side
			_exits.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
		if (dir != West && corridor.height != 1) // east side
			_exits.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

		return true;
	}

	return false;
}

bool RandomDungeon::placeRect(const Rect& rect, char tile)

{
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > _width - 1 || rect.y + rect.height > _height - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (getTile(x, y) != Unused)
				return false; // the area already used
		}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				setTile(x, y, Wall);
			else
				setTile(x, y, tile);
		}

	return true;
}
bool RandomDungeon::placeObject(char tile)

{
	if (_rooms.empty())
		return false;

	int r = randomInt(_rooms.size()); // choose a random room
	int x = randomInt(_rooms[r].x + 1, _rooms[r].x + _rooms[r].width - 2);
	int y = randomInt(_rooms[r].y + 1, _rooms[r].y + _rooms[r].height - 2);

	if (getTile(x, y) == Floor)
	{
		setTile(x, y, tile);

		// place one object in one room (optional)
		_rooms.erase(_rooms.begin() + r);

		return true;
	}

	return false;
}

std::istream& operator>>(std::istream& in, RandomDungeon& rd)
{

	for (int y = 0; y < rd._height; y++) {
		for (int x = 0; x < rd._width; x++) {
			char temp;

			in >> temp;

			std::cout << temp;

			rd.setTile(x, y, temp);
		}
		std::cout << std::endl;
	}

	return in;
}
