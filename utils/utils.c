#include "../so_long.h"

void globs_init()
{
    g_val.map_w = 0;
    g_val.map_h = 0;
    g_val.def_rect_size = 50;
    g_val.p_pos.x = 1;
    g_val.p_pos.y = 1;
}

void ft_putchar(char *string)
{
    while (*string)
    {
        write(1, &(*string), 1);
        string++;
    }

}

char *ft_strreplace(char *string, char c, char repl)
{
    char *dest;
    int i = 0;

    dest = (char *)malloc(ft_strlen(string) * (sizeof(char) + 1));
    while (string[i])
    {
        if(string[i] == c)
            dest[i] = repl;
        else
            dest[i] = string[i];
        ++i;
    }
    dest[i] = '\0';
    return (dest);
}

// void	put_pixel(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }