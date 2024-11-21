CC = gcc
CFLAGS = -Wall -Wextra -Werror 

INFILES = main.c \
        cub3d.c


OBJFILES = $(INFILES:.c=.o)

NAME = braiiiiiiinnnzzzZ

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME)

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
