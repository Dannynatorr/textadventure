#pragma once

#include <iostream>
#include <raylib.h>
#include <json/json.h>


enum class Stats
{
	ATK,
	DEF,
	HP,
	MONEY
};

enum class Characters {
	BOB,
	JESUS
};


class Player

{
public:
	void init(const Json::Value& data);
	void setPlayer(Characters c);
	int getStat(Stats s);
	void setStat(Stats s, int value);
	void render();
	void update();
	void setVisible(bool v) { visible = v; };
	std::string getName() { return name; };

	void print()
	{
		std::cout << "name: " << name << "\n";
		std::cout << "description: " << description << "\n";
		std::cout << "atk: " << atk << "\n";
		std::cout << "def: " << def << "\n";
		std::cout << "hp: " << hp << "\n";
	}

private:

	bool visible = false;

	std::string description = "";
	Json::Value playerData;
	std::string name;
	int atk = 0;
	int def = 0;
	int hp = 1;
	int maxHP = 1;
	int money = 0;

};