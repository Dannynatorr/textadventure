#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>

class Healthbar
{
public:

	Healthbar() { visible = false; currentX = -2 * width; }
	void update();
	void render();
	void setHP(float hp) { currentHP = hp; };
	void setMaxHP(float hp) { maxHP = hp; };
	void addHealth(float health);
	void removeHealth(float health);
	float getCurrentHP() { return currentHP; };
	float getMaxHP() { return maxHP; };
	void setPosition(int xx, int yy, int w, int h) { x = xx; y = yy; width = w; height = h; }
	void setColor(const Color& front, const Color& back) { colorBack = back; colorFront = front; };
	void setName(const std::string& n) { name = n; };

	Color colorFront = GREEN;
	Color colorBack = RED;

	void setVisible(bool v) { visible = v; };

private:

	int currentX = 0;
	int x = 25;
	int y = 270;
	int width = 300;
	int height = 50;



	bool visible = false;
	float maxHP = 1;
	float currentHP = 1;
	float redBoxWidth = 0;
	float greenBoxWidth = 0;

	std::string name = "Player";
	

	float t = 0;
	
};

