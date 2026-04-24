#pragma once
#include "Auction.h"

class AuctionManager {
private:
    Auction** auctions;
    int count;

    AuctionManager();

public:
    static AuctionManager& getInstance();

    void addAuction(Auction* auction);
    void update();        // called every second
    void closeExpired();
};