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

    delete[] users;
    users = nullptr;
    userCount = 0;

    std::ifstream file("users.txt");

    if (!file.is_open()) {
        std::cout << "users.txt not found\n";
        return;
    }

    int id;
    string username, password, role;

    while (file >> id >> username >> password >> role) {

        User user(id, username, password, role);

        User* temp = new User[userCount + 1];

        for (int i = 0; i < userCount; i++)
            temp[i] = users[i];

        temp[userCount] = user;

        delete[] users;
        users = temp;

        userCount++;
    }

    file.close();
}
void DBManager::loadItems() {

    delete[] items;
    items = nullptr;
    itemCount = 0;
    std::ifstream file("items.txt");

    if (!file.is_open()) {
        std::cout << "items.txt not found\n";
        return;
    }

    int id, sellerId;
    string title;
    double base, current;

    while (file >> id >> title >> base >> current >> sellerId) {

        Item item(id, title, base, sellerId);
        item.updatePrice(current);

        Item* temp = new Item[itemCount + 1];

        for (int i = 0; i < itemCount; i++)
            temp[i] = items[i];

        temp[itemCount] = item;

        delete[] items;
        items = temp;

        itemCount++;
    }

    file.close();
}
void DBManager::loadBids() {

    delete[] bids;
    bids = nullptr;
    bidCount = 0;
    std::ifstream file("bids.txt");

    if (!file.is_open()) {
        std::cout << "bids.txt not found\n";
        return;
    }

    int userId, itemId;
    double amount;

    while (file >> userId >> itemId >> amount) {

        Bid bid(userId, itemId, amount);

        Bid* temp = new Bid[bidCount + 1];

        for (int i = 0; i < bidCount; i++)
            temp[i] = bids[i];

        temp[bidCount] = bid;

        delete[] bids;
        bids = temp;

        bidCount++;
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
User* DBManager::getAllUsers(int& count) {
    count = userCount;
    return users;
}
void DBManager::removeUserById(int id) {

    int newCount = 0;

    // STEP 1: calculate new size (excluding target user)
    for (int i = 0; i < userCount; i++) {
        if (users[i].getId() != id)
            newCount++;
    }

    // STEP 2: create new array
    User* temp = new User[newCount];
    int index = 0;

    // STEP 3: copy all except the deleted user
    for (int i = 0; i < userCount; i++) {
        if (users[i].getId() != id) {
            temp[index] = users[i];
            index++;
        }
    }

    // STEP 4: replace old memory
    delete[] users;
    users = temp;
    userCount = newCount;
}
void DBManager::removeItemById(int id) {

    int newCount = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].getId() != id)
            newCount++;
    }

    Item* temp = new Item[newCount];
    int index = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].getId() != id) {
            temp[index] = items[i];
            index++;
        }
    }

    delete[] items;
    items = temp;
    itemCount = newCount;
}
Bid* DBManager::getAllBids(int& count) {
    count = bidCount;
    return bids;
}
void DBManager::rewriteUsersFile() {

    std::ofstream file("users.txt");

    for (int i = 0; i < userCount; i++) {
        file << users[i].getId() << " "
            << users[i].getUsername() << " "
            << users[i].getPassword() << " "
            << users[i].getRole() << "\n";
    }

    file.close();
}
void DBManager::rewriteItemsFile() {

    std::ofstream file("items.txt");

    for (int i = 0; i < itemCount; i++) {
        file << items[i].getId() << " "
            << "Item "
            << items[i].getCurrentPrice() << " "
            << items[i].getCurrentPrice() << " "
            << 1 << "\n";
    }

    file.close();
}
void DBManager::rewriteBidsFile() {

    std::ofstream file("bids.txt");

    for (int i = 0; i < bidCount; i++) {
        file << bids[i].getUserId() << " "
            << bids[i].getItemId() << " "
            << bids[i].getAmount() << "\n";
    }

    file.close();
}
void DBManager::removeBidsByItemId(int itemId) {

    int newCount = 0;

    for (int i = 0; i < bidCount; i++) {
        if (bids[i].getItemId() != itemId)
            newCount++;
    }

    Bid* temp = new Bid[newCount];
    int index = 0;

    for (int i = 0; i < bidCount; i++) {
        if (bids[i].getItemId() != itemId)
            temp[index++] = bids[i];
    }

    delete[] bids;
    bids = temp;
    bidCount = newCount;
}