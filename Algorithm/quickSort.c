#include <stdio.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int arr[], int low, int high) {
	int i, j;
	int pivot, pivotPos;

	pivot = arr[low];
	j = low;

	for (i = low + 1; i <= high; i++) 
		if (arr[i] < pivot) {
			j++;
			swap(&arr[i], &arr[j]);
		}

	pivotPos = j;
	swap(&arr[low], &arr[pivotPos]);

	return pivotPos;
}

void quickSort(int a[], int low, int high) {
	int pivotPos;
	
	if (low >= high) return;

	pivotPos = partition(a, low, high);
	quickSort(a, low, pivotPos - 1);
	quickSort(a, pivotPos + 1, high);
}

int main() {
	int i, arr[] = {5, 3 , 8, 7, 4, 2, 1, 6};

	for (i = 0; i < 8; i++)
		printf("%d%c", arr[i], (i==7)?'\n':' ');

	quickSort(arr, 0, 7);

	for (i = 0; i < 8; i++)
		printf("%d%c", arr[i], (i==7)?'\n':' ');
}

