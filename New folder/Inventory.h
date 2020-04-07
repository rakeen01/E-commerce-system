#pragma once

#include "pch.h"
#include "Linked List.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Inventory : public LinkedList {

private:
	LinkedList* inventoryList;
	void buildLinkedList(LinkedList* &invList, fstream &inputFile);

public:

	// Constructor

	Inventory();

	// Overloaded constructors

	Inventory(fstream &dataFile);
	Inventory(LinkedList* &invList, fstream &dataFile);

	// Accessor

	LinkedList* getInventoryList() {
		return inventoryList;
	}

	// Other functions

	void addItem();
	void deleteItem();
	void updateCost();
	void updateQty();
	void showInventory();
	~Inventory();
};