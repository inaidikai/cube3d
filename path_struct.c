/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/10 14:14:40 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"
int is_map_empty(t_map *map)
{
    if(!map->map)
    {
        return 1;
    }
    return(0);
}
void calc_dimensions(t_map *map, int *num_rows , int *max_length, int *length)
{
    *num_rows = 0;
    *max_length = 0;
    *length = 0;
    while (map->map[*num_rows])
    {
        *length = ft_strlen(map->map[*num_rows]);
        if(*length > *max_length)
        {
            *max_length = *length;
        }
        (*num_rows)++;
    }
}
void initmap(t_map *map, char *newmap[], int num_rows, int max_length)
{
    int i;
    int length;
    int j;
    i =0;
    while(i < num_rows)
    {
        newmap[i] = malloc(max_length + 1);
        ft_strcpy(newmap[i], map->map[i]);
        length = ft_strlen(newmap[i]);
        j = length;
        while(j < max_length)
        {
            newmap[i][j] = ' ';
            j++;
        }
        newmap[i][max_length] = '\0';
        i++;
    }
}
void formatmap(t_map *map)
{
    int num_rows;
    int max_length;
    int length;
    int i;
    char **newmap;
    
    num_rows = 0;
    max_length = 0;
    length = 0;
    i = 0;
    calc_dimensions(&map, &num_rows, &max_length, &length);
    newmap = (char **)malloc(num_rows * sizeof(char *));
    if(newmap)
    {
        initmap(&map ,newmap, num_rows, max_length);
        i = 0;
        while(i < num_rows)
        {
            free(map->map[i]);
            map->map[i] = newmap[i];
            i++;
        }
        free(newmap);
    }
}
int char_check(t_map *map)
{
    int i = 0;
    int j;
    int count;
    count = 0;
    while(map->map[i])
    {
        j =0;
        while(map->map[i][j])
        {
            if(!ft_strchr(" 10NSWE", map->map[i][j]))
                return 0;
            if (map->map[i][j] == "N"|| map->map[i] == "S"|| \
            map->map[i] == "E"||map->map[i] == "W")
            {
                
                count++;
            }           
            j++; 
        }
        i++;
    }
    return(count);
}
int path_struct(t_map *map)
{
    int i ;
    if(is_map_empty(&map) == 1)
        return 1;
    formatmap(&map);
    if(ft_arraylength(map->map) < 3 || char_check(&map) != 1 )
}
	if (ft_array_length(data()->map) < 3 || check_characters() != 1)
		return (1);
	i = 0;
	while (data()->map[i])
	{
		if (ft_strlen(data()->map[i]) == 0)
		{
			if (is_end(i) == 1)
				return (1);
			break ;
		}
		if (check_isclosed(i) == 1)
			return (1);
		i++;
	}
	return (0);
}