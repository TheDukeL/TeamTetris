#include "Screen.h"
#include <iostream>

using namespace std;

Screen::Screen() : level(0), lines(0), points(0) {};
Screen::~Screen() {};

//sets window and configures text and music
void Screen::setInitialConfig(RenderWindow & window)
{
	this->window = &window;

	loadFiles();
	
	sqr.setTexture(textureSqr);
	background.setTexture(textureBackground);
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	music.setLoop(true);
}


//Attempts to load files, shows a message if it fails and closes the app if the missing file is a critical one 
void Screen::loadFiles()
{
	int i = 0;

	while (i < FILELOADATTEMPTS)
	{
		if (!textureBackground.loadFromFile(BACKKGROUNDFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << CRITICALFILEERROR; sleep(seconds(2)); close(); }
		}
		else { break; }

	}

	i = 0;

	while (i < FILELOADATTEMPTS)
	{
		if (!textureSqr.loadFromFile(TEXTUREFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << CRITICALFILEERROR; sleep(seconds(2)); close(); }
		}
		else { break; }

	}

	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!font.loadFromFile(FONTFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << CRITICALFILEERROR; sleep(seconds(2)); close(); }
		}
		else { break; }

	}
	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!music.openFromFile(MUSICFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << FILEERROR;}
		}
		else { break; }
	}
}

//draws board and tetromino
void Screen::draw(Board& board, Tetromino& tetromino, const int x, const int y)
{
	if (window->isOpen())
	{
		window->clear();

		window->draw(background);
		drawBoard(board);
		drawTetromino(tetromino, x, y);
		drawCurrentGameInfo();

		window->display();
	}
}

//draws board
void Screen::drawBoard(Board & board)
{
	for (int i = 0; i < board.getSIZEY(); i++)
	{
		for (int j = 0; j <board.getSIZEX(); j++)
		{
			if (board.getSettledPieces()[i][j] != EMPTY)
			{		
				asignColor(board.getSettledPieces()[i][j]);

				//sets the offset for the squares
				sqr.setPosition(Vector2f((STARTINGXPX + ((ONEXYPX)*j)),
					(STARTINGYPX + ((ONEXYPX)*i))));

				window->draw(sqr);
			}
		}
	}
}

//draws tetromino
void Screen::drawTetromino(Tetromino & tetromino, const int x, const int y)
{
	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if (tetromino.getPiece()[i][j] != EMPTY)
			{	
				asignColor(tetromino.getPiece()[i][j]);

				//sets the offset for the squares
				sqr.setPosition(Vector2f((STARTINGXPX + ((ONEXYPX)*(j+x))),
					(STARTINGYPX + ((ONEXYPX)*(i+y)))));

				window->draw(sqr);
			}
		}
	}
}

//asign color to the sprint
void Screen::asignColor(const int oneSqr)
{
	switch (oneSqr)	{
	case colors::LIGHTBLUE: {sqr.setColor(Color(colorsRGB[colors::LIGHTBLUE-1][R], 
		colorsRGB[colors::LIGHTBLUE-1][G], colorsRGB[colors::LIGHTBLUE-1][B])); break; }
	
	case colors::BLUE:{	sqr.setColor(Color(colorsRGB[colors::BLUE-1][R], 
		colorsRGB[colors::BLUE-1][G], colorsRGB[colors::BLUE-1][B])); break; }
	
	case colors::ORANGE:{sqr.setColor(Color(colorsRGB[colors::ORANGE-1][R], 
		colorsRGB[colors::ORANGE-1][G], colorsRGB[colors::ORANGE-1][B])); break; }
	
	case colors::YELLOW:{sqr.setColor(Color(colorsRGB[colors::YELLOW-1][R], 
		colorsRGB[colors::YELLOW-1][G], colorsRGB[colors::YELLOW-1][B])); break; }
	
	case colors::GREEN:{sqr.setColor(Color(colorsRGB[colors::GREEN-1][R], 
		colorsRGB[colors::GREEN-1][G], colorsRGB[colors::GREEN-1][B])); break; }
	
	case colors::VIOLET:{sqr.setColor(Color(colorsRGB[colors::VIOLET-1][R], 
		colorsRGB[colors::VIOLET-1][G], colorsRGB[colors::VIOLET-1][B])); break; }
	
	case colors::RED: {sqr.setColor(Color(colorsRGB[colors::RED-1][R],
		colorsRGB[colors::RED-1][G], colorsRGB[colors::RED - 1][B])); break;
	}
	default: {break; }
	}
}

//updates the level, lines and points
void Screen::setCurrentGameInfo(const int lev, const int lin, const int poi)
{
	level = lev;
	lines = lin;
	points = poi;
}

//draws text
void Screen::drawText(const string str, const int fontSize, const float x, const float y, const bool clear, const bool display)
{
	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setPosition(x,y);
	
	if (window->isOpen())
	{
		if (clear)
			window->clear();

		window->draw(text);

		if (display)
			window->display();
	}
}

//shows start screen
void Screen::start()
{
	float offsetY = STARTINGY - OFFSET;
	drawText(GAMENAME, BIGFONT, STARTINGXCENTER,offsetY, true, false);
	
	offsetY = offsetY + (OFFSET * 2);
	drawText(START,MEDIUMFONT,STARTINGXCENTER,offsetY,false, false);
	
	offsetY = offsetY + OFFSET;
	drawText(INSTRUCTION1,SMALLFONT,STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION2, SMALLFONT, STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION3, SMALLFONT, STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION4, SMALLFONT, STARTINGXLEFT,offsetY, false, true);

	playMusic();
}

//draws level, points, and lines to next level
void Screen::drawCurrentGameInfo()
{
	float offset = STARTINGY;
	drawText(LEVEL, MEDIUMFONT, STARTINGXRIGHT, offset, false, false);
	
	offset = offset + OFFSET;
	drawText(to_string(level), MEDIUMFONT, STARTINGXRIGHT+OFFSET, offset, false, false);
	
	offset = offset + OFFSET;
	drawText(POINTS, MEDIUMFONT, STARTINGXRIGHT, offset, false, false);
	
	offset = offset + OFFSET;
	drawText(to_string(points), MEDIUMFONT, STARTINGXRIGHT, offset, false, false);
	
	offset = STARTINGYLOW;
	drawText(NEXTLEVEL1, SMALLFONT, STARTINGXRIGHT, offset, false, false);
	
	offset = offset + SMALLOFFSET ;
	drawText(NEXTLEVEL2, SMALLFONT, STARTINGXRIGHT, offset, false, false);

	offset = offset + SMALLOFFSET ;
	drawText(to_string(LINESFORLEVEL - lines), MEDIUMFONT, STARTINGXRIGHT+OFFSET, offset, false, false);

	offset = STARTINGYLOW;
	drawText(PAUSE, SMALLFONT, SMALLOFFSET/3, offset, false, false);

	offset = offset+SMALLOFFSET;
	drawText(RESUME, SMALLFONT, SMALLOFFSET/3, offset, false, false);
}

//shows winner screen
void Screen::win()
{
	drawText(WIN1, MEDIUMFONT, STARTINGXCENTER, STARTINGY, true, false);
	drawText(WIN2, MEDIUMFONT, STARTINGXCENTER, STARTINGY+OFFSET, false, true);
}


//closes the game
void Screen::close()
{
	window->close();
}


//shows game over sceen
void Screen::gameOver()
{
	float offset = STARTINGY;
	drawText( GAMEOVER1, MEDIUMFONT,STARTINGXBOARD , offset, false, false);
	offset = offset + OFFSET;
	drawText(GAMEOVER2, SMALLFONT, STARTINGXBOARD-OFFSET, offset, false, false);
	offset = offset + OFFSET;
	drawText(GAMEOVER3, SMALLFONT, STARTINGXBOARD-OFFSET, offset, false, true);
	stopMusic();
}

//show exit sceen
void Screen::closing()
{
	float offset = STARTINGY;
	drawText(CLOSE1, MEDIUMFONT, STARTINGXCENTER, offset, true, false);
	offset = offset + OFFSET;
	drawText(CLOSE2, MEDIUMFONT, STARTINGXCENTER, offset, false, true);
	stopMusic();
}

//plays music
void Screen::playMusic()
{
	music.play();
}

//stops music
void Screen::stopMusic()
{
	music.stop();
}

//pauses music
void Screen::pauseMusic()
{
	music.pause();
}