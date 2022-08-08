/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:54:55 by heehkim           #+#    #+#             */
/*   Updated: 2022/08/07 18:43:47 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return ;
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		check_texture(map, line, line[0]);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		check_color(map, line);
	else if (ft_strchr(" 01NSWE", line[0]))
	{
		if (map->info == FALSE)
		{
			check_info(map);
			map->info = TRUE;
		}
		check_valid_word(map, line);
	}
}

static void	read_mapfile(t_map *map, char *path)
{
	int		fd;
	char	*line;

	if (check_filename(path) == FALSE)
		exit_error("Invalid map file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("Failed to open file");
	line = get_next_line(fd);
	while (line)
	{
		map->end += 1;
		check_mapfile(map, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!map->player)
		exit_error("No player");
	close(fd);
}

// 나중에 삭제!
void	print_info(t_info *info)
{
	printf("========= map =========\n");
	for (int i = 0; i < info->map->height; i++)
		printf("|%s|\n", info->map->map[i]);
	printf("======== player ======= \n");
	printf("strart_dir: %c\n", info->map->start_dir);
	printf("pos_x: %f, pos_y: %f\n", info->player->pos.x, info->player->pos.y);
	printf("dir_x: %f, dir_y: %f\n", info->player->dir.x, info->player->dir.y);
	printf("plane_x: %f, plane_y: %f\n", info->player->plane.x, info->player->plane.y);
	for (int j = 0; j < 4; j++)
		printf("tex[%d]: %s\n", j, info->map->tex_files[j]);
}

int	force_quit(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		exit_error("Usage: ./cub3D map.cub");
	init_info(&info);
	read_mapfile(info.map, av[1]);
	init_player(info.player, info.map->start_dir);
	make_map(&info, av[1]);
	init_texture(&info);
	print_info(&info);
	mlx_loop_hook(info.mlx, draw_screen, &info);
	mlx_hook(info.window, PRESS_KEY, 0, play, &info);
	mlx_hook(info.window, MOUSE_EXIT, 0, force_quit, &info);
	mlx_loop(info.mlx);
	return (0);
}
