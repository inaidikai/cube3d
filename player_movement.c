/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:39:06 by fkuruthl          #+#    #+#             */
/*   Updated: 2024/12/30 03:27:42 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void move_forward(t_vars *vars, double move_speed)
{
	double new_x = vars->pos_x + vars->dir_x * move_speed;
	double new_y = vars->pos_y + vars->dir_y * move_speed;

	if (vars->map[(int)(vars->pos_y)][(int)(new_x)] != '1')
		vars->pos_x = new_x;
	if (vars->map[(int)(new_y)][(int)(vars->pos_x)] != '1')
		vars->pos_y = new_y;
}

void move_backward(t_vars *vars, double move_speed)
{
	double new_x = vars->pos_x - vars->dir_x * move_speed;
	double new_y = vars->pos_y - vars->dir_y * move_speed;

	if (vars->map[(int)(vars->pos_y)][(int)(new_x)] != '1')
		vars->pos_x = new_x;
	if (vars->map[(int)(new_y)][(int)(vars->pos_x)] != '1')
		vars->pos_y = new_y;
}

void move_left(t_vars *vars, double move_speed)
{
	double new_pos_x = vars->pos_x - vars->plane_x * move_speed;
	double new_pos_y = vars->pos_y - vars->plane_y * move_speed;

	if (vars->map[(int)new_pos_y][(int)(vars->pos_x)] != '1')
		vars->pos_y = new_pos_y;
	if (vars->map[(int)(vars->pos_y)][(int)new_pos_x] != '1')
		vars->pos_x = new_pos_x;
}

void move_right(t_vars *vars, double move_speed)
{
	double new_pos_x = vars->pos_x + vars->plane_x * move_speed;
	double new_pos_y = vars->pos_y + vars->plane_y * move_speed;

	if (vars->map[(int)new_pos_y][(int)(vars->pos_x)] != '1')
		vars->pos_y = new_pos_y;
	if (vars->map[(int)(vars->pos_y)][(int)new_pos_x] != '1')
		vars->pos_x = new_pos_x;
}

void rotate_left(t_vars *vars, double rot_speed)
{
	double old_dir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(-rot_speed) - vars->dir_y * sin(-rot_speed);
	vars->dir_y = old_dir_x * sin(-rot_speed) + vars->dir_y * cos(-rot_speed);

	double old_plane_x = vars->plane_x;
	vars->plane_x = vars->plane_x * cos(-rot_speed) - vars->plane_y * sin(-rot_speed);
	vars->plane_y = old_plane_x * sin(-rot_speed) + vars->plane_y * cos(-rot_speed);
}

void rotate_right(t_vars *vars, double rot_speed)
{
	double old_dir_x = vars->dir_x;
	vars->dir_x = vars->dir_x * cos(rot_speed) - vars->dir_y * sin(rot_speed);
	vars->dir_y = old_dir_x * sin(rot_speed) + vars->dir_y * cos(rot_speed);

	double old_plane_x = vars->plane_x;
	vars->plane_x = vars->plane_x * cos(rot_speed) - vars->plane_y * sin(rot_speed);
	vars->plane_y = old_plane_x * sin(rot_speed) + vars->plane_y * cos(rot_speed);
}

void initialize_keys(t_vars *vars)
{
	vars->keys.w = 13;
	vars->keys.a = 0;
	vars->keys.s = 1;
	vars->keys.d = 2;
}

int exit_game(t_vars *vars)
{
    if (vars->textures)
    {
        if (vars->textures->no)
            mlx_destroy_image(vars->mlx, vars->textures->no->img);
        if (vars->textures->so)
            mlx_destroy_image(vars->mlx, vars->textures->so->img);
        if (vars->textures->we)
            mlx_destroy_image(vars->mlx, vars->textures->we->img);
        if (vars->textures->ea)
            mlx_destroy_image(vars->mlx, vars->textures->ea->img);
    }
    if (vars->img)
        mlx_destroy_image(vars->mlx, vars->img);
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    free_cube3d(vars);
    exit(0);
    return (0); // Return 0 as required by mlx_hook
}

int handle_key_release(int keycode, t_vars *vars)
{
    if (keycode == vars->keys.w)
        vars->keys.w = 0;
    else if (keycode == vars->keys.s)
        vars->keys.s = 0;
    else if (keycode == vars->keys.a)
        vars->keys.a = 0;
    else if (keycode == vars->keys.d)
        vars->keys.d = 0;
    else if (keycode == LEFT_ARROW)
        vars->keys.left = 0;
    else if (keycode == RIGHT_ARROW)
        vars->keys.right = 0;
    return (0);
}

int handle_key_press(int keycode, t_vars *vars)
{
	double move_speed = 0.1;
	double rot_speed = 0.05;

	if (keycode == vars->keys.w)
		move_forward(vars, move_speed);
	else if (keycode == vars->keys.s)
		move_backward(vars, move_speed);
	else if (keycode == vars->keys.a)
		move_left(vars, move_speed);
	else if (keycode == vars->keys.d)
		move_right(vars, move_speed);
	else if (keycode == LEFT_ARROW)
		rotate_left(vars, rot_speed);
	else if (keycode == RIGHT_ARROW)
		rotate_right(vars, rot_speed);
	else if (keycode == ESC_KEY)
		exit_game(vars);
	return (0);
}