/*
    Name: R.Shyam Sundar
    Roll: CS20B1029
    Date: 26/09/2022
    OS Lab8 - Question 2
*/

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

void *Print_till_N(void *pt)
{
    int* msg;
    msg = (int*)pt;
    printf("Passed value from main Process: %d\n", *msg);
    printf("Printing inside the thread : ");
    for(int i=0; i <= *msg; i++)
        printf("%d ", i);
    printf("\n");
}

int main()
{
    char* msg = "Inside the thread: ";
    pthread_t thread;
    int Irt, num;

    printf("Value of n: ");
    scanf("%d", &num);

    Irt = pthread_create(&thread, NULL, Print_till_N, &num);
    if(Irt != 0) 
    {
        printf("Thread creation is unsuccessful..\n");
        return -1;
    }

    if(pthread_join(thread, NULL)!=0) {
        printf("Joining thread is unsuccessful..\n");
        return -1;
    }
    return 0; 
}