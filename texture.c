/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 01:55:13 by fkuruthl          #+#    #+#             */
/*   Updated: 2024/12/30 03:35:03 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_background(t_vars *vars)
{
    int y = 0;
    int x;
    while (y < vars->height / 2) 
    {
        x = 0;
        while (x < vars->width)
        {
            mlx_pixel_put(vars->mlx, vars->win, x, y, SKY_COLOR);
            x++;
        }
        y++;
    }
    while (y < vars->height)
    {
        x = 0;
        while (x < vars->width)
        {
            mlx_pixel_put(vars->mlx, vars->win, x, y, FLOOR_COLOR);
            x++;
        }
        y++;
    }
}

t_texture *load_texture(void *mlx, char *path)
{
    t_texture *texture = malloc(sizeof(t_texture));
    if (!texture)
    {
        perror("Error: Memory allocation failed for texture");
        exit(EXIT_FAILURE);
    }
    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
    if (!texture->img)
    {
        perror("Error: Failed to load texture");
        free(texture);
        exit(EXIT_FAILURE);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    return texture;
}


void free_texture(t_vars *vars, t_texture *texture)
{
    if (texture && texture->img)
        mlx_destroy_image(vars->mlx, texture->img);
    free(texture);
}