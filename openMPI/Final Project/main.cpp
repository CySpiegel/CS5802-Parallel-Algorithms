// call with mpirun -np 4 ./hello_world
// compile with  mpicxx -o hello_world hello_world.cpp

#include <cstdlib>
#include <mpi.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    // All code from here on is run in parrallel on each CPU
    MPI_Init(&argc, &argv);
    int process_id;
    int size;
    int num_of_books = 0;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::string> collection;

    if (process_id == 0)
    {
        collection.push_back("Book_1");
        collection.push_back("Book_2");
        collection.push_back("Book_3");
        collection.push_back("Book_4");
        num_of_books = collection.size();
        for (int i =0; i < size; i++)
        {
            MPI_Send(&num_of_books, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    
    // Getting vector size from processor_id 0
    int local_vector_size = 0;
    if (process_id != 0)
    {   
        // Resizing vectors on all processors to match the size of the vector on processor_id 0
        MPI_Recv(&local_vector_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        collection.resize(local_vector_size);

    }
    
    // Wait for All processors to finish reading in data
    MPI_Barrier(MPI_COMM_WORLD);

    // Broadcasting book names to all processors
    // collection.size works because it was resized before this point on all processors
    for(int i =0; i < collection.size(); i++)
        MPI_Bcast(&collection[i], 20, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Wait for All processors to finish reading in data
    MPI_Barrier(MPI_COMM_WORLD);

    /* ------------------------------------------------------------------------------------ */

    // Set each processors to be available for work
    int readyForWork = 1;
    // Total number of jobs needing to be processed
    int jobsLeft = collection.size();
    // Index of current job needing to be processed
    int jobIndex = 0;



    if (process_id == 0)
    {   
        int proc = 0;
        while(jobIndex < jobsLeft)
        {
            MPI_Recv(&readyForWork, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            proc = status.MPI_SOURCE;
            cout << "From Processor: " << proc << endl;
            MPI_Send(&jobIndex, 1, MPI_INT, proc, 0, MPI_COMM_WORLD);
            jobIndex++;
        }
        cout << "Process 0 Terminated" << endl;
    }
    else
    {   
        status.MPI_SOURCE = process_id;
        MPI_Ssend(&readyForWork, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        while(jobIndex >= 0)
        {
            MPI_Recv(&jobIndex, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << "Proc: " << process_id << " job: " << jobIndex << endl;
        }

    }

    



    
    MPI_Finalize();
    return 0;
}
