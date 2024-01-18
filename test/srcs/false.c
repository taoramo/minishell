#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	printf("false %s\n", argv[1]);
	return (1);
}
