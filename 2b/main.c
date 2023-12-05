#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

#define MAX_LINE_LENGTH 256

int
get_color_id (char character)
{
    if (character == 'r')
    {
        return 0;
    }
    if (character == 'g')
    {
        return 1;
    }
    if (character == 'b')
    {
        return 2;
    }
    else
    {
        printf("[ERROR] Wrong group_id %c\n", character);
        exit(1);
    }
}

int
get_game_score (char *line)
{
    char *header  = strtok(line, ":");
    char *content = strtok(NULL, ":");
    int   game_id = atoi(header + 5);

    int color_count[] = { 0, 0, 0 }; // RGB

    printf("[%d]\nGAME:%s", game_id, content);
    char *stage = content;

    while ((stage = strtok_r(content, ";", &content)))
    {
        printf("> %s\n", stage);
        char *color_data;
        char *rest = stage;

        while ((color_data = strtok_r(rest, ",", &rest)))
        {
            printf("   -%s\n", color_data);

            int   count    = atoi(strtok(color_data, " "));
            char *group_id = strtok(NULL, " ");
            int   color_id = get_color_id(*group_id);

            if (color_count[color_id] < count)
            {
                color_count[color_id] = count;
            }
        }
    }
    return color_count[0] * color_count[1] * color_count[2];
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