#include "ItemService.h"
#include "DBManager.h"
#include "Item.h"
#include <cstdlib>

void ItemService::createItem(std::string title, double price, int sellerId) {
    int id = DBManager::getInstance().generateItemId();
    Item item(id, title, price, sellerId);
    DBManager::getInstance().addItem(item);
}