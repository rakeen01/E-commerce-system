#include "pch.h"
#include "Linked List.h"
#include "Inventory.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Build an inventory list containing all the product info

void Inventory::buildLinkedList(LinkedList* &invList, fstream &inputFile) {

	string tempString;

	// Read in the numeric file contents and store it in the list

	while (!(inputFile.eof())) {

		for (int i = 0; i < 4; i++) {

			if ((i == 0) && !(inputFile.eof())) {

				// Read in the item number

				inputFile >> TempStruct->itemNumber;

			}
			else if ((i == 1) && !(inputFile.eof())) {

				// Use seekg to skip over ",Product "

				inputFile.seekg(9L, ios::cur);

				// Get item name

				getline(inputFile, TempStruct->itemName, ',');
			}
			else if ((i == 2) && !(inputFile.eof())) {

				// Use seekg to skip over ","

				// inputFile.seekg(1L, ios::cur);

				// Get item cost

				inputFile >> TempStruct->cost;
			}

			else if ((i == 3) && !(inputFile.eof())) {

				// Use seekg to skip over ","

				inputFile.seekg(1L, ios::cur);

				// Get quantity of item left

				inputFile >> TempStruct->Qty;

				// Use getline to go to next line

				getline(inputFile, tempString);
			}
		}

		// add this node to the list before loop begins again

		if (invList == nullptr) {

			// Overloaded operator cannot work with an empty list

			appendNode(invList, TempStruct);
		}
		else {
			*invList += TempStruct;
		}
	}
}

Inventory::Inventory() : LinkedList() {
	TempStruct = new node;
	inventoryList = nullptr;
}

Inventory::Inventory(fstream &dataFile) : LinkedList() {
	TempStruct = new node;
	inventoryList = nullptr;
	buildLinkedList(inventoryList, dataFile);
	setHead(inventoryList);
}

Inventory::Inventory(LinkedList* &invList, fstream &dataFile) : LinkedList(invList) {
	TempStruct = new node;
	inventoryList = invList;
	buildLinkedList(inventoryList, dataFile);
	invList = inventoryList;
	setHead(invList);
}

// Add an item to existing inventory

void Inventory::addItem() {

	TempStruct = new node;

	cout << "Enter the Item Number of your new product: ";
	cin >> TempStruct->itemNumber;
	cout << "Enter the name of your new product: ";
	cin >> TempStruct->itemName;
	cout << "Enter the Unit Price of your new product: ";
	cin >> TempStruct->cost;
	cout << "Enter the quantity of your new product you have in stock: ";
	cin >> TempStruct->Qty;

	*inventoryList += TempStruct;
}

// Delete an item

void Inventory::deleteItem() {

	string userChoice;
	TempStruct = new node;

	cout << "Enter the item name of the product to be deleted: ";
	cin >> userChoice;

	// Get node position of the node to be deleted

	TempStruct = searchLinkedList(inventoryList, userChoice);

	// If product is not found

	if (TempStruct->itemNumber == 0) {
		cout << "Sorry, that product was not found.";
	}

	// Delete product if found

	else {
		deleteNode(inventoryList, userChoice);
	}
}

// Update quantity of a product

void Inventory::updateQty() {

	string userChoice;
	int newQty;

	cout << "Enter the item number of the product whose quantity is to be updated: ";
	cin >> userChoice;

	// Get the product to be updated

	TempStruct = searchLinkedList(inventoryList, userChoice);

	// If product is not found

	if (TempStruct->itemNumber == 0) {
		cout << "Sorry, that product was not found.";
	}

	// If product is found

	else {
		cout << "Enter the new product quantity: ";
		cin >> newQty;
		TempStruct->Qty = newQty;
		setQty(TempStruct, inventoryList);
	}
}

// Update cost of a product

void Inventory::updateCost() {

	string userChoice;
	double newCost;

	cout << "Enter the item number of the product whose cost is to be updated: ";
	cin >> userChoice;

	// Get the product to be updated

	TempStruct = searchLinkedList(inventoryList, userChoice);

	// If product is not found

	if (TempStruct->itemNumber == 0) {
		cout << "Sorry, that product was not found.";
	}

	// If product is found

	else {
		cout << "Enter the new product cost: ";
		cin >> newCost;
		TempStruct->cost = newCost;
		setCost(TempStruct, inventoryList);
	}
}

// Show existing inventory

void Inventory::showInventory() {
	printLinkedList(inventoryList);
}

Inventory::~Inventory() {

}