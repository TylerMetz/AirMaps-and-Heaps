/*
 * @Date 4/14/20
 * @Author Tyler Metz
 * @Version 1.0
 * @Description: First version working to implement the basis for the rest of the program
 * @Changes: First Commit
 */

#include "AirBnb.h"

struct User {
    int region;
    int nightsToStay;
    int budget;
};

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
                    Sprice, SminNights, SminPrice, Scity;
            getline(stream, Sid, ','); //1
            getline(stream, Sname, ','); //2
            getline(stream, ShostID, ','); //3
            getline(stream, ShostName, ','); //4
            getline(stream, Slatitude, ','); //6
            getline(stream, Slongitude, ','); //7
            getline(stream, SroomType, ','); //8
            getline(stream, Sprice, ','); //9
            getline(stream, SminNights, ','); //10
            getline(stream, Scity); //11
            //creates new house
            //cout << stoi(Sid) <<' ' << stof(Slatitude) << ' ' << stof(Slongitude) << ' ' <<endl;
            MinHeap::House listing = MinHeap::House(stoi(Sid), Sname, stoi(ShostID), ShostName,
                                                    stof(Slatitude), stof(Slongitude), SroomType, stoi(Sprice),
                                                    stoi(SminNights), stoi(SminNights) * stoi(Sprice),
                                                    Scity);
            //sets new key value of listing id with matching House object
            AirBnbListings[stoi(Sid)] = listing;
            smallHeap.insertMinHeap(listing);
        }
    }
}

/************Output************/
void AirBnb::PrintListings() {
    //for(auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
    //cout << iter->first << ' ' << iter->second.city << endl;
    //}
    for (int i = 0; i < AirBnbListings.size(); i++) {
        cout << "min: " << smallHeap.extractMin().minPrice << endl;
    }
}

void AirBnb::MenuPrinting() {
    string input = "";
    while (true) {
        //collects input from console
        cout << "Hello! How would you like to search for your AirBnb?" << endl;
        cout << "[1] Price" << endl;
        cout << "[2] Room Options" << endl;
        cout << "[3] Host ID" << endl;
        cout << "[4] Listing ID" << endl;
        cout << "[5] City" << endl;
        cout << "[6] Owner Name" << endl;
        cout << "[7] Region" << endl;
        cout << "[-1] To exit: " << endl;
        cin >> input;
        if (stoi(input) == -1)
            break;
        ByCityMenu(stoi(input)); //sends menu choice to further menu process
    }
}

void AirBnb::PrintTuples(vector<MinHeap::House> tuples) {
    cout << left << setfill('=') << setw(108);
    cout << "" << endl;
    cout
            << "||      ID      ||      Name      ||     RoomType     || Price Per Night || Min Nights || Total Min Price ||"
            << endl;
    cout << left << setfill(' ');
    for (int i = 0; i < tuples.size(); i++) {
        cout << "||";
        PrintProperSpace(to_string(tuples[i].ID), 14);
        cout << "||";
        if (tuples[i].name.length() > 16) {
            cout << left << setw(13) << tuples[i].name.substr(0, 13) << "...";
        } else {
            cout << left << setw(16) << tuples[i].name;
        }
        cout << "||";
        PrintProperSpace(tuples[i].roomType, 18);
        cout << "||";
        PrintProperSpaceMoney(to_string(tuples[i].price), 17);
        cout << "||";
        PrintProperSpace(to_string(tuples[i].minNights), 12);
        cout << "||";
        PrintProperSpaceMoney(to_string(tuples[i].minPrice), 17);
        cout << "||" << endl;
    }
    cout << left << setfill('=') << setw(108);
    cout << "" << endl;
}

void AirBnb::PrintProperSpace(const string input, int lengthOfField) {
    int leading = (lengthOfField - input.length()) / 2;
    int trailing = lengthOfField - leading - input.length();
    for (int i = 0; i < leading; i++) {
        cout << " ";
    }
    cout << input;
    for (int i = 0; i < trailing; i++) {
        cout << " ";
    }
}

void AirBnb::PrintProperSpaceMoney(const string input, int lengthOfField) {
    string output = "$";
    output += input;
    int leading = (lengthOfField - output.length()) / 2;
    int trailing = lengthOfField - leading - output.length();
    for (int i = 0; i < leading; i++) {
        cout << " ";
    }
    cout << output;
    for (int i = 0; i < trailing; i++) {
        cout << " ";
    }
}


/************MenuOptions************/
void AirBnb::ByCityMenu(int menuInput) {
    string input;
    if (menuInput == 1)//by price
    {
        vector<MinHeap::House> allTuples;
        while (input != "-1") {
            cout << "Enter your budget" << endl;
            cout << "[-1] to exit: " << endl;
            cin >> input;
            if (input == "-1") {
                for (int i = 0; i < allTuples.size(); i++) {
                    smallHeap.insertMinHeap(allTuples[i]);
                }
            } else {
                PrintTuples(SearchForPriceMap(stoi(input)));
                vector<MinHeap::House> store = SearchForPriceMinHeap(stoi(input));
                PrintTuples(store);
                for (int i = 0; i < store.size(); i++) {
                    allTuples.push_back(store[i]);
                }
            }
        }
    } else if (menuInput == 2)//room options
    {
        vector<MinHeap::House> allTuples;
        while (input != "-1") {
            cout << "What type of room would you like to search for" << endl;
            cout << "[1] Entire home/apt" << endl;
            cout << "[2] Private room" << endl;
            cout << "[3] Shared room" << endl;
            cout << "[-1] To exit: " << endl;
            cin >> input;
            if (input != "-1") {
                PrintTuples(RoomOptionsMap(stoi(input)));
                vector<MinHeap::House> store = RoomOptionsMinHeap(stoi(input));
                PrintTuples(store);
                for (int i = 0; i < store.size(); i++) {
                    allTuples.push_back(store[i]);
                }
            }
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    } else if (menuInput == 3)//by HostID
    {
        vector<MinHeap::House> allTuples;
        cout << "Enter Host ID to search for: " << endl;
        cin >> input;
        PrintTuples(HostIDMap(stoi(input)));
        vector<MinHeap::House> store = HostIDMinHeap(stoi(input));
        PrintTuples(store);
        for (int i = 0; i < store.size(); i++) {
            allTuples.push_back(store[i]);
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    } else if (menuInput == 4)//listingID
    {
        vector<MinHeap::House> allTuples;
        cout << "Enter Listing ID to search for: " << endl;
        cin >> input;
        PrintTuples(ListingIDMap(stoi(input)));
        vector<MinHeap::House> store = ListingIDMinHeap(stoi(input));
        PrintTuples(store);
        for (int i = 0; i < store.size(); i++) {
            allTuples.push_back(store[i]);
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    } else if (menuInput == 5)//city
    {
        vector<MinHeap::House> allTuples;
        cout << "Enter city to search for listings in: ";
        cin.ignore();
        getline(cin, input);
        input += string("\r");
        PrintTuples(ByCityMap(input));
        vector<MinHeap::House> store = ByCityMinHeap(input);
        PrintTuples(store);
        for (int i = 0; i < store.size(); i++) {
            allTuples.push_back(store[i]);
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    } else if (menuInput == 6)
    {
        vector<MinHeap::House> allTuples;
        cout << "Enter the first name of the owner that listed their property: ";
        cin.ignore();
        getline(cin, input);
        PrintTuples(HostNameMap(input));
        vector<MinHeap::House> store = HostNameMinHeap(input);
        PrintTuples(store);
        for (int i = 0; i < store.size(); i++) {
            allTuples.push_back(store[i]);
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    }//owner name
    else if (menuInput == 7)//region
    {
        vector<MinHeap::House> allTuples;
        string input;
        cout << "Enter the corresponding number to select what region you would like to search for listings in "
             << endl;
        cout << "[1] North" << endl;
        cout << "[2] East" << endl;
        cout << "[3] South" << endl;
        cout << "[4] West" << endl;
        cout << "[5] Northeast" << endl;
        cout << "[6] Southeast" << endl;
        cout << "[7] Southwest" << endl;
        cout << "[8] Northwest" << endl;
        cin >> input;
        PrintTuples(ByRegionMap(stoi(input)));
        vector<MinHeap::House> store = ByRegionMinHeap(stoi(input));
        PrintTuples(store);
        for (int i = 0; i < store.size(); i++) {
            allTuples.push_back(store[i]);
        }
        for (int i = 0; i < allTuples.size(); i++) {
            smallHeap.insertMinHeap(allTuples[i]);
        }
    }
}

/************Search************/
//idea for these are that they will return a vector of house objects and then print function prints them
vector<MinHeap::House> AirBnb::SearchForPriceMinHeap(int budget) {
    int counter = 0;
    string input;
    vector<MinHeap::House> listings;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 50; i++) {
        listings.push_back(smallHeap.extractMin());
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
    return listings;
}
vector<MinHeap::House> AirBnb::SearchForPriceMap(int budget) {
    string input;
    vector<MinHeap::House> listings;
    auto start = high_resolution_clock::now();
    vector<MinHeap::House> storage;
    vector<int> AddedIds;
    int min;
    for (int i = 0; i < 50; i++) {
        MinHeap::House minHouse;
        min = budget;
        for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
            if (iter->second.minPrice <= min) {
                bool alreadyAdded = false;
                for (int j = 0; j < AddedIds.size(); j++) {
                    if (iter->first == AddedIds[j]) {
                        alreadyAdded = true;
                    }
                }
                if (!alreadyAdded) {
                    minHouse = iter->second;
                    min = iter->second.minPrice;
                }
            }
        }
        if (minHouse.ID != 0) {
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    bool swapped;
    for (int i = 0; i < storage.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < storage.size() - i - 1; j++) {
            if (storage[j] > storage[j + 1]) {
                MinHeap::House temp = storage[j];
                storage[j] = storage[j + 1];
                storage[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to find the tuples using a Map: " << duration.count() << " microseconds." << endl;
    return storage;
}

vector<MinHeap::House> AirBnb::RoomOptionsMinHeap(int option) {
    bool correctInput = false;
    string input;
    vector<MinHeap::House> listings;
    int counter = 0;
    while (!correctInput) {
        if (option == 1) {
            correctInput = true;
            auto start = high_resolution_clock::now();
            while (counter < 50) {
                MinHeap::House extractedHouse = smallHeap.extractMin();
                if (extractedHouse.roomType == "Entire home/apt") {
                    listings.push_back(extractedHouse);
                    counter++;
                }
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        } else if (option == 2) {
            correctInput = true;
            auto start = high_resolution_clock::now();
            while (counter < 50) {
                MinHeap::House extractedHouse = smallHeap.extractMin();
                if (extractedHouse.roomType == "Private room") {
                    listings.push_back(extractedHouse);
                    counter++;
                }
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        } else if (option == 3) {
            correctInput = true;
            auto start = high_resolution_clock::now();
            while (counter < 50) {
                MinHeap::House extractedHouse = smallHeap.extractMin();
                if (extractedHouse.roomType == "Shared room") {
                    listings.push_back(extractedHouse);
                    counter++;
                }
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        } else {
            cout << "That is not a valid input!" << endl;
        }
    }
    return listings;
}
vector<MinHeap::House> AirBnb::RoomOptionsMap(int option) {
    bool correctInput = false;
    string input;
    vector<MinHeap::House> listings;
    vector<MinHeap::House> storage;
    vector<int> AddedIds;
    MinHeap::House minHouse;
    while (!correctInput) {
        if (option == 1) {
            auto start = high_resolution_clock::now();
            correctInput = true;
            for (int i = 0; i < 50; i++) {
                int min = INT_MAX;
                for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                    if (iter->second.minPrice <= min) {
                        bool alreadyAdded = false;
                        for (int j = 0; j < AddedIds.size(); j++) {
                            if (iter->first == AddedIds[j]) {
                                alreadyAdded = true;
                            }
                        }
                        if (!alreadyAdded && iter->second.roomType == "Entire home/apt") {
                            minHouse = iter->second;
                            min = minHouse.minPrice;
                        }
                    }
                }
                storage.push_back(minHouse);
                AddedIds.push_back(minHouse.ID);
            }
            bool swapped;
            for (int i = 0; i < storage.size() - 1; i++) {
                swapped = false;
                for (int j = 0; j < storage.size() - i - 1; j++) {
                    if (storage[j] > storage[j + 1]) {
                        MinHeap::House temp = storage[j];
                        storage[j] = storage[j + 1];
                        storage[j + 1] = temp;
                        swapped = true;
                    }
                }
                if (!swapped) {
                    break;
                }
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
        } else if (option == 2) {
            auto start = high_resolution_clock::now();
            correctInput = true;
            for (int i = 0; i < 50; i++) {
                int min = INT_MAX;
                for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                    if (iter->second.minPrice <= min) {
                        bool alreadyAdded = false;
                        for (int j = 0; j < AddedIds.size(); j++) {
                            if (iter->first == AddedIds[j]) {
                                alreadyAdded = true;
                            }
                        }
                        if (!alreadyAdded && iter->second.roomType == "Private room") {
                            minHouse = iter->second;
                            min = minHouse.minPrice;
                        }
                    }
                }
                storage.push_back(minHouse);
                AddedIds.push_back(minHouse.ID);
            }
            bool swapped;
            for (int i = 0; i < storage.size() - 1; i++) {
                swapped = false;
                for (int j = 0; j < storage.size() - i - 1; j++) {
                    if (storage[j] > storage[j + 1]) {
                        MinHeap::House temp = storage[j];
                        storage[j] = storage[j + 1];
                        storage[j + 1] = temp;
                        swapped = true;
                    }
                }
                if (!swapped) {
                    break;
                }
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
        } else if (option == 3) {
            auto start = high_resolution_clock::now();
            correctInput = true;
            for (int i = 0; i < 50; i++) {
                int min = INT_MAX;
                for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                    if (iter->second.minPrice <= min) {
                        bool alreadyAdded = false;
                        for (int j = 0; j < AddedIds.size(); j++) {
                            if (iter->first == AddedIds[j]) {
                                alreadyAdded = true;
                            }
                        }
                        if (!alreadyAdded && iter->second.roomType == "Shared room") {
                            minHouse = iter->second;
                            min = minHouse.minPrice;
                        }
                    }
                }
                storage.push_back(minHouse);
                AddedIds.push_back(minHouse.ID);
            }
            bool swapped;
            for (int i = 0; i < storage.size() - 1; i++) {
                swapped = false;
                for (int j = 0; j < storage.size() - i - 1; j++) {
                    if (storage[j] > storage[j + 1]) {
                        MinHeap::House temp = storage[j];
                        storage[j] = storage[j + 1];
                        storage[j + 1] = temp;
                        swapped = true;
                    }
                }
                if (!swapped) {
                    break;
                }
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
        } else {
            cout << "That is not a valid input!" << endl;
        }
    }
    return storage;
}

vector<MinHeap::House> AirBnb::HostIDMap(int hostID) {
    bool found = false;
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
        if (iter->second.hostID == hostID) {
            found = true;
            storage.push_back(iter->second);
        }
    }
    if (!found) {
        cout << "No host with that ID was found." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
    }
    return storage;
}
vector<MinHeap::House> AirBnb::HostIDMinHeap(int hostID) {
    bool found = false;
    vector<MinHeap::House> storage;
    vector<MinHeap::House> garbage;
    auto start = high_resolution_clock::now();
    int size = smallHeap.heapsize;
    for (int i = 0; i < size; i++) {
        MinHeap::House temp = smallHeap.extractMin();
        if (temp.hostID == hostID) {
            found = true;
            storage.push_back(temp);
        }
        else
        {
            garbage.push_back(temp);
        }
    }
    if (!found) {
        cout << "No host with that ID was found." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a Minheap: " << duration.count() << " microseconds." << endl;
    }
    for(int i = 1; i < garbage.size(); i++)
    {
        smallHeap.insertMinHeap(garbage[i]);
    }
    return storage;
}

vector<MinHeap::House> AirBnb::ListingIDMap(int listingID) {
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    storage.push_back(AirBnbListings[listingID]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to find the tuples using a Map: " << duration.count() << " microseconds." << endl;
    return storage;
}
vector<MinHeap::House> AirBnb::ListingIDMinHeap(int listingID) {
    bool found = false;
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    int size = smallHeap.heapsize;
    vector<MinHeap::House> garbage;
    for (int i = 0; i < size; i++) {
        MinHeap::House temp = smallHeap.extractMin();
        if (temp.ID == listingID) {
            found = true;
            storage.push_back(temp);
        } else {
            garbage.push_back(temp);
        }
    }
    if (!found) {
        cout << "No host with that ID was found." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
    }
    for (int i = 0; i < garbage.size(); i++) {
        smallHeap.insertMinHeap(garbage[i]);
    }
    return storage;
}

vector<MinHeap::House> AirBnb::ByCityMap(string city) {
    string input;
    vector<MinHeap::House> storage;
    vector<int> AddedIds;
    MinHeap::House minHouse;
    bool found = false;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 50; i++) {
        int min = INT_MAX;
        for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
            if(iter->second.minPrice <= min)
            {
                bool alreadyAdded =false;
                for(int j = 0; j < AddedIds.size(); j++)
                {
                    if(iter->first == AddedIds[j])
                    {
                        alreadyAdded = true;
                    }
                }
                if(!alreadyAdded && iter->second.city == city)
                {
                    found = true;
                    minHouse = iter->second;
                    min = minHouse.minPrice;
                }
            }
        }
        storage.push_back(minHouse);
        AddedIds.push_back(minHouse.ID);
    }
    if (!found) {
        cout << "No listing in that city was found." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
    }
    return storage;
}
vector<MinHeap::House> AirBnb::ByCityMinHeap(string city) {
    bool found = false;
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    int size = smallHeap.heapsize;
    vector<MinHeap::House> garbage;
    int counter = 0;
    while(counter < 50)
    {
        MinHeap::House extractedHouse = smallHeap.extractMin();
        if (extractedHouse.city == city) {
            storage.push_back(extractedHouse);
            counter++;
            found = true;
    }
        else
        {
            garbage.push_back(extractedHouse);
        }}
    if (!found) {
        cout << "No listing in that city was found." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
    }
    for (int i = 0; i < garbage.size(); i++) {
        smallHeap.insertMinHeap(garbage[i]);
    }
    return storage;
}

vector<MinHeap::House> AirBnb::HostNameMap(string name) {
    bool found = false;
    vector<MinHeap::House> storage;
    vector<int> AddedIds;
    MinHeap::House minHouse;
    auto start = high_resolution_clock::now();
    for(int i = 0; i < 50; i++) {
        int min = INT_MAX;
        for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
            if (iter->second.minPrice <= min) {
                bool alreadyAdded = false;
                for (int j = 0; j < AddedIds.size(); j++) {
                    if (iter->first == AddedIds[j]) {
                        alreadyAdded = true;
                    }
                }
                if (!alreadyAdded && iter->second.hostName == name) {
                    found = true;
                    minHouse = iter->second;
                    min = minHouse.minPrice;
                }
            }
        }
        storage.push_back(minHouse);
        AddedIds.push_back(minHouse.ID);
    }
    if (!found) {
        cout << "No hosts with that name have posted a listing." << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a map: " << duration.count() << " microseconds." << endl;
    }
    return storage;
}
vector<MinHeap::House> AirBnb::HostNameMinHeap(string name) {
    bool found = false;
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    int size = smallHeap.heapsize;
    vector<MinHeap::House> garbage;
    int counter = 0;
    while(counter < 50)
    {
        MinHeap::House extractedHouse = smallHeap.extractMin();
        if (extractedHouse.hostName == name) {
            storage.push_back(extractedHouse);
            counter++;
            found = true;
        }
        else
        {
            garbage.push_back(extractedHouse);
        }}
    if (!found) {
        cout << "No owner with that name has posted a listing" << endl;
    } else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
    }
    for (int i = 0; i < garbage.size(); i++) {
        smallHeap.insertMinHeap(garbage[i]);
    }
    return storage;
}

//number will be 1-8 and each coordinates to cardinal direction
vector<MinHeap::House> AirBnb::ByRegionMap(int choice) {
    bool found = false;
    vector<MinHeap::House> storage;
    vector<int> AddedIds;
    auto start = high_resolution_clock::now();
    if (choice == 1){
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min && North(iter->second)) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 2) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 3) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && !North(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 4) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && !East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 5) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && North(iter->second) && East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 6) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && !North(iter->second) && East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 7) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && !North(iter->second) && !East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    else if (choice == 8) {
        MinHeap::House minHouse;
        for(int i = 0; i < 50; i++)
        {
            int min = INT_MAX;
            for (auto iter = AirBnbListings.begin(); iter != AirBnbListings.end(); ++iter) {
                if (iter->second.minPrice <= min) {
                    bool alreadyAdded = false;
                    for (int j = 0; j < AddedIds.size(); j++) {
                        if (iter->first == AddedIds[j]) {
                            alreadyAdded = true;
                        }
                    }
                    if (!alreadyAdded && North(iter->second) && !East(iter->second)) {
                        found = true;
                        minHouse = iter->second;
                        min = minHouse.minPrice;
                    }
                }
            }
            storage.push_back(minHouse);
            AddedIds.push_back(minHouse.ID);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to find the tuples using a Map: " << duration.count() << " microseconds." << endl;
    return storage;
}
vector<MinHeap::House> AirBnb::ByRegionMinHeap(int choice) {
    bool found = false;
    vector<MinHeap::House> storage;
    auto start = high_resolution_clock::now();
    int size = smallHeap.heapsize;
    vector<MinHeap::House> garbage;
    int counter = 0;
    if (choice == 1) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (North(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 2) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (East(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 3) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (!North(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 4) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (!East(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 5) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (North(extractedHouse) && East(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 6) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (!North(extractedHouse) && East(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 7) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (!North(extractedHouse) && !East(extractedHouse) ) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    else if (choice == 8) {
        while(counter < 50)
        {
            MinHeap::House extractedHouse = smallHeap.extractMin();
            if (North(extractedHouse) && !East(extractedHouse)) {
                storage.push_back(extractedHouse);
                counter++;
                found = true;
            }
            else
            {
                garbage.push_back(extractedHouse);
            }}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to find the tuples using a MinHeap: " << duration.count() << " microseconds." << endl;
        for (int i = 0; i < garbage.size(); i++) {
            smallHeap.insertMinHeap(garbage[i]);
        }
    }
    return storage;
}

/************Directional************/
bool AirBnb::North(const MinHeap::House &house) {
    bool north = false;
    if (house.latitude > 38)
        north = true;
    return north;
}

bool AirBnb::East(const MinHeap::House &house) {
    bool east = false;
    if (house.longitude > -98)
        east = true;
    return east;
}