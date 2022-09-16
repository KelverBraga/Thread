#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

/*
Grupo 
    1) Kelver Ruan Braga de Cristo GRR20162817
    2) Gustavo Hammer
*/

#define ROWS 8    /* if you need a constant, #define one (or more) */
#define COLS 4
        //arrival_time[i] = Tempo chegada Tc.
        //burst_time[i] = Tempo de duração Td.
    
/* fill m[ROWS][COLS] with values read from fp.
 * returns 1 on success, 0 otherwise.
 */
int getmatrix (int (*m)[COLS], FILE *fp)
{

  fscanf(fp, "%*[^\n]");  // Read and discard a line
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      if (fscanf (fp, "%d", &m[row][col]) != 1) {
     
        fprintf (stderr, "error reading m[%d][%d]\n", row, col);
        return 0;
      }
    }
  }
  
  return 1;
}

void prnmatrix (int (*m)[COLS])
{
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      printf (col ? " %4d" : "%4d", m[row][col]);
    }
    putchar ('\n');
  }
}

// method 1 for first come first server algorithm
void * fcfs(void *arg){

        int job_number = 10;
        int arrival_time[]= {2, 7, 8, 10, 9, 9, 12, 2, 3, 7}, burst_time[]={0, 2, 8, 12, 16, 20, 22, 28, 30, 31};
        arrival_time[job_number], burst_time[job_number]; 
        int completion_time[job_number],turnaround_time[job_number],waiting_time[job_number];

	    // loop control variables
	    int i,j;
	 
	    int flag=0,time=0;
	    float avg_turnaround_time=0,avg_waiting_time=0;

	    for(i=0; i<job_number; i++)
	    {
		if(flag<arrival_time[i])
		{
		    time=arrival_time[i]-flag;
		}

		flag=flag+burst_time[i]+time;
		time=0;
		completion_time[i]=flag;
		turnaround_time[i]=completion_time[i]-arrival_time[i];
		avg_turnaround_time=avg_turnaround_time+turnaround_time[i];
		waiting_time[i]=turnaround_time[i]-burst_time[i];
		avg_waiting_time=avg_waiting_time+waiting_time[i];
	    }
	    printf("\n-------------------------------------------\n");
	    printf("Segue abaixo resultados, para o método solicitado:\n");
	    printf(" \nPid\tTd\tTc\tCT\tTt\tTw\n");

	    for(i=0; i<job_number; i++)
	    {
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arrival_time[i],burst_time[i],completion_time[i],
		turnaround_time[i],waiting_time[i]);
	    }

	    printf("Average Turnaround Time=%f ",avg_turnaround_time/job_number);
	    printf("\nAverage Waiting Time=%f",avg_waiting_time/job_number);
	    printf("\n");
}

// method 2 for shortest job first algorithm

void * sjf(void *arg){

    int arrival_time[]= {2, 7, 8, 10, 9, 9, 12, 2, 3, 7}, burst_time[]={0, 2, 8, 12, 16, 20, 22 ,28, 30, 31};

    int i,j;
    int num_job=10;

    printf("Tempo de duração:\n");

    for(i=0;i<num_job;i++)
    arrival_time[i];
    printf("Tempo de espera:\n");
    
    for(i=0;i<num_job;i++)
    burst_time[i];
    
    int Bt[num_job],Ct[num_job];
    for(i=0;i<num_job;i++)
    Bt[i]=burst_time[i];
    int count=0;
    j=0;
    while(j<num_job)
    {
        int min_limit=1000,index=-1;
        for(i=0;i<num_job;i++)
        {
            if(Bt[i]==min_limit)
            {
                if(arrival_time[i]<arrival_time[index])
                index=i;
            }
            
            else if(Bt[i]<min_limit)
            {
                if(arrival_time[i]<=count)
                {
                    min_limit=Bt[i];
                    index=i;
                }
            }
            
        }
        if(index!=-1)
        {
            Ct[index]=burst_time[index]+count;
            count+=burst_time[index];
            j++;
            Bt[index]=1001;
        }
        else
        count++;
    }
    
    int TAT[num_job],WT[num_job];
    
    for(i=0;i<num_job;i++)
    TAT[i]=Ct[i]-arrival_time[i];
    
    for(i=0;i<num_job;i++)
    WT[i]=TAT[i]-burst_time[i];
    
    printf("\nTabela de Processos:\nPid\tTd\tTc\tCT\tTt\tTw\n");
    for(i=0;i<num_job;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),arrival_time[i],burst_time[i],Ct[i],TAT[i],WT[i]);
    
    float avg_var=0;
    for(i=0;i<num_job;i++)
    avg_var+=(float)TAT[i];
    printf("Tempo médio de execução: %f",avg_var/num_job);
    avg_var=0;
    for(i=0;i<num_job;i++)
    avg_var+=(float)WT[i];
    printf("\nTempo médio de espera: %f",avg_var/num_job);
    printf("\n");

}

// method 3 for shortest remaining time first
void * srtf(void *arg){

    int i,j;
    int n=10;
    int arrival_time[]={0, 2, 8, 12, 16, 20, 22 ,28, 30, 31},burst_time[]={2, 7, 8, 10, 9, 9, 12, 2, 3, 7};

    for(i=0;i<n;i++)
    arrival_time[i];
    for(i=0;i<n;i++)
    burst_time[i];
    int Bt[n],completion_time[n],response_time[n];
    for(i=0;i<n;i++)
    Bt[i]=burst_time[i];
    for(i=0;i<n;i++)
    response_time[i]=-1;
    int count=0,prev=-1;
    j=0;

    while(j<n)
    {
        int min=1000,ind=-1;
        for(i=0;i<n;i++)
        {
            if(Bt[i]==min && Bt[i]>0)
            {
                if(arrival_time[i]<arrival_time[ind])
                ind=i;
            }
            
            else if(Bt[i]<min && Bt[i]>0)
            {
                if(arrival_time[i]<=count)
                {
                    min=Bt[i];
                    ind=i;
                }
            }
            
        }
        
        if(ind!=-1)
        Bt[ind]-=1;
        
        if(ind!=prev && response_time[ind]==-1)
        {
            response_time[ind]=count-arrival_time[ind];
        }
        
        count++;
        
        if(Bt[ind]==0 && ind!=-1)
        {
            completion_time[ind]=count;
            j++;
        }
        prev=ind;
    }
    
    int turnaround_time[n],WT[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    WT[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nTabela de Processos:\nPid\tTd\tTc\tCT\tTt\tTw\tRT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),burst_time[i],arrival_time[i],completion_time[i],turnaround_time[i],WT[i],response_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage turnaround_time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)WT[i];
    printf("\nTempo médio de execução: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)response_time[i];
    printf("\nTempo médio de resposta: %f",for_avg/n);
    printf("\n");
}

// method 4 for round robin algoritm
void * rr(void *arg){


	int n,i,j,time_quanta,len=0;
    //printf("Total Number of Processes:");
    //scanf("%d",&n);
    n=10;
    //int arrival_time[n],burst_time[n];
    int arrival_time[]= {2, 7, 8, 10, 9, 9, 12, 2, 3, 7}, burst_time[]={0, 2, 8, 12, 16, 20, 22 ,28, 30, 31};
    printf("Arrival times:\n");
    for(i=0;i<n;i++)
    //scanf("%d",&arrival_time[i]);
    arrival_time[i];
    //printf("Burst times:\n");
    for(i=0;i<n;i++)
    //scanf("%d",&burst_time[i]);
    burst_time[i];
    //printf("Enter Time Quanta:");
    //scanf("%d",&time_quanta);
    time_quanta=3;
    int Bt[n],Ct[n],Rt[n];
    for(i=0;i<n;i++)
    {
        Bt[i]=burst_time[i];
        len+=burst_time[i];
        Rt[i]=-1;
    }
    int ready[len];
    int count=0,front=0,rear=-1,dec=0;
    j=0;

    while(j<n)
    {
        int found=0;
        if(front>rear)
        {
            for(i=0;i<n;i++)
            if(arrival_time[i]==count)
            {
                ready[++rear]=i;
                found=1;
            }
            if(found==0)
            {
                if(dec==0)
                {
                    printf("%d-Idle-",count);
                    dec=1;
                }
                count++;
            }
        }
        else
        {
            int k,ind=ready[front++],dec=0;
            
            printf("%d-P%d-",count,(ind+1));
            
            if(Rt[ind]==-1)
            Rt[ind]=count-arrival_time[ind];
            
            if(Bt[ind]<=time_quanta)
            {
                for(k=0;k<Bt[ind];k++)
                {
                    count++;
                    for(i=0;i<n;i++)
                    {
                        if(arrival_time[i]==count)
                        ready[++rear]=i;
                    }
                }
                Bt[ind]=0;
                Ct[ind]=count;
                j++;
            }
            else
            {
                for(k=0;k<time_quanta;k++)
                {
                    count++;
                    for(i=0;i<n;i++)
                    {
                        if(arrival_time[i]==count)
                        ready[++rear]=i;
                    }
                }
                Bt[ind]-=time_quanta;
                ready[++rear]=ind;
            }
        }
    }
    
    printf("%d|\n",count);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=Ct[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    
    printf("\nProcess Table:\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),arrival_time[i],burst_time[i],Ct[i],turnaround_time[i],waiting_time[i],Rt[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Turnaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)Rt[i];
    printf("\nAverage Response Time: %f",for_avg/n);
    printf("\n");
}

// method 5 for preemptive priority alogritm
void * pp(void *arg){

    int i,j;
    int n=10;

    int arrival_time[]={0, 2, 8, 12, 16, 20, 22 ,28, 30, 31},burst_time[]={2, 7, 8, 10, 9, 9, 12, 2, 3, 7},priority_num[]={5, 2, 4, 5, 1, 5, 2, 2, 5, 4};
    
    for(i=0;i<n;i++)
    arrival_time[i];

    for(i=0;i<n;i++)
    burst_time[i];

    for(i=0;i<n;i++)
    priority_num[i];

    int Bt[n],completion_time[n],response_time[n],Pr[n];
    for(i=0;i<n;i++)
    Bt[i]=burst_time[i];
    for(i=0;i<n;i++)
    Pr[i]=priority_num[i];
    for(i=0;i<n;i++)
    response_time[i]=-1;
    int counter=0,prev=-1,dec=0;
    j=0;
    printf("\nWhich Priority do You Want ?\n");
    int choice;
    //printf("Option:\n1.Low number High priority.\n2.Low number Low priority.\n>>>");
    //scanf("%d",&choice);
    choice=1;

    switch(choice)
    {
        case 1:
            while(j<n)
            {
                int min=1000,ind=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==min && Bt[i]>0)
                    {
                        if(arrival_time[i]<arrival_time[ind])
                        ind=i;
                    }
                    
                    else if(Pr[i]<min && Bt[i]>0)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            min=Pr[i];
                            ind=i;
                        }
                    }
                    
                }
                
                if(ind!=-1)
                {
                    Bt[ind]-=1;
                    if(ind!=prev)
                    printf("%d-P%d-",counter,(ind+1));
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    dec=1;
                }
                
                if(ind!=prev && response_time[ind]==-1)
                response_time[ind]=counter-arrival_time[ind];
                
                counter++;
                
                if(Bt[ind]==0 && ind!=-1)
                {
                    completion_time[ind]=counter;
                    j++;
                    dec=0;
                }
                prev=ind;
            }
        break;
        case 2:
            while(j<n)
            {
                int max=-10,ind=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==max && Bt[i]>0)
                    {
                        if(arrival_time[i]<arrival_time[ind])
                        ind=i;
                    }
                    
                    else if(Pr[i]>max && Bt[i]>0)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            max=Pr[i];
                            ind=i;
                        }
                    }
                    
                }
                
                if(ind!=-1)
                {
                    Bt[ind]-=1;
                    if(ind!=prev)
                    printf("%d-P%d-",counter,(ind+1));
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    dec=1;
                }
                
                
                if(ind!=prev && response_time[ind]==-1)
                response_time[ind]=counter-arrival_time[ind];
                
                counter++;
                
                if(Bt[ind]==0 && ind!=-1)
                {
                    completion_time[ind]=counter;
                    j++;
                    dec=0;
                }
                prev=ind;
            }
        break;
        default:
            printf("Wrong choice..\n");
        break;
    }

    
    printf("%d|\n",counter);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nProcess Table:\nPid\tPr\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),priority_num[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Tunaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)response_time[i];
    printf("\nAverage Response Time: %f",for_avg/n);
    printf("\n");

}
// method 6 for round non preemptive priority algoritm

void * npp(void *arg){


    int i,j;
    int n=10;

    //int arrival_time[n],burst_time[n],num_priority[n];
    //printf("Enter the Arrival time:\n");
    int arrival_time[]={0, 2, 8, 12, 16, 20, 22 ,28, 30, 31},burst_time[]={2, 7, 8, 10, 9, 9, 12, 2, 3, 7},num_priority[]={5, 2, 4, 5, 1, 5, 2, 2, 5, 4};

    for(i=0;i<n;i++)
    //scanf("%d",&arrival_time[i]);
    //printf("Enter the Burst time for processes:\n");
    arrival_time[i];

    for(i=0;i<n;i++)
    //scanf("%d",&burst_time[i]);
    //printf("Priority:\n");
    burst_time[i];

    for(i=0;i<n;i++)
    //scanf("%d",&num_priority[i]);
    num_priority[i];

    int Pr[n],completion_time[n];
    

    for(i=0;i<n;i++)
    Pr[i]=num_priority[i];
    int counter=0,dec=0;
    j=0;
    int choice;
    //printf("Option:\n1.Low number High priority.\n2.Low number Low priority.\n>>>");
    //scanf("%d",&choice);
    choice = 1;    
    switch(choice)
    {
        case 1:
            while(j<n)
            {
                int min=1000,index=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==min)
                    {
                        if(arrival_time[i]<arrival_time[index])
                        index=i;
                    }
                    
                    else if(Pr[i]<min)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            min=Pr[i];
                            index=i;
                        }
                    }
                    
                }
                if(index!=-1)
                {
                    printf("%d-P%d-",counter,(index+1));
                    completion_time[index]=burst_time[index]+counter;
                    counter+=burst_time[index];
                    j++;
                    Pr[index]=1001;
                    dec=0;
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    counter++;
                    dec=1;
                }
            }
        break;
        case 2:
            while(j<n)
            {
                int max=-1,index=-1;
                for(i=0;i<n;i++)
                {
                    if(Pr[i]==max)
                    {
                        if(arrival_time[i]<arrival_time[index])
                        index=i;
                    }
                    
                    else if(Pr[i]>max)
                    {
                        if(arrival_time[i]<=counter)
                        {
                            max=Pr[i];
                            index=i;
                        }
                    }
                    
                }
                if(index!=-1)
                {
                    printf("%d-P%d-",counter,(index+1));
                    completion_time[index]=burst_time[index]+counter;
                    counter+=burst_time[index];
                    j++;
                    Pr[index]=-2;
                    dec=0;
                }
                else
                {
                    if(dec==0)
                    printf("%d-Idle-",counter);
                    counter++;
                    dec=1;
                }
            }
        break;
        default:
            printf("Wrong choice..\n");
        break;
    }
    
    printf("%d|\n",counter);
    
    int turnaround_time[n],waiting_time[n];
    
    for(i=0;i<n;i++)
    turnaround_time[i]=completion_time[i]-arrival_time[i];
    
    for(i=0;i<n;i++)
    waiting_time[i]=turnaround_time[i]-burst_time[i];
    
    printf("\nTabela de processos:\nPid\tPr\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),num_priority[i],arrival_time[i],burst_time[i],completion_time[i],turnaround_time[i],waiting_time[i]);
    
    float for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)turnaround_time[i];
    printf("\nAverage Turnaround Time: %f",for_avg/n);
    for_avg=0;
    for(i=0;i<n;i++)
    for_avg+=(float)waiting_time[i];
    printf("\nAverage Waiting Time: %f",for_avg/n);
    printf("\n");
}

// Main Method to call all the above methods  on user choice
int main(int argc, char **argv){
  
    pthread_t t1,t2,t3,t4,t5,t6;
    int a1,a2,a3,a4,a5,a6;

    printf("\nTabela de Processos:\nPid\tTd\tTc\tPrio\n");
    int matrix[ROWS][COLS] = {{0}};   /* do not use global variables */
    /* use filename provided as 1st argument (stdin by default) */
    //  FILE *fp = argc > 1 ? fopen (argv[1], "r") : stdin;
        FILE *fp = fopen("entrada.txt", "r");

        if (!fp) {  /* validate file open for reading in caller */
        perror ("file open failed");
        return 1;
    }
  
        if (!getmatrix (matrix, fp)) {    /* pass array and open FILE*, validate */
        return 1;
    }

  fclose (fp);
  
  prnmatrix (matrix);       /* output results */

        printf("\n------------------------------------------\n ");
        printf(" Menu para métodos de escalonamento.\n");
        printf("------------------------------------------\n\n");
        printf("Press 1 for 'FIRST COME FIRST SERVE' \n");
        printf("Press 2 for 'SHORTEST JOB FIRST' \n");
        printf("Press 3 for 'SHORTEST REMAINING TIME FIRST' \n");
        printf("Press 4 for 'ROUND ROBIN' \n");
        printf("Press 5 for 'PREEMPTIVE PROPERTY' \n");
        printf("Press 6 for 'NON PREEMPTIVE PROPERTY' \n");
        printf("\n------------------------------------------\n");
        int choice ;
       // printf("Entre com uma opção : ");
       // scanf("%d",&choice);	
	


    pthread_create(&t1,NULL,fcfs,(void*)(&a1));
    pthread_create(&t2,NULL,sjf,(void*)(&a2));
    pthread_create(&t3,NULL,srtf,(void*)(&a3));
    pthread_create(&t4,NULL,rr,(void*)(&a4));
    pthread_create(&t5,NULL,pp,(void*)(&a5));
    pthread_create(&t6,NULL,npp,(void*)(&a6));

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    pthread_join(t6,NULL);

    return 0;
}