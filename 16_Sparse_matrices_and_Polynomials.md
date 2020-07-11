# Sparse Matrices #

Square matrices in which the majority of elements are zero are referred to as __sparse matrices__. The storage and processing of sparse matrices such that they ignore (or pad) zeros where needed is of concern here.

There are two methods to handle sparse matrices:

1. Coordinate list/three-column representation
2. Compressed sparse row

## Coordinate list ##

This involves a list of tuples, specifically, which hold values for row number, column number and the value itself.

|Row   |  Column    | Value |
|:-----|:-----------|:------|
|_8_   | _9_        | _8_   |
|1     | 8          | 3     |
|2     | 3          | 8     |
|2     | 6          | 10    |
| ...  | ...        | ...   |

The above table is not complete but illustrates the idea. The first row is reserved for the number of non-zero rows, the number of non-zero columns and the number of non-zero elements in the sparse matrix. The remaining rows map the position of each element.

## Compressed sparse rows ##

This approach uses three arrays. 

+ The first array lists the value of the non-zero elements one row at a time, left-to-right. Hence the length of the first array is the same as the number of non-zero elements present.

+ The second array represents the cumulative sum of elements as one crosses each row. The first element is always 0 because the number of non-zero elements counted is zero. The remaining the elements give the cumulative sum. As a result, the last element of the second array is the total number of non-zero elements present, and the length of the second array is always one element larger than array one, the dimension of the sparse matrix. When the value of two consecutive elements is equal then the row crossed contained no non-zero elements.

+ The third array simply lists the column index for the element with the same index in the first array is located. The length of arrays one and three are equal.

## Addition of sparse matrices ##

Regarding coordinate listing, the matrices `A` and `B` are provided in tabular form, as shown above. Prepare a table which represents the sum of the two matrices.

Matrix A

| Row  | _3_   |1   | 2    | 3   | 3   |
|------|-------|----|------|-----|-----|
|Column| _2_   |4   | 2    | 2   | 4   |
|------|-------|----|------|-----|-----|
|Value | _4_   |6   | 7    | 2   | 5   |

Matrix B

| Row  | _2_   |2   | 2    | 3   |
|------|-------|----|------|-----|
|Column| _3_   |2   | 5    | 3   |
|------|-------|----|------|-----|
|Value | _3_   |3   | 5    | 2   |

Matrix A + B

| Row  | _3_   |1   | 2    | 2   | 3   | 3  | 3  |
|------|-------|----|------|-----|-----|----|----|
|Column| _5_   |4   | 2    | 5   | 2   | 3  | 4  |
|------|-------|----|------|-----|-----|----|----|
|Value | _4_   |6   | 10   | 5   | 2   | 2  | 5  |

Computationally, the program will check the row number then column number to see if the non-zero elements lie in the same position. If not, then the value with the lowest row number followed by column number is copied across to the new table. If a sum is taken, then both markers (counters i and j, see later) advance one place to the right of their respective table.

The first column representing the sum A + B has to be deduced at the end. Subtraction is performed in an analogous way.

### Sum algorithm ###

The tuple is defined by a structure:

```cpp
struct Element{
    int i;
    int j;
    int x;
}
```

