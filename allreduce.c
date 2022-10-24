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
	int* sendarr;
	int *ansbuff;
	int data;
	int buff;
	int redans;
	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;
	//NON BLOCKING RECEIVE SINCE PROCESS 0 HAVE TO RECEIVE AS WELL
	ansbuff = (int*)(malloc(sizeof(int)*procs));

	
	if (world_rank == 0)
	 {
	int sum;
        //printf("Process 0 Preparing to Gather data \n");
	
	sendarr = (int*)(malloc(sizeof(int)*procs));

	data=world_rank;
        MPI_Irecv(&sendarr[0],1,MPI_INT,root,0,MPI_COMM_WORLD,&request);
        MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
        
	int i,j;
         for( i=1;i<procs;i++)
	{
	MPI_Recv(&sendarr[i],1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

         }

	for( j=0;j<procs;j++)
	{
	sum=sum+sendarr[j];
	
	}
	MPI_Irecv(&redans,1,MPI_INT,root,0,MPI_COMM_WORLD,&request);
        MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	  for( i=1;i<procs;i++)
	{
	MPI_Send(&sum,1,MPI_INT,i,0,MPI_COMM_WORLD);
	}
	
printf("Process %d have received reduces data:%d\n", world_rank,redans);	
}


	else
   {
data=world_rank;
MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
MPI_Recv(&redans,1,MPI_INT,root,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Process %d have received reduces data:%d\n", world_rank,redans);
}
	MPI_Finalize();
	}

