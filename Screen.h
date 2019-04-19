#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tetromino.h"
#include "Board.h"

using namespace sf;

class Screen
{
public:

	Screen();
	~Screen();
	void draw(Board &board, Tetromino & tetromino, const int x, const int y);
	void setInitialConfig(RenderWindow & window);
	void closing();
	void gameOver();
	void start();
	void setCurrentGameInfo(const int lev, const int lin, const int poi);
	void win();
	void close();
	void playMusic();
	void stopMusic();
	void pauseMusic();
	
private:
	void drawBoard(Board &board);
	void drawTetromino(Tetromino &tetromino, const int x, const int y);
	void asignColor(const int oneSqr);
	void drawText(const string str, const int fontSize, const float x, const float y, 
		const bool clear, const bool display);
	void drawCurrentGameInfo();
	void loadFiles();

	Texture textureBackground, textureSqr;
	Sprite background, sqr;
	Font font;
	Text text;
	Music music;
	RenderWindow *window;


	int level, lines, points;

	const char *BACKKGROUNDFILE = "assets/background.jpg", *TEXTUREFILE = "assets/sqrtetromino.png",
		*FONTFILE = "assets/font.ttf", *MUSICFILE = "assets/music.ogg", 
		*CRITICALFILEERROR = "Vital files could not be load, it is imposible to continue \n",
		*FILEERROR = "Some files could not be load \n";
	const string GAMENAME = "tetris", START = "Press enter to start", INSTRUCTION1 = "How to play:",
		INSTRUCTION2 = "ARROWS to move LEFT, RIGHT or ROTATE", INSTRUCTION3 = "DOWN arrow or SPACE to move DOWN",
		INSTRUCTION4 = "P to PAUSE or RESUME", LEVEL = "Level", POINTS = "Points", NEXTLEVEL1 = "Lines to", NEXTLEVEL2 = "next level",
		WIN1 = "Congratulations", WIN2 = "You have won!!!", GAMEOVER1 = "GAMEOVER", GAMEOVER3="Press ESC to exit", 
		GAMEOVER2="Press ENTER to restart", CLOSE1 = "Press ENTER to exit", CLOSE2="Press S to restart", PAUSE="P to Pause", RESUME="or Resume";
	const int BIGFONT = 80, MEDIUMFONT = 25, SMALLFONT = 18;
	const float STARTINGXLEFT = 50, STARTINGXCENTER = 150, STARTINGXRIGHT = 500, STARTINGXBOARD = 225, SMALLOFFSET = 30, OFFSET = 50,
		STARTINGY = 150, STARTINGYLOW=550;
	const int FILELOADATTEMPTS=3;
	


};

