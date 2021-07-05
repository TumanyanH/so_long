#include "../so_long.h"

void get_sprites()
{
	int width;
	int height;

	if (!(g_val.assets.p_img = mlx_xpm_file_to_image(g_val.mlx_ptr,
						g_val.assets.player, &width, &height)))
		ft_error("Error\nNo texture found for player");
	g_val.assets.p_data.addr = mlx_get_data_addr(g_val.assets.p_img, &g_val.assets.p_data.bits_per_pixel, &g_val.assets.p_data.line_length, &g_val.assets.p_data.endian);
	if (!(g_val.assets.e_img = mlx_xpm_file_to_image(g_val.mlx_ptr,
						g_val.assets.exit, &width, &height)))
		ft_error("Error\nNo texture found for exit");
	g_val.assets.e_data.addr = mlx_get_data_addr(g_val.assets.e_img, &g_val.assets.e_data.bits_per_pixel, &g_val.assets.e_data.line_length, &g_val.assets.e_data.endian);
	if (!(g_val.assets.c_img = mlx_xpm_file_to_image(g_val.mlx_ptr,
						g_val.assets.collectable, &width, &height)))
		ft_error("Error\nNo texture found for collectable");
	g_val.assets.c_data.addr = mlx_get_data_addr(g_val.assets.c_img, &g_val.assets.c_data.bits_per_pixel, &g_val.assets.c_data.line_length, &g_val.assets.c_data.endian);
	if (!(g_val.assets.trap_img = mlx_xpm_file_to_image(g_val.mlx_ptr,
						g_val.assets.trap, &width, &height)))
		ft_error("Error\nNo texture found for collectable");
	g_val.assets.trap_data.addr = mlx_get_data_addr(g_val.assets.trap_img, &g_val.assets.trap_data.bits_per_pixel, &g_val.assets.trap_data.line_length, &g_val.assets.trap_data.endian);

}