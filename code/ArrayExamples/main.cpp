#include <iostream>

using namespace std;

struct Array
{
    int size;           //represents the number of elements with user-defined values
    int length;         //represents the total number of elements currently available
    int A[20];
};

void findMissingSorted(struct Array);
void findMultipleMissingSorted(struct Array, struct Array*);
void findDuplicates(struct Array);
void findDuplicatesUnsorted(struct Array);
void findPairWithSum(struct Array, int);
void findPairWithSumSorted(struct Array, int);
void findMaxAndMin(struct Array);

int main()
{
    struct Array array1 = {11, 11, {1,2,3,4,5,6,8,9,10,11,12}};
    int reply;

    //1. Finding a missing element in a sorted array (should be between element indices 5 and 6)
    cout << "Example 1, finding a missing element in a sorted array.\n";
    findMissingSorted(array1);
    cout << "\n";

    //2. Finding multiple missing elements in a sorted array (should be 5, 8 and 9); store a persistent array of results as an added feature
    cout << "Example 2, finding missing elements in a sorted array.\n";
    struct Array array2 = {11, 11, {1,2,3,4,5,6,8,9,10,12,15}};
    struct Array tally2 = {array1.size, array2.length, {0}};
    findMultipleMissingSorted(array2, &tally2);
    cout << "\n";

    //3. Finding duplicates in an array
    cout << "Example 3, finding duplicates in an array.\n";
    struct Array array3 = {11, 11, {1,2,2,4,5,6,6,9,10,12,15}};
    findDuplicates(array3);
    cout << "\n";

    //4. Finding duplicates in an unsorted array
    cout << "Example 4, finding duplicates in an unsorted array.\n";
    struct Array array4 = {11, 11, {15,2,2,4,25,6,6,10,10,10,15}};
    findDuplicatesUnsorted(array4);
    cout << "\n";

    //5. Finding a pair of elements with the sum K
    int sum = 10;
    cout << "Example 5, finding a pair of elements with the sum of " << sum << "\n";
    struct Array array5 = {11, 11, {15,2,2,6,25,6,6,10,0,10,12}};
    findPairWithSum(array5, sum);
    cout << "\n";

    //6. Finding a pair of elements with the sum K in a sorted array
    int sum2 = 6;
    cout << "Example 6, finding a pair of elements with the sum of " << sum2 << " in a sorted array.\n";
    struct Array array6 = {11, 11, {1,2,2,4,5,6,6,9,10,12,15}};
    findPairWithSumSorted(array6, sum2);
    cout << "\n";

    //7. Finding max and min in a single scan
    cout << "Example 7, finding the max and min in one scan of an array\n";
    struct Array array7 = {11, 11, {15,2,2,66,25,0,6,140,10,0,15}};
    findMaxAndMin(array7);
    cout << "\n";

    return 0;
}

//1. Finding a missing element in a sorted array
void findMissingSorted(struct Array arr)
{
    int current;
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i+1] - arr.A[i] > 1)
        {
            cout << "Found a missing value between element: " << i << ", value change of " << arr.A[i] << " to " << arr.A[i+1] << "\n";
            return;
        }
    }
    cout << "Nothing missing here";
}

//2. Finding multiple missing elements in a sorted array
void findMultipleMissingSorted(struct Array arr, struct Array* tally)
{
    bool found = false;
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i+1] - arr.A[i] > 1)
        {
            tally->A[i] = -1;
            cout << "Found a missing value between element: " << i << ", value change of " << arr.A[i] << " to " << arr.A[i+1] << "\n";
            found = true;
        }
        else
            tally->A[i] = 0;
    }
    if (!found)
        cout << "Nothing missing here";
}

//3. Finding duplicates in an array
void findDuplicates(struct Array arr)
{
    bool found = false;
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i+1] == arr.A[i])
        {
            cout << "Found duplicate values at elements " << i << " and " << i+1 << " with a value of " << arr.A[i] << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "Nothing missing here";
}

//4. Finding duplicates in an unsorted array
void findDuplicatesUnsorted(struct Array arr)
{
    //temp records the index where the duplicate is found
    struct Array temp = {arr.size, arr.length, {0}};
    bool found = false;

    for (int i = 0; i < arr.length ; i++)
    {
        for (int j = i+1; j < arr.length; j++)
        {
            if (arr.A[i] == arr.A[j])
            {
                temp.A[i] = j;
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        for (int i = 0; i < temp.length; i++)
        {
            if (temp.A[i] > 0)
            {
                cout << "Found duplicate values at elements " << i << " and " << temp.A[i] << " with a value of " << arr.A[i] << "\n";
            }
        }
    }
    else
    {
        cout << "No duplicates found";
    }
}

//5. Finding a pair of elements with the sum 'sum'
void findPairWithSum(struct Array arr, int sum)
{
    //temp records the index where the other operand is found
    struct Array temp = {arr.size, arr.length, {0}};
    bool found = false;

    for (int i = 0; i < arr.length ; i++)
    {
        for (int j = i+1; j < arr.length; j++)
        {
            if (arr.A[i] + arr.A[j] == sum)
            {
                temp.A[i] = j;
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        for (int i = 0; i < temp.length; i++)
        {
            if (temp.A[i] > 0)
            {
                cout << "Found two values at elements " << i << " and " << temp.A[i] << " with a sum of " << sum << "\n";
            }
        }
    }
    else
    {
        cout << "No operands found";
    }
}

//6. Finding a pair of elements with the sum K in a sorted array
void findPairWithSumSorted(struct Array arr, int sum)
{
    //temp records the index where the other operand is found
    struct Array temp = {arr.size, arr.length, {0}};
    bool found = false;

    for (int i = 0; i < arr.length ; i++)
    {
        for (int j = i+1; (arr.A[i] + arr.A[j]) < sum, j < arr.length; j++)
        {
            if (arr.A[i] + arr.A[j] == sum)
            {
                temp.A[i] = j;
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        for (int i = 0; i < temp.length; i++)
        {
            if (temp.A[i] > 0)
            {
                cout << "Found two values at elements " << i << " and " << temp.A[i] << " with a sum of " << sum << "\n";
            }
        }
    }
    else
    {
        cout << "No operands found";
    }
}

//7. Finding the max and min of an array in one scan
void findMaxAndMin(struct Array arr)
{
    if (arr.length < 2)
    {
        cout << "Need an array of size >= 2" << "\n";
        return;
    }

    int minimum, maximum;
    if (arr.A[0] >= arr.A[1])
    {
        minimum = arr.A[1];
        maximum = arr.A[0];
    }
    else
    {
        minimum = arr.A[0];
        maximum = arr.A[1];
    }

    for (int i = 2; i < arr.length; i++)
    {
        if (arr.A[i] < minimum)
        {
            minimum = arr.A[i];
        }
        else if (arr.A[i] > maximum)
        {
            maximum = arr.A[i];
        }
    }
    cout << "The maximum value is " << maximum << " and the minimum value is " << minimum << "\n";
}

