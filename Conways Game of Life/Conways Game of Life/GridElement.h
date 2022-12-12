#pragma once

#include <raylib.h>
#include <raymath.h>
#include <random>


class GridElement
{

public:


	void init();
	void switchState() { alive = !alive; };
	void setAlive(bool state) { alive = state; };
	bool isAlive() const { return alive; };
	void update();
	void queueSwitch() { shouldSwitch = true; }
	Color getColor() { return color; };
	void setColor(const Color& c) { color = c; };
	

private:

	bool shouldSwitch = false;
	bool alive = false;
	Color color;

};

