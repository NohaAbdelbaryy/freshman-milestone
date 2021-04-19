#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include "mainmenu.h"
#include <stdlib.h>
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;

Sprite mainplayer;

struct pos {
	int X, Y;
}txtmain, txtmonster1, txtmonster2, monstPos1, monstPos2, friends;

struct velocity {

	float velocityx, velocityy;

};

struct controls {
	bool up, down, left, right, space;
}button;

struct Game {
	bool play = false, guide = false, menuvariable = true;
	bool lvl1 = false, lvl2 = false, win = false, scorewinbool = false;
	bool assignment = false, spoke = false, spoke1 = false, spoke2 = false;
	bool pausevariable = false;
};

void animateSprite(controls buttons, pos& posofsprite, int numSprite)
{
	if (buttons.up)
	{
		posofsprite.Y = 0;
		posofsprite.X++;
	}
	if (buttons.down)
	{
		posofsprite.Y = 1;
		posofsprite.X++;
	}
	if (buttons.left)
	{
		posofsprite.Y = 2;
		posofsprite.X++;
	}
	if (buttons.right)
	{
		posofsprite.Y = 3;
		posofsprite.X++;
	}
	if (posofsprite.X > numSprite)

		posofsprite.X = 0;
}

void stop(velocity velocity, RectangleShape maze[], int sizeofmaze, controls button, pos& posofsprite)
{
	for (int i = 0; i < sizeofmaze; i++)
	{
		if (mainplayer.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.left == true))
		{
			mainplayer.move(velocity.velocityx, 0);
			posofsprite.X = 0;
		}
		if (mainplayer.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.right == true))
		{
			mainplayer.move(-velocity.velocityx, 0);
			posofsprite.X = 0;
		}
		if (mainplayer.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.up == true))
		{
			mainplayer.move(0, velocity.velocityy);
			posofsprite.X = 0;
		}
		if (mainplayer.getGlobalBounds().intersects(maze[i].getGlobalBounds()) && (button.down == true))
		{
			mainplayer.move(0, -velocity.velocityy);
			posofsprite.X = 0;
		}
	}

}

void movePlayer(controls buttons, velocity velocity)
{
	if (buttons.up)
	{
		mainplayer.move(0, -velocity.velocityy);

	}
	if (buttons.down)
	{
		mainplayer.move(0, velocity.velocityy);

	}
	if (buttons.left)
	{
		mainplayer.move(-velocity.velocityx, 0);

	}
	if (buttons.right)
	{
		mainplayer.move(velocity.velocityx, 0);

	}
}

void talk(Sprite& Friend, int& countdialogue, Sprite Dialogue[], int i, controls& buttons, bool& diabool, bool& spoke)
{
	if (mainplayer.getGlobalBounds().intersects(Friend.getGlobalBounds()))
	{
		Friend.setColor(Color(111, 206, 240));


		if (buttons.space)
		{
			spoke = true;
			countdialogue++;
			buttons.space = false;


			switch (countdialogue)

			{
			case 1:Dialogue[i].setColor(Color::White);
				diabool = true;
				break;

			case 2:Dialogue[i + 1].setColor(Color::White);
				Dialogue[i].setColor(Color::Transparent);
				diabool = true;
				break;

			case 3:Dialogue[i + 2].setColor(Color::White);
				Dialogue[i + 1].setColor(Color::Transparent);
				diabool = true;
				break;

			default:Dialogue[i + 2].setColor(Color::Transparent);
				countdialogue = 0;
				diabool = false;
				break;
			}

		}

	}
	else  Friend.setColor(Color::White);
}


void mon(int& timehurt, Clock& clockhurt, int& timeavailable, Text& timescoremin, Text& timescoresec, Text& timercolon, Sound& collision, Sound& YouLose, Music& moonlight)
{

	timehurt = clockhurt.getElapsedTime().asSeconds();
	mainplayer.setColor(Color::Red);
	if (timehurt > 0)
	{
		if (timeavailable < 20 && timeavailable > 10)
		{
			moonlight.stop();
			YouLose.play();
		}
		timeavailable = timeavailable - 10;
		collision.play();
		clockhurt.restart();
	}

	timescoremin.setColor(Color::Red);
	timercolon.setColor(Color::Red);
	timescoresec.setFillColor(Color::Red);


}

void resetPlayer(Text& timescoremin, Text& timescoresec, Text& timercolon)
{
	mainplayer.setColor(Color::White);
	timescoremin.setColor(Color::Black);
	timercolon.setColor(Color::Black);
	timescoresec.setFillColor(Color::Black);
}



void collectitem(Sprite item[], int size, Sound& collect, int extraItem, int& score, bool& found, Sound& assignmentfound, int& BPcount)
{
	for (int j = 0; j < size; j++)
	{
		if (mainplayer.getGlobalBounds().intersects(item[j].getGlobalBounds()))
		{
			item[j].setColor(Color(111, 206, 240));

			if (button.space)
			{
				BPcount++;
				collect.setVolume(100);
				item[j].setPosition(1000, 1000);
				score += 2;

				if (j == extraItem)
				{
					score += 3;
					found = true;
					assignmentfound.setVolume(100);
					assignmentfound.play();
					cout << "assignment found";
				}
				else collect.play();
			}

		}
		else item[j].setColor(Color::White);
	}
}
void monpath1(Sprite& monster1, velocity& monster1velocity, int countMon1)
{
	pos monstPos1;

	if (countMon1 % 2 == 0)
	{


		monster1velocity.velocityx = 4;
		monster1velocity.velocityy = 0;
		monstPos1.X = monster1.getPosition().x;
		if (monstPos1.X > 600)
			monster1velocity.velocityx = -monster1velocity.velocityx;

	}

	else {
		monster1velocity.velocityx = 0;
		monster1velocity.velocityy = 4;
		monstPos1.Y = monster1.getPosition().y;
		if (monstPos1.Y > 70)
			monster1velocity.velocityy = -monster1velocity.velocityy;


	}


}
void monpath2(Sprite& monster1, velocity& monster1velocity, int countMon1)
{
	pos monstPos1;
	if (countMon1 % 2 == 0)
	{

		monster1velocity.velocityx = -4;
		monster1velocity.velocityy = 0;
		monstPos1.Y = monster1.getPosition().y;

		if (monstPos1.Y > 400)
			monster1velocity.velocityx = -monster1velocity.velocityx;

	}

	else
	{
		monster1velocity.velocityx = 0;
		monster1velocity.velocityy = 4;
		monstPos1.X = monster1.getPosition().x;
		if (monstPos1.X > 480)
			monster1velocity.velocityy = -monster1velocity.velocityy;

	}

}
;
Text setText(Font& font, int size, int posX, int posY)
{
	Text text;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(Color::Black);
	text.setPosition(posX, posY);


	return text;
}

void reset(Game& booleans, Sprite backpack[], int& score, int& assignmentBP, int& timeavailable,
	int& timelost, int countDialogue[], Text& timescoresec, Text& timescoremin, Text& timercolon,
	Font& font8, int fontsize, Sprite& friend1, Sprite& friend2, int& timegamed, Sprite tick[],
	Sprite cross[], int size, Text& HighScore, Text& scoreText, Text& wintext, int& countBP)
{
	cout << "reset is done";
	booleans.play = false;
	booleans.menuvariable = true;
	timeavailable = 182;
	timegamed = 0;
	timelost = 5;
	booleans.lvl2 = false;
	booleans.assignment = false;
	booleans.win = false;
	booleans.scorewinbool = false;
	booleans.spoke = false;
	booleans.spoke1 = false;
	booleans.spoke2 = false;
	countDialogue[2] = 0;
	countBP = 0;

	mainplayer.setPosition(700, 565);
	mainplayer.setColor(Color::White);
	friend1.setPosition(327, 10);
	friend2.setPosition(403, 10);
	friend1.setScale(1, 1);
	friend2.setScale(1, 1);

	scoreText.setColor(Color::Transparent);
	HighScore.setColor(Color::Transparent);
	wintext.setColor(Color::Transparent);

	timescoresec = setText(font8, 35, 83, 507);
	timescoresec.setString(" ");


	timercolon = setText(font8, 35, 68, 507);
	timercolon.setString(" ");


	timescoremin = setText(font8, 35, 48, 507);
	timescoremin.setString("Time till lecture!!");

	for (int size = 0; size < 4; size++)
	{
		cross[size].setColor(Color::Transparent);
	}

	for (int size = 0; size < 4; size++)
	{
		tick[size].setColor(Color::Transparent);
	}

	backpack[0].setPosition(sf::Vector2f(550, 225));
	backpack[1].setPosition(sf::Vector2f(650, 25));
	backpack[1].setScale(0.035, 0.035);
	backpack[2].setPosition(sf::Vector2f(650, 225));
	backpack[3].setPosition(sf::Vector2f(60, 35));
	backpack[4].setPosition(sf::Vector2f(700, 395));
	score = 0;
	srand(time(NULL));
	assignmentBP = rand() % 5;
	cout << " the bag has index: " << assignmentBP << endl;
}
int main()
{

	//creating a window

	RenderWindow window(VideoMode(800, 600), "first game");
	window.setFramerateLimit(60);


	//mainmenu window
	mainmenu menu(600, 600);
	//pause 
	mainmenu pause(600, 600);

	//shapes
	RectangleShape maze1[35], maze2[40];
	CircleShape mazeMon1, mazeMon2;

	mazeMon2.setRadius(5);
	mazeMon2.setFillColor(Color::Magenta);

	mazeMon1.setRadius(5);
	mazeMon1.setFillColor(Color::Blue);

	//music
	Music moonlight;
	if (moonlight.openFromFile("freshmen milestone/sounds/moonlight.WAV") == false)
	{
		cout << "loaded";
	}

	moonlight.play();
	moonlight.setVolume(0);
	moonlight.setLoop(true);


	SoundBuffer collectBuff;
	if (!collectBuff.loadFromFile("freshmen milestone/sounds/collect.WAV"))
	{
		cout << "not loaded";
	}

	Sound collect;
	collect.setBuffer(collectBuff);


	SoundBuffer assignmentBuff;
	if (!assignmentBuff.loadFromFile("freshmen milestone/sounds/assignment.WAV"))
	{
		cout << "not loaded";
	}

	Sound assignment;
	assignment.setBuffer(assignmentBuff);

	SoundBuffer youLoseBuff;
	if (!youLoseBuff.loadFromFile("freshmen milestone/sounds/lose.WAV"))
	{
		cout << "not loaded";
	}

	Sound YouLose;
	YouLose.setBuffer(youLoseBuff);
	moonlight.setVolume(2);
	SoundBuffer monsterBuff;
	if (!monsterBuff.loadFromFile("freshmen milestone/sounds/ouch.WAV"))
	{
		cout << "not loaded";
	}

	Sound monsterColl;
	monsterColl.setBuffer(monsterBuff);

	//maze1 settiing

	maze1[0].setPosition(Vector2f(190, 220));	maze1[0].setSize(Vector2f(10, 130));

	maze1[1].setPosition(Vector2f(70, 298));	maze1[1].setSize(Vector2f(45, 130));

	maze1[2].setPosition(Vector2f(117, 200));	maze1[2].setSize(Vector2f(1, 1));

	maze1[3].setPosition(Vector2f(45, 0));		maze1[3].setSize(Vector2f(10, 245));

	maze1[4].setPosition(Vector2f(45, 310));	maze1[4].setSize(Vector2f(10, 210));

	maze1[5].setPosition(Vector2f(45, 405));	maze1[5].setSize(Vector2f(407, 138));

	maze1[6].setPosition(Vector2f(65, 115));	maze1[6].setSize(Vector2f(265, 90));

	maze1[7].setPosition(Vector2f(45, 115));	maze1[7].setSize(Vector2f(15, 125));

	maze1[8].setPosition(Vector2f(200, 335));	maze1[8].setSize(Vector2f(195, 15));

	maze1[9].setPosition(Vector2f(470, 405));	maze1[9].setSize(Vector2f(35, 20));

	maze1[10].setPosition(Vector2f(410, 115));	maze1[10].setSize(Vector2f(285, 90));

	maze1[11].setPosition(Vector2f(275, 275));	maze1[11].setSize(Vector2f(190, 8));

	maze1[12].setPosition(Vector2f(480, 275));	maze1[12].setSize(Vector2f(95, 8));

	maze1[13].setPosition(Vector2f(700, 220));	maze1[13].setSize(Vector2f(15, 110));

	maze1[14].setPosition(Vector2f(595, 220));	maze1[14].setSize(Vector2f(15, 40));

	maze1[15].setPosition(Vector2f(510, 355));	maze1[15].setSize(Vector2f(210, 30));

	maze1[16].setPosition(Vector2f(627, 435));	maze1[16].setSize(Vector2f(187, 108));

	maze1[17].setPosition(Vector2f(710, 240));	maze1[17].setSize(Vector2f(20, 130));

	maze1[18].setPosition(Vector2f(775, 115));	maze1[18].setSize(Vector2f(20, 75));

	maze1[30].setPosition(Vector2f(465, 535));	maze1[30].setSize(Vector2f(158, 10));

	maze1[34].setPosition(Vector2f(465, 540));	maze1[34].setSize(Vector2f(158, 10));

	maze1[33].setPosition(Vector2f(465, 525));	maze1[33].setSize(Vector2f(158, 10));
	//garden


	maze1[19].setPosition(Vector2f(786, 30));	maze1[19].setSize(Vector2f(15, 70));

	maze1[20].setPosition(Vector2f(693, 75));	maze1[20].setSize(Vector2f(3, 46));

	maze1[21].setPosition(Vector2f(555, 75));	maze1[21].setSize(Vector2f(3, 46));

	maze1[22].setPosition(Vector2f(473, 28));	maze1[22].setSize(Vector2f(2, 23));

	maze1[23].setPosition(Vector2f(473, 100));	maze1[23].setSize(Vector2f(2, 17));

	maze1[24].setPosition(Vector2f(410, 5));	maze1[24].setSize(Vector2f(6, 46));

	maze1[25].setPosition(Vector2f(627, 20));	maze1[25].setSize(Vector2f(3, 46));

	maze1[26].setPosition(Vector2f(639, 5));	maze1[26].setSize(Vector2f(70, 17));

	maze1[27].setPosition(Vector2f(568, 5));	maze1[27].setSize(Vector2f(70, 17));

	maze1[28].setPosition(Vector2f(715, 5));	maze1[28].setSize(Vector2f(70, 17));

	maze1[29].setPosition(Vector2f(490, 5));	maze1[29].setSize(Vector2f(70, 17));

	maze1[32].setPosition(Vector2f(332, 15));	maze1[32].setSize(Vector2f(2, 12));

	maze1[31].setPosition(Vector2f(147, 72));	maze1[31].setSize(Vector2f(2, 11));



	//Maze 2 setting

	maze2[0].setPosition(Vector2f(0, 0));		maze2[0].setSize(Vector2f(42, 65));

	maze2[1].setPosition(Vector2f(42, 0));		maze2[1].setSize(Vector2f(27, 144));

	maze2[2].setPosition(Vector2f(69, 0));		maze2[2].setSize(Vector2f(299, 65));

	maze2[3].setPosition(Vector2f(368, 37));	maze2[3].setSize(Vector2f(67, 28));

	maze2[4].setPosition(Vector2f(529, 37));	maze2[4].setSize(Vector2f(125, 28));

	maze2[5].setPosition(Vector2f(654, 22));	maze2[5].setSize(Vector2f(146, 43));

	maze2[6].setPosition(Vector2f(741, 0));		maze2[6].setSize(Vector2f(59, 22));

	maze2[7].setPosition(Vector2f(65, 131));	maze2[7].setSize(Vector2f(103, 69));

	maze2[8].setPosition(Vector2f(262, 107));	maze2[8].setSize(Vector2f(374, 8));

	maze2[9].setPosition(Vector2f(262, 115));	maze2[9].setSize(Vector2f(179, 63));

	maze2[10].setPosition(Vector2f(513, 115));	maze2[10].setSize(Vector2f(123, 50));

	maze2[11].setPosition(Vector2f(741, 67));	maze2[11].setSize(Vector2f(4, 185));

	maze2[12].setPosition(Vector2f(747, 73));	maze2[12].setSize(Vector2f(19, 71));

	maze2[13].setPosition(Vector2f(262, 178));	maze2[13].setSize(Vector2f(8, 82));

	maze2[14].setPosition(Vector2f(477, 218));	maze2[14].setSize(Vector2f(208, 9));

	maze2[15].setPosition(Vector2f(677, 227));	maze2[15].setSize(Vector2f(8, 44));

	maze2[16].setPosition(Vector2f(683, 265));	maze2[16].setSize(Vector2f(62, 6));

	maze2[17].setPosition(Vector2f(65, 260));	maze2[17].setSize(Vector2f(4, 280));

	maze2[18].setPosition(Vector2f(70, 260));	maze2[18].setSize(Vector2f(343, 8));

	maze2[19].setPosition(Vector2f(206, 269));	maze2[19].setSize(Vector2f(394, 36));

	maze2[20].setPosition(Vector2f(69, 331));	maze2[20].setSize(Vector2f(68, 7));

	maze2[21].setPosition(Vector2f(165, 384));	maze2[21].setSize(Vector2f(7, 69));

	maze2[22].setPosition(Vector2f(172, 384));	maze2[22].setSize(Vector2f(363, 7));

	maze2[23].setPosition(Vector2f(172, 446));	maze2[23].setSize(Vector2f(154, 7));

	maze2[24].setPosition(Vector2f(459, 391));	maze2[24].setSize(Vector2f(7, 55));

	maze2[25].setPosition(Vector2f(528, 347));	maze2[25].setSize(Vector2f(7, 44));

	maze2[26].setPosition(Vector2f(535, 347));	maze2[26].setSize(Vector2f(210, 9));

	maze2[27].setPosition(Vector2f(741, 356));	maze2[27].setSize(Vector2f(4, 177));

	maze2[28].setPosition(Vector2f(519, 435));	maze2[28].setSize(Vector2f(222, 7));

	maze2[29].setPosition(Vector2f(729, 442));	maze2[29].setSize(Vector2f(12, 67));

	maze2[30].setPosition(Vector2f(552, 498));	maze2[30].setSize(Vector2f(177, 35));

	maze2[31].setPosition(Vector2f(745, 463));	maze2[31].setSize(Vector2f(23, 70));

	maze2[32].setPosition(Vector2f(43, 463));	maze2[32].setSize(Vector2f(27, 70));

	maze2[33].setPosition(Vector2f(70, 498));	maze2[33].setSize(Vector2f(351, 35));

	maze2[34].setPosition(Vector2f(0, 540));	maze2[34].setSize(Vector2f(70, 60));

	maze2[35].setPosition(Vector2f(70, 540));	maze2[35].setSize(Vector2f(88, 27));

	maze2[36].setPosition(Vector2f(663, 540));	maze2[36].setSize(Vector2f(67, 27));

	maze2[37].setPosition(Vector2f(635, 570));	maze2[37].setSize(Vector2f(10, 45));

	maze2[38].setPosition(Vector2f(0, 200));	maze2[38].setSize(Vector2f(70, 69));

	maze2[39].setPosition(Vector2f(634, 570));	maze2[39].setSize(Vector2f(15, 45));


	//monster collision

	pos mazemon1[24] = { /*1*/{105,470},/*2*/{105,331},/*3*/{365,331},/*4*/{365,300},/*5*/{750,300},/*6*/{750,260},
		/*7*/{635,270},/*8*/{635,215},/*9*/{300,215},/*10*/{300,180},/*11*/{700,180},/*12*/{700,70},/*13*/{460,70},
		/*14*/{460, 30},/*15*/{475, 30},/*16*/{475,90},/*17*/{200,90},/*18*/{200,240},/*19*/{12,240},/*20*/{12,430},
		/*21*/{30,430},/*22*/{30,570},/*23*/{510,570},/*24*/{510,450} };


	mazeMon1.setPosition(Vector2f(mazemon1[0].X, mazemon1[0].Y));
	mazeMon2.setPosition(Vector2f(mazemon1[15].X, mazemon1[15].Y));




	// Setting a transparent color for accuracy 

	for (int i = 0; i < 35; i++)
	{
		maze1[i].setFillColor(Color(100, 50, 200, 150));
	}
	maze1[30].setFillColor(Color::Red);


	for (int i = 0; i < 39; i++)
	{
		maze2[i].setFillColor(Color(100, 50, 200, 150));
	}

	//maze2[32].setFillColor(Color::Red);
	maze2[38].setFillColor(Color::Red);

	//player

	Texture mainptxt;

	if (!mainptxt.loadFromFile("freshmen milestone/sprites/boy5.png"))
		cout << "loaded";

	Texture friend1txt;
	if (!friend1txt.loadFromFile("freshmen milestone/sprites/boy1cr.png"))
		cout << " not loaded \n";

	Texture friend2txt;
	if (!friend2txt.loadFromFile("freshmen milestone/sprites/boy2cr.png"))
		cout << " not loaded \n";

	Texture friend3txt;
	if (!friend3txt.loadFromFile("freshmen milestone/sprites/girl3cr.png"))
		cout << " not loaded \n";

	Texture friend4txt;
	if (!friend4txt.loadFromFile("freshmen milestone/sprites/girl1cr.png"))
		cout << " not loaded \n";

	Texture assignmenttxt;
	if (!assignmenttxt.loadFromFile("freshmen milestone/misc/assignment.png"))
		cout << " not loaded \n";

	Texture clocktxt;
	if (!clocktxt.loadFromFile("freshmen milestone/misc/clock.png"))
		cout << " not loaded \n";

	Sprite assignmentsp;								Sprite scoreclocksp;
	assignmentsp.setPosition(0, 0);						scoreclocksp.setPosition(83, 197);
	assignmentsp.setTexture(assignmenttxt);				scoreclocksp.setTexture(clocktxt);


	Texture crosstxt;
	if (!crosstxt.loadFromFile("freshmen milestone/misc/cross.png"))
		cout << " not loaded \n";

	Texture ticktxt;
	if (!ticktxt.loadFromFile("freshmen milestone/misc/tick.png"))
		cout << " not loaded \n";

	Sprite cross[4];					Sprite tick[4];
	cross[0].setPosition(396, 297);		tick[0].setPosition(396, 297);
	cross[1].setPosition(522, 297);		tick[1].setPosition(522, 297);
	cross[2].setPosition(668, 297);		tick[2].setPosition(668, 297);

	for (int j = 0; j < 4; j++)
	{
		tick[j].setTexture(ticktxt);
		tick[j].setScale(1.5, 1.5);
		tick[j].setColor(Color::Transparent);
	}

	for (int i = 0;i < 4;i++)
	{
		cross[i].setTexture(crosstxt);
		cross[i].setScale(0.1, 0.1);
		cross[i].setColor(Color::Transparent);
	}


	Texture end, end1, end2, end3;

	if (!end.loadFromFile("freshmen milestone/misc/lvl1end.png"))
		cout << " not loaded";
	if (!end1.loadFromFile("freshmen milestone/misc/Arrow1.png"))
		cout << " not loaded";
	if (!end2.loadFromFile("freshmen milestone/misc/Arrow2.png"))
		cout << " not loaded";
	if (!end3.loadFromFile("freshmen milestone/misc/Arrow3.png"))
		cout << " not loaded";

	Sprite arrLvl1, arrLvl2_1, arrLvl2_2, arrLvl2_3;

	arrLvl1.setTexture(end);				arrLvl2_1.setTexture(end1);
	arrLvl1.setPosition(470, 480);			arrLvl2_1.setPosition(738, 280);
	arrLvl2_1.setColor(Color::White);

	arrLvl2_2.setTexture(end2);				arrLvl2_3.setTexture(end3);
	arrLvl2_2.setPosition(450, 15);			arrLvl2_3.setPosition(20, 200);
	arrLvl2_2.setColor(Color::White);		arrLvl2_3.setColor(Color::White);

	//Sprite mainplayer;


	mainplayer.setTexture(mainptxt);
	mainplayer.setPosition(Vector2f(700, 565));

	// NPC Sprites
	Sprite friend1;
	friend1.setTexture(friend1txt);
	friend1.setPosition(327, 10);

	Sprite friend2;
	friend2.setTexture(friend2txt);
	friend2.setPosition(403, 10);

	Sprite friend3;
	friend3.setTexture(friend3txt);
	friend3.setPosition(145, 69);

	Sprite friend4;
	friend4.setTexture(friend4txt);
	friend4.setPosition(630, 570);


	// monster 
	Texture monster1txt;
	if (!monster1txt.loadFromFile("freshmen milestone/sprites/monster1.png"))
		cout << "not loaded \n;";
	Texture monster2txt;
	if (!monster2txt.loadFromFile("freshmen milestone/sprites/monster2.png"))
		cout << "not loaded \n;";

	Sprite monster1;
	monster1.setTexture(monster1txt);
	monster1.setPosition(710, 463);

	Sprite monster2;
	monster2.setTexture(monster2txt);
	monster2.setPosition(460, 30);
	// set a mainmenu background

	Texture backgroundmaintxt;
	if (!backgroundmaintxt.loadFromFile("freshmen milestone/backgrounds/mainmenu.png"))
		cout << "not loaded/n";

	Sprite backgroundmain;
	Vector2u size_ = backgroundmaintxt.getSize();
	backgroundmain.setTexture(backgroundmaintxt);

	//set a background to level 1

	Texture backgroundtxt1;

	if (!backgroundtxt1.loadFromFile("freshmen milestone/backgrounds/background1.png"))
		cout << "loaded";

	Sprite background1;
	Vector2u size1 = backgroundtxt1.getSize();
	background1.setTexture(backgroundtxt1);

	//set a background to level 2 

	Texture backgroundtxt2;

	if (!backgroundtxt2.loadFromFile("freshmen milestone/backgrounds/background2.png"))
		cout << "loaded";

	Sprite background2;
	Vector2u size2 = backgroundtxt2.getSize();
	background2.setTexture(backgroundtxt2);


	//set guide window

	Texture guidetxt;

	if (!guidetxt.loadFromFile("freshmen milestone/backgrounds/Guide.png"))
		cout << "loaded";

	Sprite guide;
	Vector2u sizeg = guidetxt.getSize();
	guide.setTexture(guidetxt);


	//set score window

	Texture scoretxt;

	if (!scoretxt.loadFromFile("freshmen milestone/backgrounds/score.png"))
		cout << "loaded";

	Sprite scorewin;
	Vector2u sizef = scoretxt.getSize();
	scorewin.setTexture(scoretxt);

	//Clock Setting

	Clock clock1, clock2, clocklost, clockhurt, clockgamed;
	int timeavailable = 182;
	int timelost = 5, timehurt = 0, timewon = 0, timegamed = 0;
	int timesec = timeavailable % 60, timemin = timeavailable / 60;
	ostringstream convert;
	convert << timesec, timemin, timeavailable;
	String timestring = convert.str();

	// variables

	pos mainpos;
	velocity mainvelocity = { 3,3 }, monster1velocity = { -4,0 }, monster2velocity = { 0,4 };

	txtmonster1.X = 1;
	txtmonster2.X = 1;
	Game booleans;



	int countDialogue[4] = {};
	bool monologue = false, diabool = false, security = false, security2 = false, pauseGuide = false;
	int BPcount = 0;


	bool move = true;

	srand(time(NULL));
	int assignmentBP = rand() % 5;

	cout << " the bag has index: " << assignmentBP << endl;

	int highscore = 0;
	int score = 0;
	int countMon1 = 0, countMon2 = 14;



	//Font

	Font font8;
	if (!font8.loadFromFile("freshmen milestone/8font.otf"))
		cout << "font not loaded\n";


	//Text 

	Text timescoresec = setText(font8, 35, 83, 507);
	timescoresec.setString(" ");


	Text timercolon = setText(font8, 35, 68, 507);
	timercolon.setString(" ");


	Text timescoremin = setText(font8, 35, 48, 507);
	timescoremin.setString("Time till lecture!!");

	Text scoreText = setText(font8, 20, 60, 5);
	scoreText.setString("  ");
	scoreText.setColor(Color::Transparent);


	Text HighScore;
	HighScore = setText(font8, 35, 300, 300);
	HighScore.setColor(Color::Transparent);

	Text guidetext = setText(font8, 50, 336, 505);
	guidetext.setString("BACK");

	Text wintext;

	Text timewontxt = setText(font8, 50, 83, 297);
	timewontxt.setColor(Color::Transparent);


	Text BPcountxt = setText(font8, 50, 230, 297);
	BPcountxt.setColor(Color::Transparent);
	convert << BPcount;
	string BPstring = convert.str();



	Text skipwintext = setText(font8, 27, 411, 511);
	skipwintext.setString("Press space to skip . . .");
	skipwintext.setColor(Color(255, 255, 255, 150));


	//textures

	Texture backpacktxt;

	if (!backpacktxt.loadFromFile("freshmen milestone/sprites/backpack.png"))
		cout << "loaded";

	Texture Monologue2txt;
	if (!Monologue2txt.loadFromFile("freshmen milestone/dialogue/friend4-1.png")) cout << "DialogueFail";

	Texture dialoguetxt[14];
	if (!dialoguetxt[0].loadFromFile("freshmen milestone/dialogue/main1.png")) cout << "DialogueFail";
	if (!dialoguetxt[1].loadFromFile("freshmen milestone/dialogue/friend1-1.png")) cout << "DialogueFail";
	if (!dialoguetxt[2].loadFromFile("freshmen milestone/dialogue/main2.png")) cout << "DialogueFail";
	if (!dialoguetxt[3].loadFromFile("freshmen milestone/dialogue/friend1-2.png")) cout << "DialogueFail";
	if (!dialoguetxt[4].loadFromFile("freshmen milestone/dialogue/main3.png")) cout << "DialogueFail";
	if (!dialoguetxt[5].loadFromFile("freshmen milestone/dialogue/friend2-1.png")) cout << "DialogueFail";
	if (!dialoguetxt[6].loadFromFile("freshmen milestone/dialogue/friend2-2.png")) cout << "DialogueFail";
	if (!dialoguetxt[7].loadFromFile("freshmen milestone/dialogue/main4.png")) cout << "DialogueFail";
	if (!dialoguetxt[8].loadFromFile("freshmen milestone/dialogue/friend3-1.png")) cout << "DialogueFail";
	if (!dialoguetxt[9].loadFromFile("freshmen milestone/dialogue/main5.png")) cout << "DialogueFail";
	if (!dialoguetxt[10].loadFromFile("freshmen milestone/dialogue/friend3-2.png")) cout << "DialogueFail";
	if (!dialoguetxt[11].loadFromFile("freshmen milestone/dialogue/main6.png")) cout << "DialogueFail";
	if (!dialoguetxt[12].loadFromFile("freshmen milestone/dialogue/friend3-3.png")) cout << "DialogueFail";
	if (!dialoguetxt[13].loadFromFile("freshmen milestone/dialogue/Security.png")) cout << "DialogueFail";


	//setting textures

	Sprite backpack[5];

	for (int j = 0; j < 5; j++)
	{
		backpack[j].setTexture(backpacktxt);
		backpack[j].setScale(sf::Vector2f(0.035f, 0.035f));

	}

	Sprite dialogue[14];

	for (int j = 0; j < 14; j++)
	{
		dialogue[j].setTexture(dialoguetxt[j]);
		dialogue[j].setPosition(sf::Vector2f(0, 0));
		dialogue[j].setColor(sf::Color::Transparent);
	}

	Sprite Monologue2;

	Monologue2.setTexture(Monologue2txt);
	Monologue2.setPosition(sf::Vector2f(0, 0));
	Monologue2.setColor(sf::Color::Transparent);


	//setting initial position & size


	backpack[0].setPosition(sf::Vector2f(550, 225));
	backpack[1].setPosition(sf::Vector2f(650, 25));
	backpack[2].setPosition(sf::Vector2f(650, 225));
	backpack[3].setPosition(sf::Vector2f(60, 35));
	backpack[4].setPosition(sf::Vector2f(700, 395));



	//game loop

	while (window.isOpen())
	{

		Event event;

		while (window.pollEvent(event))
		{

			if (booleans.menuvariable)
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
					if (event.key.code == Keyboard::Return)
					{
						switch (menu.GetPressedItem())
						{
						case 0:
							cout << "play button has been pressed" << endl;
							booleans.play = true;
							booleans.lvl1 = true;
							booleans.menuvariable = false;
							break;
						case 1:
							cout << "option button has been pressed" << endl;
							booleans.guide = true;
							booleans.menuvariable = false;

							break;
						case 2:
							window.close();
						}
					}

				}
			}

			//pause game

			if (booleans.play)
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::P)
					{
						booleans.pausevariable = true;


					}

				}
			}
			if (booleans.pausevariable)
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Up)
					{
						pause.MoveUp();
						break;
					}

					if (event.key.code == Keyboard::Down)
					{
						pause.MoveDown();
						break;
					}
					if (event.key.code == Keyboard::Return)
					{
						switch (pause.GetPressedItem())
						{
						case 0:
							cout << "play " << endl;
							booleans.pausevariable = false;
							break;
						case 1:
							cout << "option" << endl;
							booleans.guide = true;
							booleans.pausevariable = false;
							pauseGuide = true;
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

			if (booleans.play == true)

			{

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

			if (booleans.guide)
			{
				if (event.key.code == Keyboard::Left)
				{
					if (pauseGuide)
					{
						pauseGuide = false;
						booleans.pausevariable = true;
						booleans.guide = false;
					}
					else booleans.menuvariable = true;
					booleans.guide = false;
				}
			}

		}


		mainplayer.setTextureRect(IntRect(txtmain.X * 33, (txtmain.Y * 34) + 3, 33, 34));
		friend1.setTextureRect(IntRect(24 * friends.X, 1, 24, 34));
		friend2.setTextureRect(IntRect(24 * friends.X, 1, 24, 34));
		friend3.setTextureRect(IntRect(24 * friends.X, 1, 24, 34));
		friend4.setTextureRect(IntRect(24 * friends.X, 1, 24, 34));
		scoreclocksp.setTextureRect(IntRect(20 * friends.X, 2, 18, 17));


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
		if (!booleans.pausevariable)
		{

			if (monologue == false && diabool == false)
			{
				movePlayer(button, mainvelocity);

				//animating sprite

				animateSprite(button, txtmain, 2);
			}

			//code of functions in level 1 only	

			if (booleans.lvl1)
			{
				stop(mainvelocity, maze1, 33, button, txtmain);


				talk(friend1, countDialogue[0], dialogue, 1, button, diabool, booleans.spoke1);


				talk(friend2, countDialogue[1], dialogue, 4, button, diabool, booleans.spoke2);


				if (countDialogue[2] >= 3)
				{

					talk(friend3, countDialogue[3], dialogue, 10, button, diabool, booleans.spoke);

					if (countDialogue[3] == 1)

						dialogue[9].setColor(Color::Transparent);

				}
				else
				{
					talk(friend3, countDialogue[2], dialogue, 7, button, diabool, booleans.spoke);
				}



				if (mainplayer.getGlobalBounds().intersects(maze1[34].getGlobalBounds()))
				{
					dialogue[13].setColor(Color::White);
					security = true;
				}
				else
				{
					security = false;
					dialogue[13].setColor(Color::Transparent);
				}

				if (booleans.spoke)
					collectitem(backpack, 5, collect, assignmentBP, score, booleans.assignment, assignment, BPcount);


				//TRANSITION TO LEVEL 2
				if (mainplayer.getGlobalBounds().intersects(maze1[33].getGlobalBounds()) && booleans.assignment)
				{
					booleans.lvl1 = false;
					booleans.lvl2 = true;
					mainplayer.setPosition(Vector2f(605, 575));
				}


			}

			//code of functions in level 2 only

			else if (booleans.lvl2)
			{

				if (mainplayer.getGlobalBounds().intersects(maze2[39].getGlobalBounds()))
				{
					Monologue2.setColor(Color::White);
					security2 = true;
				}
				else
				{
					Monologue2.setColor(Color::Transparent);
					security2 = false;
				}


				monster1.setTextureRect(IntRect(29 * txtmonster1.X, txtmonster1.Y * 34, 29, 34));
				monster2.setTextureRect(IntRect(txtmonster2.X * 28 + 5, txtmonster2.Y * 34, 28, 34));

				stop(mainvelocity, maze2, 38, button, txtmain);

				if (!booleans.win && timeavailable > 1)
				{
					if (monster1.getGlobalBounds().intersects(mainplayer.getGlobalBounds()) && timeavailable > 10)
						mon(timehurt, clockhurt, timeavailable, timescoremin, timescoresec, timercolon, monsterColl, YouLose, moonlight);

					else if (monster2.getGlobalBounds().intersects(mainplayer.getGlobalBounds()) && timeavailable > 10)
						mon(timehurt, clockhurt, timeavailable, timescoremin, timescoresec, timercolon, monsterColl, YouLose, moonlight);
					else
						resetPlayer(timescoremin, timescoresec, timercolon);
				}


				if (monster1.getGlobalBounds().intersects(maze2[29].getGlobalBounds()))
					monster1velocity.velocityx = -4;

				if (monster2.getGlobalBounds().intersects(maze2[29].getGlobalBounds()))
					monster2velocity.velocityx = -4;





				if (monster1.getGlobalBounds().intersects(mazeMon1.getGlobalBounds()))
				{
					countMon1++;

					if (countMon1 == 24)
						countMon1 = 0;


					mazeMon1.setPosition(Vector2f(mazemon1[countMon1].X, mazemon1[countMon1].Y));


					//cout << "counter 1 is:" << countMon1 << endl;


					if (countMon1 > 15)
					{
						monpath2(monster1, monster1velocity, countMon1);
					}
					else
					{

						monpath1(monster1, monster1velocity, countMon1);
					}

				}



				if (monster1velocity.velocityy > 0)
					txtmonster1.Y = 0;

				if (monster1velocity.velocityx < 0)
					txtmonster1.Y = 1;

				if (monster1velocity.velocityx > 0)
					txtmonster1.Y = 2;

				if (monster1velocity.velocityy < 0)
					txtmonster1.Y = 3;




				monster1.move(monster1velocity.velocityx, monster1velocity.velocityy);
				monster2.move(monster2velocity.velocityx, monster2velocity.velocityy);


				if (txtmonster1.X == 2)
					txtmonster1.X = 1;
				else
					txtmonster1.X = 2;

				if (txtmonster2.X == 2)
					txtmonster2.X = 1;
				else
					txtmonster2.X = 2;

				// monster 2 movement


				if (monster2.getGlobalBounds().intersects(mazeMon2.getGlobalBounds()))
				{
					countMon2++;
					if (countMon2 == 24)
					{
						countMon2 = 0;

					}

					//cout << "counter 2 is:" << countMon2 << endl;

					mazeMon2.setPosition(Vector2f(mazemon1[countMon2].X, mazemon1[countMon2].Y));



					if (countMon2 > 15)
					{
						monpath2(monster2, monster2velocity, countMon2);
					}


					else

					{
						monpath1(monster2, monster2velocity, countMon2);
					}

				}
				if (monster2velocity.velocityy > 0)
					txtmonster2.Y = 0;

				if (monster2velocity.velocityx < 0)
					txtmonster2.Y = 1;

				if (monster2velocity.velocityx > 0)
					txtmonster2.Y = 2;

				if (monster2velocity.velocityy < 0)
					txtmonster2.Y = 3;

				//finish line

				if (mainplayer.getGlobalBounds().intersects(maze2[38].getGlobalBounds()))
				{
					timewon = timeavailable;
					booleans.win = true;
					timescoremin.setColor(Color::Transparent);
					timercolon.setColor(Color::Transparent);
					timescoresec.setColor(Color::Transparent);
				}



			}

			float timergamed = clockgamed.getElapsedTime().asSeconds();

			if (booleans.scorewinbool)
			{

				backpack[1].setPosition(230, 187);		backpack[1].setScale(0.13, 0.13);
				friend1.setPosition(522, 187);			friend1.setScale(3, 3);
				friend2.setPosition(668, 187);			friend2.setScale(3, 3);
				scoreclocksp.setScale(3, 3);

				BPcountxt.setString(to_string(BPcount));
				cout << timegamed << endl;

				if (button.space && timegamed < 20)
				{
					timegamed = 20;
					cout << "space is working";
				}

				if (timergamed > 0.6)
				{
					cout << timegamed << endl;
					timegamed++;


					if (timegamed == 1)
					{
						timewontxt.setString(to_string(timewon));

					}

					if (timegamed >= 1)
					{

						timewontxt.setColor(Color::White);
					}

					if (timegamed >= 2)
						BPcountxt.setColor(Color::White);

					if (timegamed >= 3)
					{
						if (booleans.assignment)
							tick[0].setColor(Color::White);
						else
							cross[0].setColor(Color::White);

					}

					if (timegamed >= 4)
					{
						if (booleans.spoke1)
							tick[1].setColor(Color::White);
						else
							cross[1].setColor(Color::White);
					}

					if (timegamed >= 5)
					{
						if (booleans.spoke2)
							tick[2].setColor(Color::White);
						else
							cross[2].setColor(Color::White);

						score += timeavailable;
						timeavailable = 0;
					}

					if (timegamed >= 6)
					{
						scoreText.setColor(Color::Blue);

					}

					if (timegamed >= 7)
					{
						HighScore.setColor(Color::Blue);
					}


					if (timegamed % 2 == 0)
					{
						skipwintext.setColor(Color::Black);
					}
					else
						skipwintext.setColor(Color(255, 255, 255, 150));



					if (timegamed == 25)
					{
						reset(booleans, backpack, score, assignmentBP, timeavailable, timelost,
							countDialogue, timescoresec, timescoremin, timercolon, font8, 35,
							friend1, friend2, timegamed, tick, cross, 4, HighScore, scoreText, wintext, BPcount);
						moonlight.play();
						YouLose.stop();
					}



					clockgamed.restart();
				}



			}

			//MONOLOGUE
			if (booleans.play)
			{
				if (timeavailable == 182)

				{
					monologue = true;
					dialogue[0].setPosition(Vector2f(0, 0));
					dialogue[0].setColor(Color::White);
				}
				if (button.space)
				{
					dialogue[0].setColor(Color::Transparent);
					monologue = false;
				}
			}


			int timer = clock1.getElapsedTime().asSeconds();
			int timerlost = clocklost.getElapsedTime().asSeconds();


			//Timer
			if (timer > 0)
			{
				if (timeavailable == 11)
				{
					moonlight.stop();
					YouLose.play();
				}
				else if (booleans.win && timeavailable < 10)
				{
					YouLose.stop();
					moonlight.play();
				}
			}

			if (booleans.play == true && monologue == false && diabool == false && security == false && security2 == false)
			{
				if (timer > 0 && timeavailable > 0 && booleans.win == false)
				{

					--timeavailable;


					timesec = timeavailable % 60, timemin = timeavailable / 60;
					timescoremin.setString(to_string(timemin));
					timercolon.setString(":");
					timescoresec.setString(to_string(timesec));


					clock1.restart();
				}

				if (timeavailable > 181)
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


				//LOSE COND.

				if (timerlost > 0 && timeavailable < 1 && booleans.win == false)
				{
					timelost--;

					if (timelost % 2 == 0)
					{
						timescoremin.setPosition(Vector2f(200, 300));
						timescoremin.setFillColor(Color::White);
						timescoremin.setCharacterSize(56);
					}
					else
					{
						timescoremin.setPosition(Vector2f(150, 300));
						timescoremin.setFillColor(Color::Red);
						timescoremin.setCharacterSize(70);
					}

					clocklost.restart();
				}
				if (timerlost > 0 && booleans.win == true)
				{

					timelost--;

					wintext = setText(font8, 70, 270, 200);
					wintext.setString("YOU WIN");
					wintext.setColor(Color::Red);

					clocklost.restart();
				}

				if (timelost == 0)
				{
					booleans.scorewinbool = true;
					timescoremin = setText(font8, 35, 48, 507);
					wintext.setColor(Color::Transparent);
					scoreText = setText(font8, 20, 60, 5);
				}

			}
		}

		float timermov = clock2.getElapsedTime().asSeconds();

		if (timermov > 0.4)
		{

			if (move)
			{
				for (int j = 0; j < 5; j++)
					backpack[j].move(0, 4);

				arrLvl1.move(0, -4);
				arrLvl2_1.move(4, 0);
				arrLvl2_2.move(0, -4);
				arrLvl2_3.move(-4, 0);
				move = false;

			}
			else
			{
				for (int j = 0; j < 5; j++)
					backpack[j].move(0, -4);

				arrLvl1.move(0, 4);
				arrLvl2_1.move(-4, 0);
				arrLvl2_2.move(0, 4);
				arrLvl2_3.move(4, 0);
				move = true;

				timermov = 0;
			}

			if (friends.X == 0)
			{
				friends.X = 1;
			}
			else if (friends.X == 1)
			{
				friends.X = 2;
			}
			else if (friends.X == 2)
			{
				friends.X = 0;
			}
			clock2.restart();
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

		if (score > highscore)

			highscore = score;

		ofstream writeFile;
		writeFile.open("freshmen milestone/highscore.txt");

		if (writeFile.is_open())
		{
			if (score > highscore)

				highscore = score;


		}
		writeFile << highscore;

		writeFile.close();




		window.clear();

		//drawing
		if (booleans.play)


		{
			if (booleans.lvl1)
			{


				for (int i = 0; i < 33; i++)
				{
					window.draw(maze1[i]);
				}

				window.draw(background1);


				for (int i = 0; i < 5; i++)
				{
					window.draw(backpack[i]);

				}

				if (booleans.assignment)
					window.draw(arrLvl1);

				window.draw(mainplayer);

				window.draw(friend1);
				window.draw(friend2);
				window.draw(friend3);
			}
			//string drawing 
			window.draw(timescoremin);
			window.draw(timercolon);
			window.draw(timescoresec);

			for (int j = 0; j < 14; j++)
			{
				window.draw(dialogue[j]);
			}

		}


		if (booleans.lvl2)
		{
			window.draw(mazeMon1);
			window.draw(mazeMon2);


			for (int i = 0; i < 40; i++)
			{
				window.draw(maze2[i]);
			}
			window.draw(background2);
			window.draw(arrLvl2_1);
			window.draw(arrLvl2_2);
			window.draw(arrLvl2_3);
			window.draw(monster1);
			window.draw(monster2);
			window.draw(wintext);
			window.draw(friend4);
			window.draw(mainplayer);

			//string drawing 
			window.draw(timescoremin);
			window.draw(timercolon);
			window.draw(timescoresec);
			window.draw(Monologue2);


		}
		if (booleans.scorewinbool)
		{
			window.draw(scorewin);
			window.draw(scoreclocksp);
			window.draw(backpack[1]);
			window.draw(assignmentsp);
			window.draw(friend1);
			window.draw(friend2);
			window.draw(skipwintext);

			for (int i = 0; i < 4; i++)
			{

				window.draw(cross[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				window.draw(tick[i]);
			}
			window.draw(timewontxt);
			window.draw(BPcountxt);

		}


		////score drawing

		stringstream scoreString;
		scoreString << score;
		scoreText.setString(scoreString.str());
		scoreText.setPosition(160, 400);



		window.draw(scoreText);
		stringstream highest;
		highest << highscore;
		HighScore.setString(highest.str());
		HighScore.setPosition(200, 437);

		window.draw(HighScore);



		if (booleans.menuvariable)
		{
			window.draw(backgroundmain);

			menu.draw(window);
		}
		if (booleans.guide)
		{
			window.draw(guide);
			window.draw(guidetext);
		}


		if (booleans.pausevariable)
		{

			pause.draw(window);
		}
		window.display();

	}

	return 0;
}