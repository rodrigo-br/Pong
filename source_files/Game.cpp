#include "../header_files/Game.hpp"

Game::Game() {
	this->window = nullptr;
	this->running = true;
};

bool Game::initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	return true;
}