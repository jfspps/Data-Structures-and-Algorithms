#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int *A;
    int n;
};

void Set(struct Matrix *m,int i,int j,int x)
{
    if(i>=j)
        m->A[m->n*(j-1)+(j-2)*(j-1)/2+i-j]=x;
}

int Get(struct Matrix m,int i,int j)
{
    if(i>=j)
        return m.A[m.n*(j-1)+(j-2)*(j-1)/2+i-j];
    else
        return 0;
}

void DisplaySymmetric(struct Matrix m)
{
    int i,j;

    for(i=1;i<=m.n;i++)
    {
        for(j=1;j<=m.n;j++)
        {
            if(i>=j)
                //print the lower triangle as before
                printf("%d ",m.A[m.n*(j-1)+(j-2)*(j-1)/2+i-j]);
            else
                //unlike displaying lower triangular matrices, invert indices i and j and print
                printf("%d ",m.A[m.n*(i-1)+(i-2)*(i-1)/2+j-i]);
        }
        printf("\n");
    }
}

int main()
{
    struct Matrix m;
    int i,j,x;
    printf("Enter Dimension\n");
    scanf("%d",&m.n);
    m.A=(int *) malloc(m.n*(m.n+1)/2 * sizeof(int));
    printf("enter all elements\n");

    for(i=1;i<=m.n;i++)
    {
        for(j=1;j<=m.n;j++)
        {
            scanf("%d",&x);
            Set(&m,i,j,x);
        }
    }
    printf("\n\n");
    DisplaySymmetric(m);
    return 0;
}
