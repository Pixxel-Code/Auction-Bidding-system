#include "AuthService.h"
#include "DBManager.h"
#include <cstdlib>

bool AuthService::signup(string username, string password) {

    string role = "buyer";

    if (username == "admin") {
        role = "admin";   // 🔥 FIX
    }

    User user(DBManager::getInstance().generateUserId(), username, password, role);

    DBManager::getInstance().addUser(user);

    return true;
}

User AuthService::login(string username, string password) {
    int id = DBManager::getInstance().generateUserId();
    User user = DBManager::getInstance().getUser(username.c_str());

    if (user.getUsername() == username && user.getPassword() == password) {
        return user;
    }

    return User();
}