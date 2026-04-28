#include <iostream>
#include "DBManager.h"
#include "AuthService.h"
#include "ItemService.h"
#include "AdminService.h"

using namespace std;

int main() {

    cout << "===== SYSTEM START =====\n";

    DBManager& db = DBManager::getInstance();

    // LOAD DATA FROM FILES
    db.loadUsers();
    db.loadItems();
    db.loadBids();
    db.loadNotifications();

    cout << "Data Loaded\n";

    int count;

    // ==============================
    // 🔥 CREATE DATA ONLY IF EMPTY
    // ==============================

    User* usersCheck = db.getAllUsers(count);

    if (count == 0) {
        cout << "Creating default users...\n";

        AuthService::signup("admin", "123", "admin");
        AuthService::signup("user1", "123", "buyer");
        AuthService::signup("user2", "123", "seller");
    }

    // LOGIN ADMIN
    User admin = AuthService::login("admin", "123");

    cout << "\nAdmin Logged In: " << admin.getUsername() << endl;

    // CREATE ITEMS ONLY IF EMPTY
    Item* itemsCheck = db.getAllItems(count);

    if (count == 0) {
        cout << "Creating default items...\n";

        User seller = AuthService::login("user2", "123");
        ItemService::createItem("Laptop", 1000, seller.getId(), "Electronics", seller);
        ItemService::createItem("Phone", 500, seller.getId(), "Phones", seller);
    }

    // ==============================
    // 🔥 ADMIN PANEL TESTING
    // ==============================

    // 📊 VIEW USERS
    cout << "\n--- USERS ---\n";
    User* users = AdminService::getUsers(count);

    for (int i = 0; i < count; i++) {
        cout << "ID: " << users[i].getId()
            << " Name: " << users[i].getUsername()
            << endl;
    }

    // 🗑 DELETE USER
    if (count > 1) {
        int deleteId = users[1].getId();

        cout << "\nDeleting User ID: " << deleteId << endl;
        AdminService::deleteUser(deleteId, admin);
    }
 

    // 📊 VIEW USERS AGAIN
    cout << "\n--- USERS AFTER DELETE ---\n";
    users = AdminService::getUsers(count);

    for (int i = 0; i < count; i++) {
        cout << "ID: " << users[i].getId()
            << " Name: " << users[i].getUsername()
            << endl;
    }

    // ==============================

    // 📊 VIEW ITEMS
    cout << "\n--- ITEMS ---\n";
    Item* items = AdminService::getItems(count);

    for (int i = 0; i < count; i++) {
        cout << "Item ID: " << items[i].getId()
            << " Price: " << items[i].getCurrentPrice()
            << endl;
    }

    // 🗑 DELETE ITEM
    if (count > 0) {
        int deleteItemId = items[0].getId();

        cout << "\nDeleting Item ID: " << deleteItemId << endl;
        AdminService::deleteItem(deleteItemId, admin);
    }
    
    // 📊 VIEW ITEMS AGAIN
    cout << "\n--- ITEMS AFTER DELETE ---\n";
    items = AdminService::getItems(count);

    for (int i = 0; i < count; i++) {
        cout << "Item ID: " << items[i].getId()
            << " Price: " << items[i].getCurrentPrice()
            << endl;
    }


    // 📊 VIEW BIDS
    cout << "\n--- BIDS ---\n";
    Bid* bids = AdminService::getBids(count);

    for (int i = 0; i < count; i++) {
        cout << "User: " << bids[i].getUserId()
            << " Item: " << bids[i].getItemId()
            << " Amount: " << bids[i].getAmount()
            << endl;
    }

    // WATCHLIST TEST 
    cout << "\n-- WATCHLIST TEST --\n";
    User buyer = AuthService::login("user1", "123");
    Item* allItems = db.getAllItems(count);

    // Watch item
    buyer.addToWatchlist(allItems[0].getId());
    db.updateUser(buyer);
    cout << "user1 watching item: " << allItems[0].getId() << "\n";

    // Check watchlist
    int wCount = 0;
    int* watched = buyer.getWatchlist(wCount);
    cout << "Watchlist count: " << wCount << "\n";
    for (int i = 0; i < wCount; i++)
        cout << "Watching item ID: " << watched[i] << "\n";
    delete[] watched;

    // ===== RATING TEST =====
    cout << "\n--- RATING TEST ---\n";
    User seller = AuthService::login("user2", "123");

    AdminService::rateUser(buyer.getId(), seller.getId(), 5.0);
    AdminService::rateUser(buyer.getId(), seller.getId(), 6.0); // invalid
    AdminService::rateUser(buyer.getId(), buyer.getId(), 4.0);  // self rate

    cout << "Seller reputation: " << AdminService::getReputation(seller.getId()) << "\n";

    cout << "\n===== SYSTEM END =====\n";

    system("pause");
    return 0;
}