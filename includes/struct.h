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
	int		**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_map;

#endif