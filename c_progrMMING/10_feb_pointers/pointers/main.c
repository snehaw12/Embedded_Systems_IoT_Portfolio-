#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[5],*p,i;
    p=&a;

    printf("Enter the value of 5 numbers \n:");

    for (i=0;i<5;i++)
    {
        scanf("%d",p);
        p++;
    }
    p=&a;
    for (i=0;i<5;i++)
    {
        printf("%d",*p);
        p++;
    }
    return 0;
}
