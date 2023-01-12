#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{
	int i;
	int fd;
	if(argc < 2 || strcmp(argv[1], "-h") == 0)
	{
		printf("Help:\n-h will show help menu\n-a will decr all files in current folder\nif a specific file path is inputted then it will decr only that file\n");
		exit();
	}

	if(strcmp(argv[1], "-a") == 0)
	{
		int fd1;
		char buf[512], *p;
		struct dirent de;
		struct stat st;
		char *path = ".";

		//fd = open(".", O_RDWR);
		if((fd = open(path, 0)) < 0)
		{
			fprintf(2, "decr: cannot open %s\n", path);
			exit();
		}

		if(fstat(fd, &st) < 0)
		{
			fprintf(2, "decr: cannot stat %s\n", path);
			close(fd);
			exit();
		}

			if(st.type == T_DIR)
			{
			
				if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
				{
					printf("decr: path too long\n");
					exit();
				}
				strcpy(buf, path);
				p = buf+strlen(buf);
				*p++ = '/';
				while(read(fd, &de, sizeof(de)) == sizeof(de))
				{
					if(de.inum == 0) continue;
					memmove(p, de.name, DIRSIZ);
					p[DIRSIZ] = 0;
					if(stat(buf, &st) < 0)
					{
						printf("decr: cannot stat %s\n", buf);
						continue;
					}
						
				}
				fd1 = open(buf, O_RDWR);
				int h = encr(fd1);
				if(h == -1) printf("Key is not set.\n");
				else if(h == -2) printf("File type is T_DEV.\n");
				else if(h == -3) printf("File is already encrypted.\n");
				else if(h == -4) printf("No arguments.\n");
				close(fd1);
			}
			close(fd);
			exit();
	}


	for(i = 1; i < argc; i++){
		if((fd = open(argv[i], O_RDWR)) < 0){
			printf("decr: cannot open %s\n", argv[i]);
			exit();
		}
	}

	int h = encr(fd);
	if(h == -1) printf("Key is not set.\n");
	else if(h == -2) printf("File type is T_DEV.\n");
	else if(h == -3) printf("File is already encrypted.\n");
	else if(h == -4) printf("No arguments.\n");
	close(fd);

	exit();
}