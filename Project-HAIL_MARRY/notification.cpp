#include "Notification.h"

Notification::Notification(int uid, string msg) {
    userId = uid;
    message = msg;
}

string Notification::getMessage() {
    return message;
}