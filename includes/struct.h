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
	t_vector	cam;
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

typedef struct s_info
{
	t_map		*map;
	t_player	*player;
}	t_info;

#endif