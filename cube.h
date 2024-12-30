// #ifndef CUBE_H
// #define CUBE_H

// # include <unistd.h>
// # include <stdlib.h>
// # include <mlx.h>
// # include <limits.h>
// # include <stdio.h>
// # include <string.h>
// #include <fcntl.h>
// #include <fcntl.h>
// #include <string.h>
// #include "libft/libft.h"
// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 42
// # endif

// typedef struct s_vars		t_vars;
// typedef struct s_map
// {
//     char **map;
//     int width;
//     int height;
// }       t_map;
// typedef struct s_vars
// {
// 	void		*mlx;
// 	void		*win;
// 	char		*img;
// 	char		*addr;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// 	char		**map;
// 	int			map_y;
// 	int			map_x;
// 	int			pos; // player starting postion
// 	float		pos_x; // player  x position
// 	float		pos_y; //player y position
// 	int			player_side;
// 	int			map_on;
// 	int			enemy_win;
// 	int			end_game;
// 	int			steps;
// 	int			time;
// 	int			init;
// 	int			radian;
// 	int			player_angle;
// 	int			rotation;
// 	float		player_cos;
// 	float		player_sin;
// 	float		radius;
// 	double		speed;
// }
// t_vars;
// typedef struct s_texture
// {
// 		int			txt;
// 	void		*img;
// 	int			width;
// 	int			height;
// 	float		pix_x;
// 	float		pix_y;
// 	char		*addr;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// }				t_texture;

#ifndef CUBE_H
#define CUBE_H

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>


#include <string.h>
#include <fcntl.h>
#include "libft/libft.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LEFT_ARROW 123
#define RIGHT_ARROW 124
#define ESC_KEY 53
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#define SKY_COLOR 0x87CEEB 
#define FLOOR_COLOR 0x8B4513 


typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int type;
}	t_texture;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int left;
    int right;
}	t_keys;

typedef struct s_img
{
	t_texture	*no;
	t_texture	*so;
	t_texture	*we;
	t_texture	*ea;
	int			f;
	int			c;
	int			init;
}	t_img;

typedef struct s_vars
{
	void		*mlx;
	int init;
	int		map_x;
	int		map_y;
	void		*win;
	void		*img;
	char		*img_addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_img		*textures;
	char		**map;
	int			map_width;
	int			map_height;
	float		pos_x;
	float		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			width;
	int			height;
	t_keys keys;
}	t_vars;



typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
}	t_ray;



enum	e_element
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	F = 5,
	C = 6,
};

char cube3d(char *c);
void ft_free_pp(void **argv);
int handle_key_press(int keycode, t_vars *vars);
int handle_key_release(int keycode, t_vars *vars);
int exit_game(t_vars *vars);
void	raycasting(t_vars *vars);
void	init_ray(t_vars *vars, t_ray *ray, int x);
void	perform_dda(t_vars *vars, t_ray *ray);
double	calculate_distance(t_vars *vars, t_ray *ray);
void	render_column(t_vars *vars, int x, double distance, t_ray *ray);
t_texture	*load_texture(void *mlx, char *path);
int		path_struct(t_map *map);
char	*get_next_line(int fd);
void	free_cube3d(t_vars *vars);
t_vars	*ft_t_vars(void);
int path_struct(t_map *map);
int perror_cube3d(char *msg, int flag);

#endif
