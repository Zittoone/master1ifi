#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PREFIX 0
#define SUFFIX 1

#define DEBUG 0

#define max(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

struct Compare { long val; int index; };
#pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_in.val == omp_out.val ? omp_in.index < omp_out.index ? omp_in : omp_out : omp_out) initializer(omp_priv = {val: LONG_MIN, index: -1})

/*
omp_out = omp_in.val > omp_out.val ? omp_in
	: omp_in.val == omp_out.val ?
		omp_in.index < omp_out.index ? omp_in 
			: omp_out 
		: 
*/
/* Structures */
struct tablo
{
	long int *tab;
  	int size;
};

/* Headers */

void sum(struct tablo *, struct tablo *, int mode);
void montee_sum(struct tablo *, struct tablo *, int mode);
void descente_sum(struct tablo *, struct tablo *);
void final_sum(struct tablo *, struct tablo *);

void sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size);
void montee_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size);
void descente_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size);
void final_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size);

void maximum(struct tablo *, struct tablo *, int mode);
void montee_max(struct tablo *, struct tablo *, int mode);
void descente_max(struct tablo *, struct tablo *);
void final_max(struct tablo *, struct tablo *);

void maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size);
void montee_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size);
void descente_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size);
void final_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size);

void generateArray(struct tablo *, char*);
void printArray(struct tablo *);
struct tablo *allocateTablo(int);
void inverser_tablo(struct tablo *);

/*  */
int main(int argc, char *argv[])
{

	//omp_set_num_threads(8);
	/* args check */
	if(argc != 2){
		fprintf(stderr, "Usage : couvreur <file_name>\n");
		exit(EXIT_FAILURE);
	}

	/* file check */
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		fprintf(stderr, "The file \"%s\" doesn't exist.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* file reading */
	struct stat fi;
  	stat(argv[1], &fi);

	// int BLOCK_SIZE = fi.st_blksize;
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell (fp);
	rewind(fp);

	/*if(DEBUG)
	{
		printf("BLOCK_SIZE = %d octets\n", BLOCK_SIZE);
	}*/

	// char * buffer = malloc(sizeof(char) * BLOCK_SIZE); read block by block ?
	char * buffer = malloc(sizeof(char) * fileSize + 1);

	long result = fread (buffer,1,fileSize,fp);
  	if (result != fileSize) {
		fprintf(stderr, "Reading error.\n");
		exit(EXIT_FAILURE);
	}

	// ¯\_(ツ)_/¯
	buffer[fileSize] = '\0';


	/* close file */
	fclose(fp);

	/*
	 * 0. Création tableau initial
	 */
	struct tablo Q;
	generateArray(&Q, buffer);

	if(DEBUG)
	{
		printf("Tableau Q:\n");
		printArray(&Q);
	}

	/*
	 * 1. Calculer les sum-prefix de Q et les mettre dans un tableau PSUM
	 *
	 * 2. Calculer le sum-suffix de Q et les mettre dans un tableau SSUM
	 */
	struct tablo *PSUM = allocateTablo(Q.size);
	struct tablo *SSUM = allocateTablo(Q.size);

	/*
	sum(&Q, PSUM, PREFIX);
	sum(&Q, SSUM, SUFFIX);
	*/
sum_parallel(&Q, &Q, PSUM, SSUM, PREFIX, SUFFIX, Q.size);

	if(DEBUG)
	{
		printf("Tableau PSUM:\n");
		printArray(PSUM);
		printf("Tableau SSUM:\n");
		printArray(SSUM);
	}

	/*
	 * 3. Calculer le max-suffix de PSUM et le mettre dans SMAX
	 *
	 * 4. Calculer le max-prefix de SSUM et le mettre dans PMAX
	 */
	struct tablo *SMAX = allocateTablo(Q.size);
	struct tablo *PMAX = allocateTablo(Q.size);

	//#pragma omp parallel sections
	{
		//#pragma omp section
		{
			//maximum(PSUM, SMAX, SUFFIX);
		}
		//#pragma omp section
		{
			//maximum(SSUM, PMAX, PREFIX);
		}
	}
	maximum_parallel(PSUM, SSUM, SMAX, PMAX, SUFFIX, PREFIX, Q.size);

	if(DEBUG)
	{
		printf("Tableau SMAX:\n");
		printArray(SMAX);
		printf("Tableau PMAX:\n");
		printArray(PMAX);
	}

	/*
	 * 5. pour  1 <= i <= n faire en parallel
	 * 	1. Ms[i] = PMAX[i] - SSUM[i] + Q[i]
	 * 	2. Mp[i] = SMAX[i] - PSUM[i] + Q[i]
	 * 	3. M[i] = Ms[i] + Mp[i] - Q[i]
	 */

	struct tablo *M = allocateTablo(Q.size);

	#pragma omp parallel for
	for (int i = 0; i < Q.size; i++)
	{
		long Ms = PMAX->tab[i] - SSUM->tab[i] + Q.tab[i];
		long Mp = SMAX->tab[i] - PSUM->tab[i] + Q.tab[i];
		M->tab[i] = Ms + Mp - Q.tab[i];
	}

	if(DEBUG)
	{
		printf("Tableau M:\n");
		printArray(M);
	}

	struct Compare max_val;
	max_val.val = M->tab[0];
	max_val.index = 0;

	#pragma omp parallel for reduction(maximum:max_val)
	for (int i = 1; i < M->size; i++)
	{
		if (M->tab[i] > max_val.val)
		{
			max_val.val = M->tab[i];
			max_val.index = i;
		}
	}

	/*
	 *
	 * Affichage final
	*/
	printf("%ld ", max_val.val);
	for (int i = max_val.index; i < Q.size; i++)
	{
		if (M->tab[i] == max_val.val)
		{
			if(i == Q.size - 1){
				printf("%ld\n", Q.tab[i]);
			} else if(M->tab[i+1] == max_val.val){
				printf("%ld ", Q.tab[i]);
			} else {
				printf("%ld\n", Q.tab[i]);
				break;
			}
		}
	}
}

/*---- SUM ---------------------------------------*/

void sum(struct tablo *source, struct tablo *destination, int mode)
{

	struct tablo *a = allocateTablo(source->size * 2);
	montee_sum(source, a , mode);

	struct tablo *b = allocateTablo(source->size * 2);
	descente_sum(a, b);

	final_sum(a, b);

	#pragma omp parallel for
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[i] = b->tab[source->size + i + (source->size - 1 - 2 * i) * mode];
	}

	free(a);
	free(b);
}

void montee_sum(struct tablo *source, struct tablo *destination, int mode)
{

	#pragma omp parallel for
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[source->size + i] = source->tab[i + (source->size - 1 - 2 * i) * mode];
	}

	for (int l = log2(source->size) - 1; l >= 0; l--)
	{
		int c1 = ((int)pow(2, l + 1)) - 1; // Without compilaion optimizations, maybe this is recomputed every iterations
		#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= c1; i++)
		{
			destination->tab[i] = destination->tab[2 * i] + destination->tab[2 * i + 1];
		}
	}
}

void descente_sum(struct tablo *a, struct tablo *b)
{

	b->tab[1] = 0;
	for (int k = 1; k <= log2(a->size) - 1; k++)
	{
		int c1 = (int)pow(2, k + 1) - 1;
		#pragma omp parallel for
		for (int i = pow(2, k); i <= c1; i++)
		{
			if (i % 2 == 0)
			{
				b->tab[i] = b->tab[i / 2];
			}
			else
			{
				b->tab[i] = b->tab[i / 2] + a->tab[i - 1];
			}
		}
	}
}

void final_sum(struct tablo *a, struct tablo *b)
{

	int m = log2(b->size / 2);
	int c1 = (int)pow(2, m + 1) - 1;
	#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= c1; i++)
	{
		b->tab[i] = b->tab[i] + a->tab[i];
	}
}

/*---- SUM PARALLEL ---------------------------------------*/

void sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size)
{
	struct tablo *a1 = allocateTablo(size * 2);
	struct tablo *a2 = allocateTablo(size * 2);

	montee_sum_parallel(source1, source2, a1, a2, mode1, mode2, size);

	struct tablo *b1 = allocateTablo(size * 2);
	struct tablo *b2 = allocateTablo(size * 2);

	descente_sum_parallel(a1, a2, b1, b2, size * 2);


	final_sum_parallel(a1, a2, b1, b2, size * 2);

	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
			destination1->tab[i] = b1->tab[size + (i + (size- 1 - 2 * i) * mode1)];
			destination2->tab[i] = b2->tab[size + (i + (size- 1 - 2 * i) * mode2)];
	}

	free(a1);
	free(a2);
	free(b1);
	free(b2);
}
void montee_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size)
{
	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
			destination1->tab[size + i] = source1->tab[i + (size- 1 - 2 * i) * mode1];
			destination2->tab[size + i] = source2->tab[i + (size- 1 - 2 * i) * mode2];
	}

	for (int l = log2(size) - 1; l >= 0; l--)
	{
		int c1 = ((int)pow(2, l + 1)) - 1; // Without compilaion optimizations, maybe this is recomputed every iterations
		#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= c1; i++)
		{
			destination1->tab[i] = destination1->tab[2 * i] + destination1->tab[2 * i + 1];
			destination2->tab[i] = destination2->tab[2 * i] + destination2->tab[2 * i + 1];
		}
	}
}
void descente_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size)
{
	destination1->tab[1] = 0;
	destination2->tab[1] = 0;

	for (int k = 1; k <= log2(size) - 1; k++)
	{
		int c1 = (int)pow(2, k + 1) - 1;
		#pragma omp parallel for
		for (int i = pow(2, k); i <= c1; i++)
		{
			if (i % 2 == 0)
			{
				destination1->tab[i] = destination1->tab[i / 2];
				destination2->tab[i] = destination2->tab[i / 2];
			}
			else
			{
				destination1->tab[i] = destination1->tab[i / 2] + source1->tab[i - 1];
				destination2->tab[i] = destination2->tab[i / 2] + source2->tab[i - 1];
			}
		}
	}
}
void final_sum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size)
{
	int m = log2(size / 2);
	int c1 = (int)pow(2, m + 1) - 1;
	#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= c1; i++)
	{
		destination1->tab[i] = destination1->tab[i] + source1->tab[i];
		destination2->tab[i] = destination2->tab[i] + source2->tab[i];
	}
}

/*---- MAX ---------------------------------------*/

void maximum(struct tablo *source, struct tablo *destination, int mode)
{

	struct tablo *a = allocateTablo(source->size * 2);
	montee_max(source, a, mode);

	struct tablo *b = allocateTablo(source->size * 2);
	descente_max(a, b /*, mode*/);

	final_max(a, b /*, mode*/);

	#pragma omp parallel for
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[i] = b->tab[source->size + i + (source->size - 1 - 2 * i) * mode];
	}

	free(a);
	free(b);
}

void montee_max(struct tablo *source, struct tablo *destination, int mode)
{
	#pragma omp parallel for
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[source->size + i] = source->tab[i + (source->size - 1 - 2 * i) * mode];
	}

	for (int l = log2(source->size) - 1; l >= 0; l--)
	{
		int c1 = ((int)pow(2, l + 1)) - 1;
		#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= c1; i++)
		{
			destination->tab[i] = max(destination->tab[2 * i], destination->tab[2 * i + 1]);
		}
	}
}

void descente_max(struct tablo *a, struct tablo *b)
{
	b->tab[1] = LONG_MIN;
	for (int k = 1; k <= log2(a->size) - 1; k++)
	{
		int c1 = (int)pow(2, k + 1) - 1;
		#pragma omp parallel for
		for (int i = pow(2, k); i <= c1; i++)
		{
			if (i % 2 == 0)
			{
				b->tab[i] = b->tab[i / 2];
			}
			else
			{
				b->tab[i] = max(b->tab[i / 2], a->tab[i - 1]);
			}
		}
	}
}
void final_max(struct tablo *a, struct tablo *b)
{
	int m = log2(b->size / 2);
	int c1 = (int)pow(2, m + 1) - 1;
	#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= c1; i++)
	{
		b->tab[i] = max(b->tab[i], a->tab[i]);
	}
}

/*---- MAX PARALLEL ---------------------------------------*/

void maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size)
{
	struct tablo *a1 = allocateTablo(size * 2);
	struct tablo *a2 = allocateTablo(size * 2);

	montee_maximum_parallel(source1, source2, a1, a2, mode1, mode2, size);



	struct tablo *b1 = allocateTablo(size * 2);
	struct tablo *b2 = allocateTablo(size * 2);

	descente_maximum_parallel(a1, a2, b1, b2, size * 2);


	final_maximum_parallel(a1, a2, b1, b2, size * 2);

	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
			destination1->tab[i] = b1->tab[size + (i + (size- 1 - 2 * i) * mode1)];
			destination2->tab[i] = b2->tab[size + (i + (size- 1 - 2 * i) * mode2)];
	}

	free(a1);
	free(a2);
	free(b1);
	free(b2);
}
void montee_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int mode1, int mode2, int size)
{
	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
			destination1->tab[size + i] = source1->tab[i + (size- 1 - 2 * i) * mode1];
			destination2->tab[size + i] = source2->tab[i + (size- 1 - 2 * i) * mode2];
	}

	for (int l = log2(size) - 1; l >= 0; l--)
	{
		int c1 = ((int)pow(2, l + 1)) - 1; // Without compilaion optimizations, maybe this is recomputed every iterations
		#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= c1; i++)
		{
			destination1->tab[i] = max(destination1->tab[2 * i], destination1->tab[2 * i + 1]);
			destination2->tab[i] = max(destination2->tab[2 * i], destination2->tab[2 * i + 1]);
		}
	}
}
void descente_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size)
{
	destination1->tab[1] = LONG_MIN;
	destination2->tab[1] = LONG_MIN;

	for (int k = 1; k <= log2(size) - 1; k++)
	{
		int c1 = (int)pow(2, k + 1) - 1;
		#pragma omp parallel for
		for (int i = pow(2, k); i <= c1; i++)
		{
			if (i % 2 == 0)
			{
				destination1->tab[i] = destination1->tab[i / 2];
				destination2->tab[i] = destination2->tab[i / 2];
			}
			else
			{
				destination1->tab[i] = max(destination1->tab[i / 2], source1->tab[i - 1]);
				destination2->tab[i] = max(destination2->tab[i / 2], source2->tab[i - 1]);
			}
		}
	}
}
void final_maximum_parallel(struct tablo * source1, struct tablo * source2, struct tablo * destination1, struct tablo * destination2, int size)
{
	int m = log2(size / 2);
	int c1 = (int)pow(2, m + 1) - 1;
	#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= c1; i++)
	{
		destination1->tab[i] = max(destination1->tab[i], source1->tab[i]);
		destination2->tab[i] = max(destination2->tab[i], source2->tab[i]);
	}
}

/*---- Utils ---------------------------------------*/
void generateArray(struct tablo *s, char* buffer)
{
	int count = 0;
	int size = 2;
	long* array = malloc(sizeof(long int) * size);
	if(array == NULL)
	{
		fprintf(stderr, "An error occured allocating memory.\n");
		exit(EXIT_FAILURE);
	}

	char* token = strtok(buffer , " ");
	while(token != NULL)
	{
		array[count] = atol(token);
		count = count + 1;
		token = strtok(NULL , " ");
		if(size <= count){
			size = size * 2; // 2^n so, everytime we realloc with power up ;)
			array = realloc(array, sizeof(long int) * size);
			if(array == NULL)
			{
				fprintf(stderr, "An error occured re-allocating memory.\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	s->size = count;
	s->tab = array;
}

void printArray(struct tablo *tmp)
{
	printf("---- Array of size %i ---- \n", tmp->size);
	int size = tmp->size;
	int i;
	for (i = 0; i < size; ++i)
	{
		printf("%ld ", tmp->tab[i]);
	}
	printf("\n");
}

struct tablo *allocateTablo(int size)
{
	struct tablo *tmp = malloc(sizeof(struct tablo));
	if(tmp == NULL)
	{
		fprintf(stderr, "An error occured allocatinng memory.\n");
		exit(EXIT_FAILURE);
	}
	tmp->size = size;
	tmp->tab = malloc(size * sizeof(long));
	if(tmp->tab == NULL)
	{
		fprintf(stderr, "An error occured allocatinng memory.\n");
		exit(EXIT_FAILURE);
	}
	return tmp;
}