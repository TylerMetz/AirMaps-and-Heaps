#include "MinHeap.h"

MinHeap::MinHeap(int capacity){
    heapsize = 0;
    cap = capacity;
    heap = new int[capacity];
}
void MinHeap::insertMinHeap(int k){
    if(cap == heapsize){
        return;
    }
    heapsize++;
    int lastIn = heapsize -1;
    heap[lastIn] = k;
    int parent = (lastIn - 1)/2;
    if(heap[parent] > heap[lastIn] && lastIn != 0){
        //swap
        int temp = heap[lastIn];
        heap[lastIn] = heap[parent];
        heap[parent] = temp;
        //swap(&heap[lastIn], &heap[parent]);
        parent = (parent-1)/2;
        lastIn = parent;
    }
}
int MinHeap::extractMin(){
    if(heapsize <= 0){
        //return
    }
    if(heapsize == 1){
        heapsize--;
        return heap[0];
    }
    int min = heap[0];
    heap[0] = heap[heapsize -1];
    heapifyDown(0);
    heapsize--;
    return min;
}
void MinHeap::heapifyDown(int index){
    int left = (2*index)+1;
    int right = (2*index)+2;
    int temp = index;
    //index is leaf
    //find smallest child of node at index
    //see if there is a left and/or right child
    if(left < heapsize){ //see if there is a left index
        if(right < heapsize){ //see if there is a right index
            //left child is smaller than right move it up
            if(heap[left] < heap[right]){
                temp = heap[index];
                heap[index] = heap[left];
                heap[left] = temp;
                heapifyDown(left);
            }
            else{
                //right child is smaller than left
                temp = heap[index];
                heap[index] = heap[right];
                heap[right] = temp;
                heapifyDown(right);
            }
        }
        else{
            //one left child
            if(heap[index] > heap[left]){
                temp = heap[index];
                heap[index] = heap[left];
                heap[left] = temp;
            }
        }
    }
}