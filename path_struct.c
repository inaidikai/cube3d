/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2024/12/23 15:00:31 by inkahar          ###   ########.fr       */
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

static int is_end(int index, t_map *map) {
    int i = index + 1;
    while (map->map[i]) {
        if (ft_strlen(map->map[i]) > 0)
            return 1;
        i++;
    }
    return 0; // Do not modify map->map[i]
}


char **ft_dup_cpp(char **src, int len)
{
    char **dup;
    int i = 0;

    dup = (char **)malloc((len + 1) * sizeof(char *));
    if (!dup)
        return NULL;

    while (i < len && src[i])
    {
        dup[i] = ft_strdup(src[i]);
        if (!dup[i])
        {
            ft_free_pp((void **)dup);
            return NULL;
        }
        i++;
    }
    dup[i] = NULL;

    return dup;
}
char **skip_to_map(char **lines)
{
    char **map;
    int i = 0;
    int j = 0;
    size_t len;

    // Find the first valid map line
    while (lines[i])
    {
        // Ignore configuration lines and empty lines
        if (!ft_strncmp(lines[i], "NO", 2) || !ft_strncmp(lines[i], "SO", 2) || \
            !ft_strncmp(lines[i], "WE", 2) || !ft_strncmp(lines[i], "EA", 2) || \
            !ft_strncmp(lines[i], "F", 1) || !ft_strncmp(lines[i], "C", 1) || \
            ft_strlen(lines[i]) == 0)
        {
            i++;
            continue;
        }

        // If the line contains valid map characters, break
        if (ft_strchr(lines[i], '1') || ft_strchr(lines[i], '0') || \
            ft_strchr(lines[i], 'N') || ft_strchr(lines[i], 'E') || \
            ft_strchr(lines[i], 'W') || ft_strchr(lines[i], 'S'))
        {
            break;
        }

        i++;
    }

    // Ensure we found a valid starting point
    if (!lines[i])
    {
        perror_cube3d("Map section not found", 0);
        return NULL;
    }

    // Create a new array starting from the map part
    map = ft_dup_cpp(lines + i, ft_array_length(lines + i));
    if (!map)
    {
        perror_cube3d("Failed to allocate memory for the map", 0);
        return NULL;
    }

    // Trim trailing newlines from each line in the map
    j = 0;
    while (map[j])
    {
        len = ft_strlen(map[j]);
        if (len > 0 && map[j][len - 1] == '\n')
            map[j][len - 1] = '\0'; // Remove trailing newline
        j++;
    }

    return map;
}


static void formatmap(t_map *map)
{
    int num_rows = 0, max_length = 0, length = 0;
    char **newmap;
    char **actual_map;
    int i = 0, j;

    // Skip configuration lines to get the actual map
    actual_map = skip_to_map(map->map);
    if (!actual_map)
        exit(perror_cube3d("Failed to extract actual map", 0));

    // Debug: Print actual_map for verification
    printf("Actual Map Extracted:\n");
    i = 0;
    while (actual_map[i])
    {
        printf("%s\n", actual_map[i]);
        i++;
    }

    // Calculate dimensions based on the actual map
    while (actual_map[num_rows])
    {
        length = ft_strlen(actual_map[num_rows]);
        if (length > max_length)
            max_length = length;
        num_rows++;
    }

    printf("Longest Row Length: %d\n", max_length);
    printf("Number of Rows: %d\n", num_rows);

    // Allocate space for the new formatted map
    newmap = (char **)malloc((num_rows + 1) * sizeof(char *));
    if (!newmap)
        exit(perror_cube3d("Memory allocation failed for newmap", 0));
    newmap[num_rows] = NULL;

    // Fill newmap with formatted rows
    i = 0;
    while (i < num_rows)
    {
        newmap[i] = malloc(max_length + 1);
        if (!newmap[i])
        {
            ft_free_pp((void **)newmap);
            exit(perror_cube3d("Memory allocation failed for newmap row", 0));
        }
        strcpy(newmap[i], actual_map[i]);
        length = ft_strlen(newmap[i]);
        for (j = length; j < max_length; j++)
            newmap[i][j] = ' '; // Pad with spaces
        newmap[i][max_length] = '\0';

        printf("Formatted Row %d: %s\n", i, newmap[i]); // DEBUG
        i++;
    }

    // Replace the original map with the formatted map
    ft_free_pp((void **)map->map); // Free the original map
    map->map = newmap; // Update map to the formatted map

    ft_free_pp((void **)actual_map); // Free the temporary actual_map
}

static int char_check(t_map *map) {
    int i = 0, j, count = 0;

    while (map->map[i]) {
        j = 0;
        while (map->map[i][j]) {
            if (!ft_strchr(" 10NSWE", map->map[i][j])) {
                printf("Invalid character '%c' found at [%d][%d]\n", map->map[i][j], i, j); // DEBUG
                return 0;
            }

            if (ft_strchr("NSWE", map->map[i][j]))
                count++;
            j++;
        }
        i++;
    }

    if (count != 1) {
        printf("Invalid number of player starting positions: %d\n", count); // DEBUG
        return 0;
    }
    return 1;
}
static int	is_closed(t_map *map, int i, size_t j)
{
    size_t row_len = ft_strlen(map->map[i]);

    // Ignore rows that are entirely spaces
    if (row_len == 0)
        return 0;

    // Handle trailing spaces
    if (j >= row_len) // Beyond the actual content of the row
        return 0;

    // Ignore leading spaces
    if (map->map[i][j] == ' ') {
        size_t k = 0;
        // Ignore spaces before the first map content
        while (k < row_len && map->map[i][k] == ' ')
            k++;
        if (j < k) // Leading spaces are valid
            return 0;

        // Ignore trailing spaces
        if (j >= row_len - 1) {
            printf("Trailing space ignored at [%d][%zu]\n", i, j); // DEBUG
            return 0;
        }

        // Check if the space is properly enclosed
        if (map->map[i - 1][j] != '1' && map->map[i - 1][j] != ' ') return 1;
        if (map->map[i + 1][j] != '1' && map->map[i + 1][j] != ' ') return 1;
        if (map->map[i][j - 1] != '1' && map->map[i][j - 1] != ' ') return 1;
        if (map->map[i][j + 1] != '1' && map->map[i][j + 1] != ' ') return 1;
    }

    // Check for '0' that is not properly enclosed
    if (map->map[i][j] == '0') {
        if (i == 0 || j == 0 || !map->map[i + 1] || j >= ft_strlen(map->map[i + 1]) || \
            j >= ft_strlen(map->map[i - 1]) || !map->map[i][j + 1]) {
            printf("Boundary violation at [%d][%zu]\n", i, j); // DEBUG
            return 1;
        }

        // Check for spaces surrounding the current cell
        if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || \
            map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ') {
            printf("Space adjacent to '0' at [%d][%zu]\n", i, j); // DEBUG
            return 1;
        }
    }

    return 0;
}


static int check_isclosed(int i, t_map *map)
{
    size_t j = 0;

    while (map->map[i][j]) {
        if (is_closed(map, i, j)) {
            printf("Map closure validation failed at [%d][%zu]: '%c'\n", i, j, map->map[i][j]); // DEBUG
            return 1;
        }
        j++;
    }
    printf("Row %d passed closure validation.\n", i); // DEBUG
    return 0;
}


int path_struct(t_map *map) {
    int i = 0;

    printf("%s", "inside path checker LOOOKING ");
    if (is_map_empty(map))
        exit(perror_cube3d("map is empty", 0));

    formatmap(map);

    if (ft_array_length(map->map) < 3 || char_check(map) != 1)
        exit(perror_cube3d("its nt right", 0));

    while (map->map[i]) {
        if (ft_strlen(map->map[i]) == 0) {
            if (is_end(i, map))
                return 0;
            break;
        }

        if (check_isclosed(i, map)) {
            printf("Validation failed at row %d\n", i); // DEBUG
            return 0;
        }
        i++;
    }

    printf("%s", "path checker LOOOKING DONE\n");
    return 1;
}
