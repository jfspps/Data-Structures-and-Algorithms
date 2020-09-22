# Tree data structures #

![](/images/Trees.svg)

Tree data structures are composed of _nodes_ and _edges_. Some other terminology:

+ __Root__: uppermost node A
+ __Parent__: node connected above a given node
+ __Child__: node connected below a given node
+ __Siblings__: nodes with the same parent node
+ __Descendants__: all nodes connected below a given node
+ __Ancestors__: all nodes connected above a given node (not including siblings)
+ __Degree of a node__: number of edges or nodes below a given node
+ __Degree of a tree__ : (usually) any value greater than or equal to the largest degree of a node (see later)
+ __Internal and external nodes__: internal, where degree of the node `> 0`; external nodes are the `leaf` nodes, with a degree of zero
+ __Levels__: designates the position relative to the root. Root is assigned level 1, its children are level 2 and so on...
+ __Height of a tree__: Number of levels, in addition to the level given by the root node. A tree made up of one node has a height of zero. Essentially, the number of edges along one path from the root node, `height = level - 1`.
+ __Forest__: a collection of trees

Most of the material presented is concerned with __binary trees__, that is, trees in which all nodes have no more than two child nodes.

## Binary trees ##

With three unlabelled nodes, one can derive five differently shaped trees.

![](/images/BinaryTrees.svg)

The general number of binary trees that can be generated is given by the Catalan number. The number of trees with the maximum height (equalling n nodes) is given by `2^(n-1)`.

Alternatively, T(n) can be deduced from the sum of `T(i - 1) * T(n - i)` from `i = 1` to `i = n`.

With three labelled nodes, there will be more permutations. So `ABC` can be written as `ACB` and `BAC` and so on. In general, the number of trees with `n` nodes is `T(n) * n!`.

### Node deduction from tree height ###

What would be the minimum and maximum number of nodes in a tree of given height `h`. 

For the minimum, this would equal the `h + 1` nodes. 

The maximum number of nodes is given by the sum of a GP series, `a + ar + ar^2 + ar^3 + ... ar^k = a/(r - 1)[(r^(k + 1) - 1)]`. Since r = 2 and a = 1 (on inspection) for the binary tree, then the maximum number of nodes for height `h`, we have `(2^(h + 1) - 1)` nodes.

### Height deduction from number of nodes ###

Conversely, what would be the minimum and maximum height of a tree with a given number of nodes?

The maximum height with `n` nodes is `n - 1`.

The minimum height is essentially the inverse of the formula for the maximum number of nodes. This results in the minimum height `h = [log[2](n + 1)] - 1`.

Making some approximations, we can state that:

+ the height of a binary tree is roughly between log N to N, with N = number of nodes
+ the number of nodes is roughly between H and 2^H, with H = height of a binary tree

### Number of nodes with a given degree in a binary tree ###

Through examination, one can observe that the `number of nodes with degree 2 = number of nodes with degree zero + 1`.  There is no clear relationship regarding nodes with degree one.

### Strict binary trees ###

Strict binary trees are also referred to as _proper_ or _complete_ binary trees. Strict binary trees can only have either zero or two child nodes, unlike a general binary tree, in which the nodes can have zero, one or two child nodes.

The minimum number of nodes for general binary trees (of height `h`) and for strict binary trees are the same : `2h + 1`.

The maximum number of nodes for a strict binary tree of height `h` is `2^(h + 1) - 1`. (Compare this to `n = [log[2](h + 1)] - 1` for general binary trees.)

The minimum height of a strict binary tree is the inversion of maximum number of nodes `n`: `log[2](n + 1) - 1`.

The maximum height of a strict binary tree is the inversion of minimum number of nodes `n`: `(n - 1)/2`.

For strict binary trees, the height varies between (roughly) log n and n nodes, similar to general binary trees.

The number of internal nodes and external nodes in a strict binary tree is differs by one: `number of internal nodes = number of external nodes - 1`.