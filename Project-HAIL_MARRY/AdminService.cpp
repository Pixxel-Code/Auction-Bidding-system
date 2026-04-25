#include "AdminService.h"
#include<iostream>

// VIEW
User* AdminService::getUsers(int& count) {
    return DBManager::getInstance().getAllUsers(count);
}

Item* AdminService::getItems(int& count) {
    return DBManager::getInstance().getAllItems(count);
}

Bid* AdminService::getBids(int& count) {
    return DBManager::getInstance().getAllBids(count);
}

// DELETE USER
bool AdminService::deleteUser(int id, User currentUser) {

    if (currentUser.getRole() != "admin") {
        cout << "Access denied\n";
        return false;
    }

    DBManager& db = DBManager::getInstance();

    db.removeUserById(id);
    db.rewriteUsersFile();

    cout << "User deleted successfully\n";

    return true;
}
// DELETE ITEM
bool AdminService::deleteItem(int id, User currentUser) {

    if (currentUser.getRole() != "admin") {
        cout << "Access denied\n";
        return false;
    }

    DBManager& db = DBManager::getInstance();

    db.removeItemById(id);
    db.removeBidsByItemId(id);

    db.rewriteItemsFile();
    db.rewriteBidsFile();

    cout << "Item deleted successfully\n";

    return true;
}