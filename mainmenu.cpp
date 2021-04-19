#include "mainmenu.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;

mainmenu::mainmenu(float height, float width)
{
	if (!font.loadFromFile("freshmen milestone/8font.otf"))
	{
		cout << "loaded failed";
	}

	//play
	mainmenuarr[0].setFont(font);
	mainmenuarr[0].setColor(sf::Color::Blue);
	mainmenuarr[0].setString("Play");
	mainmenuarr[0].setCharacterSize(50);
	mainmenuarr[0].setPosition(sf::Vector2f(350, 210));



	//guide

	mainmenuarr[1].setFont(font);
	mainmenuarr[1].setColor(sf::Color::White);
	mainmenuarr[1].setString("Guide");
	mainmenuarr[1].setCharacterSize(40);
	mainmenuarr[1].setPosition(sf::Vector2f(335, 298));


	//exit

	mainmenuarr[2].setFont(font);
	mainmenuarr[2].setColor(sf::Color::White);
	mainmenuarr[2].setString("Exit");
	mainmenuarr[2].setCharacterSize(40);
	mainmenuarr[2].setPosition(sf::Vector2f(350, 379));

	mainMenuSelected = 0;
}

//function of drawing mainmenu

void mainmenu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainmenuarr[i]);
	}
}



//move down

void mainmenu::MoveDown()
{
	
		mainmenuarr[mainMenuSelected].setColor(sf::Color::White);
		mainmenuarr[mainMenuSelected].setCharacterSize(40);

		mainMenuSelected++;
		if (mainMenuSelected == 3)
		{
			mainMenuSelected = 0;
		}
		mainmenuarr[mainMenuSelected].setColor(sf::Color::Blue);
		mainmenuarr[mainMenuSelected].setCharacterSize(50);
	
}



//move up
void mainmenu::MoveUp()
{
	
	mainmenuarr[mainMenuSelected].setColor(sf::Color::White);
	mainmenuarr[mainMenuSelected].setCharacterSize(40);
	mainMenuSelected--;
	if (mainMenuSelected == -1)
	{
		mainMenuSelected = 2;
	}
	mainmenuarr[mainMenuSelected].setColor(sf::Color::Blue);
	mainmenuarr[mainMenuSelected].setCharacterSize(50);

	
}