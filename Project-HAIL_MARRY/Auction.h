#pragma once
#include "Item.h"
#include "Bid.h"

class Auction {
private:
    Item item;
    Bid* bids;
    int bidCount;
    bool isActive;

public:
    Auction(Item item);
    ~Auction();

    bool placeBid(Bid bid);
    Bid getHighestBid();
    void closeAuction();

    // ✅ ADD THESE
    Item getItem();
    Bid* getAllBids(int& count);
    void checkAndClose();
};