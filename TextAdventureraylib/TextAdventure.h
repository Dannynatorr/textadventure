#pragma once

#include "Textbox.h"
#include "Choices.h"
#include "Map.h"
#include "Player.h"
#include "Healthbar.h"

#include <raylib.h>
#include <json/json.h>
#include <fstream>
#include <iostream>


class TextAdventure
{
public:

	TextAdventure();
	virtual ~TextAdventure();

	void run();
	void processInput();
	void update();
	void render();
	void setDialogue( Json::Value d) ;
	void showShop();
	void showEnemy();
	void showExit();

	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;

private:

	Textbox textbox;

	Choices choices;
	
	Map map;

	Player player;
	Healthbar healthBar;

	std::string c = "";
	
	
	Json::Value jsonData = {0};

	Json::Value dialogue;
	Json::Value lastDialogue;
	int textNumber = 0;

	bool quitting;
	bool fleeing = false;
	float absorbing = 1;
	float shielding = 1;

	
	

};

