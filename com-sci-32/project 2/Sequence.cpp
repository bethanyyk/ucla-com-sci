#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
{
	// Design: Circular doubly-linked list with a dummy node
	head = new Node;
	head->m_next = head;
	head->m_prev = head;

	m_size = 0;
}

Sequence::Sequence(const Sequence& other)
{
	// Creating a second Sequence
	head = new Node;
	head->m_next = head;
	head->m_prev = head;
	m_size = 0;

	for (int i = 0; i < other.m_size; i++)
	{
		ItemType value;
		other.get(i, value);
		insert(i, value); // Copying values in other into our newly created Sequence
	}
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}

Sequence::~Sequence()
{
	while (!empty())
	{
		erase(0); // Erase all of the nodes individually until there are no remaining nodes
	}
	delete head; // Delete the head pointer
}

bool Sequence::empty() const
{
	if (size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::size() const
{
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > size())
	{
		return -1;
	}

	// Create a new node and a pointer to that node
	// Set m_item in the node that the pointer points to
	Node* pNewNode = new Node;
	pNewNode->m_item = value;

	Node* p = head->m_next; // Pointer to the first node in the Sequence
	for (int i = 0; i < pos; i++) // Loop until we get to the correct node
	{
		p = p->m_next;
	}
	
	// Insert the new node before the node that p points to
	pNewNode->m_next = p;
	pNewNode->m_prev = p->m_prev;
	pNewNode->m_prev->m_next = pNewNode;
	p->m_prev = pNewNode;

	m_size++; // Increment the size because we inserted a new node
	return pos;
}

int Sequence::insert(const ItemType& value)
{
	Node* p = head->m_next;
	int pos = 0;
	while (p != head && p->m_item < value) // Loop until we get to the correct node
	{
		pos++;
		p = p->m_next;
	}

	int retVal = insert(pos, value); // Pass that position that we just found and the value into the insert function with two parameters
	// m_size is incremented within the insert function with two parameters
	return retVal;
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= size())
	{
		return false;
	}

	Node* p = head->m_next;
	for (int i = 0; i < pos; i++)
	{
		p = p->m_next;
	}
	// Adjust the previous node's and the next node's pointer to point to each other
	p->m_prev->m_next = p->m_next;
	p->m_next->m_prev = p->m_prev;
	delete p; // Delete the node

	m_size--; // Decrement m_size since we got rid of an item in the Sequence
	return true;
}

int Sequence::remove(const ItemType& value)
{
	int count = 0; // Need to keep track of how many items we get rid of

	Node* p = head->m_next;
	while (p != head)
	{
		if (p->m_item == value) // Check if the pointer's node's m_item is the value we are looking for
		{
			Node* pToRemove = p;
			p = p->m_next;
			// Adjust the previous node's and the next node's pointers to point to each other
			pToRemove->m_prev->m_next = pToRemove->m_next;
			pToRemove->m_next->m_prev = pToRemove->m_prev;
			delete pToRemove; // Delete the node
			m_size--; // Decrement since we got rid of a node
			count++; // Increment the count
		}
		else
		{
			p = p->m_next;
		}
	}

	return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= size())
	{
		return false;
	}

	Node* p = head->m_next;
	for (int i = 0; i < pos; i++)
	{
		p = p->m_next;
	}
	value = p->m_item;

	return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos >= size())
	{
		return false;
	}

	Node* p = head->m_next;
	for (int i = 0; i < pos; i++)
	{
		p = p->m_next;
	}
	p->m_item = value;

	return true;
}

int Sequence::find(const ItemType& value) const
{
	Node* p = head->m_next;

	for (int i = 0; i < m_size; i++) // Loop through each item in the Sequence
	{
		if (p->m_item == value)
		{
			return i;
		}
		p = p->m_next; // If the index is not where the item is, move the pointer to the next item
	}

	return -1;
}

void Sequence::dump() const // FOR DEBUGGING PURPOSES 
{
	cerr << "Size: " << m_size << endl;

	cerr << "Sequence: ";
	Node* p = head->m_next;
	for (; p != head; p = p->m_next)
	{
		cerr << p->m_item << " ";
	}
	cerr << endl;
}

void Sequence::swap(Sequence& other)
{
	Node* tempHead = head;
	head = other.head;
	other.head = tempHead;

	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (seq2.size() == 0)
	{
		return -1;
	}

	for (int i = 0; i <= seq1.size() - seq2.size(); i++) // If the remaining length of seq1 is not enough to match seq2, there's no need to check further
	{
		bool match = true;
		for (int j = 0; j < seq2.size(); j++) // Look through each item in sequence
		{
			ItemType value1;
			ItemType value2;
			seq1.get(i + j, value1); // i is the index of the current element in seq2, j is the current index in seq1
			seq2.get(j, value2);
			if (value1 != value2) {
				match = false;
				break;
			}
		}
		if (match) {
			return i;
		}
	}

	return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence tempSeq; // To prevent issues that arise from aliasing

	for (int i = 0; i < seq2.size(); i++)
	{
		ItemType value;
		seq2.get(i, value);
		tempSeq.insert(0, value); // Copy values in seq2 in reverse order into tempSeq
	}
	for (int i = 0; i < seq1.size(); i++)
	{
		ItemType value;
		seq1.get(i, value);
		tempSeq.insert(0, value); // Copy values in seq1 in reverse order into tempSeq
	}

	result = tempSeq; // Copy the values in tempSeq into result
}