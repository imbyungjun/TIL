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


