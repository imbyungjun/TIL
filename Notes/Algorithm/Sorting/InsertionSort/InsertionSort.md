#Insertion Sort

자료 배열의 모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를 찾아 삽입함으로써 정렬을 완성하는 알고리즘

![img](example_before.png)

각 반복에서 정렬되지 않은 나머지 부분 중 첫 번째 항목은 제거되어 정확한 위치에 삽입된다.

![img](example_after.png)

배열이 길어질수록 효율이 떨어지지만, 구현이 간단하다는 장점이 있다.

선택 정렬이나 거품 정렬과 같은 같은 O(n2) 알고리즘에 비교하여 빠르며, 안정 정렬이고 in-place 알고리즘이다.

자신의 위치에 삽입하여 자신보다 큰 이미 정렬된 원소들을 밀어내는 작업을 수행해야한다는점에서 매우 비효율적. memcpy를 이용하면 조금 더 빠르게 수행이 가능함.

####Example
```
void insertion_sort ( int *data, int n )
{
  int i, j, remember;
  for ( i = 1; i < n; i++ )
  {
    remember = data[(j=i)];
    while ( --j >= 0 && remember < data[j] )
        data[j+1] = data[j];
    data[j+1] = remember; 
  }
}
```

####Example - memcpy
```
void insertion_sort ( int *data, int n )
{
  int i, j, remember;
  i = n-1;
  while ( i-- > 0 )  
  {
    remember = data[(j=i)];
    while ( ++j < n && remember > data[j] );

    if ( --j == i ) continue;
    memcpy ( data+i, data+i+1, sizeof(*data) * (j-i) );
    data[j] = remember;
  }
}
```
