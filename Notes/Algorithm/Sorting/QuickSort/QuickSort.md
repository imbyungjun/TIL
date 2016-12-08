#Quick Sort
###Divide and Conquer algorithm

####Divide
배열의 원소중에 임의의 데이터를 pivot으로 선택한다.  
배열에 있는 데이터들을 pivot 보다 작은 그룹과 pivot 보다 큰 그룹으로 나눈다.

####Conquer
Pivot 을 중심으로 나누어진 두 그룹을 재귀적으로 quick sorting 수행한다.

####Combine
Combine 단계는 필요하지 않음.  
Divide 단계에 의해서 결과적으로 정렬된 데이터를 얻게됨.

####Analysis
* Basic operation : 배열에 저장된 데이터와 pivot을 비교하는 연산
* T(n) : n 개의 데이터에 대하여 quick sorting 을 수행하는 basic operation 의 횟수
* Worst case 는 이미 정렬된 데이터가 입력되는 경우 O(n^2) 
* Best case 는 merge sort 에서와 같이 나누어지는 모든 배열의 크기가 각각 n/2인 경우이다.  
	이 경우에는 O(nlogn) 이다.
* 특수하게 O(nlogn)을 빅오노테이션으로 표기함.


####Example) Python
```
def quickSort(arr) :
	if len(arr) <= 1 :
		return arr
  
	pivot = arr[len(arr)/2]
	less = [ ]
	more = [ ]
	equal = [ ]

	for x in arr :
		if x < pivot :
			less.append(x)
		elif x > pivot :
			more.append(x)
		else
			equal.append(x)

	return quickSort(less) + equal + quickSort(more)

# equal 을 사용할 경우 분할 및 정렬 작업의 수행을 줄일 수 있다.
# 예를들어 n 개의 같은 값을 갖는 원소들이 입력으로 주어진 경우
# (<, >=) 두개의 그룹으로 나누는 기존의 방식은 O(n*n)의 의미없는 수행이 이루어짐
# equal 을 사용하면 소요시간이 O(n)으로 줄어든다.

# 이 코드는 in-place 방식이 아니기때문에 메모리 효율입장에선 적합하지 않음.
```

####Example) C
```
int partition(int arr[], int low, int high) {
	int i, j;
	int pivot, pivotPos, tmp;

	pivot = arr[low];
	j = low;

	for (i = low + 1; i <= high; i++) {
		if (arr[i] < pivot) {
			j++;
			swap(&arr[i], &arr[j]);
		}
	}

	pivotPos = j;
	swap(&arr[low], &arr[pivotPos]);

	return pivotPos;
}

void quickSort(int arr[], int low, int high) {
	int pivotPos;

	if (high > low) {
		pivotPos = partition(arr, low, high);
		quickSort(arr, low, pivotPos-1);
		quickSort(arr, pivotPos+1, high);
	}
}

```



