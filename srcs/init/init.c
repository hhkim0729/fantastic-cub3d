#include "init.h"

static void	init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->floor = -1;
	map->ceil = -1;
	map->map = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->start = 0;
	map->end = 0;
	map->player = 0;
}

void	init_info(t_info *info)
{
	info->map = (t_map *)malloc(sizeof(t_map));
	if (!info->map)
		exit(EXIT_FAILURE);
	init_map(info->map);
	info->player = NULL;
}

void	init_player(t_info *info)
{
	t_player	*player;
	char		dir;

	info->player = (t_player *)malloc(sizeof(t_player));
	if (!info->player)
		exit(EXIT_FAILURE);
	player = info->player;
	dir = info->map->start_dir;
	player->dir.x = 0;
	player->dir.y = -1;
	player->plane.x = 0.66;
	player->plane.y = 0;
	if (dir == 'S')
		player->dir.y = 1;
	else if (dir == 'W' || dir == 'E')
	{
		player->plane.x = 0;
		player->plane.y = 0.66;
		player->dir.y = 0;
		if (dir == 'W')
			player->dir.x = -1;
		else
			player->dir.x = 1;
	}
}