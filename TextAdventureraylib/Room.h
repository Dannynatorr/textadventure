#pragma once

#include "Enemy.h"

enum class RoomType
{
	EmptyRoom,
	Shop,
	Enemy,
	Exit,
	size
};


class Room
{

public:
	Room(){};

	void setLeft(Room* r) { left = r; };
	void setRight(Room* r) { right = r; };
	void setUp(Room* r) { up = r; };
	void setDown(Room* r) { down = r; };

	Room* getLeft() { return left; };
	Room* getRight() { return right; };
	Room* getUp() { return up; };
	Room* getDown() { return down; };

	void render();
	void update();

	RoomType getType() { return type; };
	void setType(RoomType t) { type = t; };

	void setPosition(Vector2 v) { position = v; };
	Vector2 getPosition() { return position; };

	bool operator==(const Room& r)
	{
		return position.x == r.position.x && position.y == r.position.y;
	};

	void setVisible(bool v) { visible = v; };
	void setEntered(bool e) { entered = e; };
	bool isVisible() { return visible; };
	bool isEntered() { return entered; };
	 
	void showEnemy(bool show);

	void show(bool show);
	bool isShowing();

	Enemy* getEnemy() { return enemy; };
	void setEnemy(Enemy* e) { enemy = e; };
	void clearRoom() { if (enemy != nullptr) { delete enemy; } };

private:

	bool visible = false;
	bool entered = false;

	bool showing = false;

	RoomType type = RoomType::EmptyRoom;

	Enemy* enemy = NULL;
	

	Vector2 position;
	Room* left;
	Room* right;
	Room* up;
	Room* down;


};

