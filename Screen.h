#ifndef SCREEN_H
#define SCREEN_H

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
	void draw(Board &board, Tetromino & tetromino);
	void setInitialConfig(RenderWindow & window);
	void closing();
	void gameOver();
	void pauseMenu();
	void start();
	void setCurrentGameInfo(std::array<std::array<int, 4>, 4> tet, int offX, int offY, const int lev, const int lin, const int poi);
	void close();
	void playMusic();
	void stopMusic();
	void playPlace();
	void playRotate();
	void playLineComplete();
	void pauseMusic();
	
private:
	void drawBoard(Board &board);
	void drawTetromino(Tetromino &tetromino, const int x, const int y);
	void drawText(std::string str, const int fontSize, const float x, const float y, const bool clear, const bool display, bool alignCenter = true);
	void drawCurrentGameInfo();
	void loadFiles();

	Texture textureBackground, textureSqr, texturePause, textureEnd;
	Sprite background, sqr, pause, end;
	Font font;
	Text text;
	SoundBuffer bufRotate, bufPlace, bufComplete;
	Sound rotate, place, lineComplete;
	Music music;
	RenderWindow *window;

	std::array<std::array<int, 4>, 4> nextTetromino; //holds the next tetromino preview
	int level, lines, points;
	int tetOffX = 0; int tetOffY = 0; //offset for the next tetromino preview (kinda hacky and last-minute)

	//file locations
	const char *BACKKGROUNDFILE = "assets/board.png", *TEXTUREFILE = "assets/pieces.png", *PAUSEFILE = "assets/pause.png", *GAMEOVERFILE = "assets/gameover.png",
		*FONTFILE = "assets/font.ttf", *MUSICFILE = "assets/music.ogg", *ROTATEFILE = "assets/rotate.wav", *PLACEFILE = "assets/place.wav", *COMPLETEFILE = "assets/lineComplete.wav", 
		*CRITICALFILEERROR = "Vital files could not be load, it is imposible to continue \n",
		*FILEERROR = "Some files could not be load \n";

	const int NORMALFONT = 42, DEBUGFONT = 12;
	const float STARTINGXLEFT = 50, STARTINGXCENTER = 150, STARTINGXRIGHT = 500, STARTINGXBOARD = 225, SMALLOFFSET = 30, OFFSET = 50,
		STARTINGY = 150, STARTINGYLOW = 550;
	const int FILELOADATTEMPTS = 3;
	const Color GRAY = Color(50, 50, 65, 255);
};

#endif