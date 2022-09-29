/*
    Name: R.Shyam Sundar
    Roll: CS20B1029
    Date: 26/09/2022
    OS Lab8 - Question 1
*/


#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

int from = 1;
int sum = 0;

void *CS(void *ptr)
{
    char* msg;
    msg = (char*)ptr;
    int tSum = (from+199)*(from+200)/2 - (from-1)*from/2;
    sum += (from+199)*(from+200)/2 - (from-1)*from/2;
    from = from+200;
    printf("Processed sum in %s [from %d to %d]: %d\n", msg, from-200, from-1, tSum);
    tSum = 0;
}

int main()
{
    pthread_t thread[5];
    int i, Irt[5];
    char* msg[5] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5"};

    for(i=0; i<5; i++) {
        Irt[i] = pthread_create(&thread[i], NULL, CS, (void*)msg[i]);
        if(Irt[i]!=0) {
            printf("Thread creation is unsuccessful..\n");
            return -1;
        }
    }

    for(i=0; i<5; i++) {
        if(pthread_join(thread[i], NULL)!=0) {
            printf("Thread joining is unsuccessful..\n");
            return -1;
        }
    }
    printf("Sum of 1000 Natural numbers is: %d\n", sum);
    return 0; 
}