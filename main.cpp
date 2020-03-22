#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>


using namespace sf;	
using namespace std;

int main()
{
	//creating a window

	RenderWindow window(VideoMode(800, 600), "first game");
	window.setFramerateLimit(60);

	//shapes
	

	//text


	Font font;
	if (font.loadFromFile("pong/font.ttf"))
		cout << "font loaded\n";
	Text score;
	score.setFont(font);
	score.setCharacterSize(50);
	score.setFillColor(Color::White);
	score.setPosition(350, 20);
	

	//textures


	//setting textures


	//position

	//key variables

	bool up1 = false, down1 = false, down2 = false, up2 = false;
	
	int velocityY2, velocityY1,velocityXBall=6, velocityYBall=-6;
	int score1 = 10, score2 = 0, highscore ;
	
	//game loop

	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			//event


			if (event.type == Event::Closed)
				window.close();

			
	/*		if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up) up1 = true;
				if (event.key.code == Keyboard::S) down2 = true;
				if (event.key.code == Keyboard::W) up2 = true;
				if (event.key.code == Keyboard::Down) down1 = true;
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up) up1 = false;
				if (event.key.code == Keyboard::S) down2 = false;
				if (event.key.code == Keyboard::W) up2 = false;
				if (event.key.code == Keyboard::Down) down1 = false;
			}
	*/	}

		//logic




		//velocity change
		
		//movement
		
		
		
		ifstream readFile;
		readFile.open("pong/highscore.txt");

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highscore;
			}

		}


		readFile.close();

		if (score1 > highscore)

			highscore = score1;

		ofstream writeFile;
		writeFile.open("pong/highscore.txt");

		if (writeFile.is_open())
		{
			if (score1 > highscore)

				highscore = score1;


		}
		writeFile << highscore;

		writeFile.close();

		window.clear();
	
		//drawing

		/*window.draw(background);
		window.draw(rectangle1);
		window.draw(rectangle2);
		window.draw(ball);
		*/
		//string 
		stringstream padscores;
		padscores << highscore;
		score.setString(padscores.str());
	
		window.draw(score); 
		window.display();
		
	}

	return 0;
}