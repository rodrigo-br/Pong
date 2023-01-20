#ifndef DEFINES_HPP
# define DEFINES_HPP


/**
 * @brief Title of the window
 */
# define TITLE "Pac-Man"

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

#endif