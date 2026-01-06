#include <stdio.h>
#include <stdlib.h>
//To find longest element in an array7
int main()
{
    int a[5],i;
    int max=0;

    printf("enter the number of elements in an array\n");

    for (i=0;i<5;i++)
    {
      scanf("%d",&a[i]);
    }


    for (i=0;i<5;i++){
        if(a[i]>max){
        max=a[i];
        }
    }
    printf("%d",max);


    return 0;
}
