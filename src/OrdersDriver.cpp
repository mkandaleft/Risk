

#include <iostream>
#include "Orders.h"
#include <vector>

using std::string;
using std::vector;

void testOrdersLists() {
	Deploy order1(1);
	Advance order2(1);
	Bomb order3(1);
	Blockade order4(1);
	Airlift order5(1);
	Negotiate order6(1);

	OrdersList testList;
	testList.addOrder(order1);
	testList.addOrder(order2);
	testList.addOrder(order3);
	testList.addOrder(order4);
	testList.addOrder(order5);
	testList.addOrder(order6);
	testList.printOrders();

	testList.remove(3);
	testList.printOrders();

	testList.move(1, 4);
	testList.printOrders();

}


int main()
{
	testOrdersLists();

	return 0;

}