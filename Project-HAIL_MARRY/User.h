#pragma once
#include <string>
using namespace std;
string getPassword();
class User {
private:
    int id;
    string username;
    string password;
    string role;

public:
    User();
    User(int id, string u, string p, string r);

    int getId();
    string getUsername();
    string getRole();
    string getPassword();
};
