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
        // Get book names from directory /Books and add them to the collection vector
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

    // Deviding work evenly as possable across all processors
    int jobs = collection.size();
    int start = process_id * (static_cast<double>(jobs)/size);
    int end = (process_id + 1) * (static_cast<double>(jobs)/size) - 1;

    // Main Driver to work through all assigned books for each processor
    for(int i = start; i <= end; i++)
    {








    }

    

    
    MPI_Finalize();
    return 0;
}
