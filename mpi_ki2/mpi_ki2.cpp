// mpi_ki2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mpi.h"


int main(int argc, char** argv)
{
    /*int ProcNum, ProcRank, RecvRank;
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
    return 0;*/

    double x[100], TotalSum, ProcSum = 0.0;
    int ProcRank, ProcNum, N = 100;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    // data preparation
    if (ProcRank == 0)
    {
        for (int i = 0; i < 100; i++)
            x[i] = 1;
    }

    // broadcast to all
   
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   
    // partial sum calculation of a vector from i1 to i2
    int k = N / ProcNum;
    int i1 = k * ProcRank;
    int i2 = k * (ProcRank + 1);
    if (ProcRank == ProcNum - 1) i2 = N;
    for (int i = i1; i < i2; i++)
        ProcSum = ProcSum + x[i];
    
    // assembling partial sum on process 0 
    MPI_Reduce(&ProcSum, &TotalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // print result
    
    MPI_Barrier(MPI_COMM_WORLD);
    if (ProcRank == 0)
        printf("\nTotal Sum = %10.2f", TotalSum);
      
    MPI_Finalize();
    

   

    return 0;

}
