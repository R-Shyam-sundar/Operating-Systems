/*
	Name: R.Shyam Sundar
	Roll: CS20B1029
	Date: 05/09/2022
	Lab6:  Inter Process Communication
	Sender Program
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>


// Shared Memory Size = 100 Bytes
#define SHSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char* shm;
	char* s;

    // Memory created with key value = 9876
	// ipcs -m = lists the memory segments
	// to remove the memory created -> ipcrm -M 9876
	key = 9876;

	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}

	shm = shmat(shmid, NULL, 0);

	if(shm == (char*) -1){
		perror("shmat");
		exit(1);
	}

    // Data to be written
	char temp[100];
	printf("Enter the data to be sent:   ");
	scanf("%s",temp);

	memcpy(shm,temp,strlen(temp));

	s = shm;
	s += strlen(temp);

	*s = 0;

    // Wait until receiver writes the output in console
	while(*shm != '*'){
		sleep (1);
	}

    // Wait until receiver transmits the message 
	while(*shm == '*'){
		sleep (1);
	}

	printf("Received Message:  ");

    // print the recieved message
	printf("%c",*shm);
	printf("\n");

	*shm = '*'; 

	return 0;
}