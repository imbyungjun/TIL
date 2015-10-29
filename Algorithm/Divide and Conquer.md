#Divide & Conquer algorithm
-
**Divide and conquer algorithm** is used to solving huge problem that can't solve at once, by split into multiple small problems.  

There's three steps in divide and conquer algorithm.  
**Step 1)  Divide**  
- Split into small problems.  
**Step 2) Conquer**  
- Solve the problem recursively until small enough to solve the problem  
**Step 3) Combine**  
- Combining small problems's answer and make the original problem's answer.

**Example ) Binary Search**  

	int a[] = {12, 15, 20, 26, 33, 40, 51, 64, 70};

**Step 1)** Divide group with the middle number M, smaller than M, and bigger than M.

	{12, 15, 20, 26}, {33}, {40, 51, 64, 70}
	
**Step 2)** Conquer step. Assume that finding number is **x**.

	1) x = M, we find the number.
	2) x < M, we can find the number in group that smaller than M.
	3) x > M, we can find the number in group that bigger than M.
	
**Step 3)** Combine the answers. Derive original problem's answer.  

Example Code:

	/* Find the 'value' and return the index of 'value' */
	int binarySearch(int arr[], int left, int right, int value) {
		int mid = (left + right) / 2;
		if (left > right) 
			return -1;		/* not found */
		else {
			if (value == arr[mid])
				return mid;
			else if (value < arr[mid])
				return binarySearch(arr, left, mid-1, value);
			else if (value > arr[mid])
				return binarySearch(arr, mid+1, right, value);
		}
	}
	
	
**Example ) Merge Sort**

	void merge(int a[], int low, int mid, int high) {
		int i, j, k;
		int tmp[MAXSIZE];
		
		if (low === high)
			return;
		
		for (i=low; i<=high; i++)
			tmp[i] = a[i];
			
		i = k = low;
		j = mid+1;
		
		while(i <= mid && j <= high) 
			if (tmp[i] <= tmp[j])
				a[k++] = tmp[i++];
			else
				a[k++] = tmp[j++];
			
		while(i <= mid)
			a[k++] = tmp[i++];
			
		while(j <= high)
			a[k++] = tmp[j++];
	}
	
	void mergeSort(int a[], int low, int high) {
		int mid;
		
		if(low == high)
			return;
		else {
			mid = (low + high) / 2;
			mergeSort(a, low, mid);
			mergeSort(a, mid+1, high);
			merge(a, low, mid, high);
		}
	}
	