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
                            || c == 'T' \
                            || c == '0' \
                            || c == '1')

// void	    put_pixel(t_data *data, int x, int y, int color);

typedef struct s_coords
{
    int x;
    int y;
} t_coords;

typedef struct s_parser
{
    int collect;
    int exit;
    int player;
} t_parser;

typedef	struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct      s_asset_paths
{
    char            *player;
	void            *p_img;
    t_data          p_data;
    char            *exit;
    void            *e_img;
    t_data          e_data;
    char            *collectable;
    void            *c_img;
    t_data          c_data;
    char            *trap;
    void            *trap_img;
    t_data          trap_data;
}                   t_asset_paths;

struct s_values
{
    void *mlx_ptr;
    void *mlx_win_ptr;
    t_data image;
    int map_w;
    int map_h;
    char **map;
    int def_rect_size;
    int coll_count;
    int step_count;
    int screen_w;
    int screen_h;
    t_coords p_pos;
    t_asset_paths assets;
    t_parser parser;
} g_val;

int             parse_map(char *map_url);
void            ft_error(char *string);
void            ft_putchar(char *string);
int	            get_next_line(const int fd, char **line);
void            globs_init();
int             key_press_hook(int keycode);
char            *ft_strreplace(char *string, char c, char repl);
unsigned int	get_pixel(t_data *data, int x, int y);
void	        put_pixel(t_data *data, int x, int y, int color);

void            get_sprites();

#endif