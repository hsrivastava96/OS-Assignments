#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	FILE *fptr;
	char *np1="pipe1", *np2="pipe2", buffer[500], ch;
	int wfd, rfd, no, i=0;
	printf("\nPlease enter your statement --> ");
	while((ch=getchar())!='.')
		buffer[i++]=ch;	
	buffer[i]='\0';
	wfd=open(np1, O_WRONLY);
	no=write(wfd, buffer, strlen(buffer));
	close(wfd);
	fptr=fopen("info.txt", "r");
	rfd=open(np2, O_RDONLY);
	no=read(rfd, buffer, 500);
	memset(buffer, 0, 500);
	fread(buffer, 500, 1, fptr);
	printf("\nResult:\n%s", buffer);
	close(rfd);
	return 0;
}
