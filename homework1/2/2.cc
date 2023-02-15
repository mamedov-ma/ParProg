#include <bits/stdc++.h>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char ** argv)
{
	int myrank, p, n;
    std::cin >> n;
	int res = 0;

	MPI_Status status;
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(myrank != 0)
	{
		int interval = n/(p-1);
		int x = interval*(myrank-1);
		int y = interval*(myrank)-1;

		res = 0;
		for(int i = x; i <= y; ++i)
			res += i;

		MPI_Send(&res, sizeof(res), MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
    else
	{
        int sum = 0;
		for(int src = 1; src < p; ++src)
		{
			MPI_Recv(&res, sizeof(res), MPI_INT, src, 0, MPI_COMM_WORLD, &status);
			std::cout << "sum recieved from the process: " << src << " is " << res << std::endl;
			sum = sum + res;
		}
	 	std::cout << "the total sum is " << sum;
	 }
	 
	MPI_Finalize();
}	