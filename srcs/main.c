#include "cub3d.h"

void	check_texture(t_map *map, char *line, char c)
{
	int	fd;
	int	i;
	char	*tmp;

	i = 3;
	while (ft_isspace(line[i]))
		i++;
	fd = open(line + i, O_RDONLY);
	// if (fd < 0)
	// 	exit(EXIT_FAILURE); //error
	tmp = ft_strdup(line + i);
	if (!tmp)
		exit(EXIT_FAILURE); //error
	if (c == 'N')
		map->north = tmp;
	else if (c == 'S')
		map->south = tmp;
	else if (c == 'W')
		map->west = tmp;
	else
		map->east = tmp;
	// close(fd);
}

void	to_rgb(t_map *map, int *color, char c)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			exit(EXIT_FAILURE);
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
		while (ft_isspace(line[i]))
			i++;
		if (line[i] && line[i] != ',')
			exit(EXIT_FAILURE);
		if (line[i++] == ',')
			cnt++;
	}
	if (cnt != 2)
		exit(EXIT_FAILURE);
	to_rgb(map, color, line[0]);
}

void	check_map(t_map *map, char line)
{
	
}

void	check_mapfile(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		check_texture(map, line, line[0]);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		check_color(map, line);
	check_map(map, line);
}

int	check_filename(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strcmp(".cub", path + len - 4) == 0)
		return (TRUE);
	return (FALSE);
}

int main(int ac, char **av)
{
	int		fd;
	char	*line;
	t_map	map;

	if (ac != 2)
		return (EXIT_FAILURE); // error
	if (check_filename(av[1]) == FALSE)
		return (EXIT_FAILURE); // error
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE); //error
	line = get_next_line(fd);
	while (line)
	{
		check_mapfile(&map, line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}