#include "pch.h"
#include "Linked List.h"
#include "Customer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Constructor

Customer::Customer() : LinkedList() {
	cartList = nullptr;
	inventoryList = nullptr;
}

// Overloaded Constructor

Customer::Customer(LinkedList* &headRef, string firstNameInput, string lastNameInput, string address, string city, string state, int ZIP) : LinkedList(headRef) {
	cartList = headRef;
	invoiceFileName = firstNameInput + " " + lastNameInput + ".txt";
	firstName = firstNameInput;
	lastName = lastNameInput;
	userAddress = address;
	userCity = city;
	userState = state;
	userZIP = ZIP;
}

// Displays shopping cart

void Customer::showCart() {
	printLinkedList(cartList);
}

// Creates an invoice file for the current customer

fstream Customer::createInvoiceFile() {
	fstream invoiceFile;
	invoiceFile.open(invoiceFileName, ios::out);
	return invoiceFile;
}

// Updates information in the invoice file for the current customer

void Customer::updateInvoiceFile(fstream &outputFile, LinkedList* headRef) {

	cout << "hello" << endl;

	LinkedList* currentCartList = headRef;
	double total = 0;

	outputFile << "Customer Name: " << firstName << " " << lastName << endl;
	outputFile << "Customer Address: " << userAddress << endl;
	int value = userCity.length() + 18;
	outputFile << setw(value) << userCity << ", " << userState << " " << userZIP << endl;
	outputFile << endl;
	outputFile << setw(20) << left << "Item Number";
	outputFile << setw(20) << left << "Item Name";
	outputFile << setw(12) << left << "Qty";
	outputFile << setw(20) << left << "Unit Cost";
	outputFile << setw(20) << left << "Total";
	outputFile << endl;
	for (int i = 0; i < 100; i++) {
		outputFile << "-";
	}
	outputFile << endl;

	// Data protection prevents direct access, so get the head address first and temporarily store it in TempStruct

	TempStruct->head = currentCartList->getHead();
	TempStruct->next = currentCartList->getNext();

	// Output the user's cart to invoice.txt

	while (TempStruct->head) {

		TempStruct->itemNumber = TempStruct->head->getItemNumber();
		TempStruct->itemName = TempStruct->head->getItemName();
		TempStruct->cost = TempStruct->head->getCost();
		TempStruct->Qty = TempStruct->head->getQty();

		outputFile << left;
		outputFile << "Item Number " << setw(8) << TempStruct->itemNumber;
		outputFile << "Product Name " << setw(7) << TempStruct->itemName;
		outputFile << setw(12) << TempStruct->Qty;
		outputFile << setw(20) << TempStruct->cost;
		outputFile << setw(20) << TempStruct->Qty * TempStruct->cost;
		outputFile << endl;

		total = total + TempStruct->Qty * TempStruct->cost;

		TempStruct->head = TempStruct->next;
		TempStruct->next = TempStruct->next->getNext();

	}

	// Formatting shopping cart for proper display and user-friendliness

	for (int i = 0; i < 100; i++) {
		outputFile << "-";
	}
	outputFile << endl;

	// Display the total the user will be charged

	outputFile << right << setw(72) << "Total: $" << total;

	// Close output file

	outputFile.close();
}

// Adds new item to the customer's shopping cart

void Customer::addItem(string userChoice) {

	TempStruct = searchLinkedList(inventoryList, userChoice);

	int numItems;

	// If the item does not exist

	if (TempStruct->itemNumber == 0) {
		cout << endl;
		cout << TempStruct->itemName << endl;
	}

	// If the item exists

	else {

		// If the desired product ran out of stock

		if (TempStruct->Qty == 0) {
			cout << endl;
			cout << "Sorry. We are currently out of stock of this product. Please try a different product." << endl;
		}

		// If the desired product is available

		else {

			// Display the product's pricing.

			cout << endl;
			cout << "Product " << TempStruct->itemName << " costs " << TempStruct->cost << endl;

			// Get numItems

			cout << endl;
			cout << "How many items of this product would you like? Please enter: ";
			cin >> numItems;

			// Validate input

			while (numItems <= 0 || numItems > TempStruct->Qty) {

				// If the user entered 0 or a negative number

				if (numItems <= 0) {
					cout << endl;
					cout << "The number of items you want must be greater than 0. Please try again: ";
					cin >> numItems;
				}

				// If the user entered an amount more than what we have

				if (numItems > TempStruct->Qty) {
					cout << endl;
					cout << "The amount you requested exceeds the amount we have in stock right now. ";
					cout << "Please request a maximum of " << TempStruct->Qty << " items: ";
					cin >> numItems;
				}

			}

			// Update the inventory list

			TempStruct->Qty = TempStruct->Qty - numItems;
			setQty(TempStruct, inventoryList);

			TempStruct->Qty = numItems;
			node* TempStruct2 = new node;
			*TempStruct2 = *TempStruct;
			TempStruct = searchLinkedList(cartList, TempStruct2->itemName);

			// If the item is not found

			if (TempStruct->itemNumber == 0) {

				if (cartList == nullptr) {

					// Overloaded operator cannot work with an empty list

					appendNode(cartList, TempStruct2);
				}
				else {
					*cartList += TempStruct2;
				}
			}

			// If it is found

			else {
				TempStruct2->Qty = TempStruct2->Qty + TempStruct->Qty;
				setQty(TempStruct2, cartList);
			}

		}
	}
}

// Change inventoryList head

void Customer::setInventoryList(LinkedList* invList) {
	inventoryList = invList;
}

// Destructor

Customer::~Customer() {
}