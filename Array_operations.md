# Array operations in C++

### The dot (.) and arrow (->) operators ###
The dot operator is used to call a given method or member (of a structure) on an object which was passed by reference. See Display(), below, for an example.

The arrow operator is used when the object was passed as a pointer. See Append() for an example.

### The array structure ###

The following examples are based on an array structure, with three variables.

```cpp
struct Array
{
    int size;
    int A[size];    //represents the number of elements with user-defined values
    int length; //represents the number of elements which are not padded with zeros
}
```

### Operations on the array structure ###

We store the structure in the heap. For display functions we simply pass by value (a copy is temporarily stored in the stack) but for other operations which can edit elements, we pass by pointer.

### Dot and arrow operators

The dot `(.)` operator calls a method on the given object when the object was passed by value. See `Display()` below for an example. If the object was passed by pointer then the arrow operator `(->)` is used instead. See `Append()` for an example.

## Displaying and appending to an array

```cpp
void Display(struct Array arr)
{
    int i;
    printf("\nElements are\n");
    for(i=0; i<arr.length; i++)
        printf("%d ", arr.A[i]);
}

//somewhere in main(){}
struct Array arr1 = {5, {2,3,4,5,6},10};
Display(arr1);
```
The add() operation increases `length` and changes a padded zero element accordingly. Append() is the same as add().

```cpp
void Append(struct Array *arr, int x)
{
    if(arr->length < arr->size)
        arr->A[arr->length++] = x;
}

//somewhere in main(){}
struct Array arr1 = {5, {2,3,4,5,6},10};
Display(arr1);
Append(&arr1, 10);
Display(arr1);  //this would print 2,3,4,5,6,10
```

We pass the address of `arr` to Append() and all other non-display functions.

## Inserting to and deleting from an array

The insertion function insert() starts the last element and copies all preceding elements until the point of insertion `index` is reached.

```cpp
void Insert(struct Array *arr, int index, int x)
{
    int i;
    if(index >= 0 && index <= arr->length)
        {
        for(i = arr->length; i > index; i--)
            arr->A[i] = arr->A[i-1];
        arr->A[index] = x;
        arr->length++;
        }
}

//somewhere in main(){}
Insert(&arr1, 0, 12);
```

The deletion operation delete() finds the given element by its index and then shifts subsequent elements down by one element. In this method, we return the integer stored at the given index.

```cpp
int Delete(struct Array *arr, int index)
{
    int x = 0;
    int i;
    if(index >= 0 && index < arr->length)
    {
        x = arr->A[index];
        for(i = index; i < arr->length-1; i++)
            arr->A[i] = arr->A[i+1];
        arr->length--;
        return x;
    }
    return 0;
}

//somewhere in main(){}
struct Array arr1 = {{2,3,4,5,6}, 10, 5};
printf("%d", Delete(&arr1, 0));     //prints 2
Display(arr1);      //prints 3,4,5,6
```

## Reversing an array

Apart from creating an array in which the elements are copied back to front, a more efficient algorithm is the immediate swapping of elements in the given array when the initial counter `i` is less than the second counter `j`. We pass by pointer this time since we want to change the elements' values.

```cpp
void Reverse2(struct Array *arr)
{
    int i, j;
    for(i = 0, j = arr->length-1; i < j; i++, j--)
    {
        swap(&arr->A[i], &arr->A[j]);
    }
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
```

## Inserting an element in a sorted array

The approach here is to check the value that is to be inserted and the element (for example) at the end of the array. If a condition is met then shift the last element down the array. Continue with this until the element in the array is less than the value to be inserted. No need to check all other preceding elements.

```cpp
void insertIntoSorted(struct Array *arr, int newElement){
    int i = arr->length - 1;

    //check that there is space to insert the element
    if (arr->length == arr->size){
        return;
    }

    //shift the values
    while (i >= 0 && arr->A[i] > x){
        arr->A[i+1] == arr->A[i];
        i--;
    }

    arr->A[i] = x;
    arr->length++;
}

