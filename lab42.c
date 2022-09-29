/*
    Name: R.Shyam Sundar
    Roll: CS20B1029
    Date: 22/08/22
    OS LAB - 4 : fork()
*/

#include <unistd.h>
#include <stdio.h>
  
int main()
{
    int n1 = fork();
  
    int n2 = fork();
  
    if (n1 > 0 && n2 > 0) {
        printf("PARENT\n");
        printf("%d %d \n", n1, n2);
        printf("ID is %d \n", getpid());
    }
    else if (n1 == 0 && n2 > 0)
    {
        printf("1st child\n");
        printf("%d %d \n", n1, n2);
        printf("ID is %d  \n", getpid());
    }
    else if (n1 > 0 && n2 == 0)
    {
        printf("2nd child\n");
        printf("%d %d \n", n1, n2);
        printf("ID is %d  \n", getpid());
    }
    else {
        printf("3rd child\n");
        printf("%d %d \n", n1, n2);
        printf(" my id is %d \n", getpid());
    }
    return 0;
}