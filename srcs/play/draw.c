#include "play.h"

static void	draw_floor_ceiling(t_info *info)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_X)
	{
		y = 0;
		while (y < SCREEN_Y)
		{
			if (y < SCREEN_Y / 2)
				info->img->data[y * SCREEN_X + x] = info->map->ceil;
			else
				info->img->data[y * SCREEN_X + x] = info->map->floor;
			y++;
		}
		x++;
	}
	// mlx_put_image_to_window(info->mlx, info->window, info->img->img, 0, 0);
}

static int	find_tex_num(t_args *args)
{
	if (args->side == 0)
	{
		if (args->ray_x < 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (args->ray_y < 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

static void	draw_line(t_info *info, int x, t_args *args)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	line_height = (int)(SCREEN_Y / args->perp_wall);
	draw_start = -line_height / 2 + SCREEN_Y / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_Y / 2;
	if (draw_end >= SCREEN_Y)
		draw_end = SCREEN_Y - 1;
	if (args->side == 0)
		args->wall_x = info->player->pos.y + args->perp_wall * args->ray_y;
	else
		args->wall_x = info->player->pos.x + args->perp_wall * args->ray_x;
	args->wall_x -= floor(args->wall_x);
	args->tex_x = (int)(args->wall_x * (double)TEX_WIDTH);
	if (args->side == 0 && args->ray_x > 0)
		args->tex_x = TEX_WIDTH - args->tex_x - 1;
	if (args->side == 1 && args->ray_y < 0)
		args->tex_x = TEX_WIDTH - args->tex_x - 1;
	args->step = 1.0 * TEX_HEIGHT / line_height;
	args->tex_pos = (draw_start - SCREEN_Y / 2 + line_height / 2) * args->step;
	while (draw_start < draw_end)
	{
		args->tex_y = (int)args->tex_pos & (TEX_HEIGHT - 1);
		args->tex_pos += args->step;
		color = info->map->texture[find_tex_num(args)][TEX_HEIGHT * args->tex_y + args->tex_x];
		info->img->data[draw_start * SCREEN_X + x] = color;
		draw_start++;
	}
}

int	draw_screen(t_info *info)
{
	t_args	args;
	int		x;

	x = 0;
	draw_floor_ceiling(info);
	while (x < SCREEN_X)
	{
		args.cam_x = 2 * x / (double)SCREEN_X - 1;
		args.ray_x = info->player->dir.x + info->player->plane.x * args.cam_x;
		args.ray_y = info->player->dir.y + info->player->plane.y * args.cam_x;
		args.map_x = (int)info->player->pos.x;
		args.map_y = (int)info->player->pos.y;
		args.delta_x = fabs(1 / args.ray_x);
		args.delta_y = fabs(1 / args.ray_y);
		args.hit = 0;
		if (args.ray_x < 0)
		{
			args.step_x = -1;
			args.side_x = (info->player->pos.x - args.map_x) * args.delta_x;
		}
		else
		{
			args.step_x = 1;
			args.side_x = (args.map_x + 1.0 - info->player->pos.x) * args.delta_x;
		}
		if (args.ray_y < 0)
		{
			args.step_y = -1;
			args.side_y = (info->player->pos.y - args.map_y) * args.delta_y;
		}
		else
		{
			args.step_y = 1;
			args.side_y = (args.map_y + 1.0 - info->player->pos.y) * args.delta_y;
		}
		while (args.hit == 0)
		{
			if (args.side_x < args.side_y)
			{
				args.side_x += args.delta_x;
				args.map_x += args.step_x;
				args.side = 0;
			}
			else
			{
				args.side_y += args.delta_y;
				args.map_y += args.step_y;
				args.side = 1;
			}
			if (info->map->map[args.map_y][args.map_x] == '1')
				args.hit = 1;
		}
		if (args.side == 0)
			args.perp_wall = (args.map_x - info->player->pos.x + (1 - args.step_x) / 2) / args.ray_x;
		else
			args.perp_wall = (args.map_y - info->player->pos.y + (1 - args.step_y) / 2) / args.ray_y;
		draw_line(info, x, &args);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img->img, 0, 0);
	return (0);
}
