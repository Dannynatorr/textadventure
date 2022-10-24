#include "Map.h"


void Map::generate(Room* r, Vector2 position)
{
	
	if (!(position.x >= 0 && position.x < rows && position.y >= 0 && position.y < cols)) { return; }

	//r.setPosition(Vector2{ position.x ,position.y });

	
	int rnd = rand() % 100;
	

	

	if(roomsGenerated < numberOfRooms)
	{
		if (r->getLeft() == NULL)
		{
			if (rnd < 20)
			{
				
				if (position.x - 1 >= 0)
				{
					
					
						Room* r2 = new Room();


						r2->setPosition(Vector2{ position.x - 1 ,position.y });
						if (rooms[position.x - 1][position.y] == NULL)
						{
							rooms[position.x - 1][position.y] = r2;
							roomsGenerated++;
							generate(r2, Vector2{ r2->getPosition() });
						}
						else
						{
							generate(r2, Vector2{ r2->getPosition() });
							delete r2;

						}
						if (roomsGenerated >= numberOfRooms) return;
						
					
				}

				
				
				
			}
		}
		

		rnd = rand() % 100;


		

		if (r->getUp() == NULL)
		{
			if (rnd < 30)
			{

				if (position.y - 1 >= 0)
				{
					
					
						Room* r2 = new Room();


						r2->setPosition(Vector2{ position.x ,position.y - 1 });
						
						if (rooms[position.x ][position.y - 1] == NULL)
						{
							rooms[position.x ][position.y - 1] = r2;
							roomsGenerated++;
							generate(r2, Vector2{ r2->getPosition() });
						}
						else
						{
							generate(r2, Vector2{ r2->getPosition() });
							delete r2;

						}
						if (roomsGenerated >= numberOfRooms) return;
					
				}

				
			}
		}
		


		rnd = rand() % 100;


		if (r->getRight() == NULL)
		{
			if (rnd < 30)
			{
				
				if (position.x + 1 < rows)
				{
					
					
						Room* r2 = new Room();


						r2->setPosition(Vector2{ position.x + 1 ,position.y });
						if (rooms[position.x + 1][position.y] == NULL)
						{
							rooms[position.x + 1][position.y] = r2;
							roomsGenerated++;
							generate(r2, Vector2{ r2->getPosition() });
						}
						else
						{
							generate(r2, Vector2{ r2->getPosition() });
							delete r2;

						}
						
						
						if (roomsGenerated >= numberOfRooms) return;
					
				}
				
			}
		}
		if (roomsGenerated >= numberOfRooms) return;

		rnd = rand() % 100;


		if (r->getDown() == NULL)
		{
			if (rnd < 30)
			{

				if (position.y + 1 < cols)
				{
					
					
						Room* r2 = new Room();


						r2->setPosition(Vector2{ position.x  ,position.y + 1 });
						if (rooms[position.x ][position.y + 1] == NULL)
						{
							rooms[position.x ][position.y + 1] = r2;
							roomsGenerated++;
							generate(r2, Vector2{ r2->getPosition() });
						}
						else
						{
							generate(r2, Vector2{ r2->getPosition() });
							delete r2;

						}
						if (roomsGenerated >= numberOfRooms) return;
					
				}

				
			}
		}
		
	}
	

	
	
	return;
}





void Map::generateRooms()
{
	
	//while (rooms.size() < numberOfRooms)
	roomList.clear();
	rooms.resize(rows, std::vector<Room*>(cols, NULL));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			Room* r = rooms[i][j];
			if (r)
			{
				r->clearRoom();
			}
			
			delete r;
			rooms[i][j] = NULL;
		}
	}


	Room* r = new Room();


	setCurrentRoom(r);

	int rndX = rand() % cols;
	int rndY = rand() % rows;
	r->setPosition(Vector2{ float(rndX),float(rndY) });






	rooms[(int)r->getPosition().x][(int)r->getPosition().y] = r;

	roomsGenerated = 1;
	while (roomsGenerated < numberOfRooms)
	{

		generate(r, Vector2{ r->getPosition() });
	}



	
	for (int i = 0; i < rooms.size(); i++)
	{
		for (int j = 0; j < rooms[i].size(); j++)
		{
			

			if (rooms[i][j] != NULL)
			{

				roomList.push_back(rooms[i][j]);

				if (i + 1 < rows)
				{

					rooms[i][j]->setRight(rooms[i + 1][j]);

				}

				if (i - 1 >= 0)
				{

					rooms[i][j]->setLeft(rooms[i - 1][j]);


				}

				if (j + 1 < cols)
				{
					rooms[i][j]->setDown(rooms[i][j + 1]);
				}

				if (j - 1 >= 0)
				{
					rooms[i][j]->setUp(rooms[i][j - 1]);
				}
			}

			

		}
	}
		
	//generate enemy Rooms


	switch (floor + 1)
	{
	
	case 1:
	case 2:
		enemyRooms = 5;

		for (int i = 0; i < enemyRooms; i++)
		{
			int rnd = rand() % roomList.size();
			while (roomList[rnd]->getType() == RoomType::Enemy)
			{
				rnd = rand() % roomList.size();
			}



			roomList[rnd]->setType(RoomType::Enemy);

			Enemy* e = new Enemy(EnemyType::SLIME, enemyData);



			roomList[rnd]->setEnemy(e);

		}
			break;
	
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:

		enemyRooms = 7;

		for (int i = 0; i < enemyRooms; i++)
		{
			int rnd = rand() % roomList.size();
			while (roomList[rnd]->getType() == RoomType::Enemy)
			{
				rnd = rand() % roomList.size();
			}
			int rndEnemy = rand() % 100;


			roomList[rnd]->setType(RoomType::Enemy);

			Enemy* e;

			if (rndEnemy < 50)
			{
				 e = new Enemy(EnemyType::SLIME, enemyData);
			}
			else 
			{
				e = new Enemy(EnemyType::BAT, enemyData);
			}
			



			roomList[rnd]->setEnemy(e);

		}


		break;

	case 8:
	case 9:
	case 10:
		enemyRooms = 11;

		for (int i = 0; i < enemyRooms; i++)
		{
			int rnd = rand() % roomList.size();
			while (roomList[rnd]->getType() == RoomType::Enemy)
			{
				rnd = rand() % roomList.size();
			}
			int rndEnemy = rand() % 100;


			roomList[rnd]->setType(RoomType::Enemy);

			Enemy* e;

			if (rndEnemy < 20)
			{
				 e = new Enemy(EnemyType::SLIME, enemyData);
			}
			else if (rndEnemy < 40)
			{
				 e = new Enemy(EnemyType::BAT, enemyData);
			}
			else
			{
				 e = new Enemy(EnemyType::DRAGON, enemyData);
			}
			



			roomList[rnd]->setEnemy(e);

		}


		break;
		
		}

	


	// generate shop
	
	int rnd = rand() % roomList.size();
	
	while (roomList[rnd]->getType() != RoomType::EmptyRoom)
	{
		rnd = rand() % roomList.size();
	}
	
	
	roomList[rnd]->setType(RoomType::Shop);

	//set start position

	rnd = rand() % roomList.size();

	
	currentRoom = roomList[rnd];

	while(currentRoom->getType() != RoomType::EmptyRoom)
	{
		rnd = rand() % roomList.size();
		currentRoom = roomList[rnd];
	}

	//generate exit
	int farthestRoomDistance = 0;
	Room* currentExit = NULL;

	for (int i = 0; i < roomList.size(); i++)
	{
		if (roomList[i]->getType() == RoomType::EmptyRoom)
		{
			Vector2 currentPos = currentRoom->getPosition();
			Vector2 pos = roomList[i]->getPosition();
			Vector2 direction{pos.x-currentPos.x,pos.y-currentPos.y};
			int d = (direction.x * direction.x + direction.y * direction.y);

			if (farthestRoomDistance < d)
			{
				currentExit = roomList[i];
				farthestRoomDistance = d;
			}
		}
	}
	
	currentExit->setType(RoomType::Exit);


}

void Map::update()
{



	




	if (currentRoom)
	{
		for (int i = 0; i < roomList.size(); i++)
		{

			if (roomList[i] == currentRoom)
			{
				if (roomList[i]->getType() == RoomType::Enemy && roomList[i]->isShowing())
				{
					currentRoom->showEnemy(true);
				}

			}
			else
			{
				currentRoom->showEnemy(false);
			}
			roomList[i]->update();

		}
	}
	



	x = Lerp(GetScreenWidth()+ width + 10, 800, t * t * (3 - 2 * t));

	if (isVisible)
	{
		t += 0.02;
	}
	else
	{
		t -= 0.02;
	}

	t = Clamp(t, 0, 1);


	if (currentRoom != NULL)
	{
		currentRoom->setVisible(true);
		currentRoom->setEntered(true);

		if(currentRoom->getUp() != NULL) currentRoom->getUp()->setVisible(true);
		if (currentRoom->getLeft() != NULL) currentRoom->getLeft()->setVisible(true);
		if (currentRoom->getDown() != NULL) currentRoom->getDown()->setVisible(true);
		if (currentRoom->getRight() != NULL) currentRoom->getRight()->setVisible(true);
	}
	
}


void Map::clearMap()
{
	for (int i = 0; i < rooms.size(); i++)
	{
		for (int j = 0; j < rooms[i].size(); j++)
		{
			if (rooms[i][j] != NULL)
			{
				
				
				
				
				
				rooms[i][j] == NULL;
			}
			
			
		}
	}

	currentRoom = NULL;
}

void Map::render()
{
	
	
	if (currentRoom)
	{
		for (int i = 0; i < roomList.size(); i++)
		{

			if (roomList[i] == currentRoom)
			{
				if (roomList[i]->getType() == RoomType::Enemy)
				{
					currentRoom->showEnemy(true);
				}

			}
			else
			{
				currentRoom->showEnemy(false);
			}

			roomList[i]->render();





		}
	}
	
	
	
	DrawRectangle(x, y, width * rows, height * cols, Color{246,153,197,100});
	DrawRectangleLines(x, y, width * cols, height * rows, BLUE);


	if (isVisible)
	{
		
		std::string label{ "Ebene: " + std::to_string(floor + 1)};
		DrawText(label.c_str(), x, y + cols * height + 5, 20, WHITE);

		for (int i = 0; i < rooms.size(); i++)
		{
			for (int j = 0; j < rooms[i].size(); j++)
			{
				Room* r = rooms[i][j];
				if (r != NULL)
				{
					Vector2 p = r->getPosition();
	
					if (r->isVisible())
					{
						if (currentRoom == r)
						{
							DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, DARKGREEN);
							DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, BLACK);
						}
						else
						{
							if (r->isEntered())
							{
								Vector2 v{ currentRoom->getPosition().x - r->getPosition().x, currentRoom->getPosition().y - r->getPosition().y };
								float distance = v.x * v.x + v.y * v.y;
								int a = (255 * (1 - (20 * distance / (rows * cols))));
								a = std::max(0, a);
								unsigned char aa = a;
								
								
								switch (r->getType())
								{
								case RoomType::EmptyRoom:
	
									DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ aa,aa,aa,aa });
									DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,0,aa });
									break;
								case RoomType::Shop:
	
									DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 255,255,0,aa });
									DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,0,aa });
									break;
								case RoomType::Enemy:
	
									DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 255,0,0,aa });
									DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,0,aa });
									break;
								case RoomType::Exit:

									DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,255,aa });
									DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,0,aa });
									break;
								}
								//DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ (unsigned char)a,(unsigned char)a,(unsigned char)a,(unsigned char)a });
								//DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 0,0,0,(unsigned char)a });
							}
							else
							{
								Vector2 v{ currentRoom->getPosition().x - r->getPosition().x, currentRoom->getPosition().y - r->getPosition().y };
								float distance = v.x * v.x + v.y * v.y;
								int a = (255 * (1 - (20 * distance / (rows * cols))));
								a = std::max(0, a);
								
								//DrawRectangle(x + 1 + ((int)p.x * width - 2), y + 1 + ((int)p.y * height - 2), width - space, height - space, Color{ 0,0,0,(unsigned char)a });
								DrawRectangle(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{ 40,40,40,(unsigned char)a });
	
								DrawRectangle(x + 3 + ((int)p.x * width), y + 3 + ((int)p.y * height), width - 6 - space, height - 6 - space, Color{ 133,133,133,(unsigned char)a });
	
								//DrawRectangleLines(x + ((int)p.x * width), y + ((int)p.y * height), width - space, height - space, Color{60,13,40,(unsigned char)a });
							}
	
						}
					}
	
				}
			}
	
	
	
		}
	}
		
	
	
}
