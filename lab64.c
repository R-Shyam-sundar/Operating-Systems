/*
	Name: R.Shyam Sundar
	Roll: CS20B1029
	Date: 05/09/2022
	Lab6:  Inter Process Communication
	Receiver Program
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char* shm;
	char* s;

    // Memory segment key value = 9876
	key = 9876;

	shmid = shmget(key, SHSIZE, 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}

	shm = shmat(shmid, NULL, 0);

	if(shm == (char*) -1){
		perror("shmat");
		exit(1);
	}

	printf("\nReceived Message:  ");
    // Print the received message
	for(s = shm; *s != 0; s++){
		printf("%c",*s);
	}

	printf("\n");

	s = shm;

    // Data to be written from receiver.c to shared memory segment
	char temp[25];
	// printf("Enter the message to be sent:  ");
	// scanf("%s",temp);

	strcpy(temp,shm);

	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}

	shm = shmat(shmid,NULL, 0);

	if(shm == (char*) -1){
		perror("shmat");
		exit(1);
	}

	s = shm;
  	int j = strlen(shm);
  	j--;
  	int i = 0;
  	char* j_pointer = s+j;

  	// Check whether the received string is palindrome
  	while(i<=j){
  		// printf("\ni_pointer = %c, j_pointer = %c",*s,*j_pointer);
  		if(*s != *j_pointer){
			printf("\nThe string is NOT a Palindrome.\n");
  			*shm = '*';
  			sleep (2);
  			memcpy(shm,"0",1);
  			return 0;
  		}
  		// increase left pointer by one
  		s++;
  		// Decrease right pointer by one
  		j_pointer--;
  		i++;
  		j--;
  		if(i>j)break;
  	}
  	
    // Writing into memory
  	*shm = '*';
	sleep (2);
	printf("\nThe string is a Palindrome.\n");
	memcpy(shm,"1",1);
	return 0;
}