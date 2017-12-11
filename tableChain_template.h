// FILE: tableChain_template.h


#include <cassert> 
#include <cstdlib> 
#include "hashNode.h"  

template <class RecordType>
tableChain<RecordType>::tableChain()
{
	size_t i;

	total_records = 0;
	for (i = 0; i < TABLE_SIZE; i++)
		data[i] = nullptr;
}

template <class RecordType>
tableChain<RecordType>::tableChain(const tableChain<RecordType>& source)
{
	size_t i;
	hashNode<RecordType>* tail_ptr; // Needed for list_copy

	for (i = 0; i < TABLE_SIZE; i++)
		list_copy(source.data[i], data[i], tail_ptr);
	total_records = source.total_records;
}

template <class RecordType>
tableChain<RecordType>::~tableChain()
// used: hashNode.h
{
	size_t i;

	total_records = 0;
	for (i = 0; i < TABLE_SIZE; i++)
		list_clear(data[i]);
}

template <class RecordType>
void tableChain<RecordType>::insert(const RecordType& entry)
// used: hashNode.h
{
	hashNode<RecordType>* cursor; // set to point to existing hashNode with given key

	assert(entry.key >= 0);

	// Set cursor to point to existing hashNode with given key (if there is one)
	cursor = find_node(entry.key);
	if (cursor != nullptr)
	{   // Add in existing spot
		cursor->data = entry;
	}
	else
	{   // Add in a new spot
		list_head_insert(data[hash(entry.key)], entry);
		total_records++;
	}
}

template <class RecordType>
void tableChain<RecordType>::remove(int key)
// used: hashNode.h
{
	hashNode<RecordType> *cursor = data[hash(key)];
	hashNode<RecordType> *prev = nullptr;

	// search through and find node that is being requested for deletion

	bool located = false;

	while (cursor != nullptr)
	{
		//search for node that the key is stored in
		if (cursor->data.key == key)
		{
			//If the node is found located is set to true 
			located = true;
			break;
		}
		prev = cursor;
		cursor = cursor->link;
	}
	//The node is found and it is not the head pointer
	if (located == true && prev != nullptr)
	{
		//Call the list_remove from the hashNode_template.h file to delete the node
		list_remove(prev);
		total_records--;
	}
	//The node is found and it is the head pointer
	else if (located == true && prev == nullptr)
	{
		int location;
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (cursor == data[i])
				location = i;
		}

			prev = cursor;
			list_head_remove(prev);
			data[location] = nullptr;
			total_records--;
	}
}
		

template <class RecordType>
void tableChain<RecordType>::operator =(const tableChain<RecordType>& source)
// used: hashNode.h
{
	size_t i;
	hashNode<RecordType>* tail_ptr; // Needed for list_copy

	if (this == &source)
		return; // Avoid self-assignment

	for (i = 0; i < TABLE_SIZE; i++)
	{
		list_clear(data[i]);
		list_copy(source.data[i], data[i], tail_ptr);
	}
	total_records = source.total_records;
}

template <class RecordType>
bool tableChain<RecordType>::is_present(int key) const
{
	assert(key >= 0);

	return (find_node(key) != nullptr);
}

template <class RecordType>
void tableChain<RecordType>::find(int key, bool& found, RecordType& result) const
{
	hashNode<RecordType> *cursor;

	cursor = find_node(key);
	found = (cursor != nullptr);
	if (found)
		result = cursor->data;
}

template <class RecordType>
size_t tableChain<RecordType>::hash(int key) const
{
	return (key % TABLE_SIZE);
}

template <class RecordType>
hashNode<RecordType>* tableChain<RecordType>::find_node(int key) const
{
	hashNode<RecordType>* cursor;

	cursor = data[hash(key)];
	while ((cursor != nullptr) && ((cursor->data).key != key))
		cursor = cursor->link;

	return cursor;
}

//***DISPLAY MEMBER FUNCTION****
template <class RecordType>
void tableChain<RecordType>::display_all()
{
	cout << "\n\n***DISPLAY ALL TABLE ENTRIES***" << endl;
	
	//loop through each array element
	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		//if an element is empty
		if (data[i] != nullptr)
		{
			cout << "Index = " << i << endl;
			//Display all values in the location 
			for (hashNode<RecordType>* cursor = data[i]; cursor != nullptr; cursor = cursor->link)
			{
				//***********JS added if statement to check for nullptr and check data[location], set in the the remove function*************
				if (cursor != nullptr)
					cout << '\t' << cursor->data << endl;
			}
		}
		
	}
}


//************SAMPLE OUTPUT*******************
//I have initialized an empty table.Each record in the table
//has an integer key and a real number as data.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 33.2
//33.2 has been read.
//Please enter a non - negative integer for a key : 4058
//4058 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 22.2
//22.2 has been read.
//Please enter a non - negative integer for a key : 2
//2 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 11.4
//11.4 has been read.
//Please enter a non - negative integer for a key : 1
//1 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 100
//100 has been read.
//Please enter a non - negative integer for a key : 811
//811 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 11.3
//11.3 has been read.
//Please enter a non - negative integer for a key : 1623
//1623 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 22.1
//22.1 has been read.
//Please enter a non - negative integer for a key : 2435
//2435 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 11.2
//11.2 has been read.
//Please enter a non - negative integer for a key : 3245
//3245 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 11.1
//11.1 has been read.
//Please enter a non - negative integer for a key : 5678
//5678 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : i
//Please enter a real number for a record's data: 33.1
//33.1 has been read.
//Please enter a non - negative integer for a key : 3
//3 has been read.
//The record has been inserted.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : s
//The table size is 9
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : d
//
//
//***DISPLAY ALL TABLE ENTRIES***
//Index = 0
//KEY : 811 DATA : 100
//	Index = 1
//	KEY : 5678 DATA : 11.1
//	KEY : 3245 DATA : 11.2
//	KEY : 1623 DATA : 11.3
//	KEY : 1 DATA : 11.4
//	Index = 2
//	KEY : 2435 DATA : 22.1
//	KEY : 2 DATA : 22.2
//	Index = 3
//	KEY : 3 DATA : 33.1
//	KEY : 4058 DATA : 33.2
//
//	The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : r
//Please enter a non - negative integer for a key : 3245
//3245 has been read.
//Remove has been called with that key.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : s
//The table size is 8
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : d
//
//
//***DISPLAY ALL TABLE ENTRIES***
//Index = 0
//KEY : 811 DATA : 100
//	Index = 1
//	KEY : 5678 DATA : 11.1
//	KEY : 1623 DATA : 11.3
//	KEY : 1 DATA : 11.4
//	Index = 2
//	KEY : 2435 DATA : 22.1
//	KEY : 2 DATA : 22.2
//	Index = 3
//	KEY : 3 DATA : 33.1
//	KEY : 4058 DATA : 33.2
//
//	The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : r
//Please enter a non - negative integer for a key : 2
//2 has been read.
//Remove has been called with that key.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : s
//The table size is 7
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : d
//
//
//***DISPLAY ALL TABLE ENTRIES***
//Index = 0
//KEY : 811 DATA : 100
//	Index = 1
//	KEY : 5678 DATA : 11.1
//	KEY : 1623 DATA : 11.3
//	KEY : 1 DATA : 11.4
//	Index = 2
//	KEY : 2435 DATA : 22.1
//	Index = 3
//	KEY : 3 DATA : 33.1
//	KEY : 4058 DATA : 33.2
//
//	The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : r
//Please enter a non - negative integer for a key : 3
//3 has been read.
//Remove has been called with that key.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : s
//The table size is 6
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : d
//
//
//***DISPLAY ALL TABLE ENTRIES***
//Index = 0
//KEY : 811 DATA : 100
//	Index = 1
//	KEY : 5678 DATA : 11.1
//	KEY : 1623 DATA : 11.3
//	KEY : 1 DATA : 11.4
//	Index = 2
//	KEY : 2435 DATA : 22.1
//
//	The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : r
//Please enter a non - negative integer for a key : 811
//811 has been read.
//Remove has been called with that key.
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : s
//The table size is 5
//
//The following choices are available :
//S   Print the result from the size() function
//I   Insert a new record with the insert(...) function
//R   Remove a record with the remove(...) function
//? Check whether a particular key is present
//F   Find the data associated with a specified key
//D   Display all entries in hash table
//Q   Quit this test program
//Enter choice : d
//
//
//***DISPLAY ALL TABLE ENTRIES***
//Index = 1
//KEY : 5678 DATA : 11.1
//	KEY : 1623 DATA : 11.3
//	KEY : 1 DATA : 11.4
//	Index = 2
//	KEY : 2435 DATA : 22.1