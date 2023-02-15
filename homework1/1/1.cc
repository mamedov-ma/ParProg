#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) 
{
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  std::cout << "Hello world!" << "  World Size: " << world_size << "   Rank: " << my_rank << std::endl;

  MPI_Finalize();

  return 0;
}