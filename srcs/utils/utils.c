#include "utils.h"
#include <stdio.h>

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long long	ft_atol(char *s)
{
	long long	ul;
	int			sign;
	int			tmp;

	ul = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		tmp = ul;
		ul = (*s - '0') + (ul * 10);
		s++;
		printf("%lld: atol\n", ul);
	}
	return (ul * sign);
}