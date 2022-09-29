/*
	CS20B1031
	Daathwinaagh
*/

#include<stdio.h>

struct Priority
{
 int waitingTime,arrivalTime,burstTime,turnAroundTime,priority,burstCopy;
};




// Priority
struct Priority a[100];




int main(){
    int nop,arr[10],c=0,ptr,t;
    float totalTurnAroundTime=0,totalWaitingTime=0;
    

    //User input
    printf("Enter the number of process: ");
    scanf("%d",&nop);
    
    printf("Enter the arrival Time");
    for(int i=0;i<nop;i++){
        scanf("%d",&a[i].arrivalTime);
    }
    
    printf("Enter the burst Time");
    for(int i=0;i<nop;i++){
        scanf("%d",&a[i].burstTime);
        arr[i]=a[i].burstTime;
    }
    
    printf("Enter the priority Order");
    for(int i=0;i<nop;i++){
        scanf("%d",&a[i].priority);
    }
    
    a[99].priority=100000;
    
    for(t=0;c!=nop;t++){
        ptr=99;
        for(int i=0;i<nop;i++){
            if(a[ptr].priority>a[i].priority && a[i].arrivalTime <= t && a[i].burstTime>0){
                ptr=i;
            }
        }
        
        a[ptr].burstTime=a[ptr].burstTime-1;
        
        if(a[ptr].burstTime==0){
            c++;
            a[ptr].waitingTime=t+1-a[ptr].arrivalTime-arr[ptr];
            a[ptr].turnAroundTime=t+1-a[ptr].arrivalTime;
        }
    }
    
    printf("PID\t at\t PO\t TAT\t WT\n");
    for(int i=0;i<nop;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",i+1,a[i].arrivalTime,a[i].priority,a[i].turnAroundTime,a[i].waitingTime);
    }
    
    int ttat=0,twt=0; // total TAT and total WT
    for(int i=0;i<nop;i++){
        ttat+=a[i].turnAroundTime;
        twt+=a[i].waitingTime;
    }
    
    printf("Average Turn Around Time = %f",(float)((float)ttat/nop));
    printf("Average Waiting Time = %f",(float)((float)twt/nop));
    
}