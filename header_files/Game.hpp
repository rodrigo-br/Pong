#ifndef GAME_HPP
# define GAME_HPP

# include <SDL2/SDL.h>
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
		struct Vector2	paddlePos;
		struct Vector2	paddleEnemy;
		struct Vector2	ballPos;
		struct Vector2	ballVel;
		Uint32			ticksCount;
		int8_t			paddleDirection;

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
		bool		collisionWalls();
		bool		collisionPaddle();
		bool		collisionEnemy();
		void		moveBall(float deltaTime);
		void		moveEnemy(float deltaTime);
		inline void	movePaddle(float deltaTime);
		inline void	drawObjects();
};



#endif