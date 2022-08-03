#include "map.h"

void	check_valid_word(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_isspace(line[i]) || line[i] == '0' || line[i] == '1' \
		|| ft_strchr("NSWE", line[i])))
	{
		if (ft_strchr("NSWE", line[i]))
		{
			if (map->player > 0)
				exit_error("There are many players!!\n");
			map->player = 1;
			map->start_dir = line[i];
		}
		i++;
	}
	if (line[i] && line[i] != '\n')
		exit_error("There is a invalid word\n");
	if (i > map->width)
		map->width = i;
	if (map->start == 0)
		map->start = map->end;
}

void	check_wall(t_info *info)
{
	char	**map;
	int		i;
	int		j;

	map = info->map->map;
	i = -1;
	while (++i < info->map->height)
	{
		j = -1;
		while (++j < info->map->width)
		{
			if (map[i][j] == '0' || map[i][j] == info->map->start_dir)
			{
				if (i == 0 || i == info->map->height - 1 \
					|| j == 0 || j == info->map->width - 1)
					exit_error("The wall is must be surrounded by 1");
				else if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ' || \
					map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
					exit_error("The wall is must be surrounded by 1");
			}
		}
	}
}
