#include "cube.h"
#include <stdio.h>

int name_check(char *y)
{
    int len = ft_strlen(y);
    if (len < 4)
        return 0;
    if (ft_strncmp(&y[len - 4], ".cub", 4) == 0)
        return 1;
    return 0;
}

int game_loop(t_vars *vars)
{
    printf("Game loop executing...\n");

    if (!vars->img)
        vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
    if (!vars->img_addr)
        vars->img_addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_length, &vars->endian);

    // Simple render: fill screen with green
    for (int y = 0; y < vars->height; y++)
    {
        for (int x = 0; x < vars->width; x++)
        {
            char *dst = vars->img_addr + (y * vars->line_length + x * (vars->bpp / 8));
            *(unsigned int *)dst = 0x00FF00; // Green color
        }
    }

    if (vars->img && vars->win)
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

    return 0;
}

int main(int argc, char **argv)
{
    t_vars *vars;

    if (argc != 2)
    {
        printf("Error: Invalid number of arguments.\n");
        return 1;
    }

    if (!name_check(argv[1]))
    {
        printf("Error: File extension must be .cub\n");
        return 1;
    }

    vars = ft_t_vars();

    // Check MLX initialization
    vars->mlx = mlx_init();
    if (!vars->mlx)
    {
        printf("Error: Failed to initialize MLX.\n");
        return 1;
    }

    vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "Cube3D");
    if (!vars->win)
    {
        printf("Error: Failed to create window.\n");
        return 1;
    }

    mlx_hook(vars->win, 2, 1L << 0, handle_key_press, vars);
    mlx_hook(vars->win, 3, 1L << 1, handle_key_release, vars);
    mlx_hook(vars->win, 17, 0, exit_game, vars);

    mlx_loop_hook(vars->mlx, game_loop, vars);
    mlx_loop(vars->mlx);

    free_cube3d(vars);
    return 0;
}
