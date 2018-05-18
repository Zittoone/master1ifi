#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]) {

    int N = atoi(argv[1]);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N - 1; j++) {
            printf("%d ", 1);
        }
        printf("%d\n", 1);
    }

}