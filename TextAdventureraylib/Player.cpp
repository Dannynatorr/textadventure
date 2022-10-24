#include "Player.h"
#include <raymath.h>

void Player::init(const Json::Value& data)
{

	playerData = data;

}



int Player::getStat(Stats s)
{
	switch (s)
	{
	case Stats::ATK:
		return atk;
	case Stats::DEF:
		return def;
	case Stats::HP:
		return hp;
	case Stats::MONEY:
		return money;
	}
}


void Player::setStat(Stats s,int value)
{
	switch (s)
	{
	case Stats::ATK:
		atk = value; break;
	case Stats::DEF:
		def = value; break;
	case Stats::HP:
		hp = value; break;
	case Stats::MONEY:
		money = value; break;
	}
}

void Player::setPlayer(Characters c)
{

	Json::Value character;

	switch(c)
	{
	case Characters::BOB:
		name = "Bob";
		character = playerData["bob"];
		
		break;

	case Characters::JESUS:
		name = "Jesus";
		character = playerData["jesus"];
		break;
	}

	atk = character["atk"].asInt();
	def = character["def"].asInt();
	maxHP = character["hp"].asInt();
	hp = character["hp"].asInt();
	money = character["money"].asInt();
	description = character["description"].asCString();

	std::cout << money << std::endl;
}

void Player::update()
{
	hp = Clamp(hp, 0, maxHP);
}

void Player::render()
{
	if (visible)
	{
		std::string moneyLabel{ "$ : " + std::to_string(money) };
		std::string atkLabel{ "Atk : " + std::to_string(atk) };
		std::string defLabel{ "Def : " + std::to_string(def) };

		DrawText(moneyLabel.c_str(), 0, 0, 20, WHITE);
		DrawText(atkLabel.c_str(), 100, 0, 20, WHITE);
		DrawText(defLabel.c_str(), 200, 0, 20, WHITE);

	}
	
}
