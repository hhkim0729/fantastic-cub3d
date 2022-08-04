#include "map.h"

void	check_texture(t_map *map, char *line, char c)
{
	int		i;
	char	*tmp;

	i = 3;
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_strdup(line + i, ft_strlen(line + i) - 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	if (c == 'N')
		map->tex_files[NORTH] = tmp;
	else if (c == 'S')
		map->tex_files[SOUTH] = tmp;
	else if (c == 'E')
		map->tex_files[EAST] = tmp;
	else
		map->tex_files[WEST] = tmp;
}

static void	to_rgb(t_map *map, int *color, char c)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			exit_error("This is not a rgb color\n");
	}
	if (c == 'F')
		map->floor = color[0] << 16 | color[1] << 8 | color[2];
	else
		map->ceil = color[0] << 16 | color[1] << 8 | color[2];
}

void	check_color(t_map *map, char *line)
{
	int	i;
	int	cnt;
	int	color[3];

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	cnt = 0;
	while (line[i])
	{
		color[cnt] = ft_atoi(line + i);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		while (ft_isspace(line[i]) || line[i] == '\n')
			i++;
		if (line[i] && line[i] != ',' && !ft_isdigit(line[i]))
			exit_error("Usage: [R, G, B]\n");
		if (line[i] && line[i] == ',')
		{
			i++;
			cnt++;
		}
	}
	if (cnt != 2)
		exit_error("Usage: [R, G, B]\n");
	to_rgb(map, color, line[0]);
}

void	check_info(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->tex_files[i])
			exit_error("tex file error");
		i++;
	}
	if (map->floor < 0 || map->ceil < 0)
		exit(EXIT_FAILURE);
}
