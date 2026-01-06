#include <stdio.h>
#include <stdlib.h>

int main()
{   int i=0;
    int a[5];

    for (i=0;i<4;i++){
    scanf("%d",&a[i]);
    }

    a[4]=a[3];
    a[3]=a[2];
    a[2]=a[1];
    a[1]=5;


    for (i=0;i<5;i++){
      printf("%d",a[i]);
    }
    return 0;
}
