#Recursion examples
-
**1. Palindrome**  
Palindrome is a word that be read the same forward or backward.
	
	int isPalindrome(char str[], int left, int right) {
		if (left >= right) 
			return 1;			/* it's palindrome */
		else if (str[left] != str[right])
			return 0;
		else 
			return isPalindrome(str, ++left, --right);
	}

**2. Insertion Sort**  
Insertion sort works by inserting the value at the location to should be inserted in sorted part.

	void insert(int a[], int size, int value) {
		int i;
		if (size == 1)
			return;
		else {
			if (a[size-1] < value) 
				a[size] = value;
			else {
				a[size] = a[size-1];
				insert(a, size-1, value);
			}
		}
	}
-

	void insertionSort(int a[], int size) {
		if (size == 0) 
			return;
		else {
			insertionSort(a, size-1);
			insert(a, size-1, a[size-1]);
		}
	}
		
**3. Pemutation**  
Print all possible combinations created from a given string.

	void permutation(char str[], int begin, int end) {
		int i;
		int range = end - begin;
		
		if (range == 1)
			printf("%s", str);
		
		for (i=0; i<range; i++) {
			swap(&str[begin], &str[begin+i]);
			permutation(str, begin+i, end);
			swap(&str[begin], &str[begin+i]);	/* recovery */
		}
	}
-
	int main() {
		char str[] = "abc";
		permutation(str, 0, strlen(str));
	}

**4. Hanoi Tower**  
Print the process for moving all given number disks.

	void Hanoi(int n, char a, char b, char c) {
		if (n > 0) {
			Hanoi(n-1, a, c, b);
			printf("Move disk from %c to %c\n", a, c);
			Hanoi(n-1, b, a, c);
		}
	}
-
	int main() {
		Hanoi(3, 'a', 'b', 'c');
	}
	
**5. Flood Fill**  
Change the color of all the tiles recursively.

	#define MAXSIZE 5
	void floodFill(char fig[][MAXSIZE+1], int x, int y, char oldColor, char newColor) {
		if (fig[x][y] != oldColor)
			return;
		else {
			fig[x][y] = newColor;
			floodFill(fig, x+1, y, oldColor, newColor);
			floodFill(fig, x-1, y, oldColor, newColor);			floodFill(fig, x, y+1, oldColor, newColor);
			floodFill(fig, x, y-1, oldColor, newColor);
		}
	}
-
	int main() {
		char fig[MAXSIZE][MAXSIZE+1] = {"*****",  
		 "*..**", "*...*", "**..*", "*****"};
		 
		floodFill(fig, MAXSIZE/2, MAXSIZE/2, '.', '+');
	}
	
**6. Knight's Tour**  
Check that the knight can traverse all of the given chessboard.

	#define MAXSIZE 9
	
	#define MARK 1
	#define UNMARK 0
	
	typedef struct Point{ int x,y; }point;
	point direction[] = {{1,-2}, {2,-1}, {2,1}, {1,2},  
						{-1,2}, {-2,1}, {-2,-1}, {-1,-2}};
	
	int board[MAXSIZE][MAXSIZE], path[MAXSIZE][MAXSIZE];
	
	int knightTour(int m, int n, point pos, int count) {
		int i;
		point next;
		
		if (count == m*n)
			return 1;
			
		for (i=0; i<8; i++) {
			next.x = pos.x + direction[i].x;
			next.y = pos.y + direction[i].y;
			
			if (next.x > 0 && next.x <= n &&
				next.y > 0 && nex.y <= m &&
				board[next.y][next.x] != MARK) {
					board[next.y][next.x] = MARK;
					path[next.y][next.x] = count + 1;
					if (knightTour(m, n, next, count+1))
						return 1;
					board[next.y][next.x] = UNMARK;	/* recover */
			}
		}
		return 0;
	}	
-
	void printTour(int m, int n) {
		int i, j;
		
		for (i=1; i<=m; i++) 
		for (j=1; j<=n; j++)
			printf(j==n?"%d\n":"%d ", path[i][j]);
	}
-
	 int main() {
	 	int i, j, m, n;
	 	point start;
	 	
	 	m = 6; n = 8;
	 	start.y = 3; start.x = 4;
	 	
	 	for (i=1; i<=m; i++)
	 	for (j=1; j<=n; j++)
	 		board[i][j] = UNMARK;
	 		
	 	board[start.y][start.x] = MARK;
	 	path[start.y][start.x] = 1;
	 	
	 	if (knightTour(m, n, start, 1))
	 		printTour(m, n);
	 }						