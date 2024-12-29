/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:17:35 by fkuruthl          #+#    #+#             */
/*   Updated: 2024/12/29 12:17:39 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	cubcheck(char *y)
{
	int	len = ft_strlen(y);

	if (len < 4)
		return (0);
	if (ft_strcmp(&y[len - 4], ".cub") == 0)
		return (1);
	return (0);
}
int main(int argc , char **argv)
{
	if (argc != 2)
	{
		write(1,"invalid format",15); //wrote a message
		return (1); //changed to 1 instead of 0
	}
    if (cubcheck(argv[1]))
        cube3d(argv[1]);
	else
	{
		write(1,"invalid format2",15);
		return 1;
	}
	// initialiae_data();
	// game_start();
	// mlx_stuffs();
	// exit(args);
	return(0);	
}