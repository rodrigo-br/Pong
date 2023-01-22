#include "../header_files/Game.hpp"

Game::Game() : window(nullptr), renderer(nullptr), running(true), ticksCount(0)
{
	this->Balls.push_back(std::make_pair(Vec2{BALL_X, BALL_Y}, Vec2{-200.0f, 235.0f}));
	this->Balls.push_back(std::make_pair(Vec2{BALL_X, BALL_Y}, Vec2{200.0f, -240.0f}));
	this->paddlePos = { PADDLE_X, PADDLE_Y };
	this->paddleEnemy = { ENEMY_X, ENEMY_Y };
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

bool Game::collisionWalls(std::pair<Vec2, Vec2>& ball)
{
	return ((ball.first.y <= THICKNESS && ball.second.y < 0.0f) ||
		(ball.first.y >= HEIGHT - THICKNESS && ball.second.y > 0.0f));
};

bool Game::collisionPaddle(std::pair<Vec2, Vec2>& ball)
{
	float diff = this->paddlePos.y - ball.first.y;

	diff = (diff > 0.0f) ? diff : -diff;

	return ((diff <= PADDLE_HEIGHT / 2.0f &&
		ball.first.x <= 25.0f && ball.first.x >= 20.0f &&
		ball.second.x < 0.0f));
};

bool Game::collisionEnemy(std::pair<Vec2, Vec2>& ball)
{
	float diff = this->paddleEnemy.y - ball.first.y;

	diff = (diff > 0.0f) ? diff : -diff;

	return ((diff <= PADDLE_HEIGHT / 2.0f &&
		ball.first.x >= WIDTH - 25.0f && ball.first.x <= WIDTH - 20.0f &&
		ball.second.x > 0.0f));
};

inline static bool testGameOver(float ballX)
{
	return (ballX >= -100.0f);
};

void Game::moveBall(float deltaTime, std::pair<Vec2, Vec2>& ball)
{
	ball.first.x += ball.second.x * deltaTime;
	ball.first.y += ball.second.y * deltaTime;
	if (collisionWalls(ball))
	{
		ball.second.y *= -1;
	}
	if (collisionPaddle(ball) || collisionEnemy(ball))
	{
		ball.second.x *= -1;
	}
	if (this->running)
		this->running = testGameOver(ball.first.x);
};

void Game::moveEnemy(float deltaTime, std::pair<Vec2, Vec2>& ball)
{
	if (ball.first.x < WIDTH * 0.6f)
		return;
	if (this->paddleEnemy.y < ball.first.y)
	{
		this->paddleEnemy.y += PADDLE_SPEED * deltaTime;
	}
	else if (this->paddleEnemy.y > ball.first.y)
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
	for (int i = 0; i < 3; i++)
	{
		moveBall(deltaTime, Balls[i]);
		moveEnemy(deltaTime, Balls[i]);
	}
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
	for (int i = 0; i < 3; i++)
		drawBall(this->renderer, Balls[i].first);
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
