/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:15:01 by fkuruthl          #+#    #+#             */
/*   Updated: 2024/12/29 12:15:03 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void init_ray(t_vars *vars, t_ray *ray, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)vars->width - 1;
	ray->dir_x = vars->dir_x + vars->plane_x * camera_x;
	ray->dir_y = vars->dir_y + vars->plane_y * camera_x;
	ray->map_x = (int)vars->pos_x;
	ray->map_y = (int)vars->pos_y;
	ray->delta_dist_x = fabs(1 / (ray->dir_x != 0 ? ray->dir_x : 1e-6));
	ray->delta_dist_y = fabs(1 / (ray->dir_y != 0 ? ray->dir_y : 1e-6));
}

void perform_dda(t_vars *vars, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (vars->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - vars->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (vars->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - vars->pos_y) * ray->delta_dist_y;
	}
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

double calculate_distance(t_vars *vars, t_ray *ray)
{
	if (ray->side == 0)
		return (ray->map_x - vars->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		return (ray->map_y - vars->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void render_column(t_vars *vars, int x, double distance, t_ray *ray)
{
	int line_height;
	int draw_start;
	int draw_end;
	double wall_x;
	int tex_x, tex_y;
	double tex_pos;
	double step;
	int y;
	char *color;
	t_texture *texture;

	line_height = (int)(vars->height / distance);
	draw_start = -line_height / 2 + vars->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + vars->height / 2;
	if (draw_end >= vars->height)
		draw_end = vars->height - 1;

	if (ray->side == 0 && ray->dir_x > 0)
		texture = vars->textures->ea;
	else if (ray->side == 0 && ray->dir_x < 0)
		texture = vars->textures->we;
	else if (ray->side == 1 && ray->dir_y > 0)
		texture = vars->textures->so;
	else
		texture = vars->textures->no;

	if (ray->side == 0)
		wall_x = vars->pos_y + distance * ray->dir_y;
	else
		wall_x = vars->pos_x + distance * ray->dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		tex_x = texture->width - tex_x - 1;

	step = (double)texture->height / line_height;
	tex_pos = (draw_start - vars->height / 2 + line_height / 2) * step;

	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
		char *dst = vars->img_addr + (y * vars->line_length + x * (vars->bpp / 8));
		*(unsigned int *)dst = *(unsigned int *)color;
		y++;
	}
}

void raycasting(t_vars *vars)
{
	int x;
	t_ray ray;

	x = 0;
	while (x < vars->width)
	{
		init_ray(vars, &ray, x);
		perform_dda(vars, &ray);
		double distance = calculate_distance(vars, &ray);
		render_column(vars, x, distance, &ray);
		x++;
	}
}