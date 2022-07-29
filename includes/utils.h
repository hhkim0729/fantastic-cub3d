#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

# define BUFFER_SIZE 2048

char		*get_next_line(int fd);
int			ft_isspace(char c);
void		exit_error(char *msg);

#endif