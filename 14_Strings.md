# Strings in C and C++ #

American Standard Code for Information Interchange `ASCII` codes start from 0 and end at 127, so a total of 128 bits, or 7-bits. In memory, each representation is usually stored as one byte, or 8 bits.

Codes 65-90 are A-Z. The character 'A' (single quotes) is stored as the value 65 in one byte of memory. For lowercase a-z, they are codes 97-122. The ASCII numerical codes for 0-9 are 48-57. The constant offset of 32 allows one to change the case of any character or character in a string.

Other languages, including Japanese, Chinese, Hindi etc. are defined in Unicode.

Let `temp = 'A';`. Other than using `cout << temp`, a character can be printed with `printf()` as `printf("%c", temp);`.

### Array of characters ###

Declare `char arrayOfChars[10];`. One can also initialise each element on declaration.

The size of the array can be determined without defining its length, using `char arrayOfChars[] = {'A', 'B'};`. This array `charOfArrays` would have a length of 2. Similarly, the ASCII codes can be used instead: `char arrayOfChars[] = {65, 66};`. Furthermore, the following conditional statement is valid: `if (someChar >= 'b') {...}`.

An array with a defined length but fewer initialisations lead the compiler to pad zeros (literally) to uninitialised elements.

Strings are array of characters. In C and C++, the first zero padded element is '/0' (slash-zero), a null character/string delimiter/string terminator/end of string character (marker). This signals the end of the string.

String lengths are determined by the position of the delimiter.

## Printing and scanning strings ##

One can use the aforementioned array of characters approach, including the '/0' character.

One can use double quotes: `char aString[] = "My name is ";`. The null character is automatically appended. At present the string `aString` is stored in the stack frame of the parent function.

One can declare a pointer to string, in which case, the string is stored in the heap and the string pointer is held in the stack. The statement `char* aString = "My name is ";` without brackets achieves this. One can dereference the pointer as normal with `*aString`.

The argument for `printf()` to print a string is `%s` as: `printf("%s", aString);`. The command `cout` needs `cout << aString;`. 

User input is achieved similarly with `scanf()` and `cin`. Note that `scanf` stops reading at the next whitespace character. To read a string with whitespace, use get-String `gets()`.

## Finding the length of a string ##

This method is provided in the standard libraries and (like many methods in this course) are outlined to illustrate and understand their operations.

```cpp
int main()
{
    char* s = "greetings";
    int i;
    for (i = 0; s[i] != '/0'; i++)
    {
        //keep cycling through to the end
    }
    printf("Length of the string is %d", i);
    return 0;
}
```

The above method forms the basis of other string traversing routines (changeCase(), numberOfVowels(), containsAZaz(), isPalindrome etc.). For example:

```cpp
int main()
{
    char s[] = "greetings";
    int word = 0;
    for (int i = 0; s[i] != '/0'; i++)
    {
        if (s[i] == ' ' && s[i-1] != ' ')
            word++;
    }
    printf("There are %d word(s) in the string", word);
    return 0;
}
```

## Reversing a string ##

Strings are usually immutable (compiler dependent) though they can be utilised as mutable by declaring the string as an array of characters, as shown below:

```cpp
int main()
{
    char A[] = "dude";
    int i, j;
    char temp;
    for (j = 0; j != '\0'; j++)
    {
        //go to the delimiter
    }
    j--;
    for (i = 0; i < j; i++, j--)
    {
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}
```

One can modify the above reversing algorithm to define isPalindrome().

```cpp
int main()
{
    char A[] = "dude";
    int i, j;
    char temp;
    for (j = 0; j != '\0'; j++)
    {
        //go to the delimiter
    }
    j--;
    for (i = 0; i < j; i++, j--)
    {
        if (A[i] != A[j])
            printf("The string %s is not a palindrome", A);
            break;
    }
}
```