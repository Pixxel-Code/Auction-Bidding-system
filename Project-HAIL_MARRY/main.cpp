#include <iostream>
#include "DBManager.h"
#include "AuthService.h"
#include "ItemService.h"
#include "Auction.h"

using namespace std;

int main() {

    cout << "Program started\n";


    DBManager& db = DBManager::getInstance();
    cout << "Before loading DB\n";
    db.loadUsers();
    cout << "Users loaded\n";

    db.loadItems();
    cout << "Items loaded\n";

    db.loadBids();
    cout << "Bids loaded\n";

    cout << "Data loaded\n";

    AuthService::signup("user1", "123");
    User user = AuthService::login("user1", "123");

    cout << "User ID: " << user.getId() << endl;

    ItemService::createItem("Laptop", 1000, user.getId());

    int count;
    Item* items = db.getAllItems(count);

    cout << "Items count: " << count << endl;

    if (count == 0) {
        cout << "No items found!\n";
        return 0;
    }

    Auction auction(items[0]);

    cout << "Auction created\n";

    auction.placeBid(Bid(user.getId(), items[0].getId(), 1200));
    auction.placeBid(Bid(user.getId(), items[0].getId(), 1500));


    cout << "Bids placed\n";

    cout << "Highest Bid: "
        << auction.getHighestBid().getAmount() << endl;

    cout << "Program ending\n";

    system("pause"); // VERY IMPORTANT (Windows)

    return 0;
}