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
				
			}

			if (event.type == Event::KeyReleased)
			{
				
			}
	*/	}

		//logic




		//velocity change on collision

		

		
		//movement
		
		
		//highest score
		
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