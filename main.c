#include "./so_long.h"

void draw_square(int x, int y, int color)
{
	int i = 0;
	int j = 0;

	while (y + i < y + g_val.def_rect_size)
	{
		j = 0;
		while (x + j < x + g_val.def_rect_size)
		{
			put_pixel(&g_val.image, x + j, y + i, color);
			j++;
		}
		++i;
	}
}

void calc_res()
{
	int screenW, screenH;
	mlx_get_screen_size(g_val.mlx_ptr, &screenW, &screenH);
	if ((g_val.def_rect_size * g_val.map_w) >= screenW 
		|| (g_val.def_rect_size * g_val.map_h) >= screenH)
	{
		while ((((g_val.def_rect_size * g_val.map_w) >= screenW) 
			|| ((g_val.def_rect_size * g_val.map_h) >= screenH))
			&& g_val.def_rect_size > 0)
			--g_val.def_rect_size;
	}
	g_val.screen_w = g_val.def_rect_size * g_val.map_w;
	g_val.screen_h = g_val.def_rect_size * g_val.map_h;
	g_val.allowed_def_rect_size = (g_val.def_rect_size / 10 >= 1) ? g_val.def_rect_size / 10 : 1;
}

void draw_asset(int x, int y, char asset)
{
	t_data img;
	int tex_y = 0;
	int tex_x = 0;
	int allow_count = 0;
	int super_y = 0;
	// int super_x = 0;
	
	if (asset == 'p')
		img = g_val.assets.p_data;
	else if (asset == 'e')
		img = g_val.assets.e_data;
	else if (asset == 'c')
		img = g_val.assets.c_data;

	while (tex_y < g_val.def_rect_size)
	{
		tex_x = 0;
		if (allow_count <= g_val.allowed_def_rect_size)
		{
			while (tex_x < g_val.def_rect_size)
			{
				put_pixel(&g_val.image, x + tex_x, y + super_y, get_pixel(&img, tex_x, tex_y));
				++tex_x;
			}
			++super_y;
		}
		++allow_count;
		if (allow_count == 5)
			allow_count = 0;
		++tex_y;
	}
	
}
	
void drawFrame()
{
	int x = 0;
	int y = 0;

	while (y < g_val.map_h)
	{
		x = 0;
		while (x < g_val.map_w)
		{
			switch (g_val.map[y][x])
			{
				case '1':
					draw_square(g_val.def_rect_size * x, g_val.def_rect_size * y, 0x000000FF);
					break;
				case '0':
					draw_square(g_val.def_rect_size * x, g_val.def_rect_size * y, 0);
					break;
				case 'E':
					draw_asset(g_val.def_rect_size * x, g_val.def_rect_size * y, 'e');
					break;
				case 'C':
					draw_asset(g_val.def_rect_size * x, g_val.def_rect_size * y, 'c');
					break;
				default:
					break;
			} 
			++x;
		}
		++y;
	} 
	// draw_square(g_val.p_pos.x * g_val.def_rect_size, g_val.p_pos.y * g_val.def_rect_size, 0x00FFFF00);
	draw_asset(g_val.p_pos.x * g_val.def_rect_size, g_val.p_pos.y * g_val.def_rect_size, 'p');
}

void clear_window()
{
	int y = 0;
	int x;

	while (y < g_val.screen_h)
	{
		x = 0;
		while (x < g_val.screen_w)
		{
			put_pixel(&g_val.image, x, y, 0);
			++x;
		}
		++y;
	}
}

int kill_prog()
{
	mlx_destroy_window(g_val.mlx_ptr, g_val.mlx_win_ptr);
	exit(0);
	return (0);
}

int key_press_hook(int keycode)
{
   switch (keycode)
   {
		case 13: //w
			if (g_val.map[g_val.p_pos.y - 1][g_val.p_pos.x] != '1')
				--g_val.p_pos.y;
			break;
		case 0: //a
			if (g_val.map[g_val.p_pos.y][g_val.p_pos.x - 1] != '1')
				--g_val.p_pos.x;
			break;
		case 1: //s
			if (g_val.map[g_val.p_pos.y + 1][g_val.p_pos.x] != '1')
				++g_val.p_pos.y;
			break;
		case 2: //d
			if (g_val.map[g_val.p_pos.y][g_val.p_pos.x + 1] != '1')
				++g_val.p_pos.x;
			break;
		case 53:
			kill_prog();
		default:
			break;
   }
   clear_window();
   drawFrame();
   return (0);
}

int func(struct s_values *s)
{
	clear_window();
	drawFrame();
	mlx_put_image_to_window(s->mlx_ptr, s->mlx_win_ptr, s->image.img, 0, 0);
	mlx_do_sync(s->mlx_ptr);
	return (0);
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		int y = 0;
		g_val.mlx_ptr = mlx_init();

		globs_init();

		get_sprites();
		parse_map(argv[1]);
		calc_res();

		g_val.mlx_win_ptr = mlx_new_window(g_val.mlx_ptr, g_val.screen_w, g_val.screen_h, "So Long");
		g_val.image.img = mlx_new_image(g_val.mlx_ptr, g_val.screen_w, g_val.screen_h);
		g_val.image.addr = mlx_get_data_addr(g_val.image.img, &g_val.image.bits_per_pixel, &g_val.image.line_length, &g_val.image.endian);
		while (y < g_val.map_h)
		{
			printf("%s\n", g_val.map[y]);
			y++;
		}
		drawFrame();
		mlx_hook(g_val.mlx_win_ptr, 2, 1L << 0, key_press_hook, &g_val);
		mlx_hook(g_val.mlx_win_ptr, 17, 1L << 0, kill_prog, &g_val);
		mlx_loop_hook(g_val.mlx_ptr, func, &g_val);
		mlx_loop(g_val.mlx_ptr);
	}
	// sould replace user start position
	return 0;
}