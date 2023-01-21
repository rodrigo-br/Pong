#include "../header_files/Game.hpp"

Game::Game() {
	this->window = nullptr;
	this->running = true;
	this->ballPos = { WIDTH / 2, HEIGHT / 2 };
	this->paddlePos = { THICKNESS, HEIGHT / 2 - PADDLE_HEIGHT / 2 };
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
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				this->running = false;
				break;
		}
	}
	if (state[SDL_SCANCODE_ESCAPE])
	{
		this->running = false;
	}
};

void Game::updateGame() {
	
};

void Game::generateOutput() {
	
	if (SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255) != 0)
	{
		SDL_Log("Failed to set renderer color: %s", SDL_GetError());
	}
	if (SDL_RenderClear(this->renderer) != 0)
	{
		SDL_Log("Failed to clear renderer: %s", SDL_GetError());
	}
	// draw game scene
	// ...
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_Rect left_paddle {static_cast<int>(this->paddlePos.x),
							static_cast<int>(this->paddlePos.y - THICKNESS / 2),
							THICKNESS,
							static_cast<int>(PADDLE_HEIGHT)
						};
	SDL_RenderFillRect(this->renderer, &left_paddle);
	SDL_Rect ball {static_cast<int>(this->ballPos.x - THICKNESS / 2),
					static_cast<int>(this->ballPos.y - THICKNESS / 2),
					THICKNESS, THICKNESS
				};
	SDL_RenderFillRect(this->renderer, &ball);

	// end drawing
	SDL_RenderPresent(this->renderer);
};
