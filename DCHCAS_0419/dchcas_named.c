#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	pid_t cpid;
	int ret;
	int fd;
	char buffer[32];
	char fajlnev[]="fajlnev";
	ret=mkfifo(fajlnev,0666);
	if(ret==-1)
	{
		perror("mkfifo()");
		exit(-1);
	}
	cpid=fork();
	if(cpid==-1)
	{
		perror("fork()");
		exit(-1);
	}
	if(cpid==0)
	{
		printf("%d: gyerek\n",getpid());
		fd=open(fajlnev,O_WRONLY);
		if(fd==-1)
		{
			perror("open()");
			exit(-1);
		}
		strcopy(buffer,"Hengsperger Mark, DCHCAS");
		write(fd,buffer,strlen(buffer));
		printf("%d: gyerek - iras utan\n",getpid());
		close(fd);
	}
	else
	{
		printf("%d: szulo\n",getpid());
		fd=open(fajlnev,O_WRONLY);
		if(fd==-1)
		{
			perror("open()");
			exit(-1);
		}
		printf("%d: szulo - olvasas elott\n",getpid());
		ret=read(fd,&buffer,sizeof(buffer));
		printf("read() %d byte-ot olvasott, string: %s\n",ret,buffer);
		close(fd);
		unlink(fajlnev);
	}
	return 0;
}

		