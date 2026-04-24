#include "DBManager.h"
#include <cstring>
#include <fstream>
#include <iostream>
DBManager& DBManager::getInstance() {
    static DBManager instance;
    return instance;
}

DBManager::DBManager() {
    users = nullptr;
    userCount = 0;

    items = nullptr;
    itemCount = 0;

    bids = nullptr;
    bidCount = 0;
}

DBManager::~DBManager() {
    delete[] users;
    delete[] items;
    delete[] bids;
}
void DBManager::addUser(User user) {

    User* temp = new User[userCount + 1];

    for (int i = 0; i < userCount; i++)
        temp[i] = users[i];

    temp[userCount] = user;

    delete[] users;
    users = temp;

    userCount++;

    saveUser(user);   // ✔ ONLY HERE
}
User DBManager::getUser(const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].getUsername().c_str(), username) == 0)
            return users[i];
    }
    return User();
}
void DBManager::addItem(Item item) {

    Item* temp = new Item[itemCount + 1];

    for (int i = 0; i < itemCount; i++)
        temp[i] = items[i];

    temp[itemCount] = item;

    delete[] items;
    items = temp;

    itemCount++;

    saveItem(item);   // ✔ ONLY HERE
}
Item* DBManager::getAllItems(int& count) {
    count = itemCount;
    return items;
}
void DBManager::addBid(Bid bid) {

    Bid* temp = new Bid[bidCount + 1];

    for (int i = 0; i < bidCount; i++)
        temp[i] = bids[i];

    temp[bidCount] = bid;

    delete[] bids;
    bids = temp;

    bidCount++;

    saveBid(bid);   // ✔ ONLY HERE
}
Bid* DBManager::getBidsForItem(int itemId, int& count) {

    int c = 0;
    for (int i = 0; i < bidCount; i++) {
        if (bids[i].getItemId() == itemId)
            c++;
    }

    Bid* result = new Bid[c];
    int index = 0;

    for (int i = 0; i < bidCount; i++) {
        if (bids[i].getItemId() == itemId)
            result[index++] = bids[i];
    }

    count = c;
    return result;
}
void DBManager::loadUsers() {

    std::ifstream file("users.txt");
    if (!file.is_open()) return;

    int id;
    string username, password, role;

    while (file >> id >> username >> password >> role) {
        User user(id, username, password, role);
        addUser(user);
    }

    file.close();
}
void DBManager::loadItems() {

    std::ifstream file("items.txt");
    if (!file.is_open()) return;

    int id, sellerId;
    string title;
    double base, current;

    while (file >> id >> title >> base >> current >> sellerId) {
        Item item(id, title, base, sellerId);
        item.updatePrice(current);
        addItem(item);
    }

    file.close();
}
void DBManager::loadBids() {

    std::ifstream file("bids.txt");
    if (!file.is_open()) return;

    int userId, itemId;
    double amount;

    while (file >> userId >> itemId >> amount) {
        Bid bid(userId, itemId, amount);
        addBid(bid);
    }

    file.close();
}
void DBManager::saveUser(User user) {

    std::ofstream file("users.txt", std::ios::app);

    file << user.getId() << " "
        << user.getUsername() << " "
        << user.getPassword() << " "
        << user.getRole() << "\n";

    file.close();
}
void DBManager::saveItem(Item item) {

    std::ofstream file("items.txt", std::ios::app);

    file << item.getId() << " "
        << "Item "
        << item.getCurrentPrice() << " "
        << item.getCurrentPrice() << " "
        << 1 << "\n";

    file.close();
}
void DBManager::saveBid(Bid bid) {

    std::ofstream file("bids.txt", std::ios::app);

    file << bid.getUserId() << " "
        << bid.getItemId() << " "
        << bid.getAmount() << "\n";

    file.close();
}

int DBManager::generateUserId() {
    return userCount + 1000;
}

int DBManager::generateItemId() {
    return itemCount + 5000;
}

Item* DBManager::searchByPrice(double min, double max, int& count) {

    int c = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].getCurrentPrice() >= min &&
            items[i].getCurrentPrice() <= max)
            c++;
    }

    Item* result = new Item[c];
    int index = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].getCurrentPrice() >= min &&
            items[i].getCurrentPrice() <= max)
            result[index++] = items[i];
    }

    count = c;
    return result;
}
