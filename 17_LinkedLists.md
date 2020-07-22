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

In C++, the node can defined by a class or a structure. As a structure, the first node is declared with C++ using:

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

+ Inserting a new node at a given node `N` anywhere after the first node is more involved. Build a new node somewhere in the heap. Traverse the linked list `N-1` times with a pointer `p` which was initially set to the first node (use a `for` loop). Set the new node's `next` pointer to match `p->next`, then change `p->next` to point to `N`. The time complexity here is worst-case, O(N). Compare this to an insertion into an array which is similarly expensive.

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

Two methods can reverse the nodes of a linked list.

+ Interchanging the elements (the values)
+ Interchanging the links (the pointers)

The latter method is generally preferred. Linked list nodes reside at seemingly random positions in the heap and so it would be largely meaningless to interchange data values when the resultant list is also randomly distributed. Instead, one should change the direction of the link, given be Node's `next` pointer.

#### Interchanging the elements ####

Initialise an (auxiliary) array of the same length as the linked list. Copy across all the elements to the array. Then re-assign all elements of the linked list in the reverse order.

```cpp
void changeElements(struct Node *p)
{
    int *A, i = 0;
    struct Node *q = p;
    A = (int *) malloc(sizeof(int)* count(p));

    //fill the auxiliary array and move the pointer q along the linked list
    while(q != NULL)
    {
        A[i] = q->data;
        q = q->next;
        i++;
    }
    q = p;
    i--;

    //re-assign the linked list in the reverse order
    while(q != NULL)
    {
        q->data = A[i];
        q = q->next;
        i--;    //we're going backwards...
    }
}
```

The time complexity is O(2n) or just O(n). The method requires the movement of data (with a type which must be known) between linked lists and arrays.

#### Interchanging the links: sliding (tailing) pointers

This starts with three pointers. The three pointers `p`, `q` and `r` occupy three consecutive nodes. The central node is the node which is modified at the time. The first and third pointer are needed to recall the previous pointer values. 

The method effectively reverses the 'direction' of the link to the next node. Instead of pointing the next node, the pointer is changed so that it points to the previous node.

```cpp
void changeLinks(struct Node *p)
{
    struct Node *q=NULL, *r=NULL;

    while(p!=NULL)
    {
        // first three statements slide the pointers r, p and q
        r = q;
        q = p;
        p = p->next;

        //reverse the direction of the link
        q->next = r;
    }
    first=q;
}
```

This approach is much simpler. Data need not be exchanged.

The recursive version of changeLinks(), in outline, slides to the end of the linked list from the beginning. The function terminates and the previous call re-assigns the link. In the method below, pointer `tail = NULL` and pointer `p` should point to the second node.

```cpp
void changeLinksRecursive(struct Node *tail, struct Node *p)
{
    //keep calling itself until p reaches the last node, where 
    if(p)
    {
        changeLinksRecursive(p, p->next);
        //initially, q now points to the first node and tails pointer p
        //when p == null, the direction of the last link is reversed
        p->next = tail;
    }
    else
        //Node's first
        first = tail;
}
```

### Concatenating and merging linked lists ###

Two linked lists can be joined be setting the `last` property of the last node (in one list) to the address of the second node of another linked list.

```cpp
//two nodes A and B
p = A;
while (p->next != NULL)
{
    p = p->next;
}
p->next = B;
B = NULL;   //previously pointed to the second node of Node B
```
The time complexity depends on the number nodes in Node A, so O(n).

One can also combine two sorted linked lists into a single linked list (specifically, _merging_) is somewhat analogous to the code needed to merge two sorted arrays, with the exception of data transfer. Briefly, one checks the value at both linked lists and re-assigns the link.

```cpp
struct Node
{
    int data;
    struct Node *next;
}*first = NULL, *second = NULL, *third = NULL;

//merge two Node, p and q
void Merge(struct Node *p, struct Node *q)
{
    struct Node *last;
    if(p->data < q->data)
    {
        third = last = p;
        p = p->next;
        third->next = NULL;
    }
    else
    {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }

    while(p && q)
    {
        if(p->data < q->data)
        {
            last->next = p;
            last = p;
            p = p->next;
            last->next = NULL;
        }
        else
        {
            last->next = q;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }

    if(p)
        last->next = p;
    if(q)
        last->next = q;
}
```

Follow the above code with the schematic below for the first few iterations:

![](/images/mergingLinkedLists.svg)

The pointer last trails pointers `p` and `q`. The last assignments link pointer 'last' to remaining nodes of one linked list. Note that pointers `p` or `q` can be more than one node ahead of the other.

## Looped/circular linked lists ##

A _looped linked list_ does not have any node with a `NULL` pointer at the last node. The looped linked list possesses a last node which points to any other node in the _same_ linked list. Linked lists described thus far do have a last node with a `NULL` pointer, and are known as _linear linked lists_.

One can check for looped linked lists by

+ comparing the address of all nodes and finding a repeated address
+ comparing the value of all nodes which are unique, and looking for repeated values
+ using two pointers, and racing them around the loop until they meet

We describe the last option here.

One pointer will migrate forward by two nodes (faster) and the other pointer will migrate by one node. At some point in a looped linked list (although not necessarily during the first lap) both pointers will be assigned to the same node. If one of the pointers ends up being `NULL` then the linked list is not looped. 

The length of the loop section is always less than `n` and determines how long it takes for the two pointers to 'coincide'. The time complexity is O(n).

```cpp
int isLoop(struct Node *f)
{
    struct Node *p, *q;
    // start at the beginning of Node f
    p = q = f;

    //start the race and continue until a NULL pointer is found or p == q
    do
    {
        p = p->next;
        q = q->next;
        // q is advanced an extra node ahead during each iteration
        q = q ? q->next : q;
    }
    while((p && q) && (p != q));

    if(p == q)
        return 1;
    else
        return 0;
}
```

## Linked Lists in C++ ##

The following implementation in C++ will be used in the later part of this article.

```cpp
#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
};

class LinkedList
{
private:
    Node *first;
public:
    LinkedList(){first = NULL;}
    LinkedList(int A[], int n);
    ~LinkedList();
    void Display();
    void Insert(int index, int x);
    int Delete(int index);
    int Length();
};

LinkedList::LinkedList(int A[], int n)
{
    Node *last, *t;
    int i = 0;
    first = new Node;
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(i = 1; i < n; i++)
    {
        t = new Node;
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

LinkedList::~LinkedList()
{
    Node *p = first;
    while(first)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

void LinkedList::Display()
{
    Node *p = first;
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int LinkedList::Length()
{
    Node *p = first;
    int len = 0;
    while(p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void LinkedList::Insert(int index, int x)
{
    Node *t, *p = first;
    if(index <0 || index > Length())
        return;

    t = new Node;
    t->data = x;
    t->next = NULL;
    if(index == 0)
    {
        t->next = first;
        first = t;
    }
    else
    {
        for(int i = 0; i < index-1; i++)
            p = p->next;

        t->next = p->next;
        p->next = t;
    }
}

int LinkedList::Delete(int index)
{
    Node *p, *q = NULL;
    int x = -1;
    if(index < 1 || index > Length())
        return -1;
    
    if(index == 1)
    {
        p = first;
        first = first->next;
        x = p->data;
        delete p;
    }
    else
    {
        p = first;
        for(int i = 0; i < index-1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        delete p;
    }
    
    return x;
}
```

## Doubly linked lists ##

## Comparing arrays to linked lists ##