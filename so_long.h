#ifndef SO_LONG
# define SO_LONG

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include "libs/mlx_mms/mlx.h"
# include "libs/libft/libft.h"

# define IS_ALLOWED_MEMBER(c) (c == 'P' \
                            || c == 'E' \
                            || c == 'C' \
                            || c == '0' \
                            || c == '1')

int         parse_map(char *map_url);
void        ft_error(char *string);
void        ft_putchar(char *string);
int	        get_next_line(const int fd, char **line);
void        globs_init();
int         key_press_hook(int keycode);
char        *ft_strreplace(char *string, char c, char repl);

// void	    put_pixel(t_data *data, int x, int y, int color);

typedef struct s_coords
{
    int x;
    int y;
} t_coords;


struct s_values
{
    void *mlx_ptr;
    void *mlx_win_ptr;
    int map_w;
    int map_h;
    char **map;
    int def_rect_size;
    int screen_w;
    int screen_h;
    t_coords p_pos;
} g_val;


#endif