#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LinkedList {

public:

	struct node {
		LinkedList* head;
		int itemNumber;
		string itemName;
		double cost;
		int Qty;
		LinkedList* next;
	};

private:

	LinkedList* head;
	int itemNumber;
	string itemName;
	double cost;
	int Qty;
	LinkedList* next;

public:
	LinkedList();
	LinkedList(LinkedList* &headRef);
	void operator+=(node* TempStruct);
	node* TempStruct;

	// Accessor functions

	LinkedList* getHead() {
		return head;
	}
	int getItemNumber() {
		return itemNumber;
	}
	string getItemName() {
		return itemName;
	}
	double getCost() {
		return cost;
	}
	int getQty() {
		return Qty; 
	}
	LinkedList* getNext() {
		return next;
	}

	// Mutator functions

	void setCost(node* TempStruct, LinkedList* headRef);
	void setQty(node* TempStruct, LinkedList* headRef);
	void appendNode(LinkedList* &headRef, node* TempStruct);

	// Other functions

	node* searchLinkedList(LinkedList* headRef, string userChoice) {

			TempStruct->head = nullptr;
			TempStruct->itemNumber = 0;
			TempStruct->itemName = "Product does not exist!";
			TempStruct->cost = 0.0;
			TempStruct->Qty = 0;
			TempStruct->next = nullptr;

			// Declare variables

			bool found = false;
			LinkedList* currentNode = headRef;

			while (currentNode && (found == false)) {

				// if userChoice is found

				if (currentNode->itemName == userChoice) {
					found = true;
					TempStruct->head = currentNode->head;
					TempStruct->itemNumber = currentNode->itemNumber;
					TempStruct->itemName = currentNode->itemName;
					TempStruct->cost = currentNode->cost;
					TempStruct->Qty = currentNode->Qty;
					TempStruct->next = currentNode->next;
				}

				// if not found, keep traversing the list

				else {
					currentNode = currentNode->next;
				}
			}

			return TempStruct;
	}
	void setHead(LinkedList* headRef);
	void setNext(LinkedList* nextRef);
	void deleteNode(LinkedList* &headRef, string userChoice);
	void printLinkedList(LinkedList* headRef);
	void editProductData(LinkedList* inventoryList, fstream &outputFile);
	void deleteList(LinkedList* &headRef);

	// Destructor

	virtual ~LinkedList();

};