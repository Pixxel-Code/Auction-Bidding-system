#pragma once
#include <string>

class ItemService {
public:
    static void createItem(std::string title, double price, int sellerId);
};