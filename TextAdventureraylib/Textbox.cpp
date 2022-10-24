#include "Textbox.h"
#include <math.h>

void Textbox::init()
{
	arrow = LoadTexture("images/arrow.png");
	font = LoadFont("font/RobotoSlab-Black.ttf");
}


void Textbox::resetText()
{
	if (finished)
	{
		currentLetter = 0;
		currentText = "";
		finished = false;
	}
	else
	{
		currentLetter = 0;
		currentText = "";
		finished = true;
		skipText = true;
	}
}

void Textbox::setText(const std::string& text)
{
	currentText = text;
}

bool Textbox::isFinished()
{
	return finished;
}

void Textbox::updateText(const std::string& text, bool skipAnimation)
{
	
	

	if (skipText)
	{
		currentText = text;
		currentLetter = text.size() ;
		finished = true;
		justFinished = true;
		skipText = false;
	}
	
	if (texttimer <= 0)
	{
		if (currentLetter < text.size())
		{
			currentText += text[currentLetter];
			finished = false;
		}
		else
		{
			finished = true;
		}
		texttimer = 3;
		currentLetter++;
	}

	texttimer--;

	skipText = skipAnimation;

}

void Textbox::setLastText(bool value)
{
	lastText = value;
}

void Textbox::render()
{

	position = Vector2{ 20.f,20.f };
	dimension = Vector2{ (float)GetScreenWidth() - 2*position.x,(float)GetScreenHeight() / (float)3.0 };
	
	
	DrawRectangleRec(Rectangle{ position.x, position.y, dimension.x, dimension.y }, Color{ 29,22,60,255 });
	DrawRectangleLinesEx(Rectangle{ position.x, position.y, dimension.x, dimension.y },2, Color{ 82, 100, 165, 255 });
	if (finished && !lastText)
	{
		DrawTexture(arrow, GetScreenWidth() - 2 * position.x - 20.0, (GetScreenHeight() / (float)3.0 - 18.0) + 2 * sin(0.1 * timer), Color{ 255, 255, 255, 255 });
	}
	DrawTextEx(font, currentText.c_str(), Vector2{ 20 + 20,20 + 20 }, font.baseSize, 3, WHITE);
	

	timer++;
	
	

	justFinished = false;
}
