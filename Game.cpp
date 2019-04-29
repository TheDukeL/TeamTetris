#include "Game.h"
#include "Tetromino.h"

Game::Game(RenderWindow &window): 
	level(0), lines(0), started(false), points(0), closing(false), gameOver(false)
{
	oneScreen.setInitialConfig(window);
	time = milliseconds(INITALSPEED);
	fallingTetromino = generateTetromino();
}

Game::~Game()
{
	for (int i = 0; i < nextTetrominos.size(); i++)
		delete(nextTetrominos[i]);
	nextTetrominos.clear();

	delete fallingTetromino;
}

//manages events
void Game::update(const Event event)
{
	if (event.type == Event::Closed)
	{
		oneScreen.closing();
		closing = true;
		started = false;
	}

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
		if (started)
		{
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case Keyboard::Up: { rotate(); break; }
					case Keyboard::Left: { moveLeft(); break; }
					case Keyboard::Right: { moveRight(); break; }
					case Keyboard::Down: { moveDown(origin::APP); break; }
					case Keyboard::P: { started = false; oneScreen.pauseMusic(); break; }
					default: { break; }
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
						default: { break; }
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

/* things to do after every event: drawing, checking collisions, adding tetrominos to the board 
checking game over, generating new tetromino and checking for new lines */
void Game::doAfterEvent()
{
	if (DEBUGMODE)
	{
		std::cout << std::boolalpha;
		std::cout << "\n\n\n\nleft: " << oneBoard.movementAllowed(*fallingTetromino, -1, 0) << std::endl;
		std::cout << "right: " << oneBoard.movementAllowed(*fallingTetromino, 1, 0) << std::endl;
		std::cout << "down: " << oneBoard.movementAllowed(*fallingTetromino, 0, 1) << std::endl;
	}

	/*
	//Tetromino has landed. Add it to board at [x, y] and generate new tetromino.
	if (!oneBoard.movementAllowed(*fallingTetromino, 0, 1))//(oneBoard.checkCollision(*fallingTetromino, fallingTetromino->getX(), fallingTetromino->getY()))
	{
		if (DEBUGMODE) stallPlace--;
		oneBoard.settleTetromino(*fallingTetromino);
		fallingTetromino = generateTetromino();
	}
	*/

	oneScreen.draw(oneBoard, *fallingTetromino);
	checkBoard();
	checkGameOver();
}

// "Lands" the Tetromino. Adds it to board at current tetromino position and generates a new one/
void Game::finalizeTetromino()
{
	oneBoard.settleTetromino(*fallingTetromino);
	fallingTetromino = generateTetromino();
}

//moves current piece left by one
void Game::moveLeft()
{
	if ( oneBoard.movementAllowed(*fallingTetromino, -1, 0) )
		fallingTetromino->shiftLeft();
}

//moves current piece right by one
void Game::moveRight()
{
	if ( oneBoard.movementAllowed(*fallingTetromino, 1, 0) )
		fallingTetromino->shiftRight();
}

//moves current piece down by one
void Game::moveDown(int origin)
{
	if (oneBoard.movementAllowed(*fallingTetromino, 0, 1))
		fallingTetromino->shiftDown();
	else
		finalizeTetromino();
	
	if (origin == origin::TICK)
		doAfterEvent();
}

//rotates a piece
void Game::rotate()
{
	fallingTetromino->rotate();

	// this is super ultra hacky
	if (oneBoard.checkCollision(*fallingTetromino, fallingTetromino->getX(), fallingTetromino->getY()))//if (!oneBoard.movementAllowed(*fallingTetromino, 0, 0))
	{
		//rotated tetromino experienced a collision - rotate it 3 more times to move it back to the original position
		fallingTetromino->rotate();
		fallingTetromino->rotate();
		fallingTetromino->rotate();
	}
}

//checks for lines to clean, cleans them, checks lines to next level and accumulates points
void Game::checkBoard()
{	
	int linesToAdd = oneBoard.checkAndCleanLines();
	lines = lines + linesToAdd;
	points = points + (linesToAdd*ONEPOINT);
	checkLines();
}

//controlls the levels and pass to screen data of the current game
void Game::checkLines()
{
	if (lines >= LINESFORLEVEL)
	{	
		lines = 0;
		level++;
		time = time - milliseconds(ONELEVELSPEED);
	}

	/*
	if (level > FINALLEVEL)
	{
		started = false;
		oneScreen.win();
	}
	*/

	oneScreen.setCurrentGameInfo(level, lines, points);
}

//restarts the game
void Game::restart()
{	
	oneBoard.cleanBoard();
	started = true;
	gameOver = false;
	level = 0;
	lines = 0;
	points = 0;
	oneScreen.setCurrentGameInfo(level, lines, points);
	oneScreen.draw(oneBoard, *fallingTetromino);
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
				if (!DEBUGMODE) moveDown(origin::TICK);
			}
		}
}

void Game::determineNextTetrominos()
{
	nextTetrominos.push_back(new IBlock);
	nextTetrominos.push_back(new JBlock);
	nextTetrominos.push_back(new LBlock);
	nextTetrominos.push_back(new OBlock);
	nextTetrominos.push_back(new SBlock);
	nextTetrominos.push_back(new TBlock);
	nextTetrominos.push_back(new ZBlock);

	std::random_shuffle(nextTetrominos.begin(), nextTetrominos.end());
}

Tetromino* Game::generateTetromino()
{
	//fill up nextTetrominos if it's empty
	if (!nextTetrominos.size())
		determineNextTetrominos();

	Tetromino* newTetromino = nextTetrominos.back();
	nextTetrominos.pop_back();

	return newTetromino;
}