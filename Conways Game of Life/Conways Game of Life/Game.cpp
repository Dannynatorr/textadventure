#include "Game.h"

void Game::processInput()
{



	if (IsKeyPressed(KEY_R))
	{
		grid.reset();
		
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		pause();
	}


	if (IsKeyPressed(KEY_LEFT))
	{
		iter--;

	}

	if (IsKeyPressed(KEY_RIGHT))
	{
		iter++;
	}

	iter = Clamp(iter, 0, 10);
	grid.setIter(iter);

	if (IsKeyPressed(KEY_UP))
	{
		noiseVal++;
	}

	if (IsKeyPressed(KEY_DOWN))
	{
		noiseVal--;
	}
	noiseVal = Clamp(noiseVal, 0, 100);
	grid.setNoiseVal(noiseVal);

	if (paused)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 mousePos = GetMousePosition();
			int x = (WIDTH / cellSize) * (mousePos.x/WIDTH);
			int y = (HEIGHT / cellSize) * (mousePos.y / HEIGHT);;
			grid.switchGridElementState(x,y);
		}
	}





}

void Game::update()
{

	if (!paused)
	{
		if (timer <= 0)
		{
			grid.update();
			timer = refreshTime;
		}
		
		timer -= 1;
	}

}

void Game::render()
{
	BeginDrawing();

	ClearBackground(BLACK);
	grid.render();

	if (paused)
	{
		Vector2 mousePos = GetMousePosition();
		int x = (WIDTH / cellSize) * (mousePos.x / WIDTH);
		int y = (HEIGHT / cellSize) * (mousePos.y / HEIGHT);;
		DrawRectangleLines(x* cellSize, y* cellSize, cellSize, cellSize, Color{ 223,178,50,255 });
		
	}

	

	EndDrawing();
}

void Game::run()
{
	
	InitWindow(1280, 720, "Conways Game of Life");
	SetTargetFPS(60);

	srand(time(NULL));

	grid.init();

	

	while (!WindowShouldClose())
	{
		processInput();
		update();
		render();
	}


}
