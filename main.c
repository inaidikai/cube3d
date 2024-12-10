#include "cube.h"
int	cubcheck(char *y)
{
	int	i;

	i = 0;
	while (y[i])
	{
		if (y[i] != 46)
			i++;
		else
		{
			return (0);
		}
		if (y[i + 1] == 'c')
		{
			if (y[i + 2] == 'u')
			{
				if (y[i + 3] == 'b')
				{
					if (y[i + 4] == '\0')
						return (1);
				}
			}
		}
	}
	return (0);
}
int main(int argc , char **argv)
{
	if (argc != 2)
		return (0);
    if (cubcheck(argv[1]))
        cube3d(argv[1]);
	else
	{
		write(1,"WRONG", 6);
		write(1," TRY ", 6);
		write(1,"WITH", 6);
		write(1," .cub ", 6);
		return 0;
	}
		
}