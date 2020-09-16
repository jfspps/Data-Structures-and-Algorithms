# The Stack data structure #

Based on last-in first-out LIFO mechanism, a stack can be used to reverse the sequence of elements in an array or other data structure.

Recursive functions use the (system) stack portion of memory and operate on a LIFO basis. This contrasts to a programmer's stack. Some recursive functions can be converted into iterative functions, and _vice versa_.

The stack data is composed of a collection of elements (an array or linked list) and a pointer to the top of the stack (the address of the element at the top of the stack). There are several key operations:

+ Push(x) - add one element x
+ Pop() - remove one element
+ Peek(index) - viewing the value of an element at a particular point in the stack
+ stackTop() - viewing the uppermost element value
+ isEmpty() - boolean true if the stack is empty
+ isFull() - boolean true if the stack is full

## Implementing stacks with arrays ##

Declare an array of given size and set the pointer to -1. An array is filled starting from the zeroth index and the pointer is adjusted to point to the non-null element. Constant inserting at the head of the array would require constant reshuffling of the elements, so it is preferable to fill an array starting from the first element.

One uses a `struct` to define a stack:

```cpp
struct stack
{
    int size;           //decided at runtime
    int top;            //index of the uppermost element
    int * stackPtr;     //points to the uppermost element, an ultimately represents the array or linked list data type
};

//inside the main() function...

struct stack st;

//size required from another method or the user
//build a new array of required size in the heap with the pointer 
st.stack = new int[st.size];

//represents an empty stack (this will change soon enough), when isEmpty == true
st.top = -1;    
```

Note that the structure ADT is not tied to an array. The pointer stackPtr could just as easily point to the first node of a linked list.

### The push operation ###

Achieved generally as check if isFull() is false, then top++ and then assign the value to the element.

```cpp
void push(struct stack *st, int x) 
{
    if (st->top == st->size - 1)
    {
        printf("Stack is full");
    }
    else 
    {
        st->top++;
        st->stackPtr[st->top] = x;
    }
}
```

### The pop operation ###

The pop operation can be repeated if `top >= 0`.

```cpp
int pop(struct stack *st)
{
    int x = -1;
    if (st->top == -1)
    {
        printf("Stack is empty, nothing deleted");
    }
    else
    {
        x = st->stackPtr[st->top];
        st->top--;
    }
    return x;
}
```

### The peek operation ###

The `array index required = top - n + 1`, where n = 1, 2, 3, ... and represents the element starting from the uppermost element. If one wanted to peek at the 3rd element from the top, then the array index required would be `top - 3 + 1`.

```cpp
//return the appropriate type as required (assume that all elements in the stack are positive integers)

int peek (struct stack st, int positionFromTop)
{
    int x = -1;
    if (st.top - positionFromTop + 1 < 0)
    {
        printf("Invalid position");
    }
    else
    {
        x = st.stackPtr[st.top - pos + 1];
    }
    return -1;
}
```

### The stackTop() operation ###

In addition to using peek(), one can use a modified form to give stackTop().

```cpp
int stackTop(struct stack st) {
    if (st.top == -1){
        return -1;
    }
    return st.stackPtr[top];
}
```

### The isEmpty() operation ###

```cpp
int isEmpty(struct stack st) {
    if (st.top == -1){
        return 1;
    }
    return 0;
}
```

### The isFull() operation ###

```cpp
int isFull(struct stack st) {
    if (st.top == st.size - 1){
        return 1;
    }
    return 0;
}
```

### Displaying array based stacks ###

```cpp
void Display(struct stack st)
{
    int i;
    for(i = st.top; i >= 0; i--)
        printf("%d ", st.stackPtr[i]);

    printf("\n");
}
```

## Implementing stacks with linked lists ##

Unlike arrays, linked lists are filled at the beginning while resetting the pointer `top`.

Linked lists need not have `size` properties since linked lists are effectively not fixed in size as arrays are. Therefore, the definition of linked list based stacks are somewhat different:

```cpp
struct Node 
{
    int data;
    struct Node * next;
} * top = NULL;     //recall, top is now a global variable (pointer)
```

Note that top is already declared and accessible to any function which calls `top`. This demonstrates the difference when calling methods and passing parameters.

Within this scope, a linked list based stack is empty if `top == NULL` and full if pointer `t` is `NULL` following `Node * t = new Node;`. 

### Push operations on linked list based stacks ###

First check that the stack (that is, the heap) is not full before proceeding.

```cpp
void push(int x)
{
    //in the stack
    struct Node *t;

    //in the heap
    t = (struct Node*) malloc(sizeof(struct Node));
    if (t == NULL)
        printf("The stack (and heap) is full\n");
    else
    {
        t->data = x;

        //reset the uppermost pointer
        t->next = top;
        top = t;
    }
}
```

### Pop operations on linked list based stacks ###

```cpp
int pop()
{
    struct Node *temp;
    int x =- 1;

    if(top == NULL)
        printf("Stack is Empty\n");
    else
    {
        temp = top;
        top = top->next;
        x = temp->data;
        free(temp);        //or in C++ use delete(p)
    }
    return x;
}
```

### Peek operations on linked list based stacks ###

Since linked lists are filled 'from the beginning', one can pass the position required directly.

```cpp
//again, assume that the stack ADT stores positive integers

int peek (int positionFromTop)
{
    //sync the start of the linked list with a pointer p
    Node * p = top;

    for (int i = 0; p != NULL && i < positionFromTop - 1; i++)
    {
        p = p->next;
    }

    if (p != null)
    {
        return x;
    }
    return -1;
}
```

### The stackTop() operation ###

In addition to using peek(), one can use a modified form to give stackTop().

```cpp
int stackTop() {
    if (top){
        return top->data;
    }
    return -1;
}
```

### The isEmpty() operation ###

```cpp
int isEmpty() {
    if (top){
        return 0;
    }
    return 1;
}
```

### The isFull() operation ###

```cpp
int isFull() {
    Node * temp = new Node;

    if (!temp){
        return 0;
    }
    free{temp);
    return 1;
}
```

### Displaying linked list based stacks ###

```cpp
void Display()
{
    structNode *p;    
    p = top;
    while(p != NULL)    
    {
        printf("%d ", p->data);        
        p = p->next;    
    }
    printf("\n");
}
```

All array and linked list stack operations presented above are O(1) time complexity.