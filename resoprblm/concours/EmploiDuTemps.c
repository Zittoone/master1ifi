#include <stdio.h>
#include <stdlib.h>


void quickSort(int arr[], int low, int high, int ends[]);

int main(void) {

    int n, used;
    fscanf(stdin,"%d",&n);
    used = 0;

    if(n == 0) {
        fprintf(stdout, "%d\n", 0);
        return 0;
    }

    int* classes = malloc(sizeof(int) * n);
    int* starts = malloc(sizeof(int) * n);
    int* ends = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        fscanf(stdin,"%d %d",&starts[i], &ends[i]);
    }

    quickSort(starts, 0, n, ends);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(starts[i] >= classes[j]) {
                classes[j] = ends[i];
                if(j > used)
                    used = j;
                break;
            }
        }
    }

    fprintf(stdout,"%d\n",used + 1);
	return 0;
}

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high, int ends[])
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
            swap(&ends[i], &ends[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swap(&ends[i + 1], &ends[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high, int ends[])
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high, ends);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1, ends);
        quickSort(arr, pi + 1, high, ends);
    }
}