// FILE: hashNode_template.h


#include <cassert>    
#include <cstdlib>    

template <class Item>
size_t list_length(hashNode<Item>* head_ptr)
{
	hashNode<Item> *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link)
		answer++;

	return answer;
}

template <class Item>
void list_head_insert(hashNode<Item>*& head_ptr, const Item& new_item)
{
	hashNode<Item> *insert_ptr;

	insert_ptr = new hashNode<Item>;
	insert_ptr->data = new_item;
	insert_ptr->link = head_ptr;
	head_ptr = insert_ptr;
}

template <class Item>
void list_insert(hashNode<Item>* previous_ptr, const Item& new_item)
{
	hashNode<Item> *insert_ptr;

	insert_ptr = new hashNode<Item>;
	insert_ptr->data = new_item;
	insert_ptr->link = previous_ptr->link;
	previous_ptr->link = insert_ptr;
}

template <class Item>
hashNode<Item>* list_search(hashNode<Item>* head_ptr, const Item& target)
{
	hashNode<Item> *cursor;

	for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link)
		if (cursor->data == target)
			return cursor;

	return nullptr;
}

template <class Item, class SizeType>
hashNode<Item>* list_locate(hashNode<Item>* head_ptr, SizeType position)
{
	hashNode<Item> *cursor;
	size_t i;

	assert(position > 0);

	cursor = head_ptr;
	for (i = 1; (i != position) && (cursor != nullptr); i++)
		cursor = cursor->link;
	return cursor;
}

template <class Item>
void list_head_remove(hashNode<Item>*& head_ptr)
{
	hashNode<Item> *remove_ptr;

	remove_ptr = head_ptr;
	head_ptr = head_ptr->link;
	delete remove_ptr;
}

template <class Item>
void list_remove(hashNode<Item>* previous_ptr)
{
	hashNode<Item> *remove_ptr;

	remove_ptr = previous_ptr->link;
	previous_ptr->link = remove_ptr->link;
	delete remove_ptr;
}

template <class Item>
void list_clear(hashNode<Item>*& head_ptr)
{
	while (head_ptr != nullptr)
		list_head_remove(head_ptr);
}

template <class Item>
void list_copy
(hashNode<Item>* source_ptr, hashNode<Item>*& head_ptr, hashNode<Item>*& tail_ptr)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;

	// Handle the case of the empty list
	if (source_ptr == nullptr)
		return;

	// Make the head node for the newly created list, and put data in it
	list_head_insert(head_ptr, source_ptr->data);
	tail_ptr = head_ptr;

	// Copy the rest of the nodes one at a time, adding at the tail of new list
	for (source_ptr = source_ptr->link; source_ptr != nullptr; source_ptr = source_ptr->link)
	{
		list_insert(tail_ptr, source_ptr->data);
		tail_ptr = tail_ptr->link;
	}
}

template <class Item>
void list_piece
(hashNode<Item>* start_ptr, hashNode<Item>* end_ptr, hashNode<Item>*& head_ptr, hashNode<Item>*& tail_ptr)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;

	// Handle the case of the empty list
	if (start_ptr == nullptr)
		return;

	// Make the head node for the newly created list, and put data in it
	list_head_insert(head_ptr, start_ptr->data);
	tail_ptr = head_ptr;
	if (start_ptr == end_ptr)
		return;

	// Copy the rest of the nodes one at a time, adding at the tail of new list
	for (start_ptr = start_ptr->link; start_ptr != nullptr; start_ptr = start_ptr->link)
	{
		list_insert(tail_ptr, start_ptr->data);
		tail_ptr = tail_ptr->link;
		if (start_ptr == end_ptr)
			return;
	}
}