#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
int main()
{
	char msg1[100];
	char msg2[100];
	int fd1[2];
	int fd2[2];
	pipe(fd2);
	
	if(fork()==0)
	{

		if(fork()==0)
		{

			close(fd2[0]);
			write(fd2[1],"tinku",10);
		}

		else
		{
			close(fd1[1]);
			read(fd1[0],msg1,10);
			puts(msg1);
			close(fd2[1]);
			read(fd2[0],msg1,10);
			puts(msg1);
		}
	}
	else
	{
		
		close(fd1[0]);
		write(fd1[1],"sachin",10);
	}

	return 0;
}