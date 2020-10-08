# Sorting methods #

Sorting methods are developed with the following aspects in mind:

+ No. of comparisons required
+ No. of element swaps to carry out
+ How the method behaves when the data that is sorted or unsorted (aim to perform fewest operations, O(n), if a collection is already sorted)
+ How stable the method is: how the method preserves the previous ordering of duplicated elements e.g. numerical and then, as previously, alphabetical
+ Memory efficiency

There are two main types of sorting methods: _comparison-based sorts_ and _index-based sorts_

+ Comparison based sorts
  - The following are O(n^2): bubble, insertion, selection
  - The following are O(n log n): heap, merge, quick, tree
  - Shell sort, O(n^[3/2])
+ Index based sorts (faster at O(n) but more memory demanding)
  - count, bucket/bin, radix

## Bubble sort ##

In bubble sort, the highest (or lowest element) is fed to the beginning of an array or list, through a series of consecutive passes. To feed the last element to the top would require a maximum of `n` passes for a collection of `n` elements.

![](/images/bubble_sort.svg)

In the above case, the first pass sorts the largest element, 17. The next pass sorts the next largest element, 12. In each pass, the sorted element mimics a bubble rising to the surface. The ideas applied to a sorted list of increasing elements can be applied to a sorted list of decreasing elements.

The first pass requires `n - 1` comparisons, and a maximum of `n - 1` elements are swapped. Since the largest element is at the end of the list, this element ignored in subsequent passes. Hence, the second pass requires `n - 2` comparisons and a maximum of `n - 2` elements are swapped. This continues until the last pass compares `n - (n - 1)` elements, which can also swap a maximum of `n - (n - 1)` elements in the last pass.

A maximum of `n - 1` passes are required (can't compare the zeroth element with itself). The number of comparisons for a collection of three elements is `2 + 1`. The number of comparisons for `n` elements is the sum `(n - 1) + (n - 2) + ... + (n - (n - 1))` or in reverse, `1 + 2 + 3 + ... + (n - 1)`, which is `n(n - 1)/2`. The maximum number of elements swapped is also `n(n - 1)/2`. This gives a time complexity of O(n^2).

Other uses of bubble sort:

+ quickly find the largest (or smallest) element, by running the first pass only
+ quickly find `m` largest (or smallest) elements, by running `m` passes

Bubble sort is stable since the method does not swap the sequence of two or more identical elements in the given list. The group of identical elements might change depending on the values of other different elements but the sequence within the group of identical elements is preserved. Thus, bubble sort is deemed stable.

One can make bubble sort more adaptive by checking if a swap was needed at the earliest opportunity. This results in a time complexity of O(n) (the outer for loop is run once).

```cpp
void bubbleSort(int A[],int n)
{
    //i represent the number of passes
    int i, j, flag = 0;
    for(i = 0; i < n-1; i++)
    {
        flag = 0;
        for(j = 0; j < n-i-1; j++)
        {
            if(A[j] > A[j+1])
            {
            swap(&A[j], &A[j+1]);
            flag = 1;
            }
        }
        //stop bubbleSort if a swap was not performed (makes BubbleSort more adaptive)
        if(flag == 0)
        break;
    }
}
```

## Insertion sort ##

The basis of insertion sort revolves around inserting an element in a sorted array or list by shuffling other elements of the array/revise the pointers of the list. Regarding the linked list, move the trailing pointer before the leading pointer.

Start with an unsorted collection. Mark the end of the growing collection at the end of the first element. The first pass then moves the marker by one element and the second element is extracted. It is then compared to first element and then swapped if necessary. For the example below, we sort all elements in increasing value.

![](/images/insertionSort.svg)

The results of the analysis of insertion sort are similar to that of bubble sort. There are at most `n - 1` comparisons per pass and at most `n - 1` passes. The maximum number of elements that can be swapped also equal the maximum number of comparisons. The total number of comparisons and elements swapped is `n(n - 1)/2` and so the time complexity, at worst, is O(n^2).

Some other observations:

+ Unlike bubble sort, intermediate passes are not particularly useful.
+ Insertion sort is more applicable and better suited to linked lists as opposed to arrays since elements need not be shuffled prior to insertion.

```cpp
//sort in increasing order of int's, lowest first
void insertionSort(int A[],int n)
{
  int i, j, x;

  //set i to the element which precedes the 'marker'
  for(i = 1 ; i < n; i++)
  {
    j = i - 1;

    // create a vacant placeholder at A[i] and store the value in x
    x = A[i];
    while(j > -1 && A[j] > x)
    {
      //A[j+1] is always vacant, swap with the predecessor if necessary
      A[j+1] = A[j];
      j--;
    }

    //j would be one element to the left of the vacant element placeholder
    A[j+1]=x;
  }
}
```

Insertion sort does not swap elements of a sorted collection and compared to the bubble sort, does not need a `flag` value to exit a loop. Insertion sort would require O(n) comparisons and O(1) = 0 elements swapped, overall O(n) << O(n^2). Hence insertion sort is (intrinsically) adaptive. (In fact, both bubble sort and insertion sort are the only two sort methods described in this article which are adaptive.)

Insertion sort is also stable since it only swaps elements which are greater than or less than a previous element, not equal to other elements. The sequencing of identical elements is preserved.

## Selection sort ##

As demonstrated previously, the example shown here attempts to sort a collection in increasing order, with the lowest element coming first. 

The basis of selection sort concerns three pointers. One pointer `i` points to the element which can potentially be replaced. It starts at the beginning of the collection and is incremented after each pass. Pointer `j` traverses along the collection after pointer `i` and updates pointer `k` with the currently lowest found element, initially between pointers `i` and `j` but, if appropriate thereafter between pointers `j` and `k`.

![](/images/selectionSort.svg)

For the 2nd pass, all three pointers point to the next element (unlike the first pass, shown above). At the end of each pass, the elements given by pointers `i` and `k` are interchanged.

It is referred to as selection sort because one is looking/selecting an element from the collection to take the place of a given placeholder, which, in this example was the smallest value from all proceeding elements.

The total maximum number of comparisons is `n(n - 1)/2`, however, the total number of elements swapped is `n - 1`. The last point is demonstrated by the above example: one only swaps elements once the list is processed.

Intermediate passes of selection sort yield the smallest (or largest) value or values.

```cpp
void selectionSort(int A[],int n)
{
  int i, j, k;

  for(i = 0; i < n-1; i++)
  {
    for(j = k = i; j < n; j++)
    {
      if(A[j] < A[k])
        k = j;
    }
    swap(&A[i], &A[k]);
  }
}
```

If pointers `i` and `k` point to the same element (as they would during the 2nd pass onwards) then they would automatically swap with themselves. Selection sort does not check if the collection is already swapped, it would swap ordered elements and result in the same ordered collection, regardless of the state of the collection. Therefore, selection sort is not adaptive.

Selection sort is also not stable. Take a list: 2, 4, __2__, 1, 6. At some point during the first pass, the values 2 and 1 would be swapped resulting in 1, 4, __2__, 2, 6. The sequence of the two 2's is not preserved and thus selection sort is not stable.

## Quick sort ##

Perhaps the most well known sorting technique, quick sort looks at the position of an element in the collection which will never move places on sorting. All other elements might be misplaced, but there is sometimes one element which will never be swapped.

For example, the value 10 in the following collections (assume we are sorting with increasing value again):

+ 10, 13, 15, 11, 78 (10 is always first)
+ 1, 3, 2, 10, 33, 55, 26 (10 is always in the centre)
+ 2 , 4, 7, 4, 1, 10 (10 is always last)

The value 10 is in a 'sorted position'. In a way, quick sort describes the situation where the value itself finds it place. It does this by trying to arrange the other elements which should be to its left and to its right, without looking more closely at how elements to its left or right should be listed amongst themselves.

Place two pointers, one at the beginning of the collection and one at the end of collection. Make sure that both elements pointed to are in the right place as far as you are concerned (they should be to the left or right). Move either or both pointers towards the centre of the list until you find both are in the wrong place, then swap them.

![](/images/quickSort.svg)

The list is now partitioned into two lists, hence the method referred to as 'partitioning'. The element previously given by the pivot element is now referred to as the partitioning element. Quick sort is then repeated (usually through recursion) on each partitioned list until all elements are fully ordered. If a partition is made up of one element, then quick sort does not take place and no further action is taken place.

If one is presented with the list `10, 20`, then quick sort will swap pivot with itself. This is because pointer `i` will reach 20 (which is greater than 10) and pointer `j` will reach 10 (which is less than or equal to 10). In this case, the pivot element is the same as A[j]. Quick sort will always swap at least one element.

In practice, one processes pointer `i` first until `A[i] > pivot`. Then one processes the other pointer `j` until `A[j] <= pivot`.  The partitioning of a list is achieved as follows:

```cpp
//h is the definite 'upper limit + 1' of the array; A[h] is out of bounds; l is the lower in-bounds limit
int partition(int A[], int l, int h)
{
  //one could also pick a more central pivot element of a sorted list and reduce the time taken for partition() to execute
  int pivot = A[l];

  int i = l, j = h;

  //for a do-while loop, at least one iteration is carried out
  do{
      //traverse forwards with i
      do{i++;} while(A[i] <= pivot);
      //traverse backwards with j 
      do{j--;} while(A[j] > pivot);

      if(i < j)     
        swap(&A[i], &A[j]);
  } while(i < j);   

  swap(&A[l], &A[j]); //j will be in range here, so an array with one element will swap with itself
  return j;
}
```

Partitioning has a time complexity of O(n), for a list (or partition) with `n` elements.

Quick sort calls itself recursively (note that in the recursion, the element which takes the role of the pivot element changes):

```cpp
void QuickSort(int A[], int l, int h)
{
  int j;

  //l is low index, h is high index of array A; an array with one element has l = h
  if(l < h)
  {
    //set the partition element index j
    j = partition(A, l, h);

    //run partition again and sort elements on the LHS; the previous pivot element j becomes the new out-of-bounds index
    QuickSort(A, l, j);
    //run partition on the elements on the RHS
    QuickSort(A, j+1, h);
  }
}
```

The time complexity of quick sort is O(n^2) (more precisely a total of `n(n + 1)/2` comparisons, the sum `1 + 2 + ... + n`) when the collection is already ordered (increasing or decreasing). This represents the worst case degree.

![](/images/quickSort2.svg)

The first pass compared `n = 7` elements (because of pointer `j`), the second pass compared `n = 6` elements. A total of `1 + 2 + ... + n` comparisons or `n(n + 1)/2` comparisons were carried out. The passes with a list of elements in decreasing order results in the same analysis, except that the empty partition appears on the RHS.

If the pivot element chosen resides in the centre of the list, then overall it presents a somewhat faster O(n log[2] n) time complexity.

![](/images/quickSort3.svg)

There will be roughly `log[2] n` passes since the partition is split approximately in half. The product lists each have one partition element removed, that is, two partition elements are removed per pass. Compare this to the above example where one of the product lists is `NULL` and only one partition element is removed per pass. The time taken is therefore reduced to `log[2] n` passes. Approximating the number of comparisons as `n` per pass, it means that the time complexity for quick sort in which the partition element is located at the centre of the list is O(n log[2] n). This represents one of the best-cases of quick sort.

Selecting elements more central to the list may help reduce the time required to execute quick sort.

Selection sort focuses on finding the desired _element_ (the smallest or largest element to take the place of zeroth element) and placing it in a chosen/selected position (usually the zeroth element placeholder). Quick sort focuses on finding the _position_ (where all elements to the left and all elements to the right satisfy a certain criteria) and placing the chosen/selected element (the pivot element) there.

Quick sort is sometimes also referred to as 'selection exchange sort' or 'partition exchange sort'.