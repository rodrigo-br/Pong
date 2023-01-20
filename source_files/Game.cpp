#include "../header_files/Game.hpp"

Game::Game() {
	this->window = nullptr;
	this->running = true;
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
	SDL_RenderPresent(this->renderer);
};
