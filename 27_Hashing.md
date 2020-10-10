# Hashing techniques #

Hashing supports search methods. The simplest example involves the searching of integers. Suppose an array [2, 3, 6, 10, 0, 5] is stored in an array, how would one find the value 3? With hashing one could store all the elements in another array (or other data structure, known as the _hash table_) in which the value of the element (the value is known as the _key_) forms the basis of the index of the element where it is stored. That is:

a set `[2, 3, 6, 10, 0, 5]` is stored in the hash table `B [-1, -1, 2, 3, -1, 5, 6, -1, -1, -1, 10]`

One can find any key (for now, between 0 and 10) by passing B[value]. If the key exists it will be returned, if not then a `-1` flag will be returned. This requires constant O(1). There are a number of limitation with the approach so far.

+ Restricted to values between 0 and 10. A larger hash table would be needed to store large values
+ A lot of memory is redundant, with `-1`'s stored

We address these problems by setting up a mathematical function: a range given by a set and a domain given by the set. We then build mappings or mathematical functions to facilitate hashing.

So far, our function is H(x) = x, where the value maps itself in a one-to-one approach. In this form, H(x) is an 'ideal hashing' mapping. One could reduce the memory required by modifying H(x) as `H(x) = x mod 10` or `H(x) = x % 10`, this restricts the indices to single figures, which in decimal means there will be 0 - 9 or 10 elements in the hash table available. Then:

`[2, 3, 6, 10, 0, 15]` could be stored in an array of ten (not 15) elements, `B [-1, 10, 2, 3, -1, 15, 6, -1, -1, -1]`

The problem now is how to store two keys which are mapped to the same index (try storing key 35 in B, above). This results in a __collision__ between two keys. The hashing function H(x) = x % 10 is thus an example of a many-to-one function. There are two main approaches to addressing collisions:

+ Open hashing (characteristic of using dynamic memory allocation)
  - Chaining
+ Closed hashing (characteristic of using fixed memory allocation)
  - Open addressing (mapping is not strict if collision occurs)
    1. Linear probing
    2. Quadratic probing
    3. Double hashing

## Open hashing: chaining ##

Think about implementing an array of linked lists as the hash table. This keeps the hash table to a minimal size and circumvents collisions. The linked lists are populated in an orderly state so as to assist with searching within a linked list. The linked lists resemble chains, hence the method is referred to as chaining.

![](/images/chaining.svg)

By sorting the elements in the linked list, one can quickly ascertain if the key is present by comparing magnitudes and stopping the search if the next node stores a key whose magnitude is greater.

The analysis of hashing functions is based on the load factor ` lambda = n/(hash table size)`. It represents the number of keys stored per hash table placeholder (how many nodes are linked per hash table element) assuming that all keys are equally distributed in the hash table.** Clearly, the higher the factor, the more consecutive comparisons are needed to reach (find) the latter nodes in a given chain. The load factor is taken as a measure of the maximum number of comparisons needed, the average is taken as half of this value.

The average time required to search for any key which is present is given by `O(1) + lambda/2`. The average time required to search for any key which is not present is given by `O(1) + lambda`.

The deletion of a key presents one extra step, map with O(1), search for the key (consider lambda). Then delete the node (and update pointers).

** The load factor and any analysis regarding load factors are only valid when the appropriate hash function has been selected such that it distributes all keys evenly. For example, a set of integers, all 'ending' with the digit 5 would only be stored in one linked list and thus present a less than efficient algorithm. It is expected that the programmer selects the correct hash function based on the dataset. There is no one universal hash function which accommodates all datasets.

```cpp
//assume here that the methods sortInsert() and search() call established linked list methods
#define SIZE 10

int getHashTableIndex(int key){
    return key % SIZE;
}

void insert(struct Node *H[], int key){
    int hashIndex = getHashTableIndex(key);

    sortInsert(&H[hashIndex], key);
}

//general form of main given below
void main()
{
    struct Node *hashTable[SIZE];
    struct Node *temp;

    int i;
    int key = 12;

    for (i = 0; i < SIZE; i++){
        hashTable[i] = NULL;
    }

    insert(hashTable, 12);
    //...

    temp = search(hashTable[getHashTableIndex(key)], key);

    //this will return an error if not key is not found
    printf("%d ", temp->data);
}
```