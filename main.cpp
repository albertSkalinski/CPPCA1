#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <algorithm>
#include <unordered_set>

#include "shippingDataStruct.h"

//WRITING TO THE FILE FUNCTIONS
int chooseFile(list<ShippingData>&);
void structureShippingData(const ShippingData&);
void loadShippingData(string, list<ShippingData>&);

//MENU FUNCTIONS
int displayMainMenu(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
int displayListMenu(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
int displayListMenuOption1(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
int displayListMenuOption2(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

int displayVectorMenu(list<ShippingData>& , vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
int displayVectorMenuOption2(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
int displayVectorMenuOption4(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

int displaySetMenu(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

int displayMapMenu(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

//FUNCTIONALITY FUNCTIONS
void displayListAll(list<ShippingData>&);
void displayListFirst(list<ShippingData>&);
void displayListLast(list<ShippingData>&);
void displayListByID(list<ShippingData>&);
void deleteListFirst(list<ShippingData>&);
void deleteListLast(list<ShippingData>&);
void deleteListNth(list<ShippingData>&);
void insertListElement(list<ShippingData>&);
void countRatings(list<ShippingData>&);
void sortListByRatings(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

void populateVector(list<ShippingData>&, vector<ShippingData>&);
void displayVectorAll(vector<ShippingData>&);
void displayVectorNth(vector<ShippingData>&);
void displayVectorByRating(vector<ShippingData>&);
void insertVectorElement(vector<ShippingData>&);
void sortVectorByProductCost(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);
void sortVectorByID(list<ShippingData>&, vector<ShippingData>&, unordered_set<string>&, unordered_map<int, ShippingData>&);

void validateProductImportance(list<ShippingData>&, unordered_set<string>&);

void populateMap(list<ShippingData>&, unordered_map<int, ShippingData>&);
void displayMapByID(unordered_map<int, ShippingData>&);

using namespace std;

//MAIN
int main()
{
    list<ShippingData> shippingDataList;
    vector<ShippingData> shippingDataVector;
    unordered_set<string> shippingDataSet;
    unordered_map<int, ShippingData> shippingDataMap;

    chooseFile(shippingDataList);
    displayMainMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);

    return 0;
}

//READING FROM THE FILE
int chooseFile(list<ShippingData>& shippingDataList)
{
    int fileChoice;
    cout << "\n1. Load the small file" << endl;
    cout << "2. Load the large file" << endl;
    cout << "3. Exit" << endl;

    cout << "\nEnter your choice: ";
    cin >> fileChoice;

    if (fileChoice == 1)
    {
        loadShippingData("shipping-data-small.csv", shippingDataList);
    }
    else if (fileChoice == 2)
    {
        loadShippingData("shipping-data-large.csv", shippingDataList);
    }
    else if (fileChoice == 3)
    {
        cout << "\nGoodbye!" << endl;
        exit(0);
    }
    else
    {
        cout << "\nInvalid choice." << endl;
        exit(0);
    }
    return fileChoice;
}

void structureShippingData(const ShippingData &shippingData)
{
    cout <<left
         <<setw(5) << shippingData.ID
         <<setw(5) << shippingData.warehouseBlock
         <<setw(15) << shippingData.shipmentMode
         <<setw(5) << shippingData.customerCareCalls
         <<setw(5) << shippingData.customerRating
         <<setw(7) << shippingData.productCost
         <<setw(5) << shippingData.priorPurchases
         <<setw(15) << shippingData.productImportance
         <<setw(5) << shippingData.gender
         <<setw(7) << shippingData.discountOffered
         <<setw(8) << shippingData.weightInGrams
         <<setw(5) << shippingData.reachedOnTime
         <<endl;
}

void parseLine(string line, ShippingData &shippingData)
{
    string temp;
    stringstream stringStream(line);

    getline(stringStream, temp, ',');
    shippingData.ID = stoi(temp);
    getline(stringStream, shippingData.warehouseBlock, ',');
    getline(stringStream, shippingData.shipmentMode, ',');
    getline(stringStream, temp, ',');
    shippingData.customerCareCalls = stoi(temp);
    getline(stringStream, temp, ',');
    shippingData.customerRating = stoi(temp);
    getline(stringStream, temp, ',');
    shippingData.productCost = stoi(temp);
    getline(stringStream, temp, ',');
    shippingData.priorPurchases = stoi(temp);
    getline(stringStream, shippingData.productImportance, ',');
    getline(stringStream, shippingData.gender, ',');
    getline(stringStream, temp, ',');
    shippingData.discountOffered = stoi(temp);
    getline(stringStream, temp, ',');
    shippingData.weightInGrams = stoi(temp);
    getline(stringStream, temp, ',');
    shippingData.reachedOnTime = stoi(temp);
}

void loadShippingData(string fileName, list<ShippingData> &shippingDataList)
{
    ifstream ifs(fileName);

    if(ifs)
    {
        string line;
        getline(ifs, line);
        while(getline(ifs, line))
        {
            ShippingData tempShippingData;
            parseLine(line, tempShippingData);
            shippingDataList.push_back(tempShippingData);
        }
        ifs.close();
    }
    else
    {
        cout << "\nError opening file." <<endl;
    }
}

//MENUS (1.)
int displayMainMenu(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string>& shippingDataSet, unordered_map<int, ShippingData>& shippingDataMap)
{
    int choice;
    cout << "\nWelcome to the shipping data app!" << endl;
    cout << "1. List" << endl;
    cout << "2. Vector" << endl;
    cout << "3. Set" << endl;
    cout << "4. Map" << endl;
    cout << "5. Exit" << endl;

    while (choice != 5)
    {
        cout << "\nEnter the number corresponding to the collection you would like to use: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayListMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 2:
                displayVectorMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 3:
                displaySetMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 4:
                displayMapMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 5:
                cout << "\nExiting, see you again!" << endl;
                exit(0);

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
        return choice;
    }
}

int displayListMenu(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    int choice;
    cout << "\n1. Display..." << endl;
    cout << "2. Delete..." << endl;
    cout << "3. Insert an element" << endl;
    cout << "4. Count customer ratings that are less than 2" << endl;
    cout << "5. Sort the list in order of customer ratings" << endl;
    cout << "6. Back" << endl;

    while (choice != 6)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayListMenuOption1(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 2:
                displayListMenuOption2(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 3:
                insertListElement(shippingDataList);
                break;

            case 4:
                countRatings(shippingDataList);
                break;

            case 5:
                sortListByRatings(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 6:
                cout << "\nGoing back to the main menu" << endl;
                displayMainMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayListMenuOption1(list<ShippingData> &shippingDataList, vector<ShippingData> &shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    int choice;
    cout << "\n1. ...all elements" << endl;
    cout << "2. ...first element" << endl;
    cout << "3. ...last element" << endl;
    cout << "4. ...element by its ID" << endl;
    cout << "5. Back" << endl;

    while (choice != 5)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayListAll(shippingDataList);
                break;

            case 2:
                displayListFirst(shippingDataList);
                break;

            case 3:
                displayListLast(shippingDataList);
                break;

            case 4:
                displayListByID(shippingDataList);
                break;

            case 5:
                cout << "\nGoing back" << endl;
                displayListMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayListMenuOption2(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    int choice;
    cout << "\n1. ...first element" << endl;
    cout << "2. ...last element" << endl;
    cout << "3. ...nth element" << endl;
    cout << "4. Back" << endl;

    while (choice != 4)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                deleteListFirst(shippingDataList);
                break;

            case 2:
                deleteListLast(shippingDataList);
                break;

            case 3:
                deleteListNth(shippingDataList);
                break;

            case 4:
                cout << "\nGoing back" << endl;
                displayListMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayVectorMenu(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)

{
    int choice;
    cout << "\n1. Populate a vector from the list" << endl;
    cout << "2. Display..." << endl;
    cout << "3. Insert an element at position 2" << endl;
    cout << "4. Sort..." << endl;
    cout << "5. Back" << endl;

    while (choice != 5)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                populateVector(shippingDataList, shippingDataVector);
                break;

            case 2:
                displayVectorMenuOption2(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 3:
                insertVectorElement(shippingDataVector);
                break;

            case 4:
                displayVectorMenuOption4(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 5:
                cout << "\nGoing back to the main menu" << endl;
                displayMainMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayVectorMenuOption2(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    int choice;
    cout << "\n1. ...all elements" << endl;
    cout << "2. ...nth element" << endl;
    cout << "3. ...records with the customer rating that is less than 3" << endl;
    cout << "4. Back" << endl;

    while (choice != 4)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayVectorAll(shippingDataVector);
                break;

            case 2:
                displayVectorNth(shippingDataVector);
                break;

            case 3:
                displayVectorByRating(shippingDataVector);
                break;

            case 4:
                cout << "\nGoing back" << endl;
                displayVectorMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayVectorMenuOption4(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    int choice;
    cout << "\n1. ...in order of product cost" << endl;
    cout << "2. ...in order of ID" << endl;
    cout << "3. Back" << endl;

    while (choice != 3)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                sortVectorByProductCost(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 2:
                sortVectorByID(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            case 3:
                cout << "\nGoing back" << endl;
                displayVectorMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displaySetMenu(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string>& shippingDataSet, unordered_map<int, ShippingData>& shippingDataMap)
{
    int choice;
    cout << "\n1. Validate product importance of entries" << endl;
    cout << "2. Back" << endl;

    while (choice != 2)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                validateProductImportance(shippingDataList, shippingDataSet);
                break;

            case 2:
                cout << "\nGoing back to the main menu" << endl;
                displayMainMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

int displayMapMenu(list<ShippingData>& shippingDataList, vector<ShippingData>& shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData>& shippingDataMap)
{
    int choice;
    cout << "\n1. Populate a map from the list" << endl;
    cout << "2. Display a record using its ID" << endl;
    cout << "3. Back" << endl;

    while (choice != 3)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                populateMap(shippingDataList, shippingDataMap);
                break;

            case 2:
                displayMapByID(shippingDataMap);
                break;

            case 3:
                cout << "\nGoing back to the main menu" << endl;
                displayMainMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
                break;

            default:
                cout << "\nInvalid choice, try again." << endl;
                break;
        }
    }
    return choice;
}

//FEATURES
//2. a.
void displayListAll(list<ShippingData> &shippingDataList)
{
    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        structureShippingData(*iterator);
    }
}

//2. b.
void displayListFirst(list<ShippingData> &shippingDataList)
{
    structureShippingData(shippingDataList.front());
}

//2. c.
void displayListLast(list<ShippingData> &shippingDataList)
{
    structureShippingData(shippingDataList.back());
}

//2. d.
void displayListByID(list<ShippingData> &shippingDataList)
{
    int id;
    cout << "\nEnter the ID of the element you would like to display: ";
    cin >> id;

    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        //Arrow operator is used to access the members of the object pointed to by the iterator
        if(iterator->ID == id)
        {
            structureShippingData(*iterator);
        }
    }
}

//2. e.
void deleteListFirst(list<ShippingData> &shippingDataList)
{
    shippingDataList.pop_front();
    cout << "\nFirst element deleted." << endl;
}

//2. f.
void deleteListLast(list<ShippingData> &shippingDataList)
{
    shippingDataList.pop_back();
    cout << "\nLast element deleted." << endl;
}

//2. g.
void deleteListNth(list<ShippingData> &shippingDataList)
{
    int id;
    cout << "\nEnter the ID of the element you would like to delete: ";
    cin >> id;

    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        //Arrow operator is used to access the members of the object pointed to by the iterator
        if(iterator->ID == id)
        {
            shippingDataList.erase(iterator);
            cout << "\nElement deleted." << endl;
        }
    }
}

//2. h.
void insertListElement(list<ShippingData> &shippingDataList)
{
    int n;
    cout << "\nEnter the position you would like to insert the element(integer): ";
    cin >> n;

    ShippingData userShippingData;
    cout << "\nEnter the ID: ";
    cin >> userShippingData.ID;
    cout << "Enter the warehouse block: ";
    cin >> userShippingData.warehouseBlock;
    cout << "Enter the shipment mode: ";
    cin >> userShippingData.shipmentMode;
    cout << "Enter the number of customer care calls: ";
    cin >> userShippingData.customerCareCalls;
    cout << "Enter the customer rating: ";
    cin >> userShippingData.customerRating;
    cout << "Enter the product cost: ";
    cin >> userShippingData.productCost;
    cout << "Enter the number of prior purchases: ";
    cin >> userShippingData.priorPurchases;
    cout << "Enter the product importance: ";
    cin >> userShippingData.productImportance;
    cout << "Enter the gender: ";
    cin >> userShippingData.gender;
    cout << "Enter the discount offered: ";
    cin >> userShippingData.discountOffered;
    cout << "Enter the weight (in grams): ";
    cin >> userShippingData.weightInGrams;
    cout << "Enter 1 if it reached on time, enter 0 if it didn't: ";
    cin >> userShippingData.reachedOnTime;

    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        //Arrow operator is used to access the members of the object pointed to by the iterator
        if(iterator->ID == n)
        {
            shippingDataList.insert(iterator, userShippingData);
            cout << "\nElement inserted." << endl;
        }
    }
}

//2. i.
bool isLessThanTwo(ShippingData &shippingData)
{
    if (shippingData.customerRating < 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void countRatings(list<ShippingData> &shippingDataList)
{
    int count = count_if(shippingDataList.begin(), shippingDataList.end(), isLessThanTwo);
    cout << "\nNumber of ratings less than 2: " << count << endl;
}

//2. j.
void sortListByRatings(list<ShippingData> &shippingDataList, vector<ShippingData> &shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    cout << "\n1. Ascending ratings" << endl;
    cout << "2. Descending ratings" << endl;
    cout << "3. Go back" << endl;

    int sortingChoice;
    cout << "\nEnter the way you want to sort the list: ";
    cin >> sortingChoice;

    switch (sortingChoice)
    {
        case 1:
            shippingDataList.sort([](ShippingData &shippingData1, ShippingData &shippingData2)
            {
                return shippingData1.customerRating < shippingData2.customerRating;
            });
            cout << "\nAscending order applied." << endl;
            break;

        case 2:
            shippingDataList.sort([](ShippingData &shippingData1, ShippingData &shippingData2)
            {
                return shippingData1.customerRating > shippingData2.customerRating;
            });
            cout << "\nDescending order applied." << endl;
            break;

        case 3:
            cout << "\nGoing back" << endl;
            displayListMenu(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
            break;

        default:
            cout << "\nInvalid choice, try again." << endl;
            break;
    }
    displayListAll(shippingDataList);
}

//3. a.
void populateVector(list<ShippingData> &shippingDataList, vector<ShippingData> &shippingDataVector)
{
    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        shippingDataVector.push_back(*iterator);
    }
    cout << "\nVector populated." << endl;
}

//3. b.
void displayVectorAll(vector<ShippingData> &shippingDataVector)
{
    for(auto iterator = shippingDataVector.begin(); iterator != shippingDataVector.end(); iterator++)
    {
        structureShippingData(*iterator);
    }
}

//3. c.
void displayVectorNth(vector<ShippingData> &shippingDataVector)
{
    int index;
    cout << "\nEnter the index of the element you would like to display: ";
    cin >> index;

    structureShippingData(shippingDataVector[index]);
}

//3. g.
bool isLessThanThree(ShippingData &shippingData)
{
    if (shippingData.customerRating < 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void displayVectorByRating(vector<ShippingData> &shippingDataVector)
{
    vector<ShippingData> shippingDataVector2;
    copy_if(shippingDataVector.begin(), shippingDataVector.end(), back_inserter(shippingDataVector2), isLessThanThree);

    for(auto iterator = shippingDataVector2.begin(); iterator != shippingDataVector2.end(); iterator++)
    {
        structureShippingData(*iterator);
    }
}

//3. d.
void insertVectorElement(vector<ShippingData> &shippingDataVector)
{
    ShippingData userShippingData;
    cout << "\nEnter the ID: ";
    cin >> userShippingData.ID;
    cout << "Enter the warehouse block: ";
    cin >> userShippingData.warehouseBlock;
    cout << "Enter the shipment mode: ";
    cin >> userShippingData.shipmentMode;
    cout << "Enter the number of customer care calls: ";
    cin >> userShippingData.customerCareCalls;
    cout << "Enter the customer rating: ";
    cin >> userShippingData.customerRating;
    cout << "Enter the product cost: ";
    cin >> userShippingData.productCost;
    cout << "Enter the number of prior purchases: ";
    cin >> userShippingData.priorPurchases;
    cout << "Enter the product importance: ";
    cin >> userShippingData.productImportance;
    cout << "Enter the gender: ";
    cin >> userShippingData.gender;
    cout << "Enter the discount offered: ";
    cin >> userShippingData.discountOffered;
    cout << "Enter the weight (in grams): ";
    cin >> userShippingData.weightInGrams;
    cout << "Enter 1 if it reached on time, enter 0 if it didn't: ";
    cin >> userShippingData.reachedOnTime;

    shippingDataVector.insert(shippingDataVector.begin() + 2, userShippingData);
    cout << "\nElement inserted." << endl;
}

//3. e.
void sortVectorByProductCost(list<ShippingData> &shippingDataList, vector<ShippingData> &shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    cout << "\n1. Ascending product cost" << endl;
    cout << "2. Descending product cost" << endl;
    cout << "3. Go back" << endl;

    int sortingChoice;
    cout << "\nEnter the way you want to sort the list: ";
    cin >> sortingChoice;

    switch (sortingChoice)
    {
        case 1:
            //Sort the vector in ascending order by product cost
            sort(shippingDataVector.begin(), shippingDataVector.end(), [](ShippingData &shippingData1, ShippingData &shippingData2)
                 {
                     return shippingData1.productCost < shippingData2.productCost;
                 });
            cout << "\nAscending order applied." << endl;
            break;

        case 2:
            sort(shippingDataVector.begin(), shippingDataVector.end(), [](ShippingData &shippingData1, ShippingData &shippingData2)
            {
                return shippingData1.productCost > shippingData2.productCost;
            });
            cout << "\nDescending order applied." << endl;
            break;

        case 3:
            cout << "\nGoing back" << endl;
            displayVectorMenuOption4(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
            break;

        default:
            cout << "\nInvalid choice, try again." << endl;
            break;
    }
    displayVectorAll(shippingDataVector);
}

void sortVectorByID(list<ShippingData> &shippingDataList, vector<ShippingData> &shippingDataVector, unordered_set<string> &shippingDataSet, unordered_map<int, ShippingData> &shippingDataMap)
{
    cout << "\n1. Ascending ID" << endl;
    cout << "2. Descending ID" << endl;
    cout << "3. Go back" << endl;

    int sortingChoice;
    cout << "\nEnter the way you want to sort the list: ";
    cin >> sortingChoice;

    switch (sortingChoice)
    {
        case 1:
            //Sort the vector in ascending order by product cost
            sort(shippingDataVector.begin(), shippingDataVector.end(), [](ShippingData &shippingData1, ShippingData &shippingData2)
            {
                return shippingData1.ID < shippingData2.ID;
            });
            cout << "\nAscending order applied." << endl;
            break;

        case 2:
            sort(shippingDataVector.begin(), shippingDataVector.end(), [](ShippingData &shippingData1, ShippingData &shippingData2)
            {
                return shippingData1.ID > shippingData2.ID;
            });
            cout << "\nDescending order applied." << endl;
            break;

        case 3:
            cout << "\nGoing back" << endl;
            displayVectorMenuOption4(shippingDataList, shippingDataVector, shippingDataSet, shippingDataMap);
            break;

        default:
            cout << "\nInvalid choice, try again." << endl;
            break;
    }
    displayVectorAll(shippingDataVector);
}

//4. a.
void validateProductImportance(list<ShippingData> &shippingDataList, unordered_set<string> &shippingDataSet)
{
    shippingDataSet.insert("low");
    shippingDataSet.insert("medium");
    shippingDataSet.insert("high");

    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        if (shippingDataSet.find(iterator->productImportance) == shippingDataSet.end())
        {
            cout << "\nFound invalid product importance " << endl;
            cout << "ID: " << iterator->ID << endl;
            cout << "Product importance: " << iterator->productImportance << endl;
        }
    }
}

//5.a.
void populateMap(list<ShippingData> &shippingDataList, unordered_map<int, ShippingData> &shippingDataMap)
{
    for(auto iterator = shippingDataList.begin(); iterator != shippingDataList.end(); iterator++)
    {
        shippingDataMap.insert({iterator->ID, *iterator});
    }
    cout << "\nMap populated." << endl;
}

//5.b.
void displayMapByID(unordered_map<int, ShippingData> &shippingDataMap)
{
    int ID;
    cout << "\nEnter the ID: ";
    cin >> ID;

    if (shippingDataMap.find(ID) != shippingDataMap.end())
    {
        structureShippingData(shippingDataMap[ID]);
    }
    else
    {
        cout << "\nID not found." << endl;
    }
}