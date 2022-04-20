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
    map<int, MinHeap::House> AirBnbListings;
    MinHeap smallHeap = MinHeap(226032);

public:
    /************AirBnb Constructors************/
    AirBnb();

    /************Output************/
    void PrintListings();

    void MenuPrinting();

    void PrintTuples(vector<MinHeap::House> tuples);

    void PrintProperSpace(string input, int lengthOfField);
    void PrintProperSpaceMoney(string input, int lengthOfField);

    /************MenuOptions************/
    void ByCityMenu(int MenuInput);

    /************Search************/
    //idea for these are that they will return a vector of house objects and then print function prints them
    vector<MinHeap::House> ByCityMap(string city);
    vector<MinHeap::House> ByCityMinHeap(string city);

    vector<MinHeap::House> ByRegionMap(int choice); //number will be 1-4 and each coordinates to cardinal direction
    vector<MinHeap::House> ByRegionMinHeap(int choice);

    vector<MinHeap::House> SearchForPriceMinHeap(int budget);
    vector<MinHeap::House> SearchForPriceMap(int budget);

    vector<MinHeap::House> RoomOptionsMinHeap(int option);
    vector<MinHeap::House> RoomOptionsMap(int option);

    vector<MinHeap::House> HostIDMap(int hostID);
    vector<MinHeap::House> HostIDMinHeap(int hostID);

    vector<MinHeap::House> ListingIDMap(int listingID);
    vector<MinHeap::House> ListingIDMinHeap(int listingID);

    vector<MinHeap::House> HostNameMap(string name);
    vector<MinHeap::House> HostNameMinHeap(string name);

    /************Directional************/
    static bool North(const MinHeap::House& house);//with just these two we can base the rest of the directions off of

    static bool East(const MinHeap::House& house);

};