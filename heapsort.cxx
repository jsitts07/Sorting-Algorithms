// FILE: heapsort.cxx


#include <algorithm>   
#include <cstdlib>     
#include <iostream>    
using namespace std;

// PROTOTYPES of the functions used in this test program:
void heapsort(int data[ ], size_t n);

size_t parent(size_t k);

size_t left_child(size_t k);


size_t right_child(size_t k);


void make_heap(int data[ ], size_t n);


void reheapify_down(int data[ ], size_t n);



int main( )
{
    const char BLANK = ' ';
    const size_t ARRAY_SIZE = 10;  
    int data[ARRAY_SIZE];          
    int user_input;                
    size_t number_of_elements;     
    size_t i;                      

    cout << "Please type up to " << ARRAY_SIZE << " positive integers.";
    cout << "Indicate the list's end with a zero." << endl;

    // Read the input numbers
    number_of_elements = 0;
    cin >> user_input;
    while ((user_input != 0) && (number_of_elements < ARRAY_SIZE))
    {
        data[number_of_elements] = user_input;
        ++number_of_elements;
        cin >> user_input;
    }

    // Sort the numbers and print the result with two blanks after each number
    heapsort(data, number_of_elements);
    cout << "In sorted order, your numbers are: " << endl;
    for (i = 0; i < number_of_elements; ++i)
        cout << data[i] << BLANK << BLANK;
    cout << endl;

    return EXIT_SUCCESS;
}

void heapsort(int data[ ], size_t n)
{
    size_t unsorted;

    make_heap(data, n);

    unsorted = n;

    while (unsorted > 1)
    {
        --unsorted;
        swap(data[0], data[unsorted]);
        reheapify_down(data, unsorted);
    }
}

size_t parent(size_t k)
{
    return (k-1)/2;
}

size_t left_child(size_t k)
{
    return 2*k + 1;
}

size_t right_child(size_t k)
{
    return 2*k + 2;
}

void make_heap(int data[ ], size_t n)
{
    size_t i;  // Index of next element to be added to heap
    size_t k;  // Index of new element as it is being pushed upward through the heap

    for (i = 1; i < n; ++i)
    {
        k = i;
        while ((k > 0) && (data[k] > data[parent(k)]))
        {
            swap(data[k], data[parent(k)]);
            k = parent(k);
        }
    }
}

void reheapify_down(int data[ ], size_t n)
{
    size_t current;          // Index of the node that's moving down
    size_t big_child_index;  // Index of the larger child of the node that's moving down
    bool heap_ok = false;    // Will change to true when the heap becomes correct

    current = 0;

    // Note: The loop keeps going while the heap is not okay, and while the current node has
    // at least a left child. The test to see whether the current node has a left child is
    // left_child(current) < n.
    while ((!heap_ok) && (left_child(current) < n))
    {
        // Compute the index of the larger child:
        if (right_child(current) >= n)
            // There is no right child, so left child must be largest
            big_child_index = left_child(current);
        else if (data[left_child(current)] > data[right_child(current)])
            // The left child is the bigger of the two children
            big_child_index = left_child(current);
        else
            // The right child is the bigger of the two children
            big_child_index = right_child(current);

        // Check whether the larger child is bigger than the current node. If so, then swap
        // the current node with its bigger child and continue; otherwise we are finished.
        if (data[current] < data[big_child_index])
        {
            swap(data[current], data[big_child_index]);
            current = big_child_index;
        }
        else
            heap_ok = true;
    }
}

