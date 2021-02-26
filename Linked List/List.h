/******************************************************************************
Name: List.h
Description: This file contains the prototypes of the List ADT. The ADT is 
				designed to work with TestDriver.cpp, an application written
				to interact with an ordered linked list.
Author: Caleb Manor
******************************************************************************/
#include <string>
using namespace std;

typedef string ListType;

/******************************************************************************
Creates a node structure to be used with the ordered linked list
******************************************************************************/
struct Node
{
	ListType info;
	Node * next;
	Node * prev;
};

/******************************************************************************
Ordered Linked List Function Prototypes
******************************************************************************/
class List
{
public:
	List();
	~List();
	bool Insert(ListType);
	bool Delete(ListType);
	bool Edit(ListType, ListType);
	void Print();
private:
	Node * Head;
};