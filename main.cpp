#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
    int id;
    char name[10];
};

typedef struct record new_record;

int main() {
    printf("Size of new_record: %zu bytes\n", sizeof(new_record));
    return 0;
}
