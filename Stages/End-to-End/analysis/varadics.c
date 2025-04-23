#include <stdarg.h> // Required for va_list, va_start, va_arg, va_end

int sum(int count, ...)
{                 // 'count' is a fixed argument, '...' indicates variadic arguments
    va_list args; // Declare a va_list type variable
    int total = 0;

    va_start(args, count); // Initialize args to store all arguments after 'count'

    for (int i = 0; i < count; i++)
    {
        total += va_arg(args, int); // Retrieve the next argument as 'int'
    }

    va_end(args); // Clean up the va_list

    return total;
}

int main()
{
    int s1 = sum(3, 1, 2, 3);
    int s2 = sum(5, 1, 2, 3, 4, 5);
    return 0;
}