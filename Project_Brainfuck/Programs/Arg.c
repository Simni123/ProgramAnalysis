#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv) 
{
    printf("size of argument: %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("arg %d: %d \n", i, atoi(argv[i]));
    }
    
}
