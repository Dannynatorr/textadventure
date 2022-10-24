#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "Healthbar.h"
#include "json/json.h"

enum class EnemyType
{
	SLIME,
	BAT,
	DRAGON,
	NUMBEROFENEMYTYPES
};

enum class EnemyStats
{
	HP,
	DEF,
	ATK,
	MONEY
};

class Enemy
{
public:

	Enemy(EnemyType e,const Json::Value& data) { createEnemy(e,data); };

	//void loadData(const Json::Value& data) ;
	void createEnemy(EnemyType e, const Json::Value& data);

	int getStat(EnemyStats s);
	void setStat(EnemyStats stat, int value);
	void update();
	void render();
	void showHealthBar(bool show);

private:

	Json::Value enemyData;
	Healthbar enemyHealthBar;
	int maxHP;
	int currentHP;
	int atk;
	int def;
	int moneyForDefeating;

	bool visible;

};

