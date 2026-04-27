#include "User.h"

User::User() {
    id = 0;
    username = "";
    password = "";
    role = "";
    totalRating = 0;
    ratingCount = 0;
}

User::User(int id, string u, string p, string r) {
    this->id = id;
    username = u;
    password = p;
    role = r;

    totalRating = 0;
    ratingCount = 0;
}
void User::addRating(double rating) {
    totalRating += rating;
    ratingCount++;
}
double User::getReputation() {

    if (ratingCount == 0)
        return 0;

    return totalRating / ratingCount;
}

int User::getId() { return id; }
string User::getUsername() { return username; }
string User::getRole() { return role; }
string User::getPassword() {return password; }
double User::getTotalRating() {return totalRating; }
int User::getRatingCount() {return ratingCount; }