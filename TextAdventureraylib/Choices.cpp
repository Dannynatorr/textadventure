#include "Choices.h"
#include <iostream>
#include <string>

void Choices::presentChoices(const Json::Value& choices)
{


	

	if (!isVisible)
	{
		for (ChoiceButton* b : buttons)
		{
			delete b;
		}
		buttons.clear();

		position.x =  (GetScreenWidth() - choices.size() * 220)*0.5;
		dimension.x = choices.size() * 220;

		for (int i = 0; i < choices.size(); i++)
		{
			ChoiceButton* b = new ChoiceButton(choices[i][0].asCString(), choices[i][1].asCString());
			b->setPos(Vector2{ position.x + (i * (200 + 20)) ,position.y });
			b->setSize(Vector2{ 200,100 });
			buttons.push_back(b);
		}
		setVisible(true);

		
	}
	
}

void Choices::setVisible(bool visible)
{
	isVisible = visible;
}

void Choices::init()
{
	position = { (float)0 + 20,(float)(GetScreenHeight() / 3.0) * 2.5f };
	dimension = { GetScreenWidth() - 2 * position.x, 100 };

	std::cout << position.x << " " << position.y << std::endl;

}


std::string Choices::getIDfromPressedButton()
{
	for (ChoiceButton* b : buttons)
	{
		if (b->isPressed() && isVisible)
		{
			return b->getID();
		}
	}
	return "-1";
}

std::string Choices::getIDfromHoveredButton()
{
	for (ChoiceButton* b : buttons)
	{
		
		if (b->isHovered() && isVisible)
		{
			return b->getID();
		}
	}
	return "-1";
}

void Choices::update()
{

	
	
	position.y = Lerp(GetScreenHeight()+dimension.y + 10, (float)(GetScreenHeight() / 3.0) * 2.5f, t * t * (3 - 2 * t));

	if (isVisible)
	{
		t += 0.03;
	}
	else
	{
		t -= 0.03;
	}

	t = Clamp(t, 0, 1);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->setPos(Vector2{ position.x + (i * (200 + 20)) ,position.y });
	}
}

void Choices::render()
{
	
	
	
	//DrawRectangleLines(position.x, position.y, dimension.x, dimension.y, GREEN);

	for (ChoiceButton* b : buttons)
	{
		b->render();
	}
	
}