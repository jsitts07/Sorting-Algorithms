// FILE: selectionsort.cxx

#include <algorithm>  
#include <cstdlib>    
#include <iostream>   
using namespace std;

// PROTOTYPE of the selectionsort function
void selectionsort(int data[ ], size_t n);


int main( )
{
    const char BLANK = ' ';
    const size_t ARRAY_SIZE = 10;  // Number of elements in the array to be sorted
    int data[ARRAY_SIZE];          // Array of integers to be sorted
    int user_input;                // Number typed by the user
    size_t number_of_elements;     // How much of the array is used
    size_t i;                      // Array index

	//Prompt user to input
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
    selectionsort(data, number_of_elements);
    cout << "In sorted order, your numbers are: "<< endl;
    for (i = 0; i < number_of_elements; i++)
        cout << data[i] << BLANK << BLANK;
    cout << endl;

    return EXIT_SUCCESS;
}

void selectionsort(int data[ ], size_t n)
{
    size_t i, j, index_of_largest;
    int largest;

    if (n == 0)
        return; // No work for an empty array.
        
    for (i = n-1; i > 0; --i)
    {
        largest = data[0];
        index_of_largest = 0;
        for (j = 1; j <= i; ++j)
        {
            if (data[j] > largest)
            {
                largest = data[j];
                index_of_largest = j;
            }
        }
        swap(data[i], data[index_of_largest]);
    }
}
