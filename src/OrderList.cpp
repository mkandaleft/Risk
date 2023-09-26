#include "../include/OrderList.h"

using std::string;

OrderList::OrderList() {}

void OrderList::addOrder(Order& order) {
    orders.push_back(order);
}

const vector<Order>& OrderList::getOrders() const {
    return orders;
}

