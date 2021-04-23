##include <sys/types.h>
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
	char buffer[40];
	char dchcas[]="dchcas";
	ret=mkfifo(dchcas,0666); 
	cpid=fork();         
	if(ret==-1)      
	{       
		perror("mkfifo()");    
		exit(-1);              
	}                     
	if(cpid==0)       
	{      
		printf("Gyerekprocessz PID...%d\n",getpid());
		fd=open(dchcas,O_WRONLY);               
		if(fd==-1)                   
		{               
			perror("open()");    
			exit(-1);             
		}                         
		strcpy(buffer,"Hengsperger Mark, DCHCAS");     
		write(fd,buffer,strlen(buffer)); 
		printf("Gyerek PID iras utan...%d\n",getpid());      
		close(fd);       
	}           
	else          
	{              
		printf("Szuloprocessz PID...%d\n",getpid());    
		fd=open(dchcas,O_RDONLY);   
		if(fd==-1)          
		{                 
			perror("open()");   
			exit(-1);          
		}                           
		printf("Szulo PID olvasas elott...%d\n",getpid());    
		ret=read(fd,&buffer,sizeof(buffer));                         
		printf("A read() altal olvasott byte-ok...%d, a string...%s\n",ret,buffer);  
		close(fd);                                                                     
		unlink(dchcas);                                                                  
	}                                                                                        
	return 0;

		
