#include "utils.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == 9 || (c >= 11 && c <= 13));
}

void	exit_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}