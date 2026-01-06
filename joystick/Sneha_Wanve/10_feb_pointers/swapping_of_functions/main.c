#include <stdio.h>
#include <stdlib.h>
void swap(int *a,int *b);
int main()
{   int a,b;
    scanf("%d %d",&a,&b);
    swap(&a,&b);

    return 0;
}
void swap(int *x,int *y)
{
    int z;
    z=*x;
    *x=*y;
    *y=z;
    printf("%d & %d",*x,*y);
}
