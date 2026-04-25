#pragma once
#include <string>
using namespace std;
string getPassword();
class User {
private:
private:
    int id;
    string username;
    string password;
    string role;

    double totalRating;
    int ratingCount;

public:
    User();
    User(int id, string u, string p, string r);

    int getId();
    string getUsername();
    string getRole();
    string getPassword();
    double getReputation();
    void addRating(double rating);
};
