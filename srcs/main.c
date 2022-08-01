#include "cub3d.h"

static int	check_filename(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strcmp(".cub", path + len - 4) == 0)
		return (TRUE);
	return (FALSE);
}

static void	check_mapfile(t_map *map, char *line)
{
	if (line[0] == '\n')
		return;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		check_texture(map, line, line[0]);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		check_color(map, line);
	else
		check_valid_word(map, line);
}

static void	read_mapfile(t_map *map, char *path) {
	int		fd;
	char	*line;

	if (check_filename(path) == FALSE)
		exit_error("Invalid file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("File open error"); //error
	line = get_next_line(fd);
	while (line)
	{
		map->end += 1;
		check_mapfile(map, line);
		free(line);
		line = get_next_line(fd);
	}
	check_info(map);
	if (!map->player)
		exit_error("There is no player");
	close(fd);
}

void	print_info(t_info *info)
{
	printf("========= map =========\n");
	for (int i = 0; i < info->map->height; i++)
	{
		printf("|%s|\n", info->map->map[i]);
	}
	printf("======== player ======= \n");
	printf("strart_dir: %c\n", info->map->start_dir);
	printf("pos_x: %f, pos_y: %f\n", info->player->pos.x, info->player->pos.y);
}

int main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		exit_error("Usage: ./cub3D map.cub"); // error
	init_info(&info);
	read_mapfile(info.map, av[1]);
	init_player(&info);
	make_map(&info, av[1]);
	print_info(&info);	
	return (0);
}
