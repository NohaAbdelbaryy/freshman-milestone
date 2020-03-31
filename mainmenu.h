#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Cursor.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#define UNIQUE_mainmenu
#ifndef UNIQUE_mainmenu

#endif // !UNIQUE

#define max_main_menu 3
class  mainmenu

{
private:
	int mainMenuSelected;
	sf::Font font;
	sf::Text mainmenuarr[max_main_menu];

public:
	mainmenu(float width, float height);
	void draw(sf::RenderWindow &window);
	void MoveDown();
	void MoveUp();
	int GetPressedItem()
	{
		return mainMenuSelected;
	}
};