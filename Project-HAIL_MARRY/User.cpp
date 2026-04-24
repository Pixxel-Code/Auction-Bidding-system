#include "User.h"

User::User() {
    id = 0;
    username = "";
    password = "";
    role = "";
}

User::User(int id, string u, string p, string r) {
    this->id = id;
    username = u;
    password = p;
    role = r;
}

int User::getId() { return id; }
string User::getUsername() { return username; }
string User::getRole() { return role; }
string User::getPassword() {
    return password;
}
