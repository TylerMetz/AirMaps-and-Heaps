#include "AirBnb.h"
using namespace std;

int main() {
    AirBnb listing = AirBnb();
    listing.PrintListings();
    return 0;
}

//method used to update the airbnb data
//paste into main the redo
/*
 * string line;
    string fileName = "AB_US_2020.csv";
    int counter = 0;
    vector<string> id, name, hostID, hostName, zipCode, latitude, longitude, room_type,
    price, minNights, city, garbage;
    ifstream file(fileName);
    while(getline(file, line))
    {
        counter++;
        if(counter == 1)
            continue;
        else {
            istringstream stream(line);
            string Sid, Sname, ShostID, ShostName, SzipCode, Slatitude, Slongitude, Sroom_type,
            Sprice, SminNights, Scity, Sgarbage;
            getline(stream, Sid, ','); //1
            getline(stream, Sname, ','); //2
            getline(stream, ShostID, ','); //3
            getline(stream, ShostName, ','); //4
            getline(stream, Sgarbage, ','); //5
            getline(stream, SzipCode, ','); //6
            getline(stream, Slatitude, ','); //7
            getline(stream, Slongitude, ','); //8
            getline(stream, Sroom_type, ','); //9
            getline(stream, Sprice, ','); //10
            getline(stream, SminNights, ','); //11
            getline(stream, Sgarbage, ','); //12
            getline(stream, Sgarbage, ','); //13
            getline(stream, Sgarbage, ','); //14
            getline(stream, Sgarbage, ','); //15
            getline(stream, Sgarbage, ','); //16
            getline(stream, Scity, ','); //17

            //add to vectors
            //vector<string> id, name, hostID, hostName, zipCode, latitude, longitude, room_type,
            // price, minNights, city, garbage;
            id.push_back(Sid);
            name.push_back(Sname);
            hostID.push_back(ShostID);
            hostName.push_back(ShostName);
            zipCode.push_back(SzipCode);
            latitude.push_back(Slatitude);
            longitude.push_back(Slongitude);
            room_type.push_back(Sroom_type);
            price.push_back(Sprice);
            minNights.push_back(SminNights);
            city.push_back(Scity);
        }

    }
    ofstream newFile;
    newFile.open("UpdatedAirbnb.csv");
    newFile << "id,name,hostID,hostName,zipCode,latitude,longitude,roomType,price,minNights,city" << endl;
    for(int i = 0; i < id.size(); i++)
    {
        if(i == id.size() - 1)//will make sure there is not an extra line at the bottom of new file
        {
            newFile << id[i] << ","//1
                    << name[i] << ","//2
                    << hostID[i] << ","//3
                    << hostName[i] << ","//4
                    << zipCode[i] << ","//5
                    << latitude[i] << ","//6
                    << longitude[i] << ","//7
                    << room_type[i] << ","//8
                    << price[i] << ","//9
                    << minNights[i] << ","//10
                    << city[i];//11
        }
        else
        { //prints to new file
            newFile << id[i] << ","//1
                    << name[i] << ","//2
                    << hostID[i] << ","//3
                    << hostName[i] << ","//4
                    << zipCode[i] << ","//5
                    << latitude[i] << ","//6
                    << longitude[i] << ","//7
                    << room_type[i] << ","//8
                    << price[i] << ","//9
                    << minNights[i] << ","//10
                    << city[i] << endl;//11
        }

    }
 */