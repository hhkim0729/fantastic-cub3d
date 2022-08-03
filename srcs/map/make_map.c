#include "map.h"

static void	fill_map(t_info *info, char *line, int fd)
{
	int		i;
	int		j;

	i = 0;
	while (line)
	{
		info->map->map[i] = ft_calloc(info->map->width, sizeof(char));
		if (!info->map->map[i])
			exit(EXIT_FAILURE);
		j = 0;
		while (line[j] && line[j] != '\n')
		{
			if (ft_isspace(line[j]))
				info->map->map[i][j] = ' ';
			else
				info->map->map[i][j] = line[j];
			if (line[j] == info->map->start_dir)
			{
				info->player->pos.x = j + 0.5;
				info->player->pos.y = i + 0.5;
			}
			j++;
		}
		while (j < info->map->width - 1)
			info->map->map[i][j++] = ' ';
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

void	make_map(t_info *info, char *file)
{
	t_map	*map;
	int		fd;
	int		count;
	char	*line;

	map = info->map;
	map->height = map->end - map->start + 1;
	map->map = ft_calloc((map->height + 1), sizeof(char *));
	if (!map->map)
		exit(EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("File open error");
	count = 0;
	line = get_next_line(fd);
	while (line && ++count <= map->start - 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	fill_map(info, line, fd);
	close(fd);
	check_wall(info);
}
