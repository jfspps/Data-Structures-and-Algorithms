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

A tuple is defined by a structure, which stores the coordinates and value of all non-zero elements:

```cpp
struct Element{
    int i;
    int j;
    int x;
}
```

The sparse matrix tabular representation is defined by another structure. The first column summarising the sparse matrix is stored in variables n, m, and num. The remaining elements are stored in another structure e.

```cpp
struct Sparse{
    int n;      //no. of rows
    int m;      //no of columns
    int num;    //no. of non-zero elements
    struct Element * e;
}
```

One can create the Sparse structure with create():

```cpp
void create(struct Sparse *s)
{
    int i;

    //prepare the Sparse matrix structure
    printf("Enter the dimensions of the sparse matrix:");
    scanf("%d%d", &s->m, &s->n);
    printf("Number of non-zero elements present:");
    scanf("%d", &s->num);

    //build the array e in the Sparse matrix structure S
    s->e = (struct Element *) malloc(s->num*sizeof(struct Element));

    //populate array e with coords and value of the non-zero element
    printf("Enter non-zero Elements (press enter after each row):");

    for(i = 0; i < s->num; i++)
        scanf("%d%d%d", &s->e[i].i, &s->e[i].j, &s->e[i].x);
}
```
One can display the sparse matrix as a sparse matrix (so including the zero elements) using:

```cpp
void display(struct Sparse s)
{
    int i, j, k = 0;
    for(i = 0; i < s.m; i++)
    {
        for(j = 0; j < s.n; j++)
        {
            //only print non-zeros if the coords in e[k].i and e[k].j match the current position i and j
            if(i == s.e[k].i && j == s.e[k].j)
                printf("%d ", s.ele[k++].x);
            else
                printf("0 ");
        }
        printf("\n");
        //next row
    }
}
```

The sum of two sparse matrices is given below. The same example shown above (without the first column summarising the sparse matrix) is presented here again with coords i, j and k.

`struct s1.e`

| index | i  |      |     |     |
|-------|----|------|-----|-----|
| Row i |1   | 2    | 3   | 3   |
| Col j |4   | 2    | 2   | 4   |
| x     |6   | 7    | 2   | 5   |

`struct s2.e`

| Index | j  |      |     |
|-------|----|------|-----|
| Row i |2   | 2    | 3   |
| Col j |2   | 5    | 3   |
| x     |3   | 5    | 2   |

`struct sum.e`

| Index |k   |      |     |     |    |    |
|-------|----|------|-----|-----|----|----|
| Row i |1   | 2    | 2   | 3   | 3  | 3  |
| Col j |4   | 2    | 5   | 2   | 3  | 4  |
| x     |6   | 10   | 5   | 2   | 2  | 5  |

```cpp
struct Sparse* add(struct Sparse *s1, struct Sparse *s2)
{
    struct Sparse *sum;
    int i, j, k;
    i = j = k = 0;

    // first make sure both matrices have equal dimensions
    if(s1->n != s2->n && s1->m != s2->m)
        return NULL;

    // initialise a sum sparse matrix 'sum' and another Element structure e in 'sum' in the heap
    sum=(struct Sparse *) malloc(sizeof(struct Sparse));
    sum->e = (struct Element *) malloc((s1->num + s2->num)*sizeof(struct Element));

    // i is the row no., j is the column no., k is tied to Element e in 'sum'
    while(i < s1->num && j < s2->num)
    {
        // pick the element in s1 or s2 with the smallest row coord i and advance the corresponding index (k is always advancing)
        if(s1->e[i].i < s2->e[j].i)
            sum->e[k++] = s1->e[i++];
        else if(s1->e[i].i > s2->e[j].i)
            sum->e[k++] = s2->e[j++];
        else
        {
            // pick the element in s1 or s2 with the smallest column coord j and advance the corresponding index
            if(s1->e[i].j < s2->e[j].j)
                sum->e[k++] = s1->e[i++];
            else if(s1->e[i].j > s2->e[j].j)
                sum->e[k++] = s2->e[j++];
            else
            {
                // the values in s1 and s2 are equal, so add them and copy the sum to 'sum'; advance all indices
                sum->e[k] = s1->e[i];
                sum->e[k++].x = s1->e[i++].x + s2->e[j++].x;
            }
        }
    }
    
    // either i or j my be behind by the end of the sum
    // cycle through and copy the remaining elements of s1 or s2 into sum, until both i = s1.num and j = s2.num.
    for(; i < s1->num; i++)
        sum->e[k++] = s1->e[i];

    for(; j < s2->num; j++)
        sum->e[k++] = s2->e[j];

    // Element e[] is done, now record the dimensions of the sparse matrix nxm (really, n = m at this point) and  
    // the new no. of non-zero elements in sum.e
    sum->m = s1->m;
    sum->n = s1->n;
    sum->num = k;

    //return the address of the new structure in the heap
    return sum;
}
```