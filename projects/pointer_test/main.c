#include <stdio.h>
#include <string.h>

int main () {
    char* hello = "HELLO-WORLD";
    char storage[111];

    for (int i = 0; i < 11; ++i)
        printf("CHAR: %c | MEM_LOC: %p\n", hello[i], hello[i]);

    printf("UNALLOCATED MEMORY:\n");

    for (int i = 11; i < 111; ++i) {
        printf("CHAR: %c | MEM_LOC: %p\n",hello[i], hello[i]);
        strcat(storage, &hello[i]);
    }

    printf("\nSTORAGE: %s | MEM_LOC_S: %p\n", storage, *storage);
    return 0;
}
