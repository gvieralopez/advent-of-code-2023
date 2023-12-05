#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#define MAX_LINE_LENGTH 256
#define char2int(c)     c - '0'

int
points_to_digit (char *char_ptr)
{
    if (isdigit(*char_ptr))
    {
        return char2int(*char_ptr);
    }
    return 0;
}

int
process_line (char *line)
{
    int first_digit = 0, last_digit = 0;
    int current_digit = 0;

    // Read first and last digits from line
    for (char *ptr = line; *ptr != 0; ptr++)
    {
        if ((current_digit = points_to_digit(ptr)))
        {
            first_digit = first_digit ? first_digit : current_digit;
            last_digit  = current_digit;
        }
    }

    // Check that the line contains at least one digit
    if (!first_digit)
    {
        printf("[ERROR] Found line with no digits on it:\n%s\n\n", line);
        exit(1);
    }
    return (first_digit * 10) + last_digit;
}

int
main ()
{
    // Reads the input file
    const char *file_path = "input.txt";
    FILE       *file      = open(file_path, "r");

    // Iterates over file lines
    char line[MAX_LINE_LENGTH];
    int  sum = 0;
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        sum += process_line(line);
    }

    // Print result
    printf("%d\n\n", sum);

    // Close the file and return
    close(file);
    return 0;
}