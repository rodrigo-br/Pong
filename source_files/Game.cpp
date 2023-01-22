#include "../header_files/Game.hpp"

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->running = true;
	this->ballPos = { BALL_X, BALL_Y };
	this->paddlePos = { PADDLE_X, PADDLE_Y };
	this->paddleEnemy = { ENEMY_X, ENEMY_Y };
	this->ticksCount = 0;
	this->ballVel = { -200.0f, 235.0f };
};

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	this->window = SDL_CreateWindow(TITLE, START_X, START_Y, WIDTH, HEIGHT, W_FLAGS);
	if (!this->window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	this->renderer = SDL_CreateRenderer(this->window, R_DRIVER, R_FLAGS);
	if (!this->renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
};

void Game::shutdown()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
};

void Game::runLoop()
{
	while (this->running)
	{
		this->processInput();
		this->updateGame();
		this->generateOutput();
	}
};

void Game::processInput()
{
	SDL_Event		event;
	const Uint8*	state = SDL_GetKeyboardState(NULL);

	this->paddleDirection = STOPPED;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				this->running = false;
				break;
		}
	}
	if (state[SDL_SCANCODE_W])
	{
		this->paddleDirection -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		this->paddleDirection += 1;
	}
	if (state[SDL_SCANCODE_ESCAPE])
	{
		this->running = false;
	}
};

inline void Game::movePaddle(float deltaTime)
{
	this->paddlePos.y += this->paddleDirection * PADDLE_SPEED * deltaTime;
};

bool Game::collisionWalls()
{
	return ((this->ballPos.y <= THICKNESS && this->ballVel.y < 0.0f) ||
		(this->ballPos.y >= HEIGHT - THICKNESS && this->ballVel.y > 0.0f));
};

bool Game::collisionPaddle()
{
	float diff = this->paddlePos.y - this->ballPos.y;

	diff = (diff > 0.0f) ? diff : -diff;

	return ((diff <= PADDLE_HEIGHT / 2.0f &&
		this->ballPos.x <= 25.0f && this->ballPos.x >= 20.0f &&
		this->ballVel.x < 0.0f));
};

bool Game::collisionEnemy()
{
	float diff = this->paddleEnemy.y - this->ballPos.y;

	diff = (diff > 0.0f) ? diff : -diff;

	return ((diff <= PADDLE_HEIGHT / 2.0f &&
		this->ballPos.x >= WIDTH - 25.0f && this->ballPos.x <= WIDTH - 20.0f &&
		this->ballVel.x > 0.0f));
};

inline static bool testGameOver(float ballX)
{
	return (ballX >= -100.0f);
};

void Game::moveBall(float deltaTime)
{
	this->ballPos.x += this->ballVel.x * deltaTime;
	this->ballPos.y += this->ballVel.y * deltaTime;
	if (collisionWalls())
	{
		this->ballVel.y *= -1;
	}
	if (collisionPaddle() || collisionEnemy())
	{
		this->ballVel.x *= -1;
	}
	this->running = testGameOver(this->ballPos.x);
};

void Game::moveEnemy(float deltaTime)
{
	if (this->ballPos.x < WIDTH * 0.6f)
		return;
	if (this->paddleEnemy.y < this->ballPos.y)
	{
		this->paddleEnemy.y += PADDLE_SPEED * deltaTime;
	}
	else if (this->paddleEnemy.y > this->ballPos.y)
	{
		this->paddleEnemy.y -= PADDLE_SPEED * deltaTime;
	}
};

void Game::updateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->ticksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - this->ticksCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	this->ticksCount = SDL_GetTicks();
	if (this->paddleDirection != STOPPED)
	{
		movePaddle(deltaTime);
		if (this->paddlePos.y < (PADDLE_HEIGHT / 2.0f + THICKNESS))
		{
			this->paddlePos.y = PADDLE_HEIGHT / 2.0f + THICKNESS;
		}
		else if (this->paddlePos.y > (HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS))
		{
			this->paddlePos.y = HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS;
		}
	}
	moveBall(deltaTime);
	moveEnemy(deltaTime);
};

inline static void drawPaddle(SDL_Renderer *renderer, struct Vector2 &position)
{
	SDL_Rect paddle{
		static_cast<int>(position.x),
		static_cast<int>(position.y - PADDLE_HEIGHT / 2),
		THICKNESS,
		static_cast<int>(PADDLE_HEIGHT)
	};
	SDL_RenderFillRect(renderer, &paddle);
};

inline static void drawBall(SDL_Renderer *renderer, struct Vector2 &position)
{
	SDL_Rect ball{	
		static_cast<int>(position.x - THICKNESS / 2),
		static_cast<int>(position.y - THICKNESS / 2),
		THICKNESS,
		THICKNESS
	};
	SDL_RenderFillRect(renderer, &ball);
};

inline static void drawWalls(SDL_Renderer *renderer)
{
	SDL_Rect wall{ 0, 0, static_cast<int>(WIDTH), THICKNESS };
	SDL_RenderFillRect(renderer, &wall);
	
	wall.y = 768 - THICKNESS;
	SDL_RenderFillRect(renderer, &wall);
};

inline void Game::drawObjects()
{
	drawWalls(this->renderer);
	drawPaddle(this->renderer, this->paddlePos);
	drawPaddle(this->renderer, this->paddleEnemy);
	drawBall(this->renderer, this->ballPos);
};

static void clearOutput(SDL_Renderer *renderer)
{
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0)
	{
		SDL_Log("Failed to set renderer color: %s", SDL_GetError());
	}
	if (SDL_RenderClear(renderer) != 0)
	{
		SDL_Log("Failed to clear renderer: %s", SDL_GetError());
	}
};

void Game::generateOutput()
{
	clearOutput(this->renderer);
	if (SDL_SetRenderDrawColor(this->renderer, 200, 75, 200, 255))
	{
		SDL_Log("Failed to set renderer obj color: %s", SDL_GetError());
	}

	drawObjects();

	SDL_RenderPresent(this->renderer);
};
