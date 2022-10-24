#pragma once

#include <raylib.h>
#include <string>

class Textbox
{

public:

	Textbox() {
		
	}

	void init();
	void render();
	void updateText(const std::string& text ,bool skipAnimation);
	void resetText();
	void setText(const std::string& text);
	bool isFinished();
	bool isjustFinished(){ return justFinished; };
	bool isSkiped() { return skipText; };
	void setLastText(bool value);
	bool isLastText() { return lastText; };

	int getCurrentTextLength()
	{
		return currentText.size();
	}

private:

	bool lastText = false;
	std::string currentText = "";
	bool skipText = false;
	bool finished = false;
	bool justFinished = false;
	Texture2D arrow;
	int timer = 0;
	int texttimer = 0;
	int currentLetter = 0;
	Font font;

	Vector2 position{20.f,20.f};
	Vector2 dimension{ (float)GetScreenWidth(),(float)GetScreenHeight() / (float)3.0};



};

