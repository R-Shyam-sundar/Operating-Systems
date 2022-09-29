#include<stdio.h>


/*
	a[0] = process id, a[1] = arrival time , a[2] = burst time,
	a[3] = completion time, a[4] = tat, a[5] = wt

*/

void swapp(int p[][7], int j,int i)
{
	int temp;
	temp = p[j][0]; p[j][0] = p[i][0]; p[i][0] = temp;
	temp = p[j][1]; p[j][1] = p[i][1]; p[i][1] = temp;
	temp = p[j][2]; p[j][2] = p[i][2]; p[i][2] = temp;
	temp = p[j][3]; p[j][3] = p[i][3]; p[i][3] = temp;
	temp = p[j][4]; p[j][4] = p[i][4]; p[i][4] = temp;
	temp = p[j][5]; p[j][5] = p[i][5]; p[i][5] = temp;
	return;
}

void bubblesort_arrivaltime(int p[][7], int start,int end)
{
	for(int i=start;i<end;i++){
		for(int j=start;j<end;j++){
			if(p[j][1] > p[i][1]){
				swapp(p,j,i);
			}
			else if(p[j][1] == p[i][1]){
				if(p[j][2] > p[i][2]){
					swapp(p,j,i);
				}
			}
		}
	}
}

void bubblesort_priority(int p[][7], int start,int end)
{
	for(int i=start;i<end;i++){
		for(int j=start;j<end;j++){
			if(p[j][6] < p[i][6]){
				swapp(p,j,i);
			}
		}
	}
}

void debugprocess(int p[][7],int st,int end){
	for(int i=st;i<end;i++){
		printf("\n [pid : %d] [ar tm : %d] [bst time : %d] [comp time: %d] [tat : %d] [wt : %d] [priority : %d]",p[i][0],p[i][1],p[i][2],p[i][3],p[i][4],p[i][5],p[i][6]);
	}
}

void line()
{
	printf("\n-----------------------------------------------------------------------------------------\n");
}

void addatindex(int pq[][7],int p[][7],int pqindex,int index)
{
	for(int i=0;i<7;i++){
		pq[pqindex][i] = p[index][i];
	}
}

void removeatindex(int pq[][7],int pqindex,int len)
{
	for(int i=0;i<len;l++){
		swapp(pq,i,i+1);
	}
}


void priorityCPUscheduling()
{
	int n; 
	printf("\nEnter the number of processes :  ");
	scanf("%d",&n);
	int p[n][7];
	int samearrivaltime = -1;
	here:
	printf("\nIs all arrival time same [1 = YES] : ");
	scanf("%d",&samearrivaltime);
	if(samearrivaltime != 1){
		for(int i=0;i<n;i++){
			printf("\nEnter the [process id] [arrival time] [burst time] [priority]#%d:  ",i+1);
			scanf("%d%d%d%d",&p[i][0],&p[i][1],&p[i][2],&p[i][6]);
			p[i][3] = -1;
			p[i][4] = -1;
			p[i][5] = -1;
		}
	}
	else{
		for(int i=0;i<n;i++){
			printf("\nEnter the [process id] [burst time] [priority]#%d:  ",i+1);
			scanf("%d%d%d",&p[i][0],&p[i][2],&p[i][6]);
			p[i][1] = 0;
			p[i][3] = -1;
			p[i][4] = -1;
			p[i][5] = -1;
		}
	}

	bubblesort_arrivaltime(p,0,n);

	debugprocess(p,0,n);

	int pq_index = 0, pq[n+1000][7];
	int front = 0;
	addatindex(pq,p,pq_index,0);
	pq_index++;
	bubblesort_priority(pq,0,1);
	pq[0][2]--;
	if(pq[0][2] <= 0){
		front++;
	}
	int sec = 0;
	while(true)
	{	
		for(int i=0;i<n;i++){
			if(pq[i][1] == sec){
				addatindex(pq,p,pq_index,0);
				pq_index++;
				bubblesort_priority(pq,front,pq_index);
			}
		}
		bubblesort_priority(pq,0,pq_index);
		pq[0][2]--;
		if(pq[0][2] <= 0){
			front++;
			pq[0][3] = sec;
		}
		sec++;
		if(front == pq_index-1)break;
	}
	debugprocess()
}

int main()
{
	priorityCPUscheduling();
	return 0;
}