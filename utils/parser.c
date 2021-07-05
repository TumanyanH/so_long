#include "../so_long.h"

static int is_map_url(char *string)
{
	return (string[ft_strlen(string) - 1] == 'r' \
		&& string[ft_strlen(string) - 2] == 'e' \
		&& string[ft_strlen(string) - 3] == 'b' \
		&& string[ft_strlen(string) - 4] == '.');
}

static int check_row(char *row)
{
	while (*row)
	{
		if (!IS_ALLOWED_MEMBER(*row))
			ft_error("MAP - Not allowed character!");
		row++;
	}
	return (1);
}

static void sizes_calc(char *map_url)
{
	int fd = 0;
	char *line;
	int i = 0;

	fd = open(map_url, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		check_row(line);
		if (i++ == 0)
			g_val.map_w = (int)ft_strlen(line);
		if (g_val.map_w != (int)ft_strlen(line))
			ft_error("MAP - Wrong map");
		g_val.map_h++;
	}
	close(fd);
}

static int find_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

static void fill_matrix(char *map_url)
{
	int fd = 0;
	char *line;
	int y = 0;

	fd = open(map_url, O_RDONLY);
	g_val.map = malloc(g_val.map_h * (sizeof(char *) + 1));
	while (get_next_line(fd, &line) > 0)
	{
		g_val.map[y] = malloc(g_val.map_w * (sizeof(char) + 1));
		g_val.p_pos.x = (find_char(line, 'P') >= 0) ? find_char(line, 'P') : g_val.p_pos.x;
		g_val.p_pos.y = (find_char(line, 'P') >= 0) ? y : g_val.p_pos.y;
		if (find_char(line, 'C') > -1)
			g_val.parser.collect = 1;
		if (find_char(line, 'E') > -1)
			g_val.parser.exit = 1;
		if (find_char(line, 'P') > -1)
			g_val.parser.player = 1;
		line = ft_strreplace(line, 'P', '0');
		ft_strlcpy(g_val.map[y], line, (ft_strlen(line) + 1));
		++y;
	}
	close(fd);
}

static int check_map()
{
	int y = 0;
	int x = 0;

	while (y < g_val.map_h)
	{
		if (y == 0 || y == g_val.map_h - 1)
		{
			x = 0;
			while (x < g_val.map_w)
			{
				if (g_val.map[y][x] != '1')
					ft_error("MAP - Invalid wall construction");
				++x;
			}
		}
		if (g_val.map[y][0] != '1' || g_val.map[y][(g_val.map_w - 1)] != '1')
			ft_error("MAP - Invalid wall construction");
		y++;
	}
	return (0);
}

int parse_map(char *map_url)
{
	if (!is_map_url(map_url))
		ft_error("MAP - Url is invalid");
	sizes_calc(map_url);
	fill_matrix(map_url);
	check_map();
	if (!g_val.parser.collect || !g_val.parser.exit || !g_val.parser.player)
		ft_error("MAP - An important part of your map does not exists");
	return (0);
}