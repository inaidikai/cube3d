#include "cube.h"
int invisible_yes_no(char c)
{
    if(c == 32 || (c >= 9 && c<=13))
        return (1);
    return 0;
}
t_img	*ft_t_img(void)
{
	static t_img			img;
	static t_texture		no;
	static t_texture		so;
	static t_texture		we;
	static t_texture		ea;

	if (!img.init)
	{
		img.no = &no;
		img.so = &so;
		img.we = &we;
		img.ea = &ea;
		img.f = 0;
		img.c = 0;
		img.init = 1;
	}
	return (&img);
}
int val_chk(t_img *img, char *temp)
{
    if(!*temp)
        return 0;
    if(strncmp(temp, "NO", 2) == 0 && !img->no->img )
        return(NO);
    if(strncmp(temp, "SO", 2) == 0 && !img->so->img )
        return(SO);
    if(strncmp(temp, "WE", 2) == 0 && !img->we->img )
        return(WE);
    if(strncmp(temp, "EA", 2) == 0 && !img->ea->img )
        return(EA);
    if(strncmp(temp, "F", 2) == 0 && !img->f )
        return(F);
    if(strncmp(temp, "C", 2) == 0 && !img->c )
        return(C);
    return 0;
}
int find_element(char *element, int fd)
{
    int val;
    int i;
    i = 0;
    val = 0;
    while(*element && invisible_yes_no(*element) )
        element++;
    val = val_chk(ft_t_img(), element);
    if(val > 0)
    {
        element++;
        if(val < 5)
            element++;
        while(invisible_yes_no(*element))
            element++;
        while(element[i] && !invisible_yes_no(element[i]))
            i++;
        element[i] = '\0';
        if(init_element(elemnt , val))
    }
}
void element_hunter(int fd)
{
    int i;
    char *temp;
    i = 6;
    temp = get_next_line(fd);
    while(i && temp)
    {
        i-= find_element(temp, fd);
        free(temp);
        temp = get_next_line(fd);
    }
    if(temp)
        free(temp);
    if(i != 0)
    {
        close(fd);
        exit(0);
    }
}
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
    element_hunter(fd);
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