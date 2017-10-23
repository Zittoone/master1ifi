#include <unistd.h>
#include <stdio.h>

int main(void){
    int pagesize = getpagesize();
    printf("Page size is %d\n", pagesize);

    return 0;
}
