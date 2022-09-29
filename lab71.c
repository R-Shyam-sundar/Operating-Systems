/*
	Name: R.Shyam Sundar
	Date: 19/09/2022
	OS Lab 7: Fork() and Pipes()
	Question: Reverse a string using pipes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	// We use two pipes
	// First pipe to send input string from parent
	// Second pipe to send concatenated string from child

	int fd1[2]; // Used to store two ends of first pipe
	int fd2[2]; // Used to store two ends of second pipe

	char input_str[100];
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	if (pipe(fd2) == -1) {
		fprintf(stderr, "Pipe Failed");
		return 1;
	}
	printf("\nEnter the string:  ");
	scanf("%s", input_str);
	p = fork();

	if (p < 0) {
		fprintf(stderr, "fork Failed");
		return 1;
	}

	// Parent process
	else if (p > 0) {
		char cstr[100];

		close(fd1[0]); // Close reading end of first pipe

		// Write input string and close writing end of first
		// pipe.
		write(fd1[1], input_str, strlen(input_str) + 1);
		close(fd1[1]);

		// Wait for child to send a string
		wait(NULL);

		close(fd2[1]); // Close writing end of second pipe

		// Read string from child, print it and close
		// reading end.
		read(fd2[0], cstr, 100);
		printf("Reversed string %s\n", cstr);
		close(fd2[0]);
	}

	// child process
	else {
		close(fd1[1]); // Close writing end of first pipe

		// Read a string using first pipe
		char cstr[100];
		read(fd1[0], cstr, 100);

		// Concatenate a fixed string with it

		int i = 0,j = strlen(cstr)-1;
		while(i<j){
			char temp = cstr[i];
			cstr[i] = cstr[j];
			cstr[j] = temp;
			i++;j--;
		}

		// Close both reading ends
		close(fd1[0]);
		close(fd2[0]);

		// Write concatenated string and close writing end
		write(fd2[1], cstr, strlen(cstr) + 1);
		close(fd2[1]);

		exit(0);
	}
}
