#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <json/json.h>

#include "ChoiceButton.h"


class Choices
{
public:

	void render();
	void update();
	void presentChoices(const Json::Value& choices);
	void setVisible(bool visible);
	void init();
	std::string getIDfromPressedButton();
	std::string getIDfromHoveredButton();
	
private:

	Vector2 position;
	Vector2 dimension;


	bool isVisible = false;
	std::vector<ChoiceButton*> buttons;

	float t;
};