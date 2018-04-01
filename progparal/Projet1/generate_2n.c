#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define max_number 45000
#define minimum_number -45000


int main(int argc, char *argv[])
{

	/* args check */
	if(argc != 2){
		fprintf(stderr, "Usage : generate_2c <number>\n");
		exit(EXIT_FAILURE);
	}

    srand(time(NULL));

    int iterations = pow(2, atoi(argv[1]));
    for(int i = 0; i < iterations - 1; i++){
        printf("-2 ");
    }

    printf("-1\n");

}