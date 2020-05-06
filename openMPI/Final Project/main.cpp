// call with mpirun -np 4 ./hello_world
// compile with  mpicxx -o hello_world hello_world.cpp

#include <cstdlib>
#include <mpi.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>

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
    std::vector<std::string> filenames;
    std::vector<std::string> collection;

    if (process_id == 0)
    {   
        // Get book names from directory /Books and add them to the collection vector
        DIR *dpdf;
        struct dirent *epdf;
        dpdf = opendir("Books");
        if (dpdf != NULL) 
        {
            while ((epdf = readdir(dpdf))) 
            {
                filenames.push_back(std::string(epdf->d_name).c_str());
            }
        }
        for (int i = 2; i < filenames.size(); i++)
        {   
            collection.push_back(filenames[i]);
        }
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
    int start = process_id * (static_cast<double>(collection.size())/size);
    int end = (process_id + 1) * (static_cast<double>(collection.size())/size) - 1;

    if(process_id == 1 )
    {   
        for(int i = 0; i < collection.size(); i ++)
            cout << collection[i] << endl;
    }


    
    MPI_Finalize();
    return 0;
}
