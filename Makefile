CC = gcc
CFLAGS = -Wall -Wextra -Werror 

INFILES = main.c \
          cub3d.c \
          get_next_line.c \
          get_next_line_utils.c

OBJFILES = $(INFILES:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME)

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
