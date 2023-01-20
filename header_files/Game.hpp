#ifndef GAME_HPP
# define GAME_HPP

# include <SDL2/SDL.h>

/**
 * @brief The game class is responsible for the game loop. The game loop is
 * basically a loop that runs until the game is over. It is responsible for
 * processing the input, updating the game world and generating the output.
 */
class Game
{
	private:
		SDL_Window*		window;
		bool			running;

	public:
		Game();
		bool initialize();
		void runLoop();
		void shutdown();

	private:
		void processInput();
		void updateGame();
		void generateOutput();
};



#endif