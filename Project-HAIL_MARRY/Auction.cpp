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

    Bid previousHighest = getHighestBid();

    // NOTIFY outbid user
    if (previousHighest.getAmount() > 0 && previousHighest.getUserId() != bid.getUserId()) {
        string msg = "You have been outbid on: " + item.getTitle();
        DBManager::getInstance().addNotification(Notification(previousHighest.getUserId(), msg));
    }

    item.updatePrice(bid.getAmount());
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
        cout << "Winner User ID: " << winner.getUserId()
            << " with bid $" << winner.getAmount() << endl;

        // Notify winner
        string winMsg = "Congratulations! You won the auction for: "
            + item.getTitle()
            + " at $" + to_string((int)winner.getAmount());
        DBManager::getInstance().addNotification(Notification(winner.getUserId(), winMsg));

        // Notify seller
        string sellMsg = "Your item \"" + item.getTitle()
            + "\" was sold for $" + to_string((int)winner.getAmount());
        DBManager::getInstance().addNotification(Notification(item.getSellerId(), sellMsg));

        // Rate buyer and seller
        DBManager& db = DBManager::getInstance();
        int count = 0;
        User* allUsers = db.getAllUsers(count);

        for (int i = 0; i < count; i++) {
            if (allUsers[i].getId() == winner.getUserId() ||
                allUsers[i].getId() == item.getSellerId()) {
                allUsers[i].addRating(4.0);
                db.updateUser(allUsers[i]);
            }
        }

    }
    else {
        cout << "Auction closed with no bids: " << item.getTitle() << endl;
        string noSaleMsg = "Your auction for \"" + item.getTitle() + "\" ended with no bids.";
        DBManager::getInstance().addNotification(Notification(item.getSellerId(), noSaleMsg));
    }
}
void Auction::checkAndClose() {

    if (item.isExpired() && isActive) {
        closeAuction();
    }
}