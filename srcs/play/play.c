#include "play.h"

static void	move(char **map, t_player *player, int key)
{
	int		x;
	int		y;
	double	x_offset;
	double	y_offset;

	x = (int)player->pos.x;
	y = (int)player->pos.y;
	if (key == KEY_A)
	{
        x_offset = player->plane.x * MOVE_SPEED * -1;
        y_offset = player->plane.y * MOVE_SPEED * -1;
	}
    if (key == KEY_D)
	{
        x_offset = player->plane.x * MOVE_SPEED;
        y_offset = player->plane.y * MOVE_SPEED;
	}
    if (key == KEY_S)
	{
        x_offset = player->dir.x * MOVE_SPEED * -1;
        y_offset = player->dir.y * MOVE_SPEED * -1;
	}
    if (key == KEY_W)
	{
        x_offset = player->dir.x * MOVE_SPEED;
        y_offset = player->dir.y * MOVE_SPEED;
	}
	if (map[(int)(y + y_offset)][(int)(x + x_offset)] != '1')
	{
	    player->pos.x = player->pos.x + x_offset;
	    player->pos.y = player->pos.y + y_offset;
	}
}

static void	rotate(t_player *player, double sin_val, double cos_val)
{
	double	old_dir_x;
	double	old_plane_x;

	printf("sin_val: %f\ncos_val: %f\n", sin_val, cos_val);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos_val - player->dir.y * sin_val;
	player->dir.y = old_dir_x * sin_val + player->dir.y * cos_val;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos_val - player->plane.y * sin_val;
	player->plane.y = old_plane_x * sin_val + player->plane.y * cos_val;
	printf("dir_x: %f, dir_y: %f\n", player->dir.x, player->dir.y);
	printf("plane_x: %f, plane_y: %f\n", player->plane.x, player->plane.y);
}

int	play(int key, t_info *info)
{
	t_map		*map;
	t_player	*player;

	map = info->map;
	player = info->player;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		move(map->map, player, key);
	if (key == KEY_LEFT)
		rotate(player, sin(-ROT_SPEED), cos(-ROT_SPEED));
	if (key == KEY_RIGHT)
		rotate(player, sin(ROT_SPEED), cos(ROT_SPEED));
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
