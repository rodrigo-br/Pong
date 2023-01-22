#ifndef GAME_HPP
# define GAME_HPP

# include <SDL2/SDL.h>
# include <vector>
# include <utility>
# include "../header_files/defines.hpp"

/**
 * @brief The game class is responsible for the game loop. The game loop is
 * basically a loop that runs until the game is over. It is responsible for
 * processing the input, updating the game world and generating the output.
 */
class Game
{
	private:
		SDL_Window		*window;
		SDL_Renderer	*renderer;
		bool			running;
		Vec2			paddlePos;
		Vec2			paddleEnemy;
		Uint32			ticksCount;
		int8_t			paddleDirection;
		std::vector<std::pair<Vec2, Vec2>> Balls;

	public:
		/**
		 * @brief Construct a new Game object, setting the window to a null
		 * pointer and the running variable to true.
		 */
		Game();

		/**
		 * @brief Initialize the game.
		 * 
		 * @return true if the game was initialized successfully.
		 * false otherwise.
		 */
		bool initialize();

		/**
		 * @brief Run the game loop until the game is over (running is false).
		 */
		void runLoop();

		/**
		 * @brief Shutdown the game.
		 */
		void shutdown();

	private:

		void		processInput();
		void		updateGame();
		void		generateOutput();
		bool		collisionWalls(std::pair<Vec2, Vec2>& ball);
		bool		collisionPaddle(std::pair<Vec2, Vec2>& ball);
		bool		collisionEnemy(std::pair<Vec2, Vec2>& ball);
		void		moveBall(float deltaTime, std::pair<Vec2, Vec2>& ball);
		void		moveEnemy(float deltaTime, std::pair<Vec2, Vec2>& ball);
		inline void	movePaddle(float deltaTime);
		inline void	drawObjects();
};



#endif