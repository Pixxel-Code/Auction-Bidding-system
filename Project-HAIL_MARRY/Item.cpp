#include "Item.h"

Item::Item() {
    id = 0;
    title = "";
    basePrice = 0;
    currentPrice = 0;
    sellerId = 0;
    duration = 0;
    startTime = 0;
    category = "";
    isActive = false;
}
Item::Item(int id, string title, double base, int seller,string category) {
    this->id = id;
    this->title = title;
    this->basePrice = base;
    this->currentPrice = base;
    this->sellerId = seller;
    this->category = category;

    duration = 60; // default 60 sec (change later)
    startTime = time(0);
    isActive = true;
}
void Item::updatePrice(double newPrice) {
    currentPrice = newPrice;
}
bool Item::isExpired() {
    time_t now = time(0);
    return difftime(now, startTime) >= duration;
}
double Item::getCurrentPrice() { return currentPrice; }
int Item::getId() { return id; }
string Item::getTitle() { return title; }
double Item::getBasePrice() { return basePrice; }
int Item::getSellerId() { return sellerId; }
string Item::getCategory() { return category ; }
void Item::setCategory(string cat) { category = cat; }