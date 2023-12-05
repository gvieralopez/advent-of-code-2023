#include <stdio.h>
#include <stdlib.h>

FILE *
open (const char *path, const char *mode)
{
    printf("[INFO] Opening File %s (%s)\n", path, mode);
    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        printf("[ERROR] Failed to open file %s\n", path);
        exit(1);
    }
    return file;
}

void
close (FILE *file)
{
    if (fclose(file) != 0)
    {
        printf("[ERROR] Error while closing the file\n");
        exit(1);
    }
}
