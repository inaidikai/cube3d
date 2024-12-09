/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuruthl <fkuruthl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/09 15:19:16 by fkuruthl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
int path_struct(t_map *map)
{
    if(!map->map)
    {
        return(printf("where is the map broski"),1);
    }
	if(!map_sides)
	{
		return(printf("no walls present, who stole"),1);
	}
	if(!no_map_elements)
	{
		return(printf("no elements, who ate"),1);
	}
	if(!no_player && player->pdir == 0 && > 1)
	{
		return(printf("no player found, then with what will u play?"),1);
	}
	if(anytthing_after_the_map == 0)
	{
		return(printf("There shoudn't be anything after the map"),1);
	}
}