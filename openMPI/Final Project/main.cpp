// call with mpirun -np 4 ./hello_world
// compile with  mpicxx -o hello_world hello_world.cpp

#include <mpi.h>
#include <stdio.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    // All code from here on is run in parrallel on each CPU
    MPI_Init(&argc, &argv);
    int process_id;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string collection[4];

    if (process_id == 0)
    {
        collection[0] = "Book_1";
        collection[1] = "Book_2";
        collection[2] = "Book_3";
        collection[3] = "Book_4";

    }

    // Broadcasting book names to all processors
    for(int i =0; i < 4; i++)
        MPI_Bcast(&collection[i], 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);
    for(int i =0; i < 4; i++)
        cout << "process_id: " << process_id << ": " << collection[i] << endl;

    // Wait for All processors to finish reading in data
    MPI_Barrier(MPI_COMM_WORLD);


    // Main work loop for program
    if (process_id == 0)
    {
        cout << "Finished Broadcasting data: " << sizeof(&collection) << endl;



    }
    else
    {
        /* code exicuted on all worker processors  */
    }
    

    MPI_Finalize();
    return 0;
}
