#include<stdio.h>


struct process{
	int pid,at,bt,ct,tat,wt;
};
}
int main()
{
	int p;
	printf("Enter the number of processes :  ");
	scanf("%d",&p);
	process data[p];
	for(int i=0;i<p;i++){
		printf("Enter the value of [process id] [arrival time] [burst time] #%d:  ",i+1);
		int t1,t2,t3;
		scanf("%d %d %d",&t1,&t2,&t3);
		data[i].pid = t1;
		data[i].at = t2;
		data[i].bt = t3;
	}
	int time = data[0].at;
	for(int i=0;i<p;i++){
		data[i].ct = time + data[i].bt;
		time = data[i].ct;
		data[i].tat = data[i].ct - data[i].at;
		data[i].wt = data[i].tat - data[i].bt;
	}
	char str[7][200] = {"[Process Id : ","\t[Arrival Time : ", "\t[Burst Time] : ", "\t[Completion Time] : ", "\t[Turn Around Time] : ", "\t[Wait Time] : ","]"};
	for(int i=0;i<p;i++){
		printf("\nProcess #%d : \n",i+1);
		printf("%s",str[0]);
		printf("%d",data[i].pid);
		printf("%s",str[6]);
		printf("%s",str[1]);
		printf("%d",data[i].at);
		printf("%s",str[6]);
		printf("%s",str[2]);
		printf("%d",data[i].bt);
		printf("%s",str[6]);
		printf("%s",str[3]);
		printf("%d",data[i].ct);
		printf("%s",str[6]);
		printf("%s",str[4]);
		printf("%d",data[i].tat);
		printf("%s",str[6]);
		printf("%s",str[5]);
		printf("%d",data[i].wt);
		printf("%s",str[6]);
		printf("\n");
	}
	return 0;
}