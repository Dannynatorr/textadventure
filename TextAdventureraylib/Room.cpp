#include "Room.h"


void Room::show(bool s)
{
	showing = s;
}

bool Room::isShowing()
{
	return showing;
}

void Room::showEnemy(bool show)
{
	if (enemy)
	{
		enemy->showHealthBar(show);
	}
	
}


void Room::render()
{
	if (enemy != NULL)
	{
		enemy->render();
	}
}

void Room::update()
{
	if (enemy != NULL)
	{
		
		enemy->update();
	}
	
}