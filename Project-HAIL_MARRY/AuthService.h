#pragma once
#include <string>
#include "User.h"

using namespace std;

class AuthService {
public:
    static bool signup(string username, string password);
    static User login(string username, string password);
};
