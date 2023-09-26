#pragma once

#include <iostream>
#include <vector>
#include "Order.h"
using std::string;
using std::vector;

class  OrderList {
    
    private:
    vector<Order> orders;

    public:
    OrderList();

    void addOrder(Order& order);

    const vector<Order>& getOrders() const;
};
