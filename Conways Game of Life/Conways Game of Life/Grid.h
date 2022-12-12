#pragma once

#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <random>


#include "GridElement.h"

class Grid
{

public:

	void init();
	void update();
	void render();
	void switchGridElementState(int x, int y);

	void conway();
	void noise(int threshhold);
	void caveGen(int noiseDensity, int iterations);


	void clearGrid();

	void setNoiseVal(int n) { noiseVal = n; };
	void setIter(int i) { iter = i; };

	void setColors();

	void reset();


private:


	int iter = 5;
	int noiseVal = 50;

	int rows = 1280;
	int cols = 720;

	int cellWidth = 8;
	int cellHeight = 8;
	
	std::vector<std::vector<GridElement*>> grid;


};

