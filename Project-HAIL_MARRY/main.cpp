#include <iostream>
#include "DBManager.h"
#include "AuthService.h"
#include "ItemService.h"
#include "AdminService.h"

using namespace std;

int main() {

   
    // LOAD DATA
    cout << "===== SYSTEM START =====\n";

    cout << "Before DB instance\n";
    DBManager& db = DBManager::getInstance();
    cout << "After DB instance\n";

    cout << "Before loadUsers\n";
    db.loadUsers();
    cout << "After loadUsers\n";

    cout << "Before loadItems\n";
    db.loadItems();
    cout << "After loadItems\n";

    cout << "Before loadBids\n";
    db.loadBids();
    cout << "After loadBids\n";

    cout << "Data Loaded\n";

    // CREATE TEST USERS
    AuthService::signup("admin", "123");
    AuthService::signup("user1", "123");
    AuthService::signup("user2", "123");

    User admin = AuthService::login("admin", "123");

    cout << "\nAdmin Logged In: " << admin.getUsername() << endl;

    // CREATE ITEMS
    ItemService::createItem("Laptop", 1000, admin.getId());
    ItemService::createItem("Phone", 500, admin.getId());

    // ==============================
    // 🔥 ADMIN PANEL TESTING
    // ==============================

    int count;

    // 📊 VIEW USERS
    cout << "\n--- USERS ---\n";
    User* users = AdminService::getUsers(count);

    for (int i = 0; i < count; i++) {
        cout << "ID: " << users[i].getId()
            << " Name: " << users[i].getUsername()
            << endl;
    }

    // 🗑 DELETE USER (delete second user if exists)
    if (count > 1) {
        int deleteId = users[1].getId();

        cout << "\nDeleting User ID: " << deleteId << endl;
        AdminService::deleteUser(deleteId);
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
        AdminService::deleteItem(deleteItemId);
    }

    // 📊 VIEW ITEMS AGAIN
    cout << "\n--- ITEMS AFTER DELETE ---\n";
    items = AdminService::getItems(count);

    for (int i = 0; i < count; i++) {
        cout << "Item ID: " << items[i].getId()
            << " Price: " << items[i].getCurrentPrice()
            << endl;
    }

    // ==============================

    // 📊 VIEW BIDS (SYSTEM MONITORING)
    cout << "\n--- BIDS ---\n";
    Bid* bids = AdminService::getBids(count);

    for (int i = 0; i < count; i++) {
        cout << "User: " << bids[i].getUserId()
            << " Item: " << bids[i].getItemId()
            << " Amount: " << bids[i].getAmount()
            << endl;
    }

    cout << "\n===== SYSTEM END =====\n";

    system("pause");
    return 0;
}