

#include "mergesort.hpp"


using std::cout;
using std::endl;



int main()
{   
    std::vector<int> MyVector;

    for(int i = 10; i > 0; --i)
    {
        MyVector.push_back(i);
    } 

    int vectorSize = MyVector.size() - 1;

    for(int i : MyVector)
    {
        cout << i << endl;
    }


    mergeSort(MyVector, 0, vectorSize);

    std::cout << "hello world" << std::endl;

    for(int i : MyVector)
    {
        cout << i << endl;
    }


    return 0;
}

