#pragma once
#include <string>

using namespace std;

class Validator {
public:
    static bool isEmpty(string str) {
        return str.empty();
    }

    static bool isValidPrice(double price) {
        return price > 0;
    }
};
