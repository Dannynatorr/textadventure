#include "TextAdventure.h"




TextAdventure::TextAdventure()
{
	

	

	

	

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "TextAdventure");
	SetTargetFPS(60);

	srand(time(NULL));

	
	
	
	



}

TextAdventure::~TextAdventure()
{
	CloseWindow();
	
}

void TextAdventure::setDialogue(Json::Value d)
{
	
	textNumber = 0;
	dialogue = d;
	//std::cout << dialogue << std::endl;
	if (!dialogue) return;
	textbox.updateText(dialogue["text"][textNumber].asCString(), false);

	textbox.setLastText(false);

	
	textbox.resetText();
	
}

void TextAdventure::showShop()
{
	if (map.getCurrentRoom() != NULL)
	{
		if (map.getCurrentRoom()->getType() == RoomType::Shop)
		{

			textbox.resetText();
			setDialogue(jsonData["texts"]["shop"]);

		}

	}
}

void TextAdventure::showExit()
{
	if (lastDialogue == jsonData["texts"]["exit"]) return;

	if (map.getCurrentRoom() != NULL)
	{
		if (map.getCurrentRoom()->getType() == RoomType::Exit)
		{

			textbox.resetText();
			setDialogue(jsonData["texts"]["exit"]);

		}

	}
}

void TextAdventure::showEnemy()
{
	if (map.getCurrentRoom() != NULL)
	{
		if (map.getCurrentRoom()->getType() == RoomType::Enemy)
		{
			map.getCurrentRoom()->show(true);
			textbox.resetText();
			setDialogue(jsonData["texts"]["battle-start"]);

		}

	}
}


void TextAdventure::run()
{
	
	

	std::fstream file("text.json");



	Json::Reader r;

	r.parse(file, jsonData);
	
	file.close();
	

	textbox.init();
	choices.init();
	player.init(jsonData["chars"]);
	map.loadEnemyData(jsonData["enemies"]);

	
	//healthBar.setColor(Color{ 91,206,250,255 }, Color{ 245,169,184,255 });
	

	//std::string s = jsonData["1"]["options"][2].asCString();

	//std::cout << jsonData << std::endl;

	dialogue = jsonData["texts"]["characterSelect"];

	

	while (!WindowShouldClose())
	{
		
		processInput();
		update();
		render();
		
		if(quitting) CloseWindow();

	}
}

void TextAdventure::processInput()
{
	if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && textNumber != dialogue["text"].size() -1)
	{

		if(textbox.isFinished()) textNumber++;

		
		textbox.resetText();
	}
	else
	{
		if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !textbox.isFinished() )
		{
			textbox.resetText();
		}
		
	}
		
	if (IsKeyDown(KEY_G))
	{
		//map.setVisible(true);
		//map.generateRooms();
	}
	

	//std::cout << choices.getIDfromHoveredButton() << std::endl;

	
	if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (dialogue == jsonData["texts"]["enemy-defeated"])
		{

			map.getCurrentRoom()->setType(RoomType::EmptyRoom);
		}
	}
	



	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		
		

		if (choices.getIDfromPressedButton() != "-1")
		{
			
			
			//setDialogue(jsonData["texts"][choices.getIDfromPressedButton().c_str()]);
			
			if (choices.getIDfromPressedButton() ==  "bob" )
			{
				player.setPlayer(Characters::BOB);
				player.print();
				
				

				healthBar.setMaxHP(player.getStat(Stats::HP));
				player.setStat(Stats::HP, player.getStat(Stats::HP) * 0.2);
				
				healthBar.setVisible(true);
				player.setVisible(true);

				setDialogue(jsonData["texts"]["pickedBob"]);
				
			}

			if (choices.getIDfromPressedButton() ==  "jesus" )
			{
				player.setPlayer(Characters::JESUS);
				player.print();
				
				healthBar.setMaxHP(player.getStat(Stats::HP));
				player.setStat(Stats::HP, player.getStat(Stats::HP));
				
				healthBar.setVisible(true);
				player.setVisible(true);

				setDialogue(jsonData["texts"]["pickedJesus"]);

			}

			if (choices.getIDfromPressedButton() == "shop-done")
			{
				

				setDialogue(jsonData["texts"]["room"]);

			}
			
			if (choices.getIDfromPressedButton() == "shop-heilung")
			{

				if (player.getStat(Stats::MONEY) >= 20)
				{
					if (healthBar.getCurrentHP() == healthBar.getMaxHP())
					{
						setDialogue(jsonData["texts"]["shop-heilung-volleLeben"]);
					}
					else
					{
						
						player.setStat(Stats::HP, player.getStat(Stats::HP) + 100);
						player.setStat(Stats::MONEY, player.getStat(Stats::MONEY) - 20);

						setDialogue(jsonData["texts"]["shop-heilung-erfolg"]);
					}
					
					
				}
				else
				{
					
					setDialogue(jsonData["texts"]["shop-heilung-noMoney"]);
					
				}
				

			}

			if (choices.getIDfromPressedButton() == "shop-schwert")
			{
				if (player.getName() == "Jesus")
				{
					setDialogue(jsonData["texts"]["shop-schwert-jesus"]); 
				}
				else
				{
					if (player.getStat(Stats::MONEY) < 100)
					{
						setDialogue(jsonData["texts"]["shop-schwert-noMoney"]);
					}
					else
					{
						setDialogue(jsonData["texts"]["shop-schwert-erfolg"]);
						player.setStat(Stats::ATK, player.getStat(Stats::ATK) + 3.0);
						player.setStat(Stats::MONEY, player.getStat(Stats::MONEY) - 100);
						player.print();
					}
					
				}
			}

			if (choices.getIDfromPressedButton() == "quit")
			{
				quitting = true;

			}

			if (choices.getIDfromPressedButton() == "newGame")
			{
				healthBar.setMaxHP(1);
				healthBar.setHP(1);
				player.setStat(Stats::HP, 1);
				healthBar.setVisible(false);
				setDialogue(jsonData["texts"]["characterSelect"]);
				
			}
			

			absorbing = 1;
			shielding = 1;

			if (choices.getIDfromPressedButton() == "shield")
			{
				int rnd = rand() % 100;

				if (rnd < 33)
				{
					setDialogue(jsonData["texts"]["shield-absorb"]);
					absorbing = -2.0;
				}
				else
				{
					setDialogue(jsonData["texts"]["shielding"]);
					shielding = 0.4;
				}
			}


			if (choices.getIDfromPressedButton() == "attack")
			{

				setDialogue(jsonData["texts"]["attack"]);
				Enemy* enemy = map.getCurrentRoom()->getEnemy();
				float atk = player.getStat(Stats::ATK);
				float def = enemy->getStat(EnemyStats::DEF);

				atk = atk + ((rand() % (int)atk) - 0.5*atk);

				int critchance = rand() % 100;
				std::cout << critchance << std::endl;
				
				float damage = atk - 0.8*atk * (1.0 - 1/pow(2,0.05*def));
				if (critchance < 20)
				{
					setDialogue(jsonData["texts"]["crit-attack"]);
					damage *= 4;
				}

				enemy->setStat(EnemyStats::HP, enemy->getStat(EnemyStats::HP) - damage);


				
			}
			
			



			if (choices.getIDfromPressedButton() == "flee")
			{
				int rnd = rand() % 100;

				if (rnd < 40)
				{
					fleeing = true;
					map.getCurrentRoom()->show(false);
					setDialogue(jsonData["texts"]["flee-success"]);
				}
				else
				{
					setDialogue(jsonData["texts"]["flee-failed"]);
				}
			}

			if (choices.getIDfromPressedButton() == "next-floor")
			{
				map.nextFloor();
				map.clearMap();
				map.generateRooms();
				
				setDialogue(jsonData["texts"]["room"]);
			}

			if (choices.getIDfromPressedButton() == "explore-further")
			{
				setDialogue(jsonData["texts"]["room"]);
			}


			if (choices.getIDfromPressedButton() == "/")
			{
				//textbox.resetText();
				setDialogue(jsonData["texts"]["/"]);
				player.setStat(Stats::HP,player.getStat(Stats::HP) - 10);
				
				

			}

			if (choices.getIDfromPressedButton() == "links")
			{
				if (map.getCurrentRoom()->getLeft() != NULL)
				{
					fleeing = false;
					map.setCurrentRoom(map.getCurrentRoom()->getLeft());
					setDialogue(jsonData["texts"]["room"]);

					//wenn im shop
					showShop();

					//wenn Gegner

					showEnemy();

					//wenn im Ziel

					showExit();

				}
					
			}
			if (choices.getIDfromPressedButton() == "rechts")
			{
				if (map.getCurrentRoom()->getRight() != NULL)
				{
					fleeing = false;
					map.setCurrentRoom(map.getCurrentRoom()->getRight());
					setDialogue(jsonData["texts"]["room"]);

					//wenn im shop
					showShop();

					//wenn Gegner

					showEnemy();

					//wenn im Ziel

					showExit();
				}
			}
			if (choices.getIDfromPressedButton() == "oben")
			{
				if (map.getCurrentRoom()->getUp() != NULL)
				{
					fleeing = false;
					map.setCurrentRoom(map.getCurrentRoom()->getUp());
					setDialogue(jsonData["texts"]["room"]);

					//wenn im shop
					showShop();

					//wenn Gegner

					showEnemy();

					//wenn im Ziel

					showExit();
				}
			}
			if (choices.getIDfromPressedButton() == "unten")
			{
				if (map.getCurrentRoom()->getDown() != NULL)
				{
					fleeing = false;

					map.setCurrentRoom(map.getCurrentRoom()->getDown());
					setDialogue(jsonData["texts"]["room"]);

					//wenn im shop
					showShop();

					//wenn Gegner

					showEnemy();

					//wenn im Ziel

					showExit();
				}
			}

			
			

			healthBar.setName(player.getName());
			choices.setVisible(false);
			
			
		}
		
		
	}

	

	



	if (IsKeyPressed(KEY_LEFT))
	{
		//player.setStat(Stats::HP, player.getStat(Stats::HP) - 100);

	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		//player.setStat(Stats::HP, player.getStat(Stats::HP) + 100);
		
	}
	if (IsKeyDown(KEY_UP))
	{
		
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		
	}
	
	

}

void TextAdventure::update()
{
	
	


	if (map.getCurrentRoom())
	{
		if (map.getCurrentRoom()->getType() == RoomType::Enemy && !fleeing)
		{
			map.setVisible(false);
		}
		else
		{
			map.setVisible(true);
		}

	}
	

	healthBar.update();
	map.update();
	choices.update();
	player.update();
	
	
	
		if (textNumber < dialogue["text"].size())
		{
			
			textbox.updateText(dialogue["text"][textNumber].asCString(), false);
			
			
		}
		else
		{

			textNumber = 0;
		}

		if (textNumber != dialogue["text"].size() - 1)
		{
			textbox.setLastText(false);
		}
		else
		{
			textbox.setLastText(true);
			if (textbox.isFinished())
			{
				if ((dialogue.get("next", NULL) != NULL) )
				{
					
					if((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !textbox.isjustFinished())
					{
						setDialogue(jsonData["texts"][dialogue["next"].asCString()]);
					}
					textbox.setLastText(false);
					
				}
				else
				{
					if (dialogue == jsonData["texts"]["room"])
					{
						
						if (map.getCurrentRoom() == NULL)
						{
							map.clearMap();
							map.generateRooms();
							map.setVisible(true);
	
						}

						dialogue["options"].clear();
						dialogue["options"][0][0] = "/";
						dialogue["options"][0][1] = "/";
						dialogue["options"][1][0] = "/";
						dialogue["options"][1][1] = "/";
						dialogue["options"][2][0] = "/";
						dialogue["options"][2][1] = "/";
						dialogue["options"][3][0] = "/";
						dialogue["options"][3][1] = "/";

						//std::cout << "options: " << dialogue["options"] << std::endl;
						
						

						if (map.getCurrentRoom()->getLeft() != NULL)
						{
							dialogue["options"][0][0] = "Links";
							dialogue["options"][0][1] = "links";
							
						}
						

						if (map.getCurrentRoom()->getRight() != NULL)
						{
							dialogue["options"][1][0] = "Rechts";
							dialogue["options"][1][1] = "rechts";

						}

						if (map.getCurrentRoom()->getUp() != NULL)
						{
							dialogue["options"][2][0] = "Oben";
							dialogue["options"][2][1] = "oben";

						}

						if (map.getCurrentRoom()->getDown() != NULL)
						{
							dialogue["options"][3][0] = "Unten";
							dialogue["options"][3][1] = "unten";

						}
					}
					choices.presentChoices(dialogue["options"]);
				}
				
			}
		}
	
	
		if (choices.getIDfromHoveredButton() != "-1" && dialogue == jsonData["texts"]["characterSelect"])
		{
			
			{
				textbox.resetText();
				textbox.setText("Dein Name war...");
			}

			if (choices.getIDfromHoveredButton() == "bob")
			{


				textbox.resetText();




				textbox.setText(jsonData["chars"]["bob"]["description"].asCString());
			}
			else if (choices.getIDfromHoveredButton() == "jesus")
			{



				textbox.resetText();



				textbox.setText(jsonData["chars"]["jesus"]["description"].asCString());
			}
			
			



		}
		

	if (healthBar.getCurrentHP() <= 0)
	{
		if (dialogue != jsonData["texts"]["gameOver"])
		{
			if(!textbox.isFinished())
			{
				textbox.resetText();
			}
			
			map.clearMap();
			map.setVisible(false);
			player.setVisible(false);
			choices.setVisible(false);
			setDialogue(jsonData["texts"]["gameOver"]);
		}
		
		

	}


	
	if (map.getCurrentRoom())
	{
		if (map.getCurrentRoom()->getEnemy())
		{
			if (map.getCurrentRoom()->getEnemy()->getStat(EnemyStats::HP) <= 0 && map.getCurrentRoom()->getType() == RoomType::Enemy)
			{
				if (lastDialogue != jsonData["texts"]["enemy-defeated"])
				{
					choices.setVisible(false);
					setDialogue(jsonData["texts"]["enemy-defeated"]);
					//map.getCurrentRoom()->setType(RoomType::EmptyRoom);
					player.setStat(Stats::MONEY, player.getStat(Stats::MONEY) + map.getCurrentRoom()->getEnemy()->getStat(EnemyStats::MONEY));
					//delete map.getCurrentRoom()->getEnemy();
				}
				
			}
		}
	}
	
	

	if (dialogue == jsonData["texts"]["enemy-attack"])
	{
		if (lastDialogue != jsonData["texts"]["enemy-attack"])
		{

			float atk = map.getCurrentRoom()->getEnemy()->getStat(EnemyStats::ATK);
			atk = atk + ((rand() % (int)atk) - 0.5 * atk);

			float def = player.getStat(Stats::DEF);
			
			std::cout << "absorbing: " << absorbing << std::endl;
			std::cout << "shielding: " << shielding << std::endl;
			float damage = absorbing*(shielding*atk - 0.8 * atk * (1.0 - 1 / pow(2, 0.05 * def)));

			player.setStat(Stats::HP, player.getStat(Stats::HP) - damage);

			healthBar.setHP(player.getStat(Stats::HP));
		}
		
	}


	if (map.getFloorNumber() == 10)
	{
		if (lastDialogue != jsonData["texts"]["game-won"])
		{
			

			
			map.setFloor(0);
			map.clearMap();
			map.setVisible(false);
			player.setVisible(false);
			healthBar.setVisible(false);
			choices.setVisible(false);
			setDialogue(jsonData["texts"]["game-won"]);
		}
	}


	healthBar.setHP(player.getStat(Stats::HP));
	lastDialogue = dialogue;

}

void test() 
{
	float x, y;

	x = 100;
	y = 500;

	DrawCircleSector(Vector2{ x,y }, 50, 270, 90, 0, RED);
	DrawRectangle(x - 50 , y , 100, 100, RED);
	DrawRectangle(x - 20, y + 75, 40, 25, Color{ 30, 30,31,255 });
	DrawRectangle(x - 70, y, 30, 60, RED);
	DrawEllipse(x + 10, y, 50, 30, WHITE);
}

void TextAdventure::render()
{

	BeginDrawing();

	ClearBackground(Color{ 30, 30,31,255 });

	textbox.render();
	choices.render();
	
	healthBar.render();
	

	map.render();

	player.render();



	
	
	//test();

	EndDrawing();



}




