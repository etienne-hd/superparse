CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -g
NAME = superparse.a

OBJ_DIR = .build/
SRC_DIR = source/
INC_DIR = include/

INCLUDE = $(INC_DIR)superparse.h
SOURCE = $(SRC_DIR)parser.c \
	$(SRC_DIR)utils.c \
	$(SRC_DIR)handler.c \
	$(SRC_DIR)help.c

OBJS = $(SOURCE:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
