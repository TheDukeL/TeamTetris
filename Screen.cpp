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
	
	end.setTexture(textureEnd);
	pause.setTexture(texturePause);
	sqr.setTexture(textureSqr);
	background.setTexture(textureBackground);
	rotate.setBuffer(bufRotate);
	place.setBuffer(bufPlace);
	lineComplete.setBuffer(bufComplete);
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	music.setLoop(true);

	end.setScale(.25f, .25f);
	end.setPosition(128, 128);

	pause.setScale(.25f, .25f);
	pause.setPosition(128, 128);
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
		if (!texturePause.loadFromFile(PAUSEFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << CRITICALFILEERROR; sleep(seconds(2)); close(); }
		}
		else { break; }
	}

	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!textureEnd.loadFromFile(GAMEOVERFILE))
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

	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!bufRotate.loadFromFile(ROTATEFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << FILEERROR;}
		}
		else { break; }
	}

	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!bufPlace.loadFromFile(PLACEFILE))
		{
			i++;
			if (i == FILELOADATTEMPTS) { cout << FILEERROR;}
		}
		else { break; }
	}

	i = 0;
	while (i < FILELOADATTEMPTS)
	{
		if (!bufComplete.loadFromFile(COMPLETEFILE))
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
void Screen::setCurrentGameInfo(std::array<std::array<int, 4>, 4> tet, int offX, int offY, const int lev, const int lin, const int poi)
{
	tetOffX = offX;
	tetOffY = offY;
	nextTetromino = tet;
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

//draws next piece preview, level, points, and lines to next level
void Screen::drawCurrentGameInfo()
{
	if (nextTetromino.size() > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (nextTetromino[i][j] != EMPTY)
				{
					sqr.setTextureRect( sf::IntRect(128*(nextTetromino[i][j]-1), 0, 128, 128) );

					sqr.setPosition(450 + (32*j) - (16*tetOffX), 150 + (32*i) - (16*tetOffY));

					sqr.setScale(.25f, .25f);
				
					window->draw(sqr);
				}
			}
		}
	}

	drawText(to_string(points), NORMALFONT, 517, 356, false, false);
	drawText(to_string(level), NORMALFONT, 517, 491, false, false);
	drawText(to_string(LINESFORLEVEL - lines), NORMALFONT, 517, 623, false, false);
}

//closes the game
void Screen::close()
{
	window->close();
}

//shows game over sceen
void Screen::gameOver()
{
	stopMusic();

	if (DEBUGMODE) std::cout << "game ended" << std::endl;

	if (window->isOpen())
	{
		window->draw(end);
		window->display();
	}
}

void Screen::pauseMenu()
{
	pauseMusic();

	if (DEBUGMODE) std::cout << "paused" << std::endl;

	if (window->isOpen())
	{
		window->clear();
		window->draw(pause);
		window->display();
	}
}

//close the game
void Screen::closing()
{
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

//play place sfx
void Screen::playPlace()
{
	place.play();
}

//play rotate sfx
void Screen::playRotate()
{
	rotate.play();
}

//play line complete sfx
void Screen::playLineComplete()
{
	lineComplete.play();
}