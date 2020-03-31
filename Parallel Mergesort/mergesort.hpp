#include <iostream>
#include <thread>
#include <vector>

// Serial Mergesort
void mergeSort(std::vector<int> &arr, int l, int r);

// Multithreaded Mergesort
void p_mergeSort(std::vector<int> &arr, int l, int r);

// Serial merge part of the mergeword algorithm
void merge(std::vector<int> &arr, int l, int m, int r); 