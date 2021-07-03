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
            mlx_pixel_put(g_val.mlx_ptr, g_val.mlx_win_ptr, x + j, y + i, color);
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
}

void movements()
{

}

void drawFrame()
{
    int x = 0;
    int y = 0;
    int color = 0;

    while (y < g_val.map_h)
    {
        x = 0;
        while (x < g_val.map_w)
        {
            switch (g_val.map[y][x])
            {
                case '1':
                    color = 0x00ff0000;
                    break;
                case '0':
                    color = 0x00000000;
                    break;
                case 'E':
                    color = 0x0000FF00;
                    break;
                case 'C':
                    color = 0x000000FF;
                    break;
                default:
                    break;
            } 
            draw_square(g_val.def_rect_size * x, g_val.def_rect_size * y, color);
            ++x;
        }
        ++y;
    } 
    draw_square(g_val.p_pos.x * g_val.def_rect_size, g_val.p_pos.y * g_val.def_rect_size, 0x00FFFF00);
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
            mlx_pixel_put(g_val.mlx_ptr, g_val.mlx_win_ptr, x, y, 0);
            ++x;
        }
        ++y;
    }
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
        default:
            break;
   }
   clear_window();
   drawFrame();
}

int main()
{
    g_val.mlx_ptr = mlx_init();

    globs_init();

    parse_map("./maps/map.ber");
    calc_res();
    g_val.mlx_win_ptr = mlx_new_window(g_val.mlx_ptr, g_val.screen_w, g_val.screen_h, "So Long");
    drawFrame();
    mlx_hook(g_val.mlx_win_ptr, 2, 1L << 0, key_press_hook, &g_val);
    mlx_loop(g_val.mlx_ptr);

    // sould replace user start position
    return 0;
}