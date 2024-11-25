#include "cube.h"
int fill(t_map *map, char *c)
{
    int fd;
    char *line;
    size_t width;
    int height;

    fd = open(c, O_RDONLY);
    if(fd < 0)
        printf("sSs");
    line =  get_next_line(fd);
    width = ft_strlen(line);
    height = 0;
     printf("%s", line);
    while(line)
    {
        if(width != ft_strlen(line))
        {
            free(line);
            printf("s");
        } 
              printf("%s", line);
        free(line);
 
        line = get_next_line(fd);
        printf("%s", line);
        height++;
    }
    close(fd);
    map->height = height;
    return(width);
}
void store (t_map *map, char *c)
{
    int fd;
    int i;
    char *line;
    map->width = fill(map, c);
    fd = open(c, O_RDONLY);
    if(fd<0)
        printf("error");
    map->map = (char **)malloc(sizeof(char *) * map->width);
    if(map->map == NULL)
    {
        exit(0);
    }
    line = get_next_line(fd);
    i = 0;
    while(line)
    {
        map->map[i] = line;
        line = get_next_line(fd);
        i++;
    }
    map->map[i] = NULL;
    close(fd);
    // parse(map, *map);
    }
char cube3d(char *c)
{
    t_map map;
    store(&map , c);
    return 0;
}