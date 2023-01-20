#include "../header_files/Game.hpp"

Game::Game() {
	this->window = nullptr;
	this->running = true;
};

bool Game::initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	this->window = SDL_CreateWindow(TITLE, START_X, START_Y, WIDTH, HEIGHT, FLAGS);
	if (!this->window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	return true;
};

void Game::shutdown() {
	SDL_DestroyWindow(this->window);
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
	
};

void Game::updateGame() {
	
};

void Game::generateOutput() {
	
};