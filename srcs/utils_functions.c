#include "ft_malloc.h"

int	get_typesize(size_t size)
{
	if (size <= TINYMAX)
	{
		return (TINY);
	}
	else if (size > TINYMAX && size <= SMALLMAX)
	{
		return (SMALL);
	}
	return (0);
}
