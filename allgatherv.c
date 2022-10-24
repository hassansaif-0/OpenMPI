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
	int *resbuff;
	int *allpd;
	int data;
	int buff;

	//INITIALIZERS
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Request request=MPI_REQUEST_NULL;

	
	int distib[]={1,2,2,3,3,2,2,1};
	int offsets[]={15,13,11,8,5,3,1,0};
	allpd = (int*)(malloc(sizeof(int)*(procs*2)));
	
	

	
	if (world_rank == 0)
	 {
	recbuff = (int*)(malloc(sizeof(int)*(procs*2)));
	resbuff = (int*)(malloc(sizeof(int)*(procs*2)));


	printf("Process 0 Preparing Data to Gather variable amount of data \n");

	MPI_Irecv(recbuff,distib[world_rank],MPI_INT,root,0,MPI_COMM_WORLD,&request);
        
	int sendarr[]={1};
        MPI_Send(sendarr,distib[world_rank],MPI_INT,0,0,MPI_COMM_WORLD);
	
	int lopv;
	int o=0;
        for(lopv=offsets[world_rank];lopv<offsets[world_rank]+distib[world_rank];lopv++)
{

	resbuff[lopv]=recbuff[o];
	o++;
}	
	
	int i,j;
        

        
   

         
	 for( j=1;j<procs;j++)
	{

	MPI_Recv(recbuff,distib[j],MPI_INT,j,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        o=0;
	       for(lopv=offsets[j];lopv<offsets[j]+distib[j];lopv++)
{
	resbuff[lopv]=recbuff[o];
	o++;
}	



}
printf("Process %d have following variable gathered data:::\n",world_rank);
int x=0;
for(x=0;x<16;x++)
printf("   %d",resbuff[x]);

 for( j=1;j<procs;j++)
	{
	MPI_Send(resbuff,procs*2,MPI_INT,j,0,MPI_COMM_WORLD);
}
}	
else
{

	temparr = (int*)(malloc(sizeof(int)*distib[world_rank]));
	
	int t;
	for(t=0;t<distib[world_rank];t++)
	{
	temparr[t]=world_rank;
	}
	
	MPI_Send(temparr,distib[world_rank],MPI_INT,0,0,MPI_COMM_WORLD);
	MPI_Recv(allpd,procs*2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	printf("Process %d have following variable gathered data:::\n",world_rank);
	int b=0;
	for(b=0;b<16;b++)
	printf("   %d",allpd[b]);
printf("\n");
	
	

	

}
MPI_Finalize();
}

	
	

