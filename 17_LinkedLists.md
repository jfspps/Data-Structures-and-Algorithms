# Linked lists #

 A linked list a collection of __nodes__ which contain a value (data) sometimes referred to as the _key_ and an address to the next node. Unlike arrays, these have potentially unlimited memory capacity (hardware memory dependent) and are distributed over the heap. Linked lists are not stored in the stack.

 The first node or _head node_ (pointer) points to the second node, which contains the first value. The head node does not possess a data value but is merely a pointer which resides in the stack. Subsequent nodes reside in the heap.

Linked lists can be implemented by structures:

```cpp
struct Node
{
    int data;
    struct Node* next;  //an example of a self-referential structure
};
```

Since `int` pointers occupy the same amount of memory as the value they reference, a single node above requires twice the memory of the data type. The head node can be declared in C with:

```cpp
struct Node * p;
p = (struct Node *) malloc(sizeof(struct Node));
```

In C++, the Node can defined by a class or a structure. As a structure, the first node is declared with C++ using:

```cpp
struct Node * p;
p = new Node;

//access the data values

p->data = 10;
p->next = 0;    //points to nothing; a null pointer NULL
```

## Moving along the linked list ##

A useful set of statements in which the head node traverses the linked list is given below:. Pointer `q` is the temporary pointer which traverses across the linked list. Pointer `p` is initially located in the stack, as the head node.

```cpp
struct Node *p, *q;
q = p;          // assign q to the location of p->data
q = p->next;    // move q to the data of the next node (p->next is itself a pointer to the next data value)

//check if q != NULL (or effectively, !(p->next)) then continue...

p = p->next;    // move p to the data of the next node
```

A null pointer has an address of zero, a pointer is `NULL` or `!pointer` is true. Pointers which point to some definite address are `true`.

## Displaying (and counting the number of nodes of) linked lists ##

In C and C++, with structures:

```cpp
struct Node
{
int data;
struct Node *next;
}*first=NULL;   //first is a global pointer to Node

void Display(struct Node *p)
{
    while(p!=NULL)
    {

        //insert a counter > 1 here to record the number of nodes processed...

        printf("%d ", p->data);
        p = p->next;
    }
}
```

The recursive form of Display can be constructed as follows:

```cpp
void RecursiveDisplay(struct Node *p)
{
    if(p!=NULL)
    {
        RecursiveDisplay(p->next);
        printf("%d ", p->data);
    }
}
```

Note that the above RecursiveDisplay also displays the nodes in reverse order. Changing the order so that we have a tail recursion, as opposed to head recursion, will print the nodes in the order they appear starting from the head node.

In C++, with classes:

```cpp
class Node{
public:
    int data;
    Node* next;
};

//somewhere in main() or some other calling function (nullptr is a C++ keyword)
    Node* p = head;
 
    while (p != nullptr){
        cout << p->data << " -> " << flush;
        p = p->next;
    }
```

Both recursive and iterative forms of Display() are time complexity of O(n). The space complexity for recursive form is also O(n+1) or just O(n), compared to iterative which is a constant O(1). 

## Creating a linked list ##

A linked list can be initialised from an array `A`, of length `n`. __This pattern is applied for many of the examples outlined below.__

```cpp
struct Node
{
    int data;
    struct Node *next;
}*first = NULL, *second = NULL, *third = NULL;

void newLinkedList(int A[], int n)
{
    int i;
    struct Node *temp, *last;

    //build the first, head node (simply a pointer) and initialise the second node (key and pointer)
    first=(struct Node *) malloc(sizeof(struct Node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    //build the self-referential struct Node, in Node.
    for(i = 1; i < n; i++)
    {
        temp = (struct Node*) malloc(sizeof(struct Node));      //new node created somewhere on the heap
        temp->data = A[i];                                      //fill with key with array data
        temp->next = NULL;                                      //set the next node location as NULL (signifies the 'new end')
        last->next = temp;                                      //update the previous node's NULL pointer to point to temp's 'data'
        last = temp;                                            //set pointer last to point to temp's key

        //by now, the temp node is part of the growing linked list...
    }
}
```

## Linked list functions ##

### The node count and summing the nodes ###

The sum of all nodes and the number of nodes in a linked list can be implemented by cycling through `while` loops, incrementing or summing as long as the `Node` pointer `p->next == true`. The sum code is commented in the node count function below:

```cpp
int count(struct Node *p)
{
    int l = 0;
    // int s=0;
    while(p)
    {
        l++;
        // s += p->data;
        p = p->next;
    }
    return l;
}

//the recursive form is...

int RecursiveCount(struct Node *p)
{
    if(p!=NULL)
        return RecursiveCount(p->next) + 1;
    else
        return 0;
}
```

### Finding the largest and smallest node ###

One can traverse through the entire linked list to find the largest key (and similarly the smallest key).

```cpp
int Max(struct Node *p)
{
    int max = INT32_MIN;
    while(p)
    {
        if(p->data > max)
            max = p->data;
        p = p->next;
    }
    return max;
}
```

### Searching linked lists ###

Searching linked lists is generally quite expensive compared to arrays. One could perform a linear search, processing each node until the required node data is found.

Improvements to the linear search of linked lists borrows from the improvements to linear searching of arrays. Recall, for arrays:

1. `Transposition`: where the required element is moved one place closer to the initial first element `A[0]` and if necessary, substituting the initial element. This makes subsequent searches for the same element faster.
2. `Move to head/front`: where the required swaps places with the initial element. This is particularly useful if the element is frequently sought after with all other elements mostly neglected.

For linked lists, it is more convenient to code the second improvement, move-to-front.

For linked lists, we move nodes as opposed to swapping the key between nodes. In this case, we have two pointers, one as a tail-pointer which follows (and is one node behind) the key pointer. Upon finding the key, we assign the tail pointer to the address of the node after the key pointer. The code is given below:

```cpp
struct Node * LinearSearch(struct Node *lead, int key)
{
    struct Node *tail = 0;
    while(lead != NULL)
    {
        if(key == lead->data)
        {
            tail->next = lead->next;
            lead->next = first;
            first = lead;
            return lead;
        }

        tail = lead;          //move tail pointer one node forward
        lead = lead->next;    //move leading pointer one node forward
    }
    return NULL;
}
```

### Inserting nodes into a linked list and creating linked lists ###

First create a new node anywhere in the heap. Then decide where in the linked list the new node will be inserted.

+ Inserting at the beginning is O(1) time complexity. After declaring the new node, assign the data value and set the new node's `next` pointer to point to the first data node in the linked list. Change the first pointer (in the stack) address so that it points to the new data of the new node.

+ Inserting a new node at a given node `N` anywhere after the first node is more involved. Build a new node somewhere in the heap. Traverse the linked list `N-1` times with a pointer `p` which was initially set to the first node (use a `for` loop). Set the new node's `next` pointer to match `p->next`, then change `p->next` to point to `N`. The time complexity here is worst-case, O(N). Compare this inserting into an array which is similarly expensive.

The code (with the structure repeated for reference) is given below for both cases:

```cpp
struct Node
{
    int data;
    struct Node *next;
}*first=NULL, *second=NULL, *third=NULL;

void Insert(struct Node *p, int index, int x)
{
    struct Node *newNode;
    int i;
    if(index < 0 || index > count(p))
        return;
    newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = x;
    if(index == 0)
    {
        newNode->next = first;
        first = newNode;
    }
    else
    {
        for(i = 0; i < index-1; i++)
            p=p->next;

        newNode->next = p->next;
        p->next = newNode;
    }
}

int count(struct Node *p)
{
    int l = 0;
    while(p)
    {
        l++;
        p = p->next;
    }
    return l;
}
```
Incidentally, the `insert()` method can be looped to create a new linked list, extending from the beginning or end, or inserting somewhere in between nodes.

To insert a new node after the last node only, the time complexity is constant O(1), as long as you know the address of the first and last nodes.

```cpp
struct Node
{
    int data;
    struct Node *next;
}*first=NULL, *second=NULL, *third=NULL;

insertLast(int x)
{
    Node * t = new Node;
    t->data = x;
    t->next = NULL;
    if (!first)
    {
        //if the linked list is empty
        first = t;
        last = t;
    }
    else 
    {
        last->next = t;
        last = t;
    }
}
```

### Sorted linked lists ###

One can check if a linked list is sorted by calling the function `isSorted()`:

```cpp
int isSorted(struct Node *p)
{
    int min = -65536;
    while(p != NULL)
    {
        if(p->data < x)
            return 0;

        min = p->data;
        p = p->next;
    }
    return 1;
}
```

This achieved by traversing along the linked list, comparing the data value and incrementing the pointer value at the same time.

```cpp
struct Node
{
    int data;
    struct Node *next;
}*first=NULL, *second=NULL, *third=NULL;

void insertInSorted(struct Node *p, int x)
{
    struct Node *newNode, *trailing = NULL;
    newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;

    if(first == NULL)
        //if the linked list is empty
        first = newNode;
    else
    {
        //traverse along the linked list, while reassigning the trailing pointer
        while(p && p->data<x)
        {
            trailing = p;
            p = p->next;
        }

        if(p == first)
        {
            newNode->next = first;
            first = newNode;
        }
        else
        {
            newNode->next = trailing->next;
            trailing->next = newNode;
        }
    }
}
```

### Deleting nodes ###

The most important step to remember here is to free the memory that the deleted node occupies. Use `free`.

```cpp
//assume here that the linked list holds integers, the type returned
int Delete(struct Node *p, int index)
{
    struct Node *trailing = NULL;
    int x = -1, i;
    if(index < 1 || index > count(p))
        return -1;
    
    if(index == 1)
    {
        trailing = first;
        x = first->data;
        first = first->next;
        free(trailing);     //use free() if malloc was used; use delete, an operator, if new was used
        return x;
    }
    else
    {
        for(i = 0; i < index-1; i++)
        {
            trailing = p;
            p = p->next;
        }
        trailing->next = p->next;
        x = p->data;
        free(p);        //use free() if malloc was used; use delete, an operator, if new was used
        return x;
    }
}
```

### Deleting nodes with duplicated data in a sorted linked list ###

The essential approach here is the compare adjacent node data values and free the node if the values are equal.

```cpp
void removeDuplicate(struct Node *p)
{
    struct Node *trailing = p->next;
    while(trailing != NULL)
    {
        if(p->data != trailing->data)
        {
            //move along the list
            p = trailing;
            trailing = trailing->next;
        }
        else
        {
            p->next = trailing->next;
            free(trailing);
            trailing = p->next;
        }
    }
}
```

### Reversing a linked list ###

### Concatenating and merging linked lists ###

## Looped/circular linked lists ##

## Doubly linked lists ##

## Comparing arrays to linked lists ##