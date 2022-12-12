#include "GridElement.h"

void GridElement::init()
{
	int rnd = rand() % 3;

	switch (rnd)
	{
	case 0:
		color = Color{ 223,178,50,255 };
		break;
	case 1:
		color = Color{ 22,190,100,255 };
		break;
	case 2:
		color = Color{ 173,69,200,255 };
		break;
	}
}

void GridElement::update()
{
	if (shouldSwitch)
	{
		switchState();
		shouldSwitch = false;
	}
}


