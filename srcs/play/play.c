#include "play.h"

static void	move_up_down(int key, t_map *map, t_player *player)
{
	int		x;
	int		y;
	double	x_offset;
	double	y_offset;

	x = (int)player->pos.x;
	y = (int)player->pos.y;
	x_offset = player->dir.x * MOVE_SPEED;
	y_offset = player->dir.y * MOVE_SPEED;
	if (key == KEY_W)
	{
		if (map->map[y][(int)(player->pos.x + x_offset)] != '1')
			player->pos.x += x_offset;
		if (map->map[(int)(player->pos.y + y_offset)][x] != '1')
			player->pos.y += y_offset;
	}
	if (key == KEY_S)
	{
		if (map->map[y][(int)(player->pos.x - x_offset)] != '1')
			player->pos.x -= x_offset;
		if (map->map[(int)(player->pos.y - y_offset)][x] != '1')
			player->pos.y -= y_offset;
	}
}

static void	move_left_right(int key, t_map *map, t_player *player)
{
	int		x;
	int		y;
	double	x_offset;
	double	y_offset;

	x = (int)player->pos.x;
	y = (int)player->pos.y;
	x_offset = player->dir.x * MOVE_SPEED;
	y_offset = player->dir.y * MOVE_SPEED;
	if (key == KEY_A)
	{
		if (map->map[y][(int)(player->pos.x + y_offset)] != '1')
			player->pos.x += y_offset;
		if (map->map[(int)(player->pos.y + x_offset)][x] != '1')
			player->pos.y += x_offset;
	}
	if (key == KEY_D)
	{
		if (map->map[y][(int)(player->pos.x - y_offset)] != '1')
			player->pos.x -= y_offset;
		if (map->map[(int)(player->pos.y - x_offset)][x] != '1')
			player->pos.y -= x_offset;
	}
}

static void	rotate(t_player *player, double sin_val, double cos_val)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos_val - player->dir.y * sin_val;
	player->dir.y = old_dir_x * sin_val + player->dir.y * cos_val;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos_val - player->plane.y * sin_val;
	player->plane.y = old_plane_x * sin_val + player->plane.y * cos_val;
}

int	play(int key, t_info *info)
{
	t_map		*map;
	t_player	*player;

	map = info->map;
	player = info->player;
	if (key == KEY_W || key == KEY_S)
		move_up_down(key, map, player);
	if (key == KEY_A || key == KEY_D)
		move_left_right(key, map, player);
	if (key == KEY_LEFT)
		rotate(player, sin(ROT_SPEED), cos(ROT_SPEED));
	if (key == KEY_RIGHT)
		rotate(player, sin(-ROT_SPEED), cos(-ROT_SPEED));
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
