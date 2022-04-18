#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "MinHeap.h"

using namespace std;

//order in the csv file
//id(1),name(2),hostID(3),hostName(4),latitude(6),longitude(7),roomType(8),price(9),minNights(10),city(11)
class AirBnb {
    struct House
    {
        int hostID, price, minNights;//3,9,10
        string name, hostName, roomType, city;//2,4,8,11
        float latitude, longitude;//6,7


        /************House Constructors************/
        House();

        House(string name_, int hostID_, string hostName_, float latitude_, float longitude_,
              string roomType_, int price_, int minNights_, string city_);

    };
    map<int, House> AirBnbListings;
    MinHeap smallHeap = MinHeap(226032);

public:
    /************AirBnb Constructors************/
    AirBnb();

    /************Output************/
    void PrintListings();
};
