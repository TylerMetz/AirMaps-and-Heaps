/*
 * @Date 4/14/20
 * @Author Tyler Metz
 * @Version 1.0
 * @Description: First version working to implement the basis for the rest of the program
 * @Changes: First Commit
 */

#include "AirBnb.h"

/************House Constructors************/
// default constructor sets everything to
AirBnb::House::House()
{
    hostID = 0;
    price = 0;
    minNights = 0;
    name = "";
    hostName = "";
    roomType = "";
    city = "";
    latitude = 0.0;
    longitude = 0.0;
    MinHeap minH = MinHeap(226033);
}

AirBnb::House::House(string name_, int hostID_, string hostName_, float latitude_, float longitude_,
                     string roomType_, int price_, int minNights_, string city_)
{
    name = name_;
    hostID = hostID_;
    hostName = hostName_;
    latitude = latitude_;
    longitude = longitude_;
    roomType = roomType_;
    price = price_;
    minNights = minNights_;
    city = city_;
    MinHeap minH = MinHeap(226033);
}

/************AirBnb Constructors************/
//default constructor
AirBnb::AirBnb() {
    const string fileName = "UpdatedAirbnb.csv";
    string line;
    int counter = 0;
    int check = 0;
    ifstream file(fileName);
    while (getline(file, line)) {//reads in data from csv file
        counter++;
        if (counter == 1)//skips the first line in csv file
            continue;
        else {
            check++;
            istringstream stream(line);
            string Sid, Sname, ShostID, ShostName, Slatitude, Slongitude, SroomType,
                    Sprice, SminNights, Scity;
            getline(stream, Sid, ','); //1
            getline(stream, Sname, ','); //2
            getline(stream, ShostID, ','); //3
            getline(stream, ShostName, ','); //4
            getline(stream, Slatitude, ','); //6
            getline(stream, Slongitude, ','); //7
            getline(stream, SroomType, ','); //8
            getline(stream, Sprice, ','); //9
            getline(stream, SminNights, ','); //10
            getline(stream, Scity, ','); //11
            //creates new house
            //cout << stoi(Sid) <<' ' << stof(Slatitude) << ' ' << stof(Slongitude) << ' ' <<endl;
            House listing = House(Sname, stoi(ShostID), ShostName,
                                   stof(Slatitude), stof(Slongitude), SroomType, stoi(Sprice), stoi(SminNights),
                                   Scity);
            //sets new key value of listing id with matching House object
            AirBnbListings[stoi(Sid)] = listing;
            smallHeap.insertMinHeap(stoi(Sprice));
        }
    }
}

/************Output************/
void AirBnb::PrintListings()
{
    for(auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
        cout << iter->first << ' ' << iter->second.city << endl;
        cout << "min: " << smallHeap.extractMin() << endl;
    }
}