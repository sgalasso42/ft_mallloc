#include "ft_malloc.h"

int		main(void)
{
	char	*str;
	char	*str1;

	if (!(str = ft_malloc(sizeof(char) * 5)))
	{
		printf("Malloc returned null 0");
		return (0);
	}
	str = strcpy(str, "12345");

	
	printf("ptr : %p\ncontent : %s\n", str, str);

	if (!(str1 = ft_malloc(sizeof(char) * 5)))
	{
		printf("Malloc returned null 1");
		return (0);
	}
	str1 = strcpy(str1, "abcde");

	printf("ptr : %p\ncontent : %s\n", str1, str1);

	ft_free(str);

	//printf("ptr : %p\ncontent : %s\n", str, str);

	ft_free(str1);

	//printf("ptr : %p\ncontent : %s\n", str1, str1);

	return (0);
}
