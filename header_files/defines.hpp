#ifndef DEFINES_HPP
# define DEFINES_HPP


/**
 * @brief Title of the window
 */
# define TITLE "Pong"

/**
 * @brief Top left x-coordinate of window
 */
# define START_X 100

/**
 * @brief Top left y-coordinate of window
 */
# define START_Y 100

/**
 * @brief Width of window
 */
# define WIDTH 1024

/**
 * @brief Height of window
 */
# define HEIGHT 768

/**
 * @brief Window flags - 0 for no flags
 */
# define W_FLAGS 0 

/**
 * @brief Renderer Driver specifies which graphics driver to use; this might be 
 * relevant if the game has multiple windows. But with only a single window, 
 * the default is -1, which means to let SDL decide
 * 
 */
# define R_DRIVER -1

/**
 * @brief the last parameter is for initialization flags. 
 * Here, i choose to use an accelerated renderer (meaning it takes advantage of 
 * graphics hardware) and enable vertical synchronization. These two flags are 
 * the only flags of note for SDL_CreateRenderer
 * 
 */
# define R_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

/**
 * @brief The thickness of the walls
 */
# define THICKNESS 15

# define PADDLE_HEIGHT 100.0f

/**
 * @brief Initial X position of the ball. Set to the center of the screen
 */
# define BALL_X (WIDTH / 2)

/**
 * @brief Initial Y position of the ball. Set to the center of the screen
 */
# define BALL_Y (HEIGHT / 2)

/**
 * @brief Initial X position of the paddle. Set to the left side of the screen
 */
# define PADDLE_X 10.0f

/**
 * @brief Initial Y position of the paddle. Set to the center of the left 
 * side of the screen
 */
# define PADDLE_Y (HEIGHT / 2)

/**
 * @brief When paddleDirection is set to 0, the paddle is not moving
 */
# define STOPPED 0

# define PADDLE_SPEED 300.0f

struct Vector2 {
	float x;
	float y;
};


#endif