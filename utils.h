#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

FILE *open(const char *path, const char *mode);
void close(FILE *file);

#endif // UTILS_H