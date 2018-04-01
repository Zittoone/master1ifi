#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define SUFFIX 1
#define PREFIX 2

#define DEBUG 0

#define BUFFER_SIZE (1 * 1024 * 1024)

#define max(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/* Structures */
struct tablo
{
	long int *tab;
	int used;
  	int size;
};

/* Headers */

void sum(struct tablo *, struct tablo *, int mode);
void montee_sum(struct tablo *, struct tablo *);
void descente_sum(struct tablo *, struct tablo *);
void final_sum(struct tablo *, struct tablo *);

void maximum(struct tablo *, struct tablo *, int mode);
void montee_max(struct tablo *, struct tablo *);
void descente_max(struct tablo *, struct tablo *);
void final_max(struct tablo *, struct tablo *);

void generateArray(struct tablo *, char*, int);
void printArray(struct tablo *);
struct tablo *allocateTablo(int);
void inverser_tablo(struct tablo *);

/*  */
int main(int argc, char *argv[])
{

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
	char buffer[BUFFER_SIZE]; // 1 MiB buffer

	// Might reconsider this ... https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1046476070&id=1043284351
	// while(!feof(fp))

	/*while(fread(buffer, BUFFER_SIZE, 1, fp) > 0)
	{
		// INT_MIN is -2147483648 -> 11 bytes long

	}*/
	// Naive reading
	if(fgets(buffer, BUFFER_SIZE, fp) == NULL)
	{
		fprintf(stderr, "An error occured reading the file \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* close file */
	fclose(fp);



	/*
	 * 1. Calculer les sum-prefix de Q et les mettre dans un tableau PSUM
	 */
	struct tablo Q;
	generateArray(&Q, buffer, strlen(buffer)); // TODO: replace this with file's input

	if(DEBUG)
	{
		printf("Tableau Q:\n");
		printArray(&Q);
	}

	struct tablo *PSUM = allocateTablo(Q.size);
	sum(&Q, PSUM, PREFIX);

	if(DEBUG)
	{
		printf("Tableau PSUM:\n");
		printArray(PSUM);
	}
	/*
	 * 2. Calculer le sum-suffix de Q et les mettre dans un tableau SSUM
	 */
	struct tablo *SSUM = allocateTablo(Q.size);
	sum(&Q, SSUM, SUFFIX);

	if(DEBUG)
	{
		printf("Tableau SSUM:\n");
		printArray(SSUM);
	}

	/*
	 * 3. Calculer le max-suffix de PSUM et le mettre dans SMAX
	 */
	struct tablo *SMAX = allocateTablo(Q.size);
	maximum(PSUM, SMAX, SUFFIX);

	if(DEBUG)
	{
		printf("Tableau SMAX:\n");
		printArray(SMAX);
	}

	/*
	 * 4. Calculer le max-prefix de SSUM et le mettre dans PMAX
	 */
	struct tablo *PMAX;
	PMAX = allocateTablo(Q.size);
	maximum(SSUM, PMAX, PREFIX);

	if(DEBUG)
	{
		printf("Tableau PMAX:\n");
		printArray(PMAX);
	}

	/*
	 * 5. pour  1 <= i <= n faire en parallel
	 * 	1. Ms[i] = PMAX[i] - SSUM[i] + Q[i]
	 * 	2. Mp[i] = SMAX[i] - PSUM[i] + Q[i]
	 * 	3. M[i] = Ms[i] + Mp[i] - Q[i]
	 */

	struct tablo *Ms = allocateTablo(Q.size);
	struct tablo *Mp = allocateTablo(Q.size);
	struct tablo *M = allocateTablo(Q.size);

#pragma omp parallel for
	for (int i = 0; i < Q.size; i++)
	{
		Ms->tab[i] = PMAX->tab[i] - SSUM->tab[i] + Q.tab[i];
		Mp->tab[i] = SMAX->tab[i] - PSUM->tab[i] + Q.tab[i];
		M->tab[i] = Ms->tab[i] + Mp->tab[i] - Q.tab[i];
	}

	if(DEBUG)
	{
		printf("Tableau M:\n");
		printArray(M);
	}

	long int max_val = M->tab[0];
	int start = 0;
	int end = 0;

#pragma omp parallel for reduction(max \
								   : max_val)
	for (int i = 1; i < M->size; i++)
	{
		if (M->tab[i] > max_val)
		{
			max_val = M->tab[i];
		}
	}

	for (int i = 0; i < M->size; i++)
	{
		if (M->tab[i] == max_val)
		{
			start = i;
			break;
		}
	}

	for (int i = start; i < M->size; i++)
	{
		if (M->tab[i] == max_val)
		{
			end = i;
		} else {
			break;
		}
	}

	if(DEBUG)
	{
		printf("Max value is : %ld within [%d, %d]\n", max_val, start + 1, end + 1);
	}

	/*
	 *
	 * Affichage final
	*/
	printf("%ld ", max_val);
	for (int i = start; i < end; i++)
	{
		printf("%ld ", Q.tab[i]);
	}

	printf("%ld\n", Q.tab[end]);
}

/*---- SUM ---------------------------------------*/

void sum(struct tablo *source, struct tablo *destination, int mode)
{

	// TODO: inverser tableau
	if (mode == SUFFIX)
	{
		inverser_tablo(source);
	}

	struct tablo *a = allocateTablo(source->size * 2);
	// TODO: do not reverse the array, iterate reverse way
	montee_sum(source, a /*, mode*/);

	struct tablo *b = allocateTablo(source->size * 2);
	descente_sum(a, b /*, mode*/);

	final_sum(a, b /*, mode*/);

	// Tab b is source size * 2 so
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[i] = b->tab[source->size + i];
	}

	if (mode == SUFFIX)
	{
		inverser_tablo(source);
		inverser_tablo(destination);
	}

	free(a);
	free(b);
}

void montee_sum(struct tablo *source, struct tablo *destination)
{
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[source->size + i] = source->tab[i];
	}

	for (int l = log2(source->size) - 1; l >= 0; l--)
	{
#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= ((int)pow(2, l + 1)) - 1; i++)
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
#pragma omp parallel for
		for (int i = pow(2, k); i <= (int)pow(2, k + 1) - 1; i++)
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
#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= (int)pow(2, m + 1) - 1; i++)
	{
		b->tab[i] = b->tab[i] + a->tab[i];
	}
}

/*---- MAX ---------------------------------------*/

void maximum(struct tablo *source, struct tablo *destination, int mode)
{

	// TODO: inverser tableau
	if (mode == SUFFIX)
	{
		inverser_tablo(source);
	}

	struct tablo *a = allocateTablo(source->size * 2);
	// TODO: do not reverse the array, iterate reverse way
	montee_max(source, a /*, mode*/);

	struct tablo *b = allocateTablo(source->size * 2);
	descente_max(a, b /*, mode*/);

	final_max(a, b /*, mode*/);

	//destination = allocateTablo(source->size);

	// Tab b is source size * 2 so
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[i] = b->tab[source->size + i];
	}

	if (mode == SUFFIX)
	{
		inverser_tablo(source);
		inverser_tablo(destination);
	}

	free(a);
	free(b);
}

void montee_max(struct tablo *source, struct tablo *destination)
{
	for (int i = 0; i < source->size; i++)
	{
		destination->tab[source->size + i] = source->tab[i];
	}

	for (int l = log2(source->size) - 1; l >= 0; l--)
	{
#pragma omp parallel for
		for (int i = (int)pow(2, l) - 1; i <= ((int)pow(2, l + 1)) - 1; i++)
		{
			destination->tab[i] = max(destination->tab[2 * i], destination->tab[2 * i + 1]);
		}
	}
}

void descente_max(struct tablo *a, struct tablo *b)
{
	b->tab[1] = INT_MIN;
	for (int k = 1; k <= log2(a->size) - 1; k++)
	{
#pragma omp parallel for
		for (int i = pow(2, k); i <= (int)pow(2, k + 1) - 1; i++)
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

#pragma omp parallel for
	for (int i = pow(2, m - 1); i <= (int)pow(2, m + 1) - 1; i++)
	{
		b->tab[i] = max(b->tab[i], a->tab[i]);
	}
}

/*---- Utils ---------------------------------------*/
void inverser_tablo(struct tablo *a)
{
	int i = a->size - 1;
	int j = 0;
	while (i > j)
	{
		int temp = a->tab[i];
		a->tab[i] = a->tab[j];
		a->tab[j] = temp;
		i--;
		j++;
	}
}

void generateArray(struct tablo *s, char* inputs, int length)
{
	char* token;
	int count = 0;
	int size = 64;
	long* array = malloc(sizeof(long) * size);

	token = strtok(inputs , " ");
	while(token != NULL)
	{
		array[count++] = atol(token);
		token = strtok(NULL , " ");

		if(size < count){
			size += 64;
			array = realloc(array, sizeof(long) * size);
		}
	}

	s->size = count;
	s->tab = array;

	//construction d'un tableau pour tester
	/*
	s->size = 16;
	s->tab = malloc(s->size * sizeof(int));
	s->tab[0] = 3;
	s->tab[1] = 2;
	s->tab[2] = -7;
	s->tab[3] = 11;
	s->tab[4] = 10;
	s->tab[5] = -6;
	s->tab[6] = 4;
	s->tab[7] = 9;
	s->tab[8] = -6;
	s->tab[9] = 1;
	s->tab[10] = -2;
	s->tab[11] = -3;
	s->tab[12] = 4;
	s->tab[13] = -3;
	s->tab[14] = 0;
	s->tab[15] = 2;
	*/
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
	tmp->size = size;
	tmp->tab = malloc(size * sizeof(long));
	return tmp;
}