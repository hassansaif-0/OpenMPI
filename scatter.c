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
	
        printf("Process 0 Preparing Data to scatter data \n");

	sendarr = (int*)(malloc(sizeof(int)*procs));
	int i,j,l=0;
         for( i=0;i<procs;)
	{
	
	sendarr[i]= i++;
         
	}
	 for( j=0;j<procs;j++)
	{

	MPI_Send(&sendarr[j],1,MPI_INT,j,0,MPI_COMM_WORLD);

	}
	
	
	}

	
        
        //WAITING HERE TILL DATA IS RECEIVED IN BUFFER
	MPI_Wait(&request,MPI_STATUS_IGNORE);
	

	
	printf("Process %d received data %d from root process\n", world_rank, buff);
	MPI_Finalize();
	}

