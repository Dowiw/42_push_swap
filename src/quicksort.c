static int	partition(int *arr, int low, int high);

/**
 * - Quicksort that sorts an int array
 * - Usage: array, first_idx, last_idx
 */
void	quicksort(int *arr, int low, int high)
{
	int	partition_idx;

	if (low < high)
	{
		partition_idx = partition(arr, low, high);
		quicksort(arr, low, partition_idx - 1);
		quicksort(arr, partition_idx + 1, high);
	}
	return ;
}

/**
 * - Helper function to do sorting in partition
 */
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
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
		j++;
	}
	temp = arr[i];
	arr[i] = arr[high];
	arr[high] = temp;
	return (i);
}

/*
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
*/
