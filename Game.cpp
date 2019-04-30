#include "Game.h"
#include "Tetromino.h"

Game::Game(RenderWindow &window): 
	level(0), lines(0), started(false), points(0), closing(false), gameOver(false)
{
	oneScreen.setInitialConfig(window);
	time = milliseconds(INITALSPEED);

	determineNextTetrominos();
	fallingTetromino = generateTetromino();
}

Game::~Game()
{
	for (int i = 0; i < nextTetrominos.size(); i++)
		delete(nextTetrominos[i]);
	nextTetrominos.clear();

	delete fallingTetromino;
}

void Game::start()
{
	started = true;
	oneScreen.playMusic();
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
					case Keyboard::P: { started = false; oneScreen.pauseMenu(); break; }
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

/* things to do after every event: drawing, checking collisions, adding tetrominos to the board 
checking game over, generating new tetromino and checking for new lines */
void Game::doAfterEvent()
{
	oneScreen.draw(oneBoard, *fallingTetromino);
	checkBoard();
	checkGameOver();
}

// "Lands" the Tetromino. Adds it to board at current tetromino position and generates a new one/
void Game::finalizeTetromino()
{
	oneBoard.settleTetromino(*fallingTetromino);
	oneScreen.playPlace();
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
	if (!oneBoard.movementAllowed(*fallingTetromino, 0, 0))
	{
		//rotated tetromino experienced a collision - rotate it 3 more times to move it back to the original position
		fallingTetromino->rotate();
		fallingTetromino->rotate();
		fallingTetromino->rotate();
	}
	else oneScreen.playRotate();
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

	//EXTREMELY HACKY logic to make sure the tetromino preview is centered (this was last-minute)
	int offX = nextTetrominos.back()->getBoundsLeft() > nextTetrominos.back()->getBoundsRight();
	int offY = nextTetrominos.back()->getBoundsTop();
	if (!offY && !nextTetrominos.back()->getBoundsBottom())
		offY++;

	oneScreen.setCurrentGameInfo(nextTetrominos.back()->getShape(), offX, offY, level, lines, points);
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

	//EXTREMELY HACKY logic to make sure the tetromino preview is centered (this was last-minute)
	int offX = nextTetrominos.back()->getBoundsLeft() > nextTetrominos.back()->getBoundsRight();
	int offY = nextTetrominos.back()->getBoundsTop();
	if (!offY && !nextTetrominos.back()->getBoundsBottom())
		offY++;

	oneScreen.setCurrentGameInfo(nextTetrominos.back()->getShape(), offX, offY, level, lines, points);
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
	if (DEBUGMODE) std::cout << "choosing next set of tetrominos" << std::endl;

	vector<Tetromino*> temp;

	temp.push_back(new IBlock);
	temp.push_back(new JBlock);
	temp.push_back(new LBlock);
	temp.push_back(new OBlock);
	temp.push_back(new SBlock);
	temp.push_back(new TBlock);
	temp.push_back(new ZBlock);

	//randomize separate array and add them to the beginning of nextTetrominoes to not change the last item in the vector (which would break next piece preview)

	std::random_shuffle(temp.begin(), temp.end());

	for (int i = 0; i < temp.size(); i++)
		nextTetrominos.insert(nextTetrominos.begin(), temp[i]);
}

Tetromino* Game::generateTetromino()
{
	if (DEBUGMODE) std::cout << "generating new tetromino" << std::endl;

	//fill up nextTetrominos if we're about to run out (don't let it ever reach 0 or the next piece preview will segfault)
	if (nextTetrominos.size() <= 1)
		determineNextTetrominos();

	Tetromino* newTetromino = nextTetrominos.back();
	nextTetrominos.pop_back();

	return newTetromino;
}