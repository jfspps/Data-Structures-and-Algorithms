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
    int A[size];
    int length; //represents the number of elements which are not padded with zeros
}
```

### Operations on the array structure ###

We store the structure in the heap. For display functions we simply pass by value (a copy is temporarily stored in the stack) but for other operations which can edit elements, we pass by pointer.

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
Displat(arr1);  //this would print 2,3,4,5,6,10
```

We pass the address of `arr` to Append() and all other non-display functions.

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
