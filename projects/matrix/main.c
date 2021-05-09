#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *fptr;
    fptr = fopen("/proc/meminfo", "r");
    srand(fptr);

    for (int i = 0; i < 2000062; i++) {
        int n = rand() % 2;
        if(n)
            printf("0 ");
        else
            printf("1 ");
    }
    printf("\n\n");
}
