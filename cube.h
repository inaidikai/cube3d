#ifndef CUBE_H
#define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
#include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(char const *str);
char	*ft_strchr(char const *str, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char const *src);
char	*ft_strjoin(char const *s1, char const *s2);

char cube3d(char *c);
typedef struct s_map
{
    char **map;
    int width;
    int height;
}       t_map;

typedef struct s_texture
{
	int			txt;
	void		*img;
	int			width;
	int			height;
}				t_texture;

 typedef struct s_img
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	int			f;
	int			c;
	int			init;
}				t_img;

enum	e_element
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	F = 5,
	C = 6,
	IN = 7,
	OUT = 8,
	UNK = 9,
	TILES = 50,
};

#endif