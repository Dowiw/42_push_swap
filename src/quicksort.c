#include <stdio.h>

static int partition(int *arr, int low, int high);

/**
 */
void	quicksort(int *arr, int low, int high)
{
	int	partition_idx;

	if (low < high)
	{
	printf("\nlow: %i, high: %i\n", low, high);
	partition_idx = partition(arr, low, high);
	for (int i = 0; i < 10; i++);
		printf("array: %i, %i, %i, %i, %i, %i, %i, %i, %i, %i\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
	quicksort(arr, low, partition_idx - 1);
	printf("exiting quicksort left\n");
	quicksort(arr, partition_idx + 1, high);
	}
	return ;
}

static int	partition(int *arr, int low, int high)
{
	int	i;
	int	j;
	int	temp;
	int	pivot;

	i = low;
	j = low;
	pivot = arr[high];
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			printf("arr[j]: %i, pivot: %i\n", arr[j], pivot);
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			printf("j: %i, arr[j]: %i, i:%i arr[i]: %i\n", j, arr[j], i, arr[i]);
			i++;
		}
		j++;
	}
	printf("OUTSIDE: i: %i, arr[i]: %i, high: %i, arr[high]: %i\n", i, arr[i], high, arr[high]);
	temp = arr[i];
	arr[i] = arr[high];
	arr[high] = temp;
	return (i);
}

int main(void)
{
	int arr[10] = {10, 7, 5, 8, 3, 2, 1, 4, 6, 9};
	for (int i = 0; i < 10; i++)
		printf("num at %i: %i\n", i, arr[i]);

	quicksort((int *)arr, 0, 10 - 1);
	for (int i = 0; i < 10; i++)
		printf("sorted num at %i: %i\n", i, arr[i]);
	
	return (0);
}
