#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	plane;
	t_vector	dir;
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	int		floor;
	int		ceil;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		start;
	int		end;
	int		player;
	char	start_dir;
}	t_map;

typedef struct s_args
{
	double	cam_x;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	perp_wall;
	int		hit;
	int		side;
}	t_args;

typedef struct s_info
{
	t_map		*map;
	t_player	*player;
	void		*mlx;
	void		*window;
}	t_info;

#endif
