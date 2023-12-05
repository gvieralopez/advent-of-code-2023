#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils.h"

#define MAX_LINE_LENGTH 250
#define TO_DIGIT(c)     (c - '0')

int
is_symbol (char *c_ptr, int i)
{
    if (!c_ptr)
    {
        return 0;
    }
    char c = *(c_ptr + i);
    return !isdigit(c) && (c != '.');
}

int
symbol_in_col (int i, char *curr, char *prev, char *next)
{
    return is_symbol(curr, i) + is_symbol(prev, i) + is_symbol(next, i);
}

int
sum_parts_in_line (char *curr_line, char *prev_line, char *next_line)
{
    int is_reading_num = 0;
    int is_part_num    = 0;
    int current_num    = 0;
    int symbol_last    = 0;
    int symbol_curr    = 0;
    int part_sum       = 0;

    for (int i = 0; *(curr_line + i); i++)
    {
        symbol_curr = symbol_in_col(i, curr_line, prev_line, next_line);

        char c = *(curr_line + i);
        if (c == '\n')
        {
            if (is_reading_num && is_part_num)
            {
                part_sum += current_num;
            }
            break;
        }
        int is_digit = isdigit(c);
        if (is_digit)
        {
            if (!is_reading_num)
            {
                is_reading_num = 1;
                is_part_num += symbol_last;
            }
            is_part_num += symbol_curr;
            current_num *= 10;
            current_num += TO_DIGIT(c);
        }
        else if (is_reading_num)
        {
            is_part_num += symbol_curr;

            if (is_part_num)
            {
                part_sum += current_num;
            }
            is_reading_num = 0;
            current_num    = 0;
            is_part_num    = 0;
        }
        symbol_last = symbol_curr;
    }

    return part_sum;
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

// int
// is_symbol (char c)
// {
//     return !isdigit(c) && (c != '.');
// }

// int
// are_symbols (int column_idx, char *curr_line, char *prev_line, char
// *next_line)
// {
//     int symbols_in_prev = prev_line ? is_symbol(*(prev_line + column_idx)) :
//     0; int symbols_in_curr = is_symbol(*(curr_line + column_idx)); int
//     symbols_in_next = next_line ? is_symbol(*(next_line + column_idx)) : 0;
//     return symbols_in_prev + symbols_in_curr + symbols_in_next;
// }

// int
// sum_parts_in_line (char *curr_line, char *prev_line, char *next_line)
// {
//     char active_tracking = 0; // Whether or not we are already reading a
//     number int  is_part_number  = 0; // Whether or not we have found
//     neighbors symbols int  partial_sum     = 0; // Sum of the valid number
//     int  current_number  = 0; // Current number being read
//     int  symbols_in_column      = 0; // Are symbols in current column?
//     int  symbols_in_prev_column = 0; // Are symbols in previous column?

//     for (int i = 0; *(curr_line + i); i++)
//     {
//         symbols_in_column = are_symbols(i, curr_line, prev_line, next_line);
//         char current_char = *(curr_line + i);
//         if (isdigit(current_char))
//         {
//             if (!active_tracking)
//             {
//                 active_tracking = 1;
//                 is_part_number += symbols_in_prev_column;
//             }
//             current_number *= 10;
//             current_number += (current_char - '0');
//             is_part_number += symbols_in_column;
//         }
//         else if (active_tracking)
//         {
//             is_part_number += symbols_in_column;
//             printf("Found: %d (%d)\n", current_number, is_part_number);
//             if (is_part_number)
//             {
//                 partial_sum += current_number;
//             }
//             current_number  = 0;
//             active_tracking = 0;
//             is_part_number  = 0;
//         }
//         symbols_in_prev_column = symbols_in_column;
//     }
//     if (active_tracking)
//     {
//         printf("Found: %d (%d)\n", current_number, is_part_number);
//         if (is_part_number)
//         {
//             partial_sum += current_number;
//         }
//     }
//     return partial_sum;
// }