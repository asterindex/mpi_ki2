// mpi_ki2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mpi.h"


int main(int argc, char** argv)
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0)
    {
        //printf("\n Hello from process %3d", ProcRank);
        for (int i = 1; i < ProcNum; i++)
        {
            MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,
                MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            printf("\n %3d Hello from process %3d, (%3d)", ProcRank, RecvRank, Status.MPI_SOURCE);
        }
    }
    else
    {
        int test = 3;
        MPI_Send(&test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
