#include <iostream>
#include<climits>
#include <chrono>
using namespace std::chrono;

using namespace std;

class MinHeap{
	int cap;
	public:
    int heapsize;
    struct House
    {
        House* operator= (House& House1);
        bool operator> (MinHeap::House& House2);
        bool operator>= (MinHeap::House& House2);
        bool operator< (MinHeap::House& House2);
        bool operator<= (MinHeap::House& House2);
        int ID, hostID, price, minNights, minPrice;//3,9,10
        string name, hostName, roomType, city;//2,4,8,11
        float latitude, longitude;//6,7


        /************House Constructors************/
        House();

        House(int ID_, string name_, int hostID_, string hostName_, float latitude_, float longitude_,
              string roomType_, int price_, int minNights_, int minPrice_, string city_);

    };
	MinHeap(int cap);
	void insertMinHeap(MinHeap::House& houseInsert);
	House extractMin();
	void heapifyDown(int index);
private:
    House* heap;
};