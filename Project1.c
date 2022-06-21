#include <stdio.h>
#include <mpi.h>
#include <time.h>

const int generate_ID(int rank)
{
  int NN, RR, D, NNRRD;
  time_t random;

  // random number between 10 and 99 is generated for NN
  srand((unsigned) time(&random) + rank);
  NN = (rand() % 90) + 10;
  NNRRD = NN; // NN is concatenated to NNRRD

  // RR is taken from the rank and concatenated to NNRRD
  NNRRD = NNRRD * 100 + rank;

  // D represents NN mod 2
  D = NN % 2;
  NNRRD = NNRRD * 10 + D; // D is concatenated to NNRRD

  // return the final ID after all concatenations
  return NNRRD;
}

int main( int argc, char *argv[] )
{

	int rank, size, currentID;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

    //e[0] = president rank, e[1] = president value, e[2] = vp rank, e[3] = vp value
    int e[4];
    currentID = generate_ID(rank);
    printf("I am process %d, and I generated %d\n", rank, currentID);

    if (rank != 0) {
        MPI_Recv(&e, 4, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        if (currentID % 2 == 0) {
          if (currentID < e[1]) {
            e[1] = currentID;
            e[0] = rank;
          }
        } else {
          if (currentID > e[3]) {
            e[3] = currentID;
            e[2] = rank;
          }
        }
        if(rank == size -1)
            MPI_Send(&e, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
        else
            MPI_Send(&e, 4, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

	
	if (rank == 0) {
        e[0]=e[2]=0;    //President and VP rank are automatically rank 0 at the start
        if((currentID % 2) == 0)
        {
            e[1] = currentID;
            e[3] = 1;
        }
        else
        {
            e[1] = 99998;
            e[3] = currentID;
        }
        MPI_Send(&e, 4, MPI_INT, (rank + 1), 0, MPI_COMM_WORLD);
	MPI_Recv(&e, 4, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Election results:\n");
        printf("President elected from process %d with value %d.\n", e[0], e[1]);
        printf("Vice President elected from process %d with value %d.\n", e[2], e[3]);
	}

	MPI_Finalize();
	return 0;
}

