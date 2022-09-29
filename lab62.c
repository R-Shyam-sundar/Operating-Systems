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

    // shm[0] = '*' is to indicate that receiver has finished writing the message on the console
	*shm = '*'; 

	s = shm;

    // Data to be written from receiver.c to shared memory segment
	char temp[25];
	printf("Enter the message to be sent:  ");
	scanf("%s",temp);

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
    // Writing into memory
	memcpy(shm,temp,strlen(temp));

	s = shm;
	s += strlen(temp);

	*s = 0;

	return 0;
}