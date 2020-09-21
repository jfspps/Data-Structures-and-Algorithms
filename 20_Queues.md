# The Queue data structure #

Queues operate on the FIFO principle. Elements are added at the rear of a queue and deleted from the front.

Queues are made up data types which are defined by the elements stored and two pointers, one which handles the front of the queue operations and one which handles the rear of the queue.

As with the stack, queue methods are standardised by name:

+ enqueue(x) - add an element x (to the rear of the queue)
+ dequeue() - remove the element (from the front of the queue)
+ isEmpty()
+ isFull()
+ first() - return the front element
+ last() - return the rear element

Queues can be implemented using either arrays or linked lists.

## Queues and arrays ##

An array in theory only requires one pointer to store the address of the rear element, since the array itself points to the front element. There are drawbacks to this however, as will be explained later.

Enqueueing takes O(1) time provided one knows the number of elements present. Dequeuing takes at worst O(n) time since each remaining element must be shuffled to the front of the array (following the FIFO principle).

### Using two pointers ###

To avoid shuffling the elements, one can instead employ two pointers and shift the position of the first element of the array. The array in memory is not changed during this process.

The condition `isEmpty` is true of `ptr(front) == ptr(rear)` _after_ the last element is removed from the array. That is, remove the element, check if `ptr(front) == ptr(rear)`. If true then the queue is empty, otherwise advance ptr(front). Repeat until `ptr(front) == ptr(rear)`. Some authors may prefer `ptr(front) > ptr(rear)` condition.

When applying two pointers, the condition `isFull()` is true when `ptr(rear) == array.size - 1`.

## Implementing queues with an array ##

First note that pointers described above are really indices, so the structure given below only uses a pointer to reference the start of an array in the heap.

```cpp
struct Queue
{
    int size;   //size of array Qarray at runtime
    int front = -1;
    int rear = -1;
    int * Qarray;
};
```

```cpp
void newQueue(struct Queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1; //if defaults are not already set
    q->Qarray = (int *) malloc(q->size * sizeof(int));
}
```

The enqueue() and dequeue() methods shift the indices before adding or removing elements:

```cpp
void enqueue(struct Queue *q, int x)
{
    if(q->rear == q->size - 1)
        printf("Queue is Full");
    else
    {
        q->rear++;
        q->
        Q[q->rear] = x;
    }
}

int dequeue(struct Queue *q)
{
    int x =- 1;
    if(q->front == q->rear)
        printf("Queue is Empty\n");
    else
    {
        q->front++;
        x = q->Q[q->front];
    }
    return x;
}
```
Both methods are constant time complexity. Notice here how the front and rear indices are always advanced forward, so at some point the queue must be reinitialised or the 'pointers' must be reset (otherwise one would find the queue is empty or full). Some of the array placeholders prior to the front pointer may be vacant.

By default, the pointers can be reset whenever the condition `isEmpty` is true. Another solution would be to employ circular queues.

## Circular queues ##

In a circular queue, the element pointed to by the front pointer is always vacant. The front and rear pointers advance but once they reach the end of the array, they are pointed to the beginning again. This ensures that the array is filled up to `size - 1` elements, unlike the non-circular queue described above.

A circular queue `isFull()` is true when the rear pointer is behind the front pointer. We use the remainder arithmetic, mod or `%` to deduce the next index.

```cpp
(q->rear + 1) % q->size == q->front;
```

For example, if rear points to element 7 of an array of size 8, and front is pointing to element 0, then the array is full. `8 % 8 == 0` is true. Similarly, if rear points to element 3 of an array of size 8, and front points to element 4 (which itself is always empty), then `4 % 8 == 4` is also true.

We move the rear pointer and then enqueue using:

```cpp
q->rear = (q->rear + 1) % q->size;
q->Q[q->rear] = x;
```

To dequeue, we advance the front pointer in the same way as the rear pointer. First we check if the queue is empty, and then dequeue.

```cpp
int x = -1;
if (q->front == q->rear)
{
    printf("Queue is empty");
}
else
{
    q->front = (q->front + 1) % q->size;

    //return x as method output
    x = q->Q[q->front];
}
return x;
```

As with non-circular queues, enqueue() and dequeue() are both O(1) time complexity.

## Queues and linked lists ##

