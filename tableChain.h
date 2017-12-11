// FILE: tableChain.h

#ifndef tableChain_H
#define tableChain_H
#include <cstdlib>    
#include "hashNode.h"    

template <class RecordType>
class tableChain
{
public:
	// MEMBER CONSTANT 
	static const std::size_t TABLE_SIZE = 811;
	
	// CONSTRUCTORS AND DESTRUCTOR
	tableChain();
	tableChain(const tableChain& source);
	~tableChain();
	
	// MODIFICATION MEMBER FUNCTIONS
	void insert(const RecordType& entry);
	void remove(int key);
	void operator =(const tableChain& source);
	
	// CONSTANT MEMBER FUNCTIONS
	void find(int key, bool& found, RecordType& result) const;
	bool is_present(int key) const;
	std::size_t size() const { return total_records; }
	
	//***DISPLAY MEMBER FUNCTION*********
	void display_all(); 
private:
	hashNode<RecordType> *data[TABLE_SIZE];
	std::size_t total_records;
	// HELPER MEMBER FUNCTION
	std::size_t hash(int key) const;
	hashNode<RecordType>* find_node(int key) const;
};

#include "tableChain_template.h" // Include the implementation

#endif
