def quickSort(arr) :
	if len(arr) <= 1 :
		return arr

	pivot = arr[len(arr)//2]
	less = [ ]
	more = [ ]
	equal = [ ]

	for x in arr :
		if x < pivot :
			less.append(x)
		elif x > pivot :
			more.append(x)
		else :
			equal.append(x)

	return quickSort(less) + equal + quickSort(more)

print quickSort([9, 3, 1, 0, 5, 2, 9, 6, 7])
