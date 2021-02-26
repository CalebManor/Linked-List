/******************************************************************************
Name: List.cpp
Description: Implementation of the function prototypes found in List.h. This
				file contains the implementations of the constructor and 
				destructor as well as the insert, delete, edit, and print 
				functions.
Author: Caleb Manor
******************************************************************************/
#include "List.h"
#include <iostream>
using namespace std;

/******************************************************************************
CONSTRUCTOR - Creates an empty linked list by assigning NULL to Head
******************************************************************************/
List::List() : Head(nullptr)
{}

/******************************************************************************
DESTRUCTOR - Deletes each node of the ordered linked list
******************************************************************************/
List::~List() {
	Node * temp = Head;
	while (Head != nullptr) {
		temp = Head->next;
		delete Head;
		Head = temp;
	}
}

/******************************************************************************
Function: Insert
Description: This function will first instantiate a new node for the new task
				that will be inserted into the to-do list. If memory is 
				unavailable, the function will return false. The item to be 
				inserted into the list will be placed into newTask->info and
				the function will iterate through the list to find where the
				new task will need to be placed alphabetically. The function
				will return true if the node is inserted correctly.
******************************************************************************/
bool List::Insert(ListType itemToInsert) {
	Node * newItem = new Node;

	if (newItem == nullptr)
		return false;
	else {
		newItem->info = itemToInsert;

		/*********************************************************************
		Empty Insertion Case
		*********************************************************************/
		if (Head == nullptr) {
			Head = newItem;
			Head->next = Head->prev = nullptr;
			return true;
		}

		Node * current;
		
		for (current = Head; current != nullptr; current = current->next) {

			/******************************************************************
			Front Insertion Case
			******************************************************************/
			if (newItem->info < Head->info) {
				newItem->next = Head;
				Head->prev = newItem;
				newItem->prev = nullptr;
				Head = newItem;
				return true;
			}

			/******************************************************************
			Middle Insertion Case
			******************************************************************/
			else if (current->info > newItem->info) {
				newItem->next = current;
				newItem->prev = current->prev;
				current->prev = newItem;
				newItem->prev->next = newItem;
				return true;
			}

			/******************************************************************
			End Insertion Case
			******************************************************************/
			else if(newItem->info > current->info && current->next == nullptr){
				current->next = newItem;
				newItem->prev = current;
				newItem->next = nullptr;
				return true;
			}
		}
	}
}

/******************************************************************************
Function: Delete
Description: This function will delete a node from the ordered linked list.
				The function will begin by instantiating a pointed that will
				be used to traverse the list, searching for the item to be
				deleted as specified by the input given by the user. The 
				traversal will search for whether the node to be deleted is 
				located in the front, middle, or end of the ordered linked
				list. If the item specified by the user is not located within
				the list, the function will return false. If the item is 
				removed succesfully, the function will return true. 
******************************************************************************/
bool List::Delete(ListType itemToDelete) {
	Node * current;

	for (current = Head; current != nullptr; current = current->next) {

		/**********************************************************************
		Front Deletion Case
		**********************************************************************/
		if (Head->info == itemToDelete) {
			if (Head->next == nullptr) {
				delete Head;
				Head = nullptr;
				return true;
			}
			else {
				Head = Head->next;
				delete Head->prev;
				Head->prev = nullptr;
				return true;
			}
		}

		/**********************************************************************
		End Deletion Case
		**********************************************************************/
		else if (current->next == nullptr && current->info == itemToDelete) {
			current->prev->next = nullptr;
			delete current;
			current = nullptr;
			return true;
		}

		/**********************************************************************
		Middle Deletion Case
		**********************************************************************/
		else if (current->info == itemToDelete) {
			current->next->prev = current->prev;
			current->prev->next = current->next;
			delete current;
			current = nullptr;
			return true;
		}

		/**********************************************************************
		Does Not Exist Case
		**********************************************************************/
		else if(current->next == nullptr && current->info != itemToDelete)
			return false;
	}
}

/******************************************************************************
Function: Edit
Description: This function will reuse the insert and delete functions in order
				to "edit" the node specified by user input. If the item to be
				edited is found in the ordered linked list, it will be deleted
				and the insert function will be called to insert the "edited"
				node. If either the delete or insert functions fail, the edit
				function will return false. If both the delete and insert 
				functions return true, the edit function will also return true.
******************************************************************************/
bool List::Edit(ListType itemToEdit, ListType editedItem) {
	if (Delete(itemToEdit)) {
		if (Insert(editedItem)) {
			return true;
		}
		return true;
	}
	else
		return false;
}

/******************************************************************************
Function: Print
Description: This function will print the contents of the entire ordered 
				linked list when it is called in the main application. The
				function will iterate through the list in alphabetical order
				and will print the contents of each node one at a time. 
******************************************************************************/
void List::Print() {
	for (Node * current = Head; current != nullptr; current = current->next)
		cout << current->info << endl;
}