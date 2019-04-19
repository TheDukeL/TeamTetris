#include "Game.h"
#include "L.h"
#include "I.h"
#include "J.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"

Game::Game(RenderWindow &window): 
	level(0), lines(0), started(false), points(0),closing(false), gameOver(false)
{
	oneScreen.setInitialConfig(window);
	time = milliseconds(INITALSPEED);
	generateTetrominos();
	generateFallingTetromino();
}

Game::~Game()
{
	for (int i = 0; i < NUMTETROMINOS; i++)
	{
		int rot = 1;
		for (int j = 0; j < rot; j++)
		{
			if (j == 0) { rot = tetrominos[i][j]->getRotNum(); }

			delete tetrominos[i][j];

		}
	}
}

//manages events
void Game::update(const Event event)
{
	
	if (event.type == Event::Closed) { oneScreen.closing(); closing = true; started = false; }

		
	if (closing)
	{
		if (event.type == Event::KeyPressed)
		{	
			
			switch (event.key.code)
			{
			case Keyboard::S: { restart(); closing = false; break; }
			case Keyboard::Return: { oneScreen.close(); break; }
			default: {break; }
			}
		}
	}
	else
	{
				if(started)
				{
	
	
					if (event.type == Event::KeyPressed)
					{
						switch (event.key.code)
						{
						case Keyboard::Up: { rotate(); break; }
						case Keyboard::Left: { moveLeft(); break; }
						case Keyboard::Right: { moveRight(); break; }
						case Keyboard::Down: { moveDown(origin::APP); break; }
						case Keyboard::Space: { moveDown(origin::APP); break; }
						case Keyboard::P: { started = false; oneScreen.pauseMusic(); break; }
						default: {break; }
						}
						
					
					}

					doAfterEvent();
					}
					else

					{

						if (gameOver)
						{
							if (event.type == Event::KeyPressed)
							{
								switch (event.key.code)
								{
								case Keyboard::Return: { restart(); break; }
								case Keyboard::Escape: { oneScreen.close(); break; }
								default: {break; }
								}
							}
						}
						else
						{
							if (event.type == Event::KeyPressed)
							{
								switch (event.key.code)
								{
								case Keyboard::Return: { started = true; break; }
								case Keyboard::P: { started = true; oneScreen.playMusic(); break; }
								default: {break; }
								}
							}
						}
					
				}
		}
	
}

//shows start screen
void Game::start()
{
	oneScreen.start();

}

/*things to do after every event: drawing, checking collisions, addinng tetrominos to the board 
checking game over, generating new tetromino and checking for new lines */
void Game::doAfterEvent()
{
	
	if (oneBoard.checkCollision(*fallingTetromino, xy[X], xy[Y]))
	{
		oneBoard.addPieceToBoard(*fallingTetromino, xy[X], xy[Y]);
		
		generateFallingTetromino();
	}

	oneScreen.draw(oneBoard, *fallingTetromino, xy[X], xy[Y]);
	checkBoard();
	checkGameOver();
	
	
}

//moves left a piece
void Game::moveLeft()
{
	if (oneBoard.movementAllowed(*fallingTetromino, (xy[X]-1), xy[Y]))
	{
		xy[X]--;
	}
}

//moves down a piece
void Game::moveDown(int origin)
{
	if (oneBoard.movementAllowed(*fallingTetromino, (xy[X]), xy[Y] + 1))
	{
		xy[Y]++;
	}
	
	if (origin == origin::TICK)
	{
		doAfterEvent();
	}
}

//moves right a piece
void Game::moveRight()
{
	if (oneBoard.movementAllowed(*fallingTetromino, (xy[X]+1), xy[Y]))
	{
		xy[X]++;
	}
}

//rotates a piece
void Game::rotate()
{
	int rot = INITIALROTATION;
	if ((fallingTetromino->getRot() + 1) <= fallingTetromino->getRotNum())
	{
		rot = (fallingTetromino->getRot() + 1);
	
	}

	Tetromino* rotatedTetromino = tetrominos[fallingTetrominoType][rot-1];

		
	if (oneBoard.movementAllowed(*rotatedTetromino, xy[X], xy[Y]))
	{			
		
				fallingTetromino= tetrominos[fallingTetrominoType][rot-1];
	}
	
}

//checks for lines to clean, cleans them, checks lines to next level and accumulates points
void Game::checkBoard()
{	
			
		int linesToAdd = oneBoard.checkAndCleanLines();
		lines = lines+ linesToAdd;
		points = points+(linesToAdd*ONEPOINT);
		checkLines();

}

//controlls the levels and pass to screen data of the current game
void Game::checkLines()
{
	if (lines >= LINESFORLEVEL)
	{	lines = 0;
		level++;
		time = time - milliseconds(ONELEVELSPEED);
	}

	if (level>FINALLEVEL)
	{
		started = false;
		oneScreen.win();
	}

	oneScreen.setCurrentGameInfo(level, lines, points);
}

//restarts the game
void Game::restart()
{	
	oneBoard.cleanBoard();
	xy[X] = oneBoard.getSTARTINGX();
	xy[Y] = oneBoard.getSTARTINGY();
	started = true;
	gameOver = false;
	level = 0;
	lines = 0;
	points = 0;
	oneScreen.setCurrentGameInfo(level,lines,points);
	oneScreen.draw(oneBoard, *fallingTetromino, xy[X], xy[Y]);
	oneScreen.playMusic();
}



//checks for game over
void Game::checkGameOver()
{
	if(oneBoard.checkGameOver())
	{
		started = false;
		gameOver = true;
		oneScreen.gameOver();
		
	}
}


//controlls time
void Game::tick()
{
		if(started)
		{

			if (clock.getElapsedTime() >= time)
			{
				clock.restart();
				moveDown(origin::TICK);
			}
		}
}

//generate the pieces with all their rotations at the start of the game
void Game::generateTetrominos() 
{
	
	for (int i = 0; i < NUMTETROMINOS; i++)
	{ int rot = 1;
		for (int j = 0; j < rot; j++)
		{		
			switch (i)
			{
			case 0: { tetrominos[i][j] = new I; break; }
			case 1: { tetrominos[i][j] = new J; break; }
			case 2: { tetrominos[i][j] = new L; break; }
			case 3: { tetrominos[i][j] = new O; break; }
			case 4: { tetrominos[i][j] = new S; break; }
			case 5: { tetrominos[i][j] = new T; break; }
			case 6: { tetrominos[i][j] = new Z; break; }
			default:
				break;
			}
			
			if (j == 0){rot = tetrominos[i][j]->getRotNum();}
			else{tetrominos[i][j]->rotate(j + 1);}
		}
	}
	
}

//generates a new random tetromino
void Game::generateFallingTetromino()
{
		
	srand(std::time(NULL));
	int num = rand() % NUMTETROMINOS;
		
	fallingTetromino = tetrominos[num][INITIALROTATION-1];
	fallingTetrominoType = num;
	xy[X] = oneBoard.getSTARTINGX();
	xy[Y] = oneBoard.getSTARTINGY();
}