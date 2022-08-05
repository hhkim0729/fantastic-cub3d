/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:55:54 by heehkim           #+#    #+#             */
/*   Updated: 2022/08/05 17:55:55 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

static void	draw_line(t_info *info, int x, t_args *args)
{
	int	draw_start;
	int	draw_end;
	int	tex;

	set_args_line(info, args, &draw_start, &draw_end);
	while (draw_start < draw_end)
	{
		args->tex_y = (int)args->tex_pos & (TEX_HEIGHT - 1);
		args->tex_pos += args->step;
		tex = find_tex_num(args);
		info->img->data[draw_start * SCREEN_X + x] \
			= info->map->texture[tex][TEX_HEIGHT * args->tex_y + args->tex_x];
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
		set_args(info, &args, x);
		find_wall_hit(info, &args);
		if (args.side == 0)
			args.perp_wall = (args.map_x - info->player->pos.x \
				+ (1 - args.step_x) / 2) / args.ray_x;
		else
			args.perp_wall = (args.map_y - info->player->pos.y \
				+ (1 - args.step_y) / 2) / args.ray_y;
		draw_line(info, x, &args);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img->img, 0, 0);
	return (0);
}
