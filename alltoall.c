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
	int *inpbuff;
	
	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;
	//NON BLOCKING RECEIVE SINCE PROCESS 0 HAVE TO RECEIVE AS WELL
	ansbuff = (int*)(malloc(sizeof(int)*procs));
	
	
	if (world_rank == 0)
	 {
	
        //printf("Process 0 Preparing to Gather data \n");
	
	sendarr = (int*)(malloc(sizeof(int)*1));
	int r;

	for(r=0;r<world_rank+1;r++)
	{
	sendarr[r]=world_rank;
	}

	
        MPI_Irecv(&ansbuff[0],1,MPI_INT,root,0,MPI_COMM_WORLD,&request);
        MPI_Send(&sendarr[0],1,MPI_INT,0,0,MPI_COMM_WORLD);
        
	int i,j;
         for( i=1;i<procs;i++)
	{
	MPI_Irecv(&ansbuff[i],1,MPI_INT,i,0,MPI_COMM_WORLD,&requests);

         }
	 for( i=1;i<world_rank+1;i++)
	{
	MPI_Isend(&sendarr[i],1,MPI_INT,i,0,MPI_COMM_WORLD,&requests);

         }

	  for( i=0;i<procs;i++)
	{
	printf("%d",ansbuff[i]);
	}
	
	
}


	else
   {
sendarr = (int*)(malloc(sizeof(int)*(world_rank+1)));
int t=0;
for(t=0;t<world_rank+1;t++)
sendarr[t]=world_rank;
MPI_Irecv(&ansbuff[0],1,MPI_INT,world_rank,0,MPI_COMM_WORLD,&request);
MPI_Send(&sendarr[world_rank],1,MPI_INT,world_rank,0,MPI_COMM_WORLD);

int i,j;
         for( i=world_rank+1;i<procs;i++)
	{
	MPI_Irecv(&ansbuff[i],1,MPI_INT,i,0,MPI_COMM_WORLD,&requests);

         }
	 for( i=0;i<world_rank+1;i++)
	{
	MPI_Isend(&sendarr[i],1,MPI_INT,i,0,MPI_COMM_WORLD,&requests);

         }

	  for( i=0;i<procs;i++)
	{
	printf("%d",ansbuff[i]);
	}
	MPI_Finalize();
	}

