#include "AdminService.h"

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

    if (currentUser.getRole() != "admin")
        return false;

    DBManager::getInstance().removeUserById(id);
    DBManager::getInstance().rewriteUsersFile();   // 🔥 important

    return true;
}

// DELETE ITEM
bool AdminService::deleteItem(int id, User currentUser) {

    if (currentUser.getRole() != "admin")
        return false;

    DBManager::getInstance().removeItemById(id);
    DBManager::getInstance().removeBidsByItemId(id); // 🔥 cascade delete
    DBManager::getInstance().rewriteItemsFile();
    DBManager::getInstance().rewriteBidsFile();

    return true;
}