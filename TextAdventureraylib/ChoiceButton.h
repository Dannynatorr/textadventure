#pragma once

#include <raylib.h>
#include <string>

class ChoiceButton
{
public:

	ChoiceButton();
	ChoiceButton(const std::string& label, const std::string& id);

	void render();
	void setPos(Vector2 pos);
	void setSize(Vector2 dim);
	bool isPressed();
	bool isHovered();
	std::string getID() { return id; };
	

private:
	std::string label;
	std::string id;
	Vector2 position;
	Vector2 dimension;
	

	bool isHover;
};