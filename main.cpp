#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>


using namespace sf;
using namespace std;

struct pos {
	int X, Y;
};
struct player {
	float velocityx = 5, velocityy = 5;
};

struct controls {
	bool up, down, left, right, space;
}button;

void stop(player velocity, Sprite player, RectangleShape maze[], int sizeofmaze,controls button)
{
	for (int i = 0; i < sizeofmaze; i++)
	{
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.left == true))
		{
			player.move(velocity.velocityx, 0);
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.right == true))
		{
			player.move(-velocity.velocityx, 0);
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.up == true))
		{
			player.move(0, velocity.velocityy);
		}
		if (player.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.down == true))
		{
			player.move(0, -velocity.velocityy);
		}
	}

}



int main()
{
	//creating a window

	RenderWindow window(VideoMode(800, 600), "first game");
	window.setFramerateLimit(60);

	//shapes
	RectangleShape maze1[20], maze2[20];
	CircleShape mainplayer(30);
	//player
	//Sprite mainplayer;
	player mainvelocity;

	//text


	/*Font font;
	if (font.loadFromFile(""))
		cout << "font loaded\n";
*/

	Text score;
	/*score.setFont(font);
	score.setCharacterSize();
	score.setFillColor();
	score.setPosition();*/



	//textures


	//setting textures


	//setting initial position

	// variables

	int highscore;
	pos mainpos;

	//game loop

	while (window.isOpen())
	{

		Event event;

		while (window.pollEvent(event))
		{
			//event


			if (event.type == Event::Closed)
				window.close();


			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					button.up = true;
				}
				if (event.key.code == Keyboard::Down)
				{
					button.down = true;
				}
				if (event.key.code == Keyboard::Left)
				{
					button.left = true;
				}
				if (event.key.code == Keyboard::Right)
				{
					button.right = true;
				}

			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					button.up = false;
				}
				if (event.key.code == Keyboard::Down)
				{
					button.down = false;
				}
				if (event.key.code == Keyboard::Left)
				{
					button.left = false;
				}
				if (event.key.code == Keyboard::Right)
				{
					button.right = false;
				}
			}

		}

		//logic

		if (mainplayer.getPosition().x < 0)
		{
			mainpos.Y = mainplayer.getPosition().y;
			mainplayer.setPosition(5, mainpos.Y);
		}
		if (mainplayer.getPosition().x >730)
		{
			mainpos.Y = mainplayer.getPosition().y;
			mainplayer.setPosition(730, mainpos.Y);
		}
		if (mainplayer.getPosition().y < 0)
		{
			mainpos.X = mainplayer.getPosition().x;
			mainplayer.setPosition( mainpos.X,5);
		}
		if (mainplayer.getPosition().y > 530)
		{
			mainpos.X = mainplayer.getPosition().x;
			mainplayer.setPosition(mainpos.X,530);
		}
			



		//velocity change on collision




		//movement

		if (button.up)
		{
			mainplayer.move(0, -mainvelocity.velocityy);
		}
		if (button.down)
		{
			mainplayer.move(0, mainvelocity.velocityy);
		}
		if (button.left)
		{
			mainplayer.move(-mainvelocity.velocityx, 0);
		}
		if (button.right)
		{
			mainplayer.move(mainvelocity.velocityx, 0);
		}






		//highest score

		ifstream readFile;
		readFile.open("freshmen milestone/highscore.txt");

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highscore;
			}

		}


		readFile.close();

		//if (/*name of score*/ > highscore)

		//	highscore = /*name of score*/;

		//ofstream writeFile;
		//writeFile.open("pong/highscore.txt");

		//if (writeFile.is_open())
		//{
		//	if (/*name of score*/ > highscore)

		//		highscore =/*name of score*/;


		//}
		//writeFile << highscore;

		//writeFile.close();




		window.clear();

		//drawing
		window.draw(mainplayer);
		/*
		window.draw();
		window.draw();
		window.draw();
		window.draw();
		*/


		//string drawing 
		//stringstream highest;
		//highest << highscore;
		// /*name of text*/.setString(highest.str());

		//window.draw(/*name of text*/); 


		window.display();

	}

	return 0;
}