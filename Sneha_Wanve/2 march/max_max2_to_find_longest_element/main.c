#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[5],max,max2,i,longest;
    printf("enter the elements of an array\n");
    for (i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
    max = a[0];
    max = a[1];
    for (i=2;i<5;i++){
        if(a[i]>max){
        max2 = max;
        max =a[i];
        }
    else if (a[i]>max2)
    {
        max2 = a[i];
    }
    }
    printf("print the longest element in an array is: %d", max2);
    return 0;
}

