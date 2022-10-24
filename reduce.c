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
        int sum;
	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;
	//NON BLOCKING RECEIVE SINCE PROCESS 0 HAVE TO RECEIVE AS WELL
	

	
	if (world_rank == 0)
	 {
	
        printf("Process 0 Preparing to Gather data  for reduction\n");
	
	sendarr = (int*)(malloc(sizeof(int)*procs));

	data=world_rank;
        MPI_Irecv(&sendarr[0],1,MPI_INT,root,0,MPI_COMM_WORLD,&request);
        MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
        
	int i,j;
         for( i=1;i<procs;i++)
	{
	MPI_Recv(&sendarr[i],1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

         }
	//WAITING HERE TILL DATA IS RECEIVED IN BUFFER
	
	printf("Now Printing Gathered Data::\n");
	for( j=0;j<procs;j++)
	{
printf("Value at index%d is %d",j,sendarr[j]);
printf("\n");
	sum=sum+sendarr[j];
	
	}
printf("Performing REduction\n");
MPI_Wait(&request,MPI_STATUS_IGNORE);
MPI_Irecv(&buff,1,MPI_INT,root,0,MPI_COMM_WORLD,&request);
MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
MPI_Wait(&request,MPI_STATUS_IGNORE);
printf("Result After REduction is::%d\n",buff);
         
}


	else
   {
data=world_rank;
MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);

}
	MPI_Finalize();
	}

