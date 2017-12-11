// FILE: insert.cxx

#include <algorithm>  
#include <cstdlib>    
#include <iostream>   
using namespace std;

// PROTOTYPE of the function used in this test program:
void insertionsort(int data[ ], size_t n);

int main( )
{
    const char BLANK = ' ';
    const size_t ARRAY_SIZE = 10;  // Number of elements in the array to be sorted
    int data[ARRAY_SIZE];          // Array of integers to be sorted
    int user_input;                // Number typed by the user
    size_t number_of_elements;     // How much of the array is used
    size_t i;                      // Array index

    cout << "Please type up to " << ARRAY_SIZE << " positive integers. ";
    cout << "Indicate the list's end with a zero." << endl;

    // Read the input numbers.
    number_of_elements = 0;
    cin >> user_input;
    while ((user_input != 0) && (number_of_elements < ARRAY_SIZE))
    {
        data[number_of_elements] = user_input;
        number_of_elements++;
        cin >> user_input;
    }

    // Sort the numbers, and print the result with two blanks after each number.
    insertionsort(data, number_of_elements);
    cout << "In sorted order, your numbers are: "<< endl;
    for (i = 0; i < number_of_elements; i++)
        cout << data[i] << BLANK << BLANK;
    cout << endl;

    return EXIT_SUCCESS;
}

void insertionsort(int data[ ], size_t size)
{
    size_t i, scan;
    int unsorted;

    if (size == 0)
        return; // No work for an empty array.

	// find proper location for unsorted value
	for (i = 1; i < size; ++i) 
	{
		unsorted = data[i];
		scan = i;
		// move elements over in sorted subset
		while (scan > 0 && data[scan - 1] > unsorted) 
		{
			data[scan] = data[scan - 1];
			scan--;
		}
		// insert unsorted in proper location
		data[scan] = unsorted;
	}
}
