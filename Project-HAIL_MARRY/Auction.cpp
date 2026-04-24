#include "Auction.h"
#include "DBManager.h"
#include<iostream>

Bid* Auction::getAllBids(int& count) {
    return DBManager::getInstance().getBidsForItem(item.getId(), count);
}
Auction::Auction(Item item) {
    this->item = item;
    bids = nullptr;
    bidCount = 0;
    isActive = true;
}
Item Auction::getItem() {
    return item;
}

Auction::~Auction() {
    delete[] bids;
}
bool Auction::placeBid(Bid bid) {

    if (!isActive || item.isExpired()) {
        cout << "Auction closed or expired\n";
        return false;
    }

    if (bid.getAmount() <= item.getCurrentPrice()) {
        cout << "Bid too low\n";
        return false;
    }

    Bid* temp = new Bid[bidCount + 1];

    for (int i = 0; i < bidCount; i++)
        temp[i] = bids[i];

    temp[bidCount] = bid;

    delete[] bids;
    bids = temp;

    bidCount++;

    item.updatePrice(bid.getAmount());

    DBManager::getInstance().addBid(bid);

    cout << "Bid accepted: " << bid.getAmount() << endl;

    return true;
}
Bid Auction::getHighestBid() {

    if (bidCount == 0)
        return Bid();

    Bid highest = bids[0];

    for (int i = 1; i < bidCount; i++) {
        if (bids[i].getAmount() > highest.getAmount())
            highest = bids[i];
    }

    return highest;
}
void Auction::closeAuction() {

    if (!isActive) return;

    isActive = false;

    Bid winner = getHighestBid();

    if (winner.getAmount() > 0) {
        cout << "Winner User ID: " << winner.getUserId() << endl;
    }
    else {
        cout << "No bids placed.\n";
    }
}
void Auction::checkAndClose() {
    if (item.isExpired() && isActive) {
        closeAuction();
    }
}