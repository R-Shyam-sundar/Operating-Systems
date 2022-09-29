/*
	Name: R.Shyam Sundar
	Roll: CS20B1029
	Date: 22/08/22
	OS LAB - 4 : Round Robin CPU Scheduling Algorithm
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

int process[1000][3],n,p[1000][6],pn;
int rq[1000][3],rq_index;
int added;

char timeline[1000];
int tl_index;

bool isempty(){
	return added >= n;
}

void swap_values(int i,int j)
{
	int temp[3];
	temp[0] = process[i][0];temp[1] = process[i][1];temp[2] = process[i][2];
	process[i][0] = process[j][0]; process[i][1] = process[j][1]; process[i][2] = process[j][2];
	process[j][0] = temp[0]; process[j][1] = temp[1]; process[j][2] = temp[2];
}

void swap_values_rq(int i,int j)
{
	int temp[3];
	temp[0] = rq[i][0];temp[1] = rq[i][1];temp[2] = rq[i][2];
	rq[i][0] = rq[j][0]; rq[i][1] = rq[j][1]; rq[i][2] = rq[j][2];
	rq[j][0] = temp[0]; rq[j][1] = temp[1]; rq[j][2] = temp[2];
}

void add_process_in_ready_queue(int temp[])
{
	rq[rq_index][0] = temp[0];
	rq[rq_index][1] = temp[1];
	rq[rq_index][2] = temp[2];
	rq_index++;
}

void delete_process(int index)
{
	while(index+1<n){
		swap_values(index,index+1);
		index++;
	}
	n--;
}

void delete_process_rq(int index)
{
	while(index+1<rq_index){
		swap_values_rq(index,index+1);
		index++;
	}
	rq_index--;
}

void copy_values(int temp[],int i)
{
	temp[0] = process[i][0];
	temp[1] = process[i][1];
	temp[2] = process[i][2];
}

void copy_values_rq(int temp[],int i)
{
	temp[0] = rq[i][0];
	temp[1] = rq[i][1];
	temp[2] = rq[i][2];
}


void if_arrived_add_it(int time)
{
	if(n <= 0)return;
	while(true){
		int mn = INT_MAX;
		int mn_index = -1;
		bool found = false;
		for(int i=0;i<n;i++){
			if(process[i][1] <= time && process[i][1] < mn){
				found = true;
				mn = process[i][1];
				mn_index = i;
			}
		}
		if(found){
			int temp[3];
			copy_values(temp,mn_index);
			add_process_in_ready_queue(temp);
			delete_process(mn_index);
		}
		else{
			break;
		}	
	}
	
}

void sort_acc_arrival_time(){
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(process[j][1] < process[i][1]){
				swap_values(i,j);
			}
		}
	}
}

void update_competion_time(int pid,int time){
	for(int i=0;i<pn;i++){
		if(p[i][0] == pid){
			p[i][3] = time;
			return;
		}
	}
}

void debug_rq(int time)
{
	printf("\n-----------------READY QUEUE DEBUG------------------------\n");
	printf("[Time = %d]\n",time);
	printf("\n[rq_index = %d]\n The process : ",rq_index);
	for(int i=0;i<rq_index;i++){
		printf("\n[Process ID: %d] [Arrival Time: %d] [Burst Time: %d]",rq[i][0],rq[i][1],rq[i][2]);

	}
	printf("\n");
}

void debug_process(int time)
{
	printf("\n---------------PROCESS DEBUG------------------------\n");
	printf("[Time = %d]\n",time);
	printf("\n[n = %d]\n The values in process : ",n);
	for(int i=0;i<n;i++){
		printf("\n[Process ID: %d] [Arrival Time: %d] [Burst Time: %d]",process[i][0],process[i][1],process[i][2]);
	}
	printf("\n");
}

void Round_Robin_CPU_Scheduling_Algorithm()
{
	printf("\nEnter the number of process :  ");
	scanf("%d",&n);
	pn = n;
	int is_arrival_time_same = 0;
	printf("\nIs arrival time for all process same? [1 = Yes / Any other = No]");
	scanf("%d",&is_arrival_time_same);
	for(int i=0;i<n;i++){
		printf("\nEnter the process id for #%d: ",i+1);
		scanf("%d",&process[i][0]);
		if(is_arrival_time_same != 1){
			printf("\nEnter the arrival time for #%d: ",i+1);
			scanf("%d",&process[i][1]);
		}else{
			process[i][1] = 0;
		}
		printf("\nEnter the Burst time for #%d:  ",i+1);
		scanf("%d",&process[i][2]);
		p[i][0] = process[i][0];
		p[i][1] = process[i][1];
		p[i][2] = process[i][2];
	}
	int tq,cs;
	printf("\nEnter the time quantum:  ");
	scanf("%d",&tq);
	printf("\nEnter the context switching time : ");
	scanf("%d",&cs);

	printf("\nTime Quantum =  %d",tq);

	sort_acc_arrival_time();

	timeline[0] = '\0';
	tl_index = 0;

	int prev_time = 0;
	int time = 0;
	debug_rq(time);
	// debug_process(time);
	while(true){
		if_arrived_add_it(time);
		debug_rq(time);
		if(rq_index <= 0){
			if(n <= 0)break;
			else{
				time++;
				continue;
			}
		}

		if(rq[0][2] > tq){
			timeline[tl_index] = rq[0][0] + '0';
			timeline[tl_index+1] = '\0';
			tl_index++;
			rq[0][2] -= tq;
			time+=tq;
			if_arrived_add_it(time);
			int temp[3];
			copy_values_rq(temp,0);
			add_process_in_ready_queue(temp);	
			delete_process_rq(0);
		}else if(rq[0][2] == tq){
			time+=tq;
			if_arrived_add_it(time);
			update_competion_time(rq[0][0],time);
			timeline[tl_index] = rq[0][0] + '0';
			timeline[tl_index+1] = '\0';
			tl_index++;
			delete_process_rq(0);
		}else{ // rq[0][2] < tq
			update_competion_time(rq[0][0],time+rq[0][2]);
			time+=rq[0][2];
			if_arrived_add_it(time);
			timeline[tl_index] = rq[0][0] + '0';
			timeline[tl_index+1] = '\0';
			tl_index++;
			delete_process_rq(0);
		}
		// debug_rq(time);
		// debug_process(time);
	}

	printf("\nThe Timeline:  %s\n",timeline);

	for(int i=0;i<pn;i++){
		p[i][4] = p[i][3] - p[i][1];
		p[i][5] = p[i][4] - p[i][2];
		printf("\n[Process ID: %d] [Arrival Time: %d] [Burst Time: %d] [Completion Time: %d] [Turn around Time: %d] [Wait Time: %d]",p[i][0],p[i][1],p[i][2],p[i][3],p[i][4],p[i][5]);
	}
	double avg_wt = 0,avg_tat = 0;
	for(int i=0;i<pn;i++){
		avg_wt += (p[i][5]);
		avg_tat += (p[i][4]);
	}
	printf("\n[Average Wait Time : %lf]\n[Average Turn Around Time : %lf]\n",avg_wt/pn,avg_tat/pn);
	printf("\n\nThank You!\n\n");
}

int main()
{
	Round_Robin_CPU_Scheduling_Algorithm();
	return 0;
}