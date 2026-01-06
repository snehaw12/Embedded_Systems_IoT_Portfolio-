#include <stdio.h>
#include <stdlib.h>
// inserting_an_element_in_an_array
int main()
{
    int array[100],position,i,n,value;

    printf("enter the number of elements in an array\n");
    scanf("%d",&n);

    printf("Enter %d elements\n",n);

    for (i=0;i<n;i++)
            scanf("%d",&array[i]);

    printf("Enter the location where you wish to insert an element\n");
            scanf("%d",&position);
    printf("Enter the value to insert\n");
    scanf("%d",&value);

    for (i=n-1;i>=position-1;i--)               //n-1=6-1, refer from notebook for array index
    array[i+1]=array[i];                        //5+1=6,,80 moved to array of 6
                                                //array[4]=array[5] array decreamented
    array[position-1]=value;                    //

    for(i=0;i<=1;i++)
            printf("%d\n",array[i]);


    return 0;
}
