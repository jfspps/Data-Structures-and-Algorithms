# Graphs #

Graphs are made up of vertices and edges, and expressed as `G(V, E)`.

![](images/graphs.svg)

Directed graphs have directed edges (outcoming one vertex and incoming to another). Two edges with opposing direction between the same vertices are parallel edges. Graphs which are not made up of self-loop(s) or parallel edges are known as _simple_ digraphs, in which a digraph is a _directed_ graph. When a graph is simply referred to as a graph then it is assumed to be non-directed. Graphs made up of two or more components are known as non-connected graph.

Vertices, which when removed, result in two or more components are known as _articulation points_ (none of the above graphs contain articulation points). Graphs which do not have any articulation points are sometimes referred to as _connected graphs_.

A graph is termed _strongly connected_ when there is a path between any two nodes. A _path_ is a set of all vertices in between two vertices. Paths are cyclic (or circular) if it traverses to and from the same vertex.

Graphs in which all edges are directed in the same direction then the graph is termed _topological_.

## Representing undirected graphs ##

### Adjacency matrix ###

![](images/undirectedGraphs.svg)

The dimensions of the matrix matches the vertices in the graph.

The graph vertices correspond to the row (i) and column (j) numbers of the matrix. Start with the row number (the starting vertex) and find the column number (the final vertex). The elements in the matrix denote if there is one edge present. For a matrix A, then `A[i][j] = 1` when there is one edge between vertices `i` and `j`, and `A[i][j] = 0` otherwise. 

It follows that `A[i][i] = 0` in all cases, except for self-loops (some implementations assign infinity instead of zero). Also see how the matrix is symmetric.

As will be demonstrated, algorithms generally have to process all elements in the matrix to verify that graph structure. Therefore, time complexities are O(n^2).

### Cost adjacency matrix (of Weighted graphs) ###

![](images/weighted_undirectedGraphs.svg)


### Adjacency list ###

This representation is essentially an array of linked lists. Each element in the array represents a given vertex and the linked list lists the connected vertices (listed in ascending order). Assume here that vertex "1" is given by the zeroth element, vertex "2" is given by the first element and so on.

![](images/undirectedGraphs2.svg)

Algorithms generally access all vertices `v` and proceed along a path `e` twice (from 1 to 2, and 2 to 1). Hence the time complexity would be `O(v = 2e)` or just `O(v + e)`.

### Cost adjacency list ###

![](images/weighted_undirectedGraphs2.svg)

### Compact list ###

This representation uses a single-dimensioned array. In this case, we require space for each vertex, two spaces per edge and a spare element to set the zeroth element as `NULL` and enable vertex number to equal the element number.

Elements 1 to n represent the first vertex index connected to vertices n. Element `n+1` is the first out-of-bounds index (in the case below, element 21) and separates the origin vertices from the neighbouring vertices.

![](images/undirectedGraphs3.svg)

The space complexity of compact lists is `O(v + 2e + 1)`, which is effectively O(n).