#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
	/*TEST ZA DOUBLE INDIRECT INODE
	
	int fd = open("/home/README", O_RDWR);
	char buf[512];
	for(int i = 0; i < 512; i++)
	{
		buf[i] = 'a';
	}

	for(int j = 0; j < 300; j++)
	{
		write(fd, buf, sizeof(buf));
	}

	close(fd);
	//TEST ZA READ WRITE ENCR DECR DODATKE
	int fd = open("/home/README", O_WRONLY);
	write(fd, "wwwwwwwwwwww\nfffffffffff", 25);
	close(fd);

	*/

	
	int i;

	for(i = 1; i < argc; i++)
		printf("%s%s", argv[i], i+1 < argc ? " " : "\n");
		
	
	
	exit();
}
