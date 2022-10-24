#include "Enemy.h"

#include <iostream>


void Enemy::createEnemy(EnemyType e, const Json::Value& data)
{
	enemyData = data;

	Json::Value enemy = enemyData;

	switch (e)
	{
	case EnemyType::SLIME:
		enemy = enemyData["slime"];
		enemyHealthBar.setColor(Color{ 129,199,30,255 }, RED);
		break;
	case EnemyType::BAT:
		enemy = enemyData["bat"];
		enemyHealthBar.setColor(Color{ 5,64,88,255 }, RED);
		break;
	case EnemyType::DRAGON:
		enemy = enemyData["dragon"];
		enemyHealthBar.setColor(Color{ 159,200,88,255 }, RED);
		break;
	}

	atk = enemy["atk"].asInt();
	def = enemy["def"].asInt();
	maxHP = enemy["hp"].asInt();
	currentHP = maxHP;
	moneyForDefeating = enemy["money"].asInt();

	enemyHealthBar.setMaxHP(maxHP);
	enemyHealthBar.setHP(maxHP);
	enemyHealthBar.setPosition(600, 270, 300, 50);
	enemyHealthBar.setName(std::string{ enemy["name"].asCString()});
	
}

void Enemy::setStat(EnemyStats s, int v)
{
	switch (s)
	{
	case EnemyStats::ATK:
		atk = v;
		break;
	case EnemyStats::DEF:
		def = v;
		break;
	case EnemyStats::HP:
		currentHP = v;
		break;
	case EnemyStats::MONEY:
		moneyForDefeating = v;
		break;
	}
}

int Enemy::getStat(EnemyStats s)
{
	switch (s)
	{
	case EnemyStats::ATK:
		return atk;
	case EnemyStats::DEF:
		return def;
	case EnemyStats::HP:
		return currentHP;
	case EnemyStats::MONEY:
		return moneyForDefeating;
	}
}


void Enemy::showHealthBar(bool show)
{
	

		enemyHealthBar.setVisible(show);

	
}

void Enemy::update()
{
	currentHP = Clamp(currentHP, 0, maxHP);
	enemyHealthBar.setHP(currentHP);
	enemyHealthBar.update();
}

void Enemy::render()
{


	
	enemyHealthBar.render();
}