#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils.h"

#define MAX_LINE_LENGTH 250

int
is_symbol (char c)
{
    return !isdigit(c) && (c != '.');
}

int
are_symbols (int column_idx, char *curr_line, char *prev_line, char *next_line)
{
    int symbols_in_prev = prev_line ? is_symbol(*(prev_line + column_idx)) : 0;
    int symbols_in_curr = is_symbol(*(curr_line + column_idx));
    int symbols_in_next = next_line ? is_symbol(*(next_line + column_idx)) : 0;
    return symbols_in_prev + symbols_in_curr + symbols_in_next;
}

int
sum_parts_in_line (char *curr_line, char *prev_line, char *next_line)
{
    char active_tracking = 0; // Whether or not we are already reading a number
    int  is_part_number  = 0; // Whether or not we have found neighbors symbols
    int  partial_sum     = 0; // Sum of the valid number found
    int  current_number  = 0; // Current number being read
    int  symbols_in_column      = 0; // Are symbols in current column?
    int  symbols_in_prev_column = 0; // Are symbols in previous column?

    for (int i = 0; *(curr_line + i); i++)
    {
        symbols_in_column = are_symbols(i, curr_line, prev_line, next_line);
        char current_char = *(curr_line + i);
        if (isdigit(current_char))
        {
            if (!active_tracking)
            {
                active_tracking = 1;
                is_part_number += symbols_in_prev_column;
            }
            current_number *= 10;
            current_number += (current_char - '0');
            is_part_number += symbols_in_column;
        }
        else if (active_tracking)
        {
            is_part_number += symbols_in_column;
            printf("Found: %d (%d)\n", current_number, is_part_number);
            if (is_part_number)
            {
                partial_sum += current_number;
            }
            current_number  = 0;
            active_tracking = 0;
            is_part_number  = 0;
        }
        symbols_in_prev_column = symbols_in_column;
    }
    if (active_tracking)
    {
        printf("Found: %d (%d)\n", current_number, is_part_number);
        if (is_part_number)
        {
            partial_sum += current_number;
        }
    }
    return partial_sum;
}

int
sum_parts_in_line (char *curr_line, char *prev_line, char *next_line)
{
}

int
main ()
{
    // Reads the input file
    const char *file_path = "input.txt";
    FILE       *file      = open(file_path, "r");

    // Iterates over file lines
    char  lines[3][MAX_LINE_LENGTH];
    char *prev_line = NULL;
    char *curr_line = lines[1];
    char *next_line = lines[2];
    int   sum       = 0;

    fgets(curr_line, MAX_LINE_LENGTH, file);

    do
    {
        /* Get the next line (or NULL if it's the end of the file) */
        next_line = fgets(next_line, MAX_LINE_LENGTH, file);
        sum += sum_parts_in_line(curr_line, prev_line, next_line);

        /*Update pointers to make room for the next line*/
        char *temp = prev_line ? prev_line : lines[0];
        prev_line  = curr_line;
        curr_line  = next_line;
        next_line  = temp;
    } while (curr_line != NULL);

    // Print result
    printf("%d\n\n", sum);

    // Close the file and return
    close(file);
    return 0;
}