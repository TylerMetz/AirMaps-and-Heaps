#include <iostream>
#include<climits>
using namespace std;


class MinHeap{
	int* heap;
	int cap;
	int heapsize;
	public:
	MinHeap(int cap);
	void insertMinHeap(int k);
	int extractMin();
	void heapifyDown(int index);

};