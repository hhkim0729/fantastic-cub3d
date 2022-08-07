/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:55:09 by heehkim           #+#    #+#             */
/*   Updated: 2022/08/07 18:40:18 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void	init_map(t_map *map)
{
	map->info = FALSE;
	map->width = 0;
	map->height = 0;
	map->floor = -1;
	map->ceil = -1;
	map->map = NULL;
	map->tex_files = (char **)ft_calloc(4, sizeof(char *));
	if (!map->tex_files)
		exit_error("Failed to allocate memory");
	map->start = 0;
	map->end = 0;
	map->player = 0;
}

void	init_info(t_info *info)
{
	info->map = (t_map *)malloc(sizeof(t_map));
	if (!info->map)
		exit_error("Failed to allocate memory");
	init_map(info->map);
	info->player = (t_player *)malloc(sizeof(t_player));
	if (!info->player)
		exit_error("Failed to allocate memory");
	info->mlx = mlx_init();
	if (!info->mlx)
		exit_error("Failed to initiate mlx");
	info->window = mlx_new_window(info->mlx, SCREEN_X, SCREEN_Y, "cub3D");
	if (!info->window)
		exit_error("Failed to create mlx winow");
	info->img = (t_img *)malloc(sizeof(t_img));
	if (!info->img)
		exit_error("Failed to allocate memory");
	info->img->img = mlx_new_image(info->mlx, SCREEN_X, SCREEN_Y);
	if (!info->img->img)
		exit_error("Failed to create mlx image");
	info->img->data = (int *)mlx_get_data_addr(info->img->img, &info->img->bpp, \
		&info->img->size_l, &info->img->endian);
	if (!info->img->data)
		exit_error("Failed to create mlx image data");
}

void	init_player(t_player *player, char dir)
{
	player->dir.x = 0;
	player->dir.y = -1;
	player->plane.x = 0.66;
	player->plane.y = 0;
	if (dir == 'S')
	{
		player->plane.x = -0.66;
		player->dir.y = 1;
	}
	else if (dir == 'W' || dir == 'E')
	{
		player->plane.x = 0;
		player->plane.y = -0.66;
		player->dir.x = -1;
		player->dir.y = 0;
		if (dir == 'E')
		{
			player->dir.x = 1;
			player->plane.y = 0.66;
		}
	}
}

static void	load_image(t_info *info, int *texture, char *path)
{
	int		x;
	int		y;
	t_img	img;

	img.img = mlx_xpm_file_to_image(info->mlx, path, &img.img_width, \
		&img.img_height);
	if (!img.img)
		exit_error("Failed to load image");
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size_l, \
		&img.endian);
	if (!img.data)
		exit_error("Failed to create mlx image data");
	y = 0;
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			texture[img.img_width * y + x] = img.data[img.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img.img);
}

void	init_texture(t_info *info)
{
	t_map	*map;
	int		i;

	map = info->map;
	map->texture = (int **)ft_calloc(4, sizeof(int *));
	if (!map->texture)
		exit_error("Failed to allocate memory");
	i = 0;
	while (i < 4)
	{
		map->texture[i] = (int *)ft_calloc(TEX_WIDTH * TEX_HEIGHT, sizeof(int));
		if (!map->texture[i])
			exit_error("Failed to allocate memory");
		load_image(info, map->texture[i], map->tex_files[i]);
		i++;
	}
}
