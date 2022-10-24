#include "Healthbar.h"
#include <string>


void Healthbar::update()
{

	currentX = Lerp(-(width+10), x, t*t*(3-2*t));

	if (visible)
	{
		t += 0.02;
	}
	else
	{
		t -= 0.02;
	}

	t = Clamp(t, 0, 1);

	if (t == 1)
	{
		greenBoxWidth = Lerp(currentHP, greenBoxWidth, 0.9);
		redBoxWidth = Lerp(currentHP, redBoxWidth, 0.95);
	}
	

	currentHP = Clamp(currentHP, 0, maxHP);
}

void Healthbar::addHealth(float health)
{
	if ((currentHP + health) > maxHP)
	{
		currentHP = maxHP;
	}
	else
	{
		currentHP += health;
	}
		
}

void Healthbar::removeHealth(float health)
{ 
	if ((currentHP - health) <= 0)
	{
		currentHP = 0;
	}
	else
	{
		currentHP -= health;
	}
};

void Healthbar::render()
{

	
	
		

		DrawRectangle(currentX, y, width, height, BLACK);
		if (visible)
		{
			DrawRectangle(currentX, y, (redBoxWidth / maxHP) * width, height,colorBack );
			DrawRectangle(currentX, y, (greenBoxWidth / maxHP) * width, height, colorFront);

			for (int i = 0; i < ((int)maxHP / 100); i++)
			{
				int x = currentX + i * width / (maxHP / 100);

				DrawLine(x, y, x, y + height, Color{0,133,23,100});
				
			}


			std::string label = "Leben: " + std::to_string((int)currentHP) + "/" + std::to_string((int)maxHP);
			DrawText(label.c_str(), currentX + 0.5 * width - 0.5 * MeasureText(label.c_str(), 20), y + 0.5 * height - 10, 20, WHITE);
			DrawText(name.c_str(), currentX, y + height + 5, 20, YELLOW);

			
		}
		
		DrawRectangleLines(currentX, y, width, height, WHITE);
		
	
	
}
