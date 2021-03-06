// linkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Node {
public:
	int data;  // data 
	Node * ptrNext;   // next node in linked list
	Node() { ptrNext = NULL; }
};

class LinkedList {   // ADT Unsorted LIST
public:
	Node * ptrHead;   // Start of linked list
	void add(int inData);
	bool remove(int inData);
	bool isEmpty();
	int count();
	void printAll();
	void bubbleSortList();
	void swap(Node *a, Node *b);
	Node * binarySearch(int valueToSearch);
	void userInput();
	Node * middleNode(Node * startNode, Node * endNode);

	LinkedList() { ptrHead = NULL; nodeCount = 0; sorted = false; }
private:
	int nodeCount;
	bool sorted;
};

void LinkedList::add(int inData)
{  // Insert at beginning - Unsorted list - Fastest insert
	if (ptrHead == NULL) 
	{  // add first data to list
		ptrHead = new Node;
		ptrHead->data = inData;
		ptrHead->ptrNext = NULL;
	}
	else   // add at beginning - already data in list
	{
		Node * ptrNewNode = new Node;
		ptrNewNode->ptrNext = ptrHead;
		ptrNewNode->data = inData;
		ptrHead = ptrNewNode;
	}
	nodeCount++;
}

void LinkedList::userInput()
{
	int size;
	int inVal;
	cout << "Enter how many numbers you would like to enter into list > ";
	cin >> size;
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Enter number to add > ";
		cin >> inVal;
		if (inVal >= 0)
		{
			add(inVal);
		}
	}
}

bool LinkedList::remove(int inData) 
{
	if (ptrHead == NULL)
	{   // no nodes ... nothing to do
		return false;
	}
	else if (nodeCount == 1)  // check only one node
	{
		Node * ptrDel = ptrHead;
		if (ptrHead->data == inData) 
		{
			delete ptrDel;
			ptrHead = NULL;
			nodeCount = 0;
			return true;
		}
		else { return false; }
	}
	else    // multiple nodes
	{
		Node * ptrCurrent = ptrHead;  // start at beginning
		Node * ptrPrevious = NULL;
		while (ptrCurrent->ptrNext != NULL)  // advance to next node... ?
		{
			ptrPrevious = ptrCurrent;  // save current as previous
			ptrCurrent = ptrCurrent->ptrNext; // advance to next node

			if (ptrCurrent->data == inData) {
				ptrPrevious->ptrNext = ptrCurrent->ptrNext;  // bypass node
				delete ptrCurrent;  // delete bypadded node
				nodeCount--;
				return true;
			}
		}
		return false;
	}
}

bool LinkedList::isEmpty() 
{
	if (ptrHead == NULL) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

int LinkedList::count() { return nodeCount; }

void LinkedList::printAll() 
{
	if (sorted)
	{
		cout << "Sorted List :" << endl;
	}
	else
	{
		cout << "Unsorted List :" << endl;
	}
	Node * ptrCurrent = ptrHead;  // start at the beginning
	while (ptrCurrent != NULL)
	{
		cout << ptrCurrent->data << endl;
		ptrCurrent = ptrCurrent->ptrNext; // advacne to next node
	}
	cout << endl;
}

void LinkedList::bubbleSortList()
{
	int swapped;
	Node *ptr1 = ptrHead;
	Node *lptr = NULL;
	// Checking for empty list 
	if (ptr1 == NULL)
	{
		return;
	}
	do
	{
		swapped = 0;
		ptr1 = ptrHead;

		while (ptr1->ptrNext != lptr)
		{
			if (ptr1->data > ptr1->ptrNext->data)
			{
				swap(ptr1, ptr1->ptrNext);
				swapped = 1;
			}
			ptr1 = ptr1->ptrNext;
		}
		lptr = ptr1;
	} while (swapped);
	sorted = true;
}

void LinkedList::swap(Node * a, Node * b)
{
		int temp = a->data;
		a->data = b->data;
		b->data = temp;
}

Node * LinkedList::middleNode(Node * startNode, Node * endNode)
{
	if (startNode == NULL)
	{
		// If the linked list is empty

		return NULL;
	}

	Node * slowPtr = startNode;
	Node * fastPtr = startNode->ptrNext;

	while (fastPtr != endNode)
	{
		fastPtr = fastPtr->ptrNext;

		if (fastPtr != endNode)
		{
			slowPtr = slowPtr->ptrNext;
			fastPtr = fastPtr->ptrNext;

			/*
			Note that for each loop iteration,
			slowPtr moves just one location
			while fastPtr moves two nodes at a time.
			*/
		}
	}
	return slowPtr;
	/*
	At the end , the slowPtr will be
	pointing to the middle node
	*/
}

Node * LinkedList::binarySearch(int valueToSearch)
{
	if (sorted)
	{
		Node * startNode = ptrHead;
		Node * endNode = NULL;
		int left = 0, right = nodeCount;
		int mid = (left + right) / 2;
		do
		{
			Node * middle = middleNode(startNode, endNode);

			if (middle == NULL)
			{
				// Searched Element Not Present
				cout << valueToSearch << " not present" << endl;
				return NULL;
			}

			if (middle->data == valueToSearch)
			{
				cout << "Found " << middle->data << endl;
				return middle;
			}
			else if (middle->data < valueToSearch)
			{
				// need to search in upper half
				startNode = middle->ptrNext;
				left = mid + 1;
			}
			else
			{
				// need to search in lower half
				endNode = middle;
				right = mid - 1;

			}

		} while (left <= right);

		// data not present
		cout << valueToSearch << " not present" << endl;
		return NULL;
	}
	else
	{
		cout << "List not sorted!" << endl;
	}
	
}

int main() 
{
	cout << "Dylan Maynard \t 2/18/2018\n\n";
	LinkedList L1;
	L1.userInput();
	L1.printAll();
	cout << "List count: " << L1.count() << "\n" << endl;
	L1.bubbleSortList();
	L1.printAll();
	L1.binarySearch(42);
	L1.binarySearch(10);
	L1.binarySearch(11);

	return 0;
}