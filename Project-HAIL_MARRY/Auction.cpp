#include "Auction.h"
#include <iostream>

using namespace std;

Auction::Auction(Item item) {
    this->item = item;
    isActive = true;
}

Item Auction::getItem() {
    return item;
}

bool Auction::isActiveAuction() {
    return isActive;
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

    // update item price
    item.updatePrice(bid.getAmount());

    // store ONLY in DB (single source of truth)
    DBManager::getInstance().addBid(bid);

    cout << "Bid accepted: " << bid.getAmount() << endl;

    return true;
}
Bid Auction::getHighestBid() {

    int count = 0;
    Bid* bids = DBManager::getInstance().getBidsForItem(item.getId(), count);

    if (count == 0)
        return Bid();

    Bid highest = bids[0];

    for (int i = 1; i < count; i++) {
        if (bids[i].getAmount() > highest.getAmount())
            highest = bids[i];
    }

    delete[] bids;

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