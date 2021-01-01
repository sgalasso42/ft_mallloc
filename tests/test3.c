#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024) // 1 048 576

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr3;

	addr1 = (char*)malloc(16 * M); // 16 777 216
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128 * M); // 134 217 728
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}