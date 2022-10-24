#include "ChoiceButton.h"
#include <iostream>


ChoiceButton::ChoiceButton()
{
	position = { 1000,500 };
	dimension = { 200,100 };
	label = "testing";
	
}

ChoiceButton::ChoiceButton(const std::string& label,const std::string& id)
{
	this->label = label;
	this->id = id;

	isHover = false;


	//std::cout << this->id << std::endl;
}

void ChoiceButton::setPos(Vector2 pos)
{
	position = pos;
}
void ChoiceButton::setSize(Vector2 dim)
{
	dimension = dim;
}


bool ChoiceButton::isPressed()
{
	Vector2 mousePos = GetMousePosition();

	
	return (mousePos.x > position.x && mousePos.x <= position.x + dimension.x && mousePos.y > position.y && mousePos.y <= position.y + dimension.y);
}

bool ChoiceButton::isHovered()
{
	
	return isHover;

}


void ChoiceButton::render()
{
	Vector2 mousePos = GetMousePosition();

	if ((mousePos.x <= position.x + dimension.x && mousePos.x > position.x) && mousePos.y <= position.y + dimension.y && mousePos.y > position.y)
	{
		isHover = true;
		
	}
	else
	{
		isHover = false;
	}

	

	if (isHover)
	{
		int textWidth = MeasureText(label.c_str(), 20);
		DrawRectangle(position.x, position.y, dimension.x, dimension.y, BLACK);
		DrawRectangleLines(position.x, position.y, dimension.x, dimension.y, BLUE);
		DrawText(label.c_str(), position.x + 0.5 * dimension.x - 0.5 * textWidth, position.y + 0.5 * dimension.y - 10 , 20, WHITE);
	}
	else
	{
		int textWidth = MeasureText(label.c_str(), 20);
		DrawRectangle(position.x, position.y, dimension.x, dimension.y, WHITE);
		DrawRectangleLines(position.x, position.y, dimension.x, dimension.y, BLUE);
		DrawText(label.c_str(), position.x + 0.5 * dimension.x - 0.5 * textWidth, position.y + 0.5 * dimension.y - 10 , 20, BLACK);
	}
	
	
}