#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#define MAX_LINE_LENGTH 256
#define MAX_STAGES      20

#define MAX_RED_CUBES   12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES  14

#define MAX_COLOR_VAL(color)      \
    (color == 'r' ? MAX_RED_CUBES \
                  : (color == 'g' ? MAX_GREEN_CUBES : MAX_BLUE_CUBES))

int
is_valid (char *stage)
{
    int   number;
    char *data = strtok(stage, " ");         // Get first number
    while ((number = atoi(data)) &&          // Parse number
           (data = strtok(NULL, " ")) &&     // Get color data
           MAX_COLOR_VAL(*data) >= number && // Check color value in range
           (data = strtok(NULL, " "))        // Check if there is next number
    )
    {
        ;
    }
    return data == NULL; // Valid if all tokens where read
}

int
get_game_score (char *line)
{
    line += 5; // Remove 'Game '

    char *id  = line;
    char *ptr = line;
    char *stages[MAX_STAGES]; // Pointers to every stage
    int   s_count = 0;        // Number of stages

    while (*(++ptr))
    {
        if (*ptr == ':' || *ptr == ';')
        {
            *ptr = 0;

            // +1 for the 0 and +1 for the initial space
            stages[s_count++] = ptr + 2;
        }
        *ptr = *ptr == ',' ? ' ' : *ptr; // Convert ',' to spaces
    }

    while (--s_count >= 0 && is_valid(stages[s_count]))
    {
        ;
    }
    return s_count == -1 ? atoi(id) : 0;
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
        sum += get_game_score(line);
    }

    // Print result
    printf("%d\n\n", sum);

    // Close the file and return
    close(file);
    return 0;
}