#include <stdio.h>
#include <stdlib.h>
//inserting elements into arrays
int main()
{   int a[10];
    int i=0;
    //scanf("%d",&a[i]);
    printf("print Elements:");

    for (i=0;i<4;i++){
       scanf("%d",&a[i]);
    }
    a[4]=a[3];
    a[3]=a[2];
    a[2]=a[1];
    a[1]=3;
    for(i=0;i<5;i++){
        printf("%d",a[i]);
    }
    return 0;
}
