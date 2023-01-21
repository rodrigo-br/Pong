#include "../header_files/Game.hpp"

Game::Game() {
	this->window = nullptr;
	this->running = true;
	this->ballPos = { BALL_X, BALL_Y };
	this->paddlePos = { PADDLE_X, PADDLE_Y };
	this->ticksCount = 0;
};

bool Game::initialize() {
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

void Game::shutdown() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
};

void Game::runLoop() {
	while (this->running)
	{
		this->processInput();
		this->updateGame();
		this->generateOutput();
	}
};

void Game::processInput() {
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

bool Game::paddleAtBorders()
{
	if (this->paddlePos.y < THICKNESS && this->paddleDirection == -1)
	{
		return true;
	}
	if (this->paddlePos.y > HEIGHT - PADDLE_HEIGHT && this->paddleDirection == 1)
	{
		return true;
	}
	return false;
}

void Game::movePaddle(float deltaTime)
{
	this->paddlePos.y += this->paddleDirection * PADDLE_SPEED * deltaTime;
}

void Game::updateGame() {
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
		if (!paddleAtBorders())
			movePaddle(deltaTime);
	}
};

bool Game::createObject(struct Vector2 object, int width, int height)
{
	SDL_Rect new_object {
					static_cast<int>(object.x - THICKNESS / 2),
					static_cast<int>(object.y - THICKNESS / 2),
					width,
					height
				};
	return SDL_RenderFillRect(this->renderer, &new_object);
}

void Game::generateOutput() {
	
	if (SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255) != 0)
	{
		SDL_Log("Failed to set renderer color: %s", SDL_GetError());
	}
	if (SDL_RenderClear(this->renderer) != 0)
	{
		SDL_Log("Failed to clear renderer: %s", SDL_GetError());
	}

	if (SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255))
	{
		SDL_Log("Failed to set renderer obj color: %s", SDL_GetError());
	}

	if (createObject(this->paddlePos, THICKNESS, PADDLE_HEIGHT) != 0)
	{
		SDL_Log("Failed to create left paddle: %s", SDL_GetError());
	}
	if (createObject(this->ballPos, THICKNESS, THICKNESS) != 0)
	{
		SDL_Log("Failed to create ball: %s", SDL_GetError());
	}

	SDL_RenderPresent(this->renderer);
};
