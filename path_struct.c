/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/14 16:32:03 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"
int	ft_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

static int is_map_empty(t_map *map) {
    return (!map->map);
}

static void calc_dimensions(t_map *map, int *num_rows, int *max_length, int *length) {
    *num_rows = 0;
    *max_length = 0;
    *length = 0;
    while (map->map[*num_rows]) {
        *length = ft_strlen(map->map[*num_rows]);
        if (*length > *max_length)
            *max_length = *length;
        (*num_rows)++;
    }
}

static int is_end(int index, t_map *map) {
    int i = index + 1;
    while (map->map[i]) {
        if (ft_strlen(map->map[i]) > 0)
            return 1;
        i++;
    }
    map->map[i] = NULL;
    return 0;
}

static void initmap(t_map *map, char *newmap[], int num_rows, int max_length) {
    int i = 0, j, length;
    while (i < num_rows) {
        newmap[i] = malloc(max_length + 1);
        if (!newmap[i]) return; // Handle allocation failure
        strcpy(newmap[i], map->map[i]);
        length = ft_strlen(newmap[i]);
        for (j = length; j < max_length; j++)
            newmap[i][j] = ' ';
        newmap[i][max_length] = '\0';
        i++;
    }
}

static void formatmap(t_map *map) {
    int num_rows = 0, max_length = 0, length = 0, i = 0;
    char **newmap;

    calc_dimensions(map, &num_rows, &max_length, &length);
    newmap = (char **)malloc((num_rows + 1) * sizeof(char *));
    if (!newmap)
        return;
    newmap[num_rows] = NULL;
    initmap(map, newmap, num_rows, max_length);

    while (i < num_rows) {
        free(map->map[i]);
        map->map[i] = newmap[i];
        printf("oppp    :::%s", map->map[i]);
        i++;
    }
    free(newmap);
}

static int char_check(t_map *map) {
    int i = 0, j, count = 0;
    while (map->map[i]) {
        j = 0;
        while (map->map[i][j]) {
            if (!ft_strchr(" 10NSWE", map->map[i][j]))
            {
                printf("imsaryy");
                return (0);
            }
                
            if (ft_strchr("NSWE", map->map[i][j]))
                count++;
            j++;
        }
        i++;
    }
    return count;
}

static int	is_closed(t_map *map, int i, int j)
{
	if (map->map[i][j] == '0' \
		|| (map->map[i][j] != '1' && map->map[i][j] != ' '))
	{
		if (i == 0 || !map->map[i + 1] || j == 0 || !map->map[i][j + 1])
			return (1);
		if (map->map[i - 1] && map->map[i - 1][j]
			&& map->map[i - 1][j] == ' ')
			return (1);
		if (map->map[i + 1] && map->map[i + 1][j]
			&& map->map[i + 1][j] == ' ')
			return (1);
		if (map->map[i] && map->map[i][j - 1]
			&& map->map[i][j - 1] == ' ')
			return (1);
		if (map->map[i] && map->map[i][j + 1]
			&& map->map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

static int check_isclosed(int i, t_map *map) {
    int j = 0;
    while (map->map[i][j]) {
        if (is_closed(map , i, j))
            return 1;
        j++;
    }
    return 0;
}

int skip_to_map(t_map *map, int *start_row) {
    int i = 0;
    while (map->map[i]) {
        if (!is_configuration_line(map->map[i]) && 
            (ft_strchr(map->map[i], '0') || 
             ft_strchr(map->map[i], '1') || 
             ft_strchr(map->map[i], 'NSWE'))) {
            *start_row = i; // Found the start of the map
            return 1;
        }
        i++;
    }
    return 0; // Map not found
}

int path_struct(t_map *map) {
    int i = 0;
    printf("%s", "inside path checker LOOOKING ");
    if (is_map_empty(map))
        exit(perror_cube3d("map is empty", 0));
    formatmap(map);
    
    if (ft_array_length(map->map) < 3 || char_check(map) != 1)
        exit(perror_cube3d("its not right", 0));
    while (map->map[i]) {
        if (ft_strlen(map->map[i]) == 0) {
            if (is_end(i, map))
                return 1;
            break;
        }
        if (check_isclosed(i, map))
            return 1;
        i++;
    }
    printf("%s", "path checker LOOOKING DONE");
    return 0;
}
