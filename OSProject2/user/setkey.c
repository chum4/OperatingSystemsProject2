#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
	char secret[256];
	int key;
	if(argc < 2 || !strcmp(argv[1], "-h"))
	{
		printf("SETKEY:\n-h writes help menu\n-s allows you to enter a key by stdin and it will be hidden\n");
		exit();
	}

	if(!strcmp(argv[1], "-s"))
	{
		int h = setecho(0);
		if(h == -1) printf("Setecho error\n");
		int n = read(0, secret, 255);
		h = setecho(1);
		if(h == -1) printf("Setecho error\n");
		secret[n] = '\0';
		key = atoi(secret);
		if(setkey(key) == -1) printf("ERROR - Key is not set.\n");;
		exit();

	}

	key = atoi(argv[1]);
	if(setkey(key) == -1) printf("ERROR - Key is not set.\n");;
	
	exit();
}
