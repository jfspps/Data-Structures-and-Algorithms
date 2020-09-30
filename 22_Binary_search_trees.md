# Binary Search Trees BST #

These are binary trees in which the left child node stores a value which is smaller than the parent, and a right-child node that stores a value larger than the parent.  Such structures are optimised for binary search behaviour.

Some key properties:

+ All nodes store unique values
+ All in-order traversals produce a sorted list of elements
+ For a BST with `n` nodes, there are always Catalan number of BSTs possible

![](/images/BinaryTrees.svg)

BSTs are usually represented by linked lists ('linked representation') but can be implemented with arrays.

## Searching from a BST ##

Starting from the parent node, one compares the required element with the node value and traverses either left or right if the required element does not equal the current node. Move to the left if the required element is less than the parent element, or, move to the right if the required element is greater than the parent node.

The time complexity of a binary search in a tree is the same as its height. Previously, the height varies between (roughly) log n and n nodes. BST trees are generally constructed such that leaf nodes are found at the highest level only. Therefore binary searches are of the order O(log[2] n), whether the search is performed recursively or iteratively.

Binary searches can be performed recursively. The base case is when a `NULL` pointer is encountered, and hence the element is not found.

```cpp
Node * recursiveBinarySearch(Node * t, int value)
{
    if (t == NULL)
    {
        return NULL;
    }

    if (value == t->data)
    {
        return t;
    }
    else if (value < t->data)
    {
        recursiveBinarySearch(t->lchild, value);
    }
    else
        recursiveBinarySearch(t->rchild, value);
}
```

Iteratively, the same method would be:

```cpp
Node * iterativeBinarySearch(Node * t, int value)
{
    while (t != NULL)
    {
        if (value == t->data)
        {
            return t;
        }
        else if (value < t->data)
        {
            t = t->lchild;
        }
        else
            t = t->rchild;
    }
    return NULL;
}
```
## Inserting into a binary search tree ##

BSTs are ordered, so searching for the element to be inserted establishes if insertion is needed and, if needed, where the element should go. The pointer t tracks the current position in the tree and can be `NULL` (when an insertion is needed). A trailing tail pointer is therefore needed to store the previous node's position, should pointer t be `NULL`. The code follows `iterativeBinarySearch()` quite closely.

Another pointer to a new Node, given here as `p` is used to create a new Node, if needed.

```cpp
Node * iterativeInsertIntoBST(Node * t, int value)
{
    Node * tailPtr = NULL, * p;
    while (t != NULL)
    {
        tailPtr = t;
        if (value == t->data)
        {
            return t;
        }
        else if (value < t->data)
        {
            t = t->lchild;
        }
        else
            t = t->rchild;
    }
    // t is NULL so insertion needed
    p = (struct Node *) malloc(sizeof(struct Node));
    p->data = value;
    p->lchild = p->rchild = NULL;

    if (p->data < tailPtr->data)
    {
        tailPtr->lchild = p;
    }
    else
        tailPtr->rchild = p;
}
```
Since insertion follows the BST search, the time complexity is O(log[2] n).

The recursive form of insertion is given below. The important call is whenever the current pointer t is `NULL`, at which point a new Node is created. The `lchild` or `rchild` conditions were established prior to the recursive call.

```cpp
Node * recursiveInsertIntoBST(Node * t, int value)
{
    Node * p;   //used to build a new Node

    if (t == NULL)
    {
        p = (struct Node *) malloc(sizeof(struct Node));
        p->data = value;
        p->lchild = p->rchild = NULL;
        return p; //done; return the pointer to either calls below
    }

    //find the correct subtree to explore
    else if (value < t->data)
    {
        t->lchild = recursiveInsertIntoBST(t->lchild, value);
    }
    else
        t->rchild = recursiveInsertIntoBST(t->rchild, value);
    
    return t;
}
```

Note that at present, the BST is not strictly binary until all insertions are matched with a sibling node.

The construction of a BST can be carried out using the search algorithm. Insertion takes O(n) time complexity (always after a finding a leaf node) and searching takes O(log[2] n) time. Since one is required to insert n elements, and each search requires O(log[2] n), a BST build has O(n log[2] n) time complexity.