// Pointers

// Rules written in obsidian notes - "The pointer & const confusion"

const int long *ptr1;

int *const ptr2;

int *ptr3;

const int *const ptr4;

// const int*  const const *const *ptr5; // This throws a warning

const int *ptr71;
const int *ptr19; // Both are same [the parser removes the space]

// const int const *ptr2; // This also throws a warning
// General Rule - a const can only appear before the type specifier and after the pointer
// The const just after the pointer get's binded to it
// and the const just before int get's binded to int-data type

int *const *ptr23;
int **const ptr41; // both are not-same

int *volatile const *ptr53;

// ptr3 is a pointer to a constant pointer to an int
// Rule the last * is the top-level pointer the ptr itself
// and as we move left the higherlevel pointer appears.

// Decide which the int-data or the top-pointer sit's at level0 in multi-level pointer

// Easy Rule - Read from right to left

int **ptr5;

int *ptr6[10]; // Array of pointers

int (*ptr7)[10]; // Pointer to an array(arrays are itself pointers) [Thus a 2-dim pointer]

int (*functionPtr)(int, int); // Pointer to a function

int main()
{
    return 0;
}