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
void Screen::draw(Board& board, Tetromino& tetromino)
{
	if (window->isOpen())
	{
		window->clear();

		window->draw(background);
		drawBoard(board);
		drawTetromino(tetromino, tetromino.getX(), tetromino.getY());
		drawCurrentGameInfo();

		window->display();
	}
}

//draws board
void Screen::drawBoard(Board & board)
{
	for (int i = 0; i < board.getSIZEY(); i++)
	{
		for (int j = 0; j < board.getSIZEX(); j++)
		{
			if (board.getSettledPieces()[i][j] != EMPTY)
			{		
				sqr.setTextureRect( sf::IntRect((board.getSettledPieces()[i][j]-1)*128, 0/*128*((level + 3) % 3) choose either 0, 128, or 256 based on level*/, 128, 128) );

				sqr.setPosition(STARTINGPX + (32*j), STARTINGPX + (32*i));

				sqr.setScale(.25f, .25f);

				window->draw(sqr);

				//print the position of each individual square
				if (DEBUGMODE) drawText("[" + to_string(j) + "," + to_string(i) + "]", DEBUGFONT, STARTINGPX + (32*j), STARTINGPX + (32*i), false, false, false);
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
			if (tetromino.getShape()[i][j] != EMPTY || DEBUGMODE)
			{
				sqr.setTextureRect( sf::IntRect(128*(tetromino.getShape()[i][j]-1), 0/*128*((level + 3) % 3)*/, 128, 128) );

				sqr.setPosition(STARTINGPX + (32*(j+x)), STARTINGPX + (32*(i+y)));

				sqr.setScale(.25f, .25f);

				//draw empty tiles as black
				if (DEBUGMODE && tetromino.getShape()[i][j] == EMPTY) sqr.setColor(sf::Color::Black);

				window->draw(sqr);

				//return color to normal if set to black
				if (DEBUGMODE) sqr.setColor(sf::Color::White);

				//print the position of each individual square
				if (DEBUGMODE) drawText("[" + to_string(j+x) + "," + to_string(i+y) + "]", DEBUGFONT, STARTINGPX + (32*(j+x)), STARTINGPX + (32*(i+y)), false, false, false);
			}
		}
	}

	//print the position of the tetromino itself
	if (DEBUGMODE) drawText("[" + to_string(tetromino.getX()) + "," + to_string(tetromino.getY()) + "]", DEBUGFONT, 32, 32, false, false, false);

	//print tetromino bounds
	if (DEBUGMODE) drawText("L:" + to_string(tetromino.getBoundsLeft()) + ",R:" + to_string(tetromino.getBoundsRight()) + "\nT:" + to_string(tetromino.getBoundsTop()) + ",B:" + std::to_string(tetromino.getBoundsBottom()), DEBUGFONT, 32, 64, false, false, false);
}

//updates the level, lines and points
void Screen::setCurrentGameInfo(const int lev, const int lin, const int poi)
{
	level = lev;
	lines = lin;
	points = poi;
}

//draws text
void Screen::drawText(string str, const int fontSize, const float x, const float y, const bool clear, const bool display, bool alignCenter)
{
	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setOutlineColor(GRAY);
	text.setOutlineThickness(3);

	if (alignCenter)
		text.setPosition(x - (text.getLocalBounds().width/2), y);
	else
		text.setPosition(x, y);

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
	drawText(GAMENAME, BIGFONT, STARTINGXCENTER, offsetY, true, false);
	
	offsetY = offsetY + (OFFSET * 2);
	drawText(START, MEDIUMFONT, STARTINGXCENTER, offsetY, false, false);
	
	offsetY = offsetY + OFFSET;
	drawText(INSTRUCTION1, SMALLFONT, STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION2, SMALLFONT, STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION3, SMALLFONT, STARTINGXLEFT, offsetY, false, false);
	
	offsetY = offsetY + SMALLOFFSET;
	drawText(INSTRUCTION4, SMALLFONT, STARTINGXLEFT, offsetY, false, true);

	playMusic();
}

//draws level, points, and lines to next level
void Screen::drawCurrentGameInfo()
{
	drawText(to_string(points), MEDIUMFONT, 384+133, 512-145-11, false, false);
	drawText(to_string(level), MEDIUMFONT, 384+133, 670-168-11, false, false);
	drawText(to_string(LINESFORLEVEL - lines), MEDIUMFONT, 384+133, 830-195-12, false, false);
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
	drawText( GAMEOVER1, MEDIUMFONT, STARTINGXBOARD, offset, false, false);
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