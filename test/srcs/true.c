#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(0);
	printf("true %s\n", argv[1]);
	return (0);
}
