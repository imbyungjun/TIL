#AVL Tree

###Definition
An AVL tree is a **binary search tree**. For any node in the tree, the height of the left and right subtress can differ by **at most 1**.  
AVL stands for Adel'son-Vel'skii and Landis

* Balance factor `bf(x) = height(left) - height(right)`
* bf(x) values -1, 0, and 1 are allowed. (AVL tree)
* If bf(x) < -1 or bf(x) > 1, then tree is **not** AVL tree

Take **O(log n)** time for searching, insertion, and deletion

(a) AVL tree

```
		 12
	   /    \
	  8      16
    /  \     /
   4   10   14
  / \
 2   6
```

(b) Not AVL tree

```
		  12
		/    \
     * 8      16	<- BF = 3 - 1 = 2
      / \     /			Not AVL tree
    4   10   14
   / \
  2   6
 /
1
```

(c) Balance factor = **height(left) - height(right)**

```
		6		BF = 1 - 0 = 1
	  /   \
     4     9	BF = 0
    / \
   1   5		BF = 0
```

###Rebalancing
To maintain AVL tree, **rebalancing** is required.

Suppose the node to be rebalanced is X.  
BF(X) = 2, there are 4 cases that we might have to fix

**Outside cases (Require single rotation - LL and RR)**  
1) An insertion in the **left subtree** of the **left child** of X.  
2) An insertion in the **right subtree** of the **right child** of X.

**Inside cases (Require double rotation - RL and LR)**  
1) An insertion in the **right subtree** of the **left child** of X.  
2) An insertion in the **left subtree** of the **right child** of X.

###AVL Balancing Operations: Rotations
####Definition for Rotations
* To switch children and parents among two or three adjacent nodes to resotre balance of a tree.
* A rotation may change the depth of some nodes, but does not change their relative ordering.

```
		x1					   x2
	   /	Single right      /  \
	  x2		--->		x3    x1
	 /
	x3
```
```
	x1						   x2
	  \		Single left		  /  \
	   x2		--->		 x1   x3
		\
		 x3
```
```
	   x1					  x3
	  /		Double right	 /  \
	 x2			--->		x2   x1
	  \
	  x3
```
```
     x1					      x3
	   \	Double left		 /  \
		x2		--->		x1  x2
	   /
	 x3
```

####LL rotation
```
		A						 B
	  /   \					   /   \
     B    ...		--->	 ...    A
   /   \					/	  /   \
 ...   ...				  ...	...   ...
 /
...
```
```
Node *rotateLL(Node *A) {
	Node *B = A->left;
	A->left = B->right;
	B->right = A;
	return B;
}
```

####RR rotation
```
	    A					    B
	  /   \					  /   \
    ...    B		--->	 A    ...
	      / \			    / \     \
        ...  ...	      ... ...   ...
			   \
			  ...
```
```
Node *rotateRR(Node *A) {
	Node *B = A->right;
	A->right = B->left;
	B->left = A;
	return B;
}
```

####LR rotation
```
		  A					 A			       C
	    /   \			   /   \		     /    \
       B    ...      	  C    ...          B      A
     /  \		  -->    /  \		-->   /  \    /  \
   ...   C         	    B   ...         ... ...  ... ...
        /  \	   	   / \
      ...  ...	 	 ... ...
```
```
Node *rotateLR(Node *A) {
	Node *B = A->left;
	A->left = rotateRR(B);
	return rotateLL(A);
}
```

####RL rotation
```
		A			      A						C
	  /   \			    /   \				  /   \
	...    B		  ...    C				 A	   B
		 /   \	 -->        /  \	-->		/  \  /  \
	    C    ...		  ...   B		 ... ... ... ...
	  /  \				 	   / \
	...  ...				 ... ...
```
```
Node *rotateRL(Node *A) {
	Node *B = A->right;
	A->right = rotateLL(B);
	return rotateRR(A);
}
```
