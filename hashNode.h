// FILE: hashNode.h

#ifndef HASH_NODE_H
#define HASH_NODE_H
#include <cstdlib> 

template <class Item>
struct hashNode
{
	Item data;
	hashNode *link;
};

// FUNCTIONS for the linked list toolkit
template <class Item>
size_t list_length(hashNode<Item>* head_ptr);

template <class Item>
void list_head_insert(hashNode<Item>*& head_ptr, const Item& entry);

template <class Item>
void list_insert(hashNode<Item>* previous_ptr, const Item& entry);

template <class Item>
hashNode<Item>* list_search(hashNode<Item>* head_ptr, const Item& target);

template <class Item, class SizeType>
hashNode<Item>* list_locate(hashNode<Item>* head_ptr, SizeType position);

template <class Item>
void list_head_remove(hashNode<Item>*& head_ptr);

template <class Item>
void list_remove(hashNode<Item>* previous_ptr);

template <class Item>
void list_clear(hashNode<Item>*& head_ptr);

template <class Item>
void list_copy
(hashNode<Item>* source_ptr, hashNode<Item>*& head_ptr, hashNode<Item>*& tail_ptr);

template <class Item>
void list_piece
(hashNode<Item>*  source_ptr, hashNode<Item>*  end_ptr,
	hashNode<Item>*& head_ptr, hashNode<Item>*& tail_ptr);

#include "hashNode_template.h"  // Include the implementation
#endif
