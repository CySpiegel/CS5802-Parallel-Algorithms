#include "mergesort.h"




int main()
{   
    int threadCounter = 0;
    clock_t serial_time_req;
    clock_t multiThread_time_req;

    vector<int64_t> serialSortedvector;
    vector<int64_t> multiThreadedSortedVector;


    // Worst Case Vector order, Decending Order
    for(int64_t i = 1000000000; i > 0; i--)
    {
        serialSortedvector.push_back(i);
        multiThreadedSortedVector.push_back(i);
    } 

    cout << "array size: " << serialSortedvector.size() << endl;

    serial_time_req = clock();
    //SerialVector Sorting
    mergeSort(serialSortedvector, 0, serialSortedvector.size() - 1);
    serial_time_req = clock() - serial_time_req;
    float SerialTimeTaken = float(serial_time_req)/CLOCKS_PER_SEC;

    multiThread_time_req = clock();
    //Multi-Threaded mergeSort
    p_mergeSort(multiThreadedSortedVector, 0, multiThreadedSortedVector.size() - 1, threadCounter);
    multiThread_time_req = clock() - multiThread_time_req;
    float multiThreadedTimeTaken = float(multiThread_time_req)/CLOCKS_PER_SEC;

    cout << "Serial MergeSort time taken: " <<  SerialTimeTaken << endl;
    cout << "Multithreaded MergeSort time taken: " << multiThreadedTimeTaken << endl;

    return 0;
}

