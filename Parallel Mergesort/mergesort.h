#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <ctime>
#include <math.h>
#include <cstdint>
using namespace std;
using std::cout;
using std::endl;

// number of threads 
#define THREAD_MAX 6



// Serial Mergesort
void mergeSort(std::vector<int64_t> &arr, int64_t l, int64_t r);

// Multithreaded Mergesort
void p_mergeSort(std::vector<int64_t>& num, int64_t low, int64_t high, int count);
// Serial merge part of the mergeword algorithm
void merge(std::vector<int64_t> &arr, int64_t l, int64_t m, int64_t r); 