#ifndef CA1_SHIPPINGDATASTRUCT_H
#define CA1_SHIPPINGDATASTRUCT_H

#include <string>

using namespace std;

struct ShippingData
{
    int ID;
    string warehouseBlock;
    string shipmentMode;
    int customerCareCalls;
    int customerRating;
    int productCost;
    int priorPurchases;
    string productImportance;
    string gender;
    int discountOffered;
    int weightInGrams;
    int reachedOnTime;
};

#endif //CA1_SHIPPINGDATASTRUCT_H
