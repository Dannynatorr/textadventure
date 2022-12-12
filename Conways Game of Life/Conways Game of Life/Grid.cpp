#include "Grid.h"

void Grid::init()
{

	rows /= cellWidth;
	cols /= cellHeight;
	
	grid.clear();
	grid.resize(rows, std::vector<GridElement*>(cols, NULL));

	for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			GridElement* g = new GridElement;

			

			grid[i][j] = g;

			
		}
	}

	
	
	//caveGen(noiseVal, iter);

}

void Grid::update()
{

	//clearGrid();

	//noise(1);
	
	
	
	conway();
	
	
	//caveGen(noiseVal, iter);

	setColors();
	//caveGen(50, 6);
	
	//caveGen(60, 2);
	

	
	



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			
			grid[i][j]->update();
		}
	}

}

void Grid::render()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j]->isAlive())
			{
				

				
				DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight, grid[i][j]->getColor());
				
				
			}
			else
			{
				DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight, Color{ 57,44,122,255 });
			}
			
		}
	}
	

}

void Grid::switchGridElementState(int x, int y)
{
	if (x < rows && x >= 0 && y < cols && y >= 0)
	{
		grid[x][y]->switchState();
	}
	
}

void Grid::conway()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//counting neighbours 

			int neighbours = 0;


			for (int x = i - 1; x <= i + 1; x++)
			{
				for (int y = j - 1; y <= j + 1; y++)
				{
					if (x >= 0 && x < rows && y >= 0 && y < cols)
					{
						if (grid[x][y]->isAlive() )
						{
							if (!(x == i && y == j))
							{
								neighbours++;
							}
							
							
						}
					}
				}
			}

			

			


			if (grid[i][j]->isAlive())
			{
				if (neighbours < 2 || neighbours > 3)
				{
					grid[i][j]->queueSwitch();
				}
			}
			else
			{
				if (neighbours == 3)
				{
					grid[i][j]->queueSwitch();
				}
			}

		}
	}
}

void Grid::noise(int threshhold)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int rnd = rand() % 100;

			if (rnd < threshhold)
			{
				grid[i][j]->setAlive(true);
			}
			
		}
	}
}

void Grid::caveGen(int noiseDensity, int iterations)
{
	noise(noiseDensity);

	for (int i = 0; i < iterations; i++)
	{
		std::vector<std::vector<GridElement*>> tmpgrid;

		tmpgrid.clear();
		tmpgrid.resize(rows, std::vector<GridElement*>(cols, NULL));

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				GridElement* g = new GridElement;

				if (grid[i][j]->isAlive())
				{
					g->setAlive(true);
				}

				tmpgrid[i][j] = g;
			}
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{


				int neighbours = 0;


				for (int x = i - 1; x <= i + 1; x++)
				{
					for (int y = j - 1; y <= j + 1; y++)
					{
						if (x >= 0 && x < rows && y >= 0 && y < cols)
						{
							if (grid[x][y]->isAlive())
							{
								if (!(x == i && y == j))
								{
									neighbours++;
								}


							}
						}
					}
				}


				if (neighbours > 4)
				{
					tmpgrid[i][j]->setAlive(true);
				}
				else
				{
					tmpgrid[i][j]->setAlive(false);
				}


			}
		}




		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				delete grid[i][j];
				grid[i][j] = tmpgrid[i][j];
				
			}
		}
		

		


	}

}

void Grid::clearGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			grid[i][j]->setAlive(false);
		}
	}
}

void Grid::setColors()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//counting neighbours 

			int neighbours = 0;


			for (int x = i - 1; x <= i + 1; x++)
			{
				for (int y = j - 1; y <= j + 1; y++)
				{
					if (x >= 0 && x < rows && y >= 0 && y < cols)
					{
						if (grid[x][y]->isAlive())
						{
							if (!(x == i && y == j))
							{
								neighbours++;
							}


						}
					}
				}
			}

			if (neighbours <= 8)
			{
				grid[i][j]->setColor(Color{ 223,178,50,255 });
			}

			if (neighbours <= 6)
			{
				grid[i][j]->setColor(Color{ 22,190,100,255 });
			}

			if (neighbours <= 2)
			{
				grid[i][j]->setColor(Color{ 173,69,200,255 });
			}

			

			

			
		}
	}
}

void Grid::reset()
{
	clearGrid();

	caveGen(noiseVal, iter);


}

