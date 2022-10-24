#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <random>
#include "Room.h"
#include "json/json.h"

class Map
{

public:


	void loadEnemyData(const Json::Value& data) {if(!enemyData) enemyData = data; };
	void render();
	void update();
	void generateRooms();
	void generate(Room* r, Vector2 position);
	void setCurrentRoom(Room* r) { currentRoom = r; };
	Room* getCurrentRoom() { return currentRoom; };
	void setVisible(bool visible) { isVisible = visible; };
	void clearMap();

	void nextFloor() { floor++; };
	void setFloor(int f) { floor = f; };
	int getFloorNumber() { return floor; };

private:
	

	Json::Value enemyData;

	bool isVisible = false;
	inline static int roomsGenerated;
	Room* currentRoom;
	int rows = 19;
	int cols = 19;
	int numberOfRooms = 40;
	int enemyRooms = 7;
	std::vector<std::vector<Room*>> rooms;
	std::vector<Room*> roomList;


	int floor = 0;

	int width = 250 / rows;
	int height = 250 / cols;
	int x = 800;
	int y = 270;
	int space = 2;

	float t = 0;
	

	



};