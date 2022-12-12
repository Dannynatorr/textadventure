#pragma once

#include <raylib.h>
#include "Grid.h"

class Game
{
	
public:

	void processInput();
	void update();
	void render();

	void run();

	void pause() { paused = !paused; };

private:


	int iter = 5;
	int noiseVal = 50;

	int refreshTime = 5;
	int timer = refreshTime;
	bool paused = false;

	int cellSize = 8;
	Grid grid;

	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
	

};

