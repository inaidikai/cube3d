#include <mlx.h>
#include <stdio.h>

int main()
{
    void *mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: Failed to initialize MLX.\n");
        return 1;
    }

    void *win = mlx_new_window(mlx, 800, 600, "Test Window");
    if (!win)
    {
        printf("Error: Failed to create window.\n");
        return 1;
    }

    mlx_loop(mlx);
    return 0;
}
