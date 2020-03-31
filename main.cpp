#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include "mainmenu.h"

using namespace sf;
using namespace std;

struct pos {
	int X, Y;
}txtmain;

struct velocity {
	float velocityx = 3, velocityy = 3;

};

struct controls {
	bool up, down, left, right, space;
}button;

void animateSpriteX(controls buttons, pos& posofsprite, int numSprite)
{
	if (buttons.up)
	{
		posofsprite.X++;
	}
	if (buttons.down)
	{
		posofsprite.X++;
	}
	if (buttons.left)
	{
		posofsprite.X++;
	}
	if (buttons.right)
	{
		posofsprite.X++;
	}
	if (posofsprite.X > numSprite)

		posofsprite.X = 0;
}

void stop(velocity velocity, Sprite& player, RectangleShape maze[], int sizeofmaze, controls button, pos& posofsprite)
{
	for (int i = 0; i < sizeofmaze; i++)
	{
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.left == true))
		{
			player.move(velocity.velocityx, 0);
			posofsprite.X = 0;
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.right == true))
		{
			player.move(-velocity.velocityx, 0);
			posofsprite.X = 0;
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.up == true))
		{
			player.move(0, velocity.velocityy);
			posofsprite.X = 0;
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.down == true))
		{
			player.move(0, -velocity.velocityy);
			posofsprite.X = 0;
		}
	}

}


void movePlayer(controls buttons, velocity velocity, Sprite& player)
{
	if (buttons.up)
	{
		player.move(0, -velocity.velocityy);

	}
	if (buttons.down)
	{
		player.move(0, velocity.velocityy);

	}
	if (buttons.left)
	{
		player.move(-velocity.velocityx, 0);

	}
	if (buttons.right)
	{
		player.move(velocity.velocityx, 0);

	}
}


int main()
{
	//creating a window

	RenderWindow window(VideoMode(800, 600), "first game");
	window.setFramerateLimit(60);


	//mainmenu window
	mainmenu menu(600, 600);

	//shapes
	RectangleShape maze1[30], maze2[20];
	//CircleShape mainplayer(10);
	//mainplayer.setPosition(Vector2f(400, 300));

	//music
	Music moonlight;
	if (moonlight.openFromFile("freshmen milestone/moonlight.WAV") == false)
	{
		cout << "loaded";
	}

	moonlight.play();
	moonlight.setVolume(50);
	//moonlight.setPlayingOffset();


	//maze1 settiing
	//maze1 settiing
	maze1[0].setSize(Vector2f(10, 130));
	maze1[0].setPosition(Vector2f(190, 220));

	maze1[1].setSize(Vector2f(45, 130));
	maze1[1].setPosition(Vector2f(70, 295));

	maze1[2].setSize(Vector2f(210, 20));
	maze1[2].setPosition(Vector2f(120, 200));

	maze1[3].setSize(Vector2f(10, 245));
	maze1[3].setPosition(Vector2f(40, 0));

	maze1[4].setSize(Vector2f(10, 260));
	maze1[4].setPosition(Vector2f(45, 320));

	maze1[5].setSize(Vector2f(420, 290));
	maze1[5].setPosition(Vector2f(40, 405));

	maze1[6].setSize(Vector2f(265, 95));
	maze1[6].setPosition(Vector2f(65, 115));

	maze1[7].setPosition(Vector2f(45, 115));
	maze1[7].setSize(Vector2f(15, 125));

	maze1[8].setPosition(Vector2f(200, 335));
	maze1[8].setSize(Vector2f(195, 15));

	maze1[9].setPosition(Vector2f(470, 405));
	maze1[9].setSize(Vector2f(35, 20));

	maze1[10].setPosition(Vector2f(410, 115));
	maze1[10].setSize(Vector2f(285, 90));

	maze1[11].setPosition(Vector2f(275, 275));
	maze1[11].setSize(Vector2f(190, 8));

	maze1[12].setPosition(Vector2f(480, 265));
	maze1[12].setSize(Vector2f(95, 10));

	maze1[13].setPosition(Vector2f(690, 220));
	maze1[13].setSize(Vector2f(15, 110));

	maze1[14].setPosition(Vector2f(595, 220));
	maze1[14].setSize(Vector2f(15, 40));

	maze1[15].setPosition(Vector2f(510, 355));
	maze1[15].setSize(Vector2f(220, 20));

	maze1[16].setPosition(Vector2f(627, 435));
	maze1[16].setSize(Vector2f(400, 480));

	maze1[17].setPosition(Vector2f(710, 240));
	maze1[17].setSize(Vector2f(15, 140));

	maze1[18].setPosition(Vector2f(775, 115));
	maze1[18].setSize(Vector2f(20, 75));
	//garden


	maze1[19].setSize(Vector2f(15, 70));
	maze1[19].setPosition(Vector2f(786, 30));

	maze1[20].setSize(Vector2f(15, 46));
	maze1[20].setPosition(Vector2f(693, 68));

	maze1[21].setSize(Vector2f(15, 46));
	maze1[21].setPosition(Vector2f(555, 68));

	maze1[22].setSize(Vector2f(8, 23));
	maze1[22].setPosition(Vector2f(473, 28));

	maze1[23].setSize(Vector2f(5, 19));
	maze1[23].setPosition(Vector2f(473, 100));


	maze1[24].setSize(Vector2f(8, 46));
	maze1[24].setPosition(Vector2f(410, 5));


	maze1[25].setSize(Vector2f(15, 46));
	maze1[25].setPosition(Vector2f(627, 30));

	maze1[26].setPosition(Vector2f(639, 5));
	maze1[26].setSize(Vector2f(70, 17));

	maze1[27].setPosition(Vector2f(568, 5));
	maze1[27].setSize(Vector2f(70, 17));

	maze1[28].setPosition(Vector2f(715, 5));
	maze1[28].setSize(Vector2f(70, 17));

	maze1[29].setPosition(Vector2f(490, 5));
	maze1[29].setSize(Vector2f(70, 17));


	// Setting a transparent color for accuracy 

	for (int i = 0; i < 30; i++)
	{
		maze1[i].setFillColor(Color(100, 50, 200, 150));
	}

	//player

	Texture mainptxt;

	if (!mainptxt.loadFromFile("freshmen milestone/boy5.png"))
		cout << "loaded";

	//Sprite mainplayer;

	Sprite mainplayer;

	mainplayer.setTexture(mainptxt);
	//mainplayer.setColor(Color::Red);
	mainplayer.setPosition(Vector2f(400, 300));
	//mainplayer.setScale(Vector2f(3f, f));

	velocity mainvelocity, backpackVelocity = {1};
	//mouse coordinates

	// set a mainmenu background

		Texture backgroundmaintxt;

	if (!backgroundmaintxt.loadFromFile("freshmen milestone/mainmenu.png"))
		cout << "not loaded/n";
	Sprite backgroundmain;
	Vector2u size_ = backgroundmaintxt.getSize();
	backgroundmain.setTexture(backgroundmaintxt);

	//set a background

	Texture backgroundtxt;

	if (!backgroundtxt.loadFromFile("freshmen milestone/background.png"))
		cout << "loaded";
	Sprite background;
	Vector2u size = backgroundtxt.getSize();
	background.setTexture(backgroundtxt);



	//Font

	Font font8;
	if (font8.loadFromFile("freshmen milestone/8font.otf"))
		cout << "font loaded\n";



	//Clock Setting

	Clock clock1,clock2;
	int timeavailable = 101;
	int timesec = timeavailable % 60, timemin = timeavailable / 60;
	ostringstream convert;
	convert << timesec, timemin, timeavailable;
	String timestring = convert.str();



	//Text 

	Text timescoresec;
	timescoresec.setFont(font8);
	timescoresec.setCharacterSize(35);
	timescoresec.setFillColor(Color::Black);
	timescoresec.setPosition(83, 507);
	timescoresec.setString(" ");

	Text timercolon;
	timercolon.setFont(font8);
	timercolon.setCharacterSize(35);
	timercolon.setFillColor(Color::Black);
	timercolon.setPosition(68, 507);
	timercolon.setString(" ");

	Text timescoremin;
	timescoremin.setFont(font8);
	timescoremin.setCharacterSize(35);
	timescoremin.setFillColor(Color::Black);
	timescoremin.setPosition(48, 507);
	timescoremin.setString("Time till lecture!!");



	//textures

	Texture backpacktxt;

	if (!backpacktxt.loadFromFile("freshmen milestone/backpack.png"))
		cout << "loaded";

	//setting textures

	Sprite backpack[5];
	
	for (int j = 0; j < 5; j++)
	{
		backpack[j].setTexture(backpacktxt);
		backpack[j].setScale(sf::Vector2f(0.035f, 0.035f));
		
	}
	
	//setting initial position & size


	backpack[0].setPosition(sf::Vector2f(550, 225));
	backpack[1].setPosition(sf::Vector2f(650, 25));
	backpack[2].setPosition(sf::Vector2f(650, 225));
	backpack[3].setPosition(sf::Vector2f(60, 5));
	backpack[4].setPosition(sf::Vector2f(700, 395));
	
	// variables

	int highscore;
	pos mainpos;
	bool moveBP = true;
	bool play = false, guide, menuvariable= true;




	//game loop

	while (window.isOpen())
	{

		Event event;

		while (window.pollEvent(event))
		{

			if (menuvariable)
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Up)
					{
						menu.MoveUp();
						break;
					}

					if (event.key.code == Keyboard::Down)
					{
						menu.MoveDown();
						break;
					}
					if (Keyboard::Return)
					{
						switch (menu.GetPressedItem())
						{
						case 0:
							cout << "play button has been pressed" << endl;
							play = true;
							menuvariable = false;
							break;
						case 1:
							cout << "option button has been pressed" << endl;
							guide = true;
							break;
						case 2:
							window.close();
						}
					}

				}
			}

			//event


			if (event.type == Event::Closed)
				window.close();

			if (play)

			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Up)
					{
						button.up = true;
						txtmain.Y = 0;
					}
					if (event.key.code == Keyboard::Down)
					{
						button.down = true;
						txtmain.Y = 1;
					}
					if (event.key.code == Keyboard::Left)
					{
						button.left = true;
						txtmain.Y = 2;
					}
					if (event.key.code == Keyboard::Right)
					{
						button.right = true;
						txtmain.Y = 3;
					}
					if (event.key.code == Keyboard::Space)
					{
						button.space = true;
					}

				}

				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Up)
					{
						button.up = false;
						txtmain.X = 0;
					}
					if (event.key.code == Keyboard::Down)
					{
						button.down = false;
						txtmain.X = 0;
					}
					if (event.key.code == Keyboard::Left)
					{
						button.left = false;
						txtmain.X = 0;
					}
					if (event.key.code == Keyboard::Right)
					{
						button.right = false;
						txtmain.X = 0;
					}
					if (event.key.code == Keyboard::Space)
					{
						button.space = false;
					}
				}
			}
		}


		mainplayer.setTextureRect(IntRect (txtmain.X *33, (txtmain.Y * 34) + 3, 33, 34));
		//logic

		if (mainplayer.getPosition().x < 0)
		{
			mainpos.Y = mainplayer.getPosition().y;
			mainplayer.setPosition(5, mainpos.Y);
			txtmain.X = 0;
		}
		if (mainplayer.getPosition().x > 770)
		{
			mainpos.Y = mainplayer.getPosition().y;
			mainplayer.setPosition(770, mainpos.Y);
			txtmain.X = 0;
		}
		if (mainplayer.getPosition().y < 0)
		{
			mainpos.X = mainplayer.getPosition().x;
			mainplayer.setPosition(mainpos.X, 5);
			txtmain.X = 0;
		}
		if (mainplayer.getPosition().y > 570)
		{
			mainpos.X = mainplayer.getPosition().x;
			mainplayer.setPosition(mainpos.X, 570);
			txtmain.X = 0;
		}


		//movement 
		movePlayer(button, mainvelocity, mainplayer);
		
		//animating sprite

		animateSpriteX(button, txtmain, 2);

		//velocity change on collision

		stop(mainvelocity, mainplayer, maze1, 30, button, txtmain);
		
		


		for (int j = 0; j < 5; j++)
		{

			if (mainplayer.getGlobalBounds().intersects(backpack[j].getGlobalBounds()))
			{
				backpack[j].setColor(Color(111, 206, 240));
	
				if (button.space)
				{

					backpack[j].setPosition(1000, 1000);
				}
			}
			else  backpack[j].setColor(Color ::Yellow);
		}

		//moving backpacks
		

		int timer = clock1.getElapsedTime().asSeconds();
		float timermov = clock2.getElapsedTime().asSeconds();
		
		if (timermov > 0.4) {

			if (moveBP)
			{
				for (int j = 0; j < 5; j++)
					backpack[j].move(0, 4);
				moveBP = false;

			}
			else
			{
				for (int j = 0; j < 5; j++)
					backpack[j].move(0, -4);
				moveBP = true;
				timermov = 0;
			}
			clock2.restart();
		}

		//Timer

		if (play)
		{
			if (timer > 0)
			{
				--timeavailable;
				timesec = timeavailable % 60, timemin = timeavailable / 60;
				timescoremin.setString(to_string(timemin));
				timercolon.setString(":");
				timescoresec.setString(to_string(timesec));


				clock1.restart();
			}

			if (timeavailable == 101)
			{
				timescoremin.setString("Time till lecture!!");
				timercolon.setString(" ");
				timescoresec.setString("");
			}
			if (timesec < 10)
			{
				timesec = timeavailable % 60, timemin = timeavailable / 60;
				timescoremin.setString(to_string(timemin));
				timercolon.setString(":0");
				timescoresec.setPosition(100, 507);
				timescoresec.setString(to_string(timesec));
			}
			else
			{
				timescoresec.setPosition(83, 507);
			}
			if (timeavailable < 1)
			{
				timescoremin.setString(" YOU'RE LATE!!");
				timercolon.setString(" ");
				timescoresec.setString(" ");
			}

		}

		//highest score

		/*ifstream readFile;
		readFile.open("freshmen milestone/highscore.txt");

		if (readFile.is_open())
		{
		while (!readFile.eof())
		{
		readFile >> highscore;
		}

		}


		readFile.close();
		*/
		//if (/name of score/ > highscore)

		//	highscore = /name of score/;

		//ofstream writeFile;
		//writeFile.open("pong/highscore.txt");

		//if (writeFile.is_open())
		//{
		//	if (/name of score/ > highscore)

		//		highscore =/name of score/;


		//}
		//writeFile << highscore;

		//writeFile.close();




		window.clear();

		//drawing
		if (play)

		{
			for (int i = 0; i < 30; i++)
			{
				window.draw(maze1[i]);
			}

			window.draw(background);

			for (int i = 0; i < 5; i++)
			{
				window.draw(backpack[i]);

			}

			window.draw(mainplayer);
			/*
			window.draw();
			window.draw();
			window.draw();
			window.draw();
			*/


			//string drawing 
			window.draw(timescoremin);
			window.draw(timercolon);
			window.draw(timescoresec);

			//stringstream highest;
			//highest << highscore;
			// /name of text/.setString(highest.str());

			//window.draw(/name of text/); 
		}
		if (menuvariable)
		{
			window.draw(backgroundmain);
			
			menu.draw(window);
		}

		window.display();



	}

	return 0;
}