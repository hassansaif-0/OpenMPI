	#include <stdio.h>
	#include <stdlib.h>
	#include <mpi.h>
	
	
	
	int main(int argc, char** argv)
 	{
	//INITIALIZER
	MPI_Init(NULL, NULL);
	//RANK AND PROCESSES
	int world_rank,procs;
	int root=0;

	//int* sendarr;
	int *recbuff;
	int *temparr;
	int data;
	int buff;

	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;

	recbuff = (int*)(malloc(sizeof(int)*(procs*2)));
	int distib[]={1,2,2,3,3,2,2,1};
	int offsets[]={0,1,3,5,8,11,13,15};

	//NON BLOCKING RECEIVE SINCE PROCESS 0 HAVE TO RECEIVE AS WELL
	

	
	if (world_rank == 0)
	 {
int lopvar=0;
	MPI_Irecv(recbuff,distib[world_rank],MPI_INT,root,0,MPI_COMM_WORLD,&request);
        printf("Process 0 Preparing Data to scatter variable amount of data \n");

	//sendarr = (int*)(malloc(sizeof(int)*procs));
	int i,j;


        
   int sendarr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

         
	 for( j=0;j<procs;j++)
	{
	temparr = (int*)(malloc(sizeof(int)*distib[j]));
	int p;
	int o=0;

         for(p=offsets[j];p<offsets[j]+distib[j];p++)
{
	temparr[o]=sendarr[p];
	o++;
}

	
	MPI_Send(temparr,distib[j],MPI_INT,j,0,MPI_COMM_WORLD);

	}
	
	
	}

	
        
       else
{
	
MPI_Recv(recbuff,distib[world_rank],MPI_INT,root,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}	
MPI_Wait(&request,MPI_STATUS_IGNORE);
	printf("Process %d received Following data  root process\n", world_rank);
	int a=0;
        for(a=0;a<distib[world_rank];a++)
{

	printf("  %d",recbuff[a]);
	
}
printf("\n");
MPI_Finalize();
}

	
	

