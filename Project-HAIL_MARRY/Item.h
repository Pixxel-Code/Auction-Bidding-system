#pragma once
#include <string>
#include <ctime>
using namespace std;

class Item {
private:
    int id;
    string title;
    double basePrice;
    double currentPrice;
    int sellerId;

    int duration;
    time_t startTime;
    bool isActive;

public:
    Item();
    Item(int id, string t, double b, int seller);

    void updatePrice(double newPrice);
    double getCurrentPrice();
    int getId();

    bool isExpired();
};