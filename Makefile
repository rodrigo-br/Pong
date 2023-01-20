NAME	= PacMan

DIRS	= obj, header_files, source_files

SRC		= $(shell ls source_files/ | grep .cpp$)

OBJ_DIR = obj

OBJ 	= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

CC		= c++

FLAGS	= -g3 -Wall -Wextra -Werror

VPATH	= $(DIRS)

all: $(NAME)

%.o:%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
		$(CC) $(FLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: %.cpp Makefile | $(OBJ_DIR)
		$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

valclean: fclean
		rm -rf leaks log

re:		fclean all

val:	re
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="leaks" ./$(NAME) 1> log