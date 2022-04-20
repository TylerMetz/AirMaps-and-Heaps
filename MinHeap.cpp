#include "MinHeap.h"


MinHeap::MinHeap(int capacity){
    heapsize = 0;
    cap = capacity;
    heap = new House[capacity];
}

/************House Constructors************/
// default constructor sets everything to
MinHeap::House::House()
{
    ID = 0;
    hostID = 0;
    price = 0;
    minNights = 0;
    name = "";
    hostName = "";
    roomType = "";
    city = "";
    latitude = 0.0;
    longitude = 0.0;
    minPrice = 0;
}

MinHeap::House::House(int ID_, string name_, int hostID_, string hostName_, float latitude_, float longitude_,
                     string roomType_, int price_, int minNights_, int minPrice_, string city_)
{
    ID = ID_;
    name = name_;
    hostID = hostID_;
    hostName = hostName_;
    latitude = latitude_;
    longitude = longitude_;
    roomType = roomType_;
    price = price_;
    minNights = minNights_;
    city = city_;
    minPrice = minPrice_;
}

MinHeap::House* MinHeap::House::operator=(House& House1)
{
    this->ID = House1.ID;
    this->name = House1.name;
    this->hostID = House1.hostID;
    this->hostName = House1.hostName;
    this->latitude = House1.latitude;
    this->longitude = House1.longitude;
    this->roomType = House1.roomType;
    this->price = House1.price;
    this->minNights = House1.minNights;
    this->city = House1.city;
    this->minPrice = House1.minPrice;
    return this;
}

bool MinHeap::House::operator>(House& House2)
{
    if(this->minPrice > House2.minPrice)
    {
        return true;
    }
    else
        return false;
}

bool MinHeap::House::operator>=(House& House2)
{
    if(this->minPrice >= House2.minPrice)
    {
        return true;
    }
    else
        return false;
}

bool MinHeap::House::operator<(House& House2)
{
    if(this->minPrice < House2.minPrice)
    {
        return true;
    }
    else
        return false;
}

bool MinHeap::House::operator<=(House& House2)
{
    if(this->minPrice <= House2.minPrice)
    {
        return true;
    }
    else
        return false;
}

void MinHeap::insertMinHeap(MinHeap::House& houseInsert){
    if(cap == heapsize){
        return;
    }
    heapsize++;
    int lastIn = heapsize -1;
    heap[lastIn] = houseInsert;
    int parent = (lastIn - 1)/2;

    //while loop keep heapify up
    while(heap[parent].minPrice > heap[lastIn].minPrice){
        if(lastIn != 0){
            //swap
            House temp = heap[lastIn];
            heap[lastIn] = heap[parent];
            heap[parent] = temp;
            lastIn = parent;
            parent = (parent - 1)/2;
        }
    }
}

MinHeap::House MinHeap::extractMin(){
    if(heapsize <= 0){
        //return
    }
    if(heapsize == 1){
        heapsize--;
        return heap[0];
    }
    House min = heap[0];
    heap[0] = heap[heapsize - 1];
    heapifyDown(0);
    heapsize--;
    return min;
}

void MinHeap::heapifyDown(int index){
    int left = (2*index)+1;
    int right = (2*index)+2;
    House temp;
    //index is leaf
    //find smallest child of House at index
    //see if there is a left and/or right child
    if(left < heapsize){ //see if there is a left index
        if(right < heapsize){ //see if there is a right index
            //left child is smaller than right move it up
            if(heap[left].minPrice < heap[right].minPrice){
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
            if(heap[index].minPrice > heap[left].minPrice){
                House temp = heap[index];
                heap[index] = heap[left];
                heap[left] = temp;
            }
        }
    }
}