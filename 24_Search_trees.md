# Other search trees #

## 2-3 (search) trees ##

`2-3 trees` are extensions of the idea of BSTs. BSTs are characterised by one parent node storing one key (value), followed by zero or two child nodes. 2-3 trees are search trees which are composed of a parent node which stores two keys and three child nodes, each of which store two keys. They are also referred to as `multiway` or `M-way` trees (M represents the degree of a node).

![](/images/2-3_trees.svg)

2-3 trees are height balanced, just as AVLs are height balanced. Each node (of degree m) must have a ceiling value of a minimum of `m/2` children, which for 2-3 trees is 2 children. The maximum number of children is the same as the highest degree possible, that is, three. Hence, these trees are referred to as `2-3` trees.

The children are labelled `left`, `middle` and `right`. The key value pairs in each node are ordered. Their value compared to the parent node is outlined below:

![](/images/2-3_trees_rules.svg)

All key values must be unique but all nodes need not be assigned two keys. Some nodes can contain one key, with space for another key.

### Inserting and building 2-3 trees ###

Insertion of nodes is accomplished as follows (note how the height is automatically balanced when nodes split):

![](/images/2-3_trees_insertion.svg)

### Deleting from a 2-3 tree ###

There are three main operations: delete from a pair of keys, delete from one key then either (i) borrow or (ii) merge. Generally, borrow is performed when the sibling node has two keys and merging is performed when a sibling has only one key. Borrowing is preferred to merging. Like insertion, note how the height is automatically balanced.

(i) When deleting from a leaf node which contains a pair of keys, simply delete the desired key value and place the remaining key in the first slot of the pair.

(iii) When deleting from a leaf left or right node with one key value, delete the key value and merge the empty node and middle node.

+ If deleting from the right leaf node (remove the empty right node) and send the higher value of the parent pair down to the middle node (this should create a full child node) 

![](/images/2-3_trees_deletion.svg)

When deleting a sole key from a middle node, one can then merge either the left or right sibling nodes with the vacant middle node. _Note how the parent node is singly occupied and therefore the right child node is removed_.

+ If merging the right node and the vacant middle node, move the higher value from the parent node down to the revised middle node (and remove the vacant right node)
+ If merging the left node and the vacant middle node, move the lower value from the parent node down to the left child node (and remove the vacant right node). Shift the right child node to the middle child node and shift remaining parent key to the left.

(ii) Another case is one referred to as borrowing, which redistributes keys amongst nodes.

Below are examples of deleting from internal nodes. These are accompanied by multiple operations (borrowing and shifting).

![](/images/2-3_trees_deletingInternal.svg)

Next is deleting from the root node. When deleting the root, replace it with the in-order predecessor or successor node.

![](/images/2-3_trees_deletingRoot.svg)

## 2-3 tree analysis ##

The minimum number of nodes of a 2-3 tree, given height `h` is `2^(h+1) - 1`.

The maximum number of nodes of a 2-3 tree, given height `h` follows a GP series and is given by `3^(h+1) - 1/(3 - 1)` or just `1/2(3^(h+1) - 1)`.

The maximum height is related to the minimum number of nodes. Max height with number of node `n` is given by `h = log[2] (n + 1) - 1`.

The minimum height with a given number of nodes `n` is given by `h = log[3] (2*n + 1) - 1`.

## Uses of 2-3 trees ##

Database management systems. Binary searches are quite efficient and storing more than one value per node permits quick access to more data, compared to BSTs. 2-3 trees are generally lower in height than BSTs (log[3] cf. log[2]).