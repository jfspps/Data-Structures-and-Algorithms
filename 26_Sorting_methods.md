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