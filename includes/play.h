#ifndef PLAY_H
# define PLAY_H

# include "cub3d.h"

void		set_args(t_info *info, t_args *args, int x);
void		find_wall_hit(t_info *info, t_args *args);
int			find_tex_num(t_args *args);
void		set_args_line(t_info *info, t_args *args, \
				int *draw_start, int *draw_end);
int			draw_screen(t_info *info);
int			check_edge(char **map, t_player *player, t_vector *next_pos, int key);
t_vector	set_offset(t_player *player, int key);
int			play(int key, t_info *info);

#endif
