#include <iostream>

using namespace std;

void permutation2(char [], int, int);
void swap(char &, char &);

int main()
{
    char test[] = "ABC";
    cout << "The permutations of " << test << " are " << endl;
    permutation2(test, 0, 2);
    return 0;
}

//l directs the starting point of the array to generate permutations (usually 0)
//h is the index of the char before null char (usually length - 1)
void permutation2(char S[], int l, int h)
{
    int i;

    if (l == h)
    {
        printf(S);
        printf("\n");
    }
    else
    {
        for (i = l; i <= h; i++)
        {
            swap(S[l], S[i]);
            permutation2(S, l+1, h);
            swap(S[l], S[i]);
        }
    }
}

void swap(char &x, char &y)
{
    char temp = x;
    x = y;
    y = temp;
}
