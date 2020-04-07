#include "pch.h"
#include "Linked List.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Constructor

LinkedList::LinkedList() {
	TempStruct = new node;
	head = nullptr;
	next = nullptr;
}

// Overloaded constructor

LinkedList::LinkedList(LinkedList* &headRef) {
	TempStruct = new node;
	head = headRef;
	next = nullptr;
}

// Overloaded += operator, which will add new product
// to existing LinkedList.

void LinkedList::operator+=(node* TempStruct) {
	appendNode(head, TempStruct);
}

// appendNode function is called whenever overloaded operator is used

void LinkedList::appendNode(LinkedList* &headRef, node* TempStruct) {

	// Declare variables

	LinkedList* tempHead = headRef;
	LinkedList* current = nullptr;
	LinkedList* newNode = new LinkedList;

	// Assign data values to newNode

	newNode->head = newNode;
	newNode->itemNumber = TempStruct->itemNumber;
	newNode->itemName = TempStruct->itemName;
	newNode->cost = TempStruct->cost;
	newNode->Qty = TempStruct->Qty;
	newNode->next = NULL;

	if (headRef == NULL) {
		tempHead = newNode;
		headRef = tempHead;
	}
	else {
		current = tempHead;

		// Traverse list until end is reached

		while (current->next) {
			current = current->next;
		}

		current->next = newNode;
	}
}

// Function to delete a linked list

void LinkedList::deleteList(LinkedList* &headRef) {

	// Declare nodes to traverse the list

	LinkedList* currentNode = headRef;
	LinkedList* nextNode = headRef;

	// Traverse list and delete each node along the way

	while (currentNode != nullptr) {
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}

	headRef = nullptr;
}

// Function to delete a product in a linked list

void LinkedList::deleteNode(LinkedList* &headRef, string userChoice) {

	// See if the product exists

	TempStruct = searchLinkedList(headRef, userChoice);

	if (TempStruct->itemNumber != 0) {

		// Declare variables

		LinkedList* tempHead = headRef;
		LinkedList* current = headRef;

		// If the first node must be deleted

		if (current->itemName == userChoice) {

			tempHead = current->next;
			delete current;
			current = nullptr;
			headRef = tempHead;

		}

		// If any other node must be deleted

		else {

			// Traverse until the node before the node to be deleted is reached

			while (current->next->itemName != userChoice) {
				current = current->next;
			}
			LinkedList* nodeDelete = current->next;
			current->next = nodeDelete->next;
			delete nodeDelete;
			nodeDelete = nullptr;

		}
	}

	else {
		cout << endl;
		cout << "Sorry, this product cannot be deleted because it does not exist." << endl;
	}
}

// Print out contents in a linked list

void LinkedList::printLinkedList(LinkedList* headRef) {

	LinkedList* current = headRef;
	double total = 0;

	// Print the headings to show user the cart

	cout << endl;
	cout << endl;
	cout << setw(20) << left << "Item Number";
	cout << setw(20) << left << "Item Name";
	cout << setw(12) << left << "Qty";
	cout << setw(20) << left << "Unit Cost";
	cout << setw(20) << left << "Total";
	cout << endl;

	while (current) {

		cout << setw(20) << left << current->itemNumber;
		cout << setw(20) << left << current->itemName;
		cout << setw(12) << left << current->Qty;
		cout << setw(20) << left << current->cost;
		cout << setw(20) << left << current->Qty * current->cost;
		cout << endl;

		total = total + current->Qty * current->cost;
		current = current->next;
	}

	// Print the total

	for (int i = 0; i < 92; i++) {
		cout << '-';
	}

	cout << endl;

	for (int i = 0; i < 72; i++) {
		cout << " ";
	}

	cout << setw(20) << left << total << endl;
}

// Update "ProductData.csv"

void LinkedList::editProductData(LinkedList* inventoryList, fstream &outputFile) {

	LinkedList* currentInventoryList = inventoryList;
	string emptyStock;

	// Traverse through the inventory list until the end

	while (currentInventoryList) {

		// If no quantity is left, delete that product 

		if (currentInventoryList->Qty = 0) {
			emptyStock = currentInventoryList->itemName;
			deleteNode(currentInventoryList, emptyStock);
		}

		currentInventoryList = currentInventoryList->next;
	}

	// Restore currentInventoryList

	currentInventoryList = inventoryList;

	// Print new inventory list to file in proper format

	while (currentInventoryList) {
		outputFile << currentInventoryList->itemNumber;
		outputFile << ", Product ";
		outputFile << currentInventoryList->itemName;
		outputFile << ', ';
		outputFile << currentInventoryList->cost;
		outputFile << ', ';
		outputFile << currentInventoryList->Qty;
		outputFile << endl;

		// Traverse list

		currentInventoryList = currentInventoryList->next;
	}
}

// Mutators

void LinkedList::setCost(node* TempStruct, LinkedList* headRef) {

	LinkedList* current = headRef;

	while (current->itemName != TempStruct->itemName) {
		current = current->next;
	}

	current->cost = TempStruct->cost;
}

void LinkedList::setQty(node* TempStruct, LinkedList* headRef) {

	LinkedList* current = headRef;

	while (current->itemName != TempStruct->itemName) {
		current = current->next;
	}

	current->Qty = TempStruct->Qty;
}

void LinkedList::setHead(LinkedList* headRef) {
	head = headRef;
}

void LinkedList::setNext(LinkedList* nextRef) {
	next = nextRef;
}

// Destructor

LinkedList::~LinkedList() {

}