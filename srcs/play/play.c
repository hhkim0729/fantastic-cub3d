#include "play.h"

int	play(int key, t_info *info)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == KEY_W)
	{
		if (info->map->map[(int)(info->player->pos.y)][(int)(info->player->pos.x + info->player->dir.x * MOVE_SPEED)] != '1')
			info->player->pos.y += info->player->dir.y * MOVE_SPEED;
		if (info->map->map[(int)(info->player->pos.y + info->player->dir.y * MOVE_SPEED)][(int)(info->player->pos.x)] != '1')
			info->player->pos.x += info->player->dir.x * MOVE_SPEED;
	}
	if (key == KEY_S)
	{
		if (info->map->map[(int)(info->player->pos.y)][(int)(info->player->pos.x - info->player->dir.x * MOVE_SPEED)] != '1')
			info->player->pos.y -= info->player->dir.y * MOVE_SPEED;
		if (info->map->map[(int)(info->player->pos.y - info->player->dir.y * MOVE_SPEED)][(int)(info->player->pos.x)] != '1')
			info->player->pos.x -= info->player->dir.x * MOVE_SPEED;
	}
	if (key == KEY_A)
	{
		if (info->map->map[(int)(info->player->pos.y)][(int)(info->player->pos.x + info->player->dir.y * MOVE_SPEED)] != '1')
			info->player->pos.x += info->player->dir.y * MOVE_SPEED;
		if (info->map->map[(int)(info->player->pos.y + info->player->dir.x * MOVE_SPEED)][(int)(info->player->pos.x)] != '1')
			info->player->pos.y += info->player->dir.x * MOVE_SPEED;
	}
	if (key == KEY_D)
	{
		if (info->map->map[(int)(info->player->pos.y)][(int)(info->player->pos.x - info->player->dir.y * MOVE_SPEED)] != '1')
			info->player->pos.x -= info->player->dir.y * MOVE_SPEED;
		if (info->map->map[(int)(info->player->pos.y - info->player->dir.x * MOVE_SPEED)][(int)(info->player->pos.x)] != '1')
			info->player->pos.y -= info->player->dir.x * MOVE_SPEED;
	}
	if (key == KEY_LEFT)
	{
		old_dir_x = info->player->dir.x;
		info->player->dir.x = info->player->dir.x * cos(-ROT_SPEED) - info->player->dir.y * sin(-ROT_SPEED);
		info->player->dir.y = old_dir_x * sin(-ROT_SPEED) + info->player->dir.y * cos(-ROT_SPEED);
		old_plane_x = info->player->plane.x;
		info->player->plane.x = info->player->plane.x * cos(-ROT_SPEED) - info->player->plane.y * sin(-ROT_SPEED);
		info->player->plane.y = old_plane_x * sin(-ROT_SPEED) + info->player->plane.y * cos(-ROT_SPEED);
	}
	if (key == KEY_RIGHT)
	{
		old_dir_x = info->player->dir.x;
		info->player->dir.x = info->player->dir.x * cos(ROT_SPEED) - info->player->dir.y * sin(ROT_SPEED);
		info->player->dir.y = old_dir_x * sin(ROT_SPEED) + info->player->dir.y * cos(ROT_SPEED);
		old_plane_x = info->player->plane.x;
		info->player->plane.x = info->player->plane.x * cos(ROT_SPEED) - info->player->plane.y * sin(ROT_SPEED);
		info->player->plane.y = old_plane_x * sin(ROT_SPEED) + info->player->plane.y * cos(ROT_SPEED);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}