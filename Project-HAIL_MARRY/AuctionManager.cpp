#include "AuctionManager.h"
#include <iostream>

AuctionManager& AuctionManager::getInstance() {
    static AuctionManager instance;
    return instance;
}

AuctionManager::AuctionManager() {
    auctions = nullptr;
    count = 0;
}
void AuctionManager::addAuction(Auction* auction) {

    Auction** temp = new Auction * [count + 1];

    for (int i = 0; i < count; i++)
        temp[i] = auctions[i];

    temp[count] = auction;

    delete[] auctions;
    auctions = temp;

    count++;
}
void AuctionManager::update() {

    for (int i = 0; i < count; i++) {
        if (auctions[i] != nullptr) {
            auctions[i]->checkAndClose();
        }
    }
}