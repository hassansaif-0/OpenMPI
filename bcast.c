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
	int data;
int buff;
	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;
	//NON BLOCKING RECEIVE SINCE PROCESS 0 HAVE TO RECEIVE AS WELL
	MPI_Irecv(&buff,1,MPI_INT,root,0,MPI_COMM_WORLD,&request);

	
	if (world_rank == 0)
	 {
	printf("Enter Data to Broadcast::");
         if(scanf("%d",&data)==1)
	{
        printf("Process 0 broadcasting data %d\n", data);
	
	int i;
         for( i=0;i<procs;i++)
	{
	
	MPI_Send(&data,1,MPI_INT,i,0,MPI_COMM_WORLD);
	
	}

	}

	else
	{
	printf("Broad cast failed\n");
	
	}
        
	
	
	} 
        //WAITING HERE TILL DATA IS RECEIVED IN BUFFER
	MPI_Wait(&request,MPI_STATUS_IGNORE);
	

	
	printf("Process %d received data %d from root process\n", world_rank, buff);
	MPI_Finalize();
	}

