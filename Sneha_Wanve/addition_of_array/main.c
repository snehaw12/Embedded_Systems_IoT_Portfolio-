#include <stdio.h>
#include <stdlib.h>

int main()
{   int i,sum;
    int a[5];
    int b[5];
    int c[5];

    for (i=0;i<5;i++){

        scanf("%d",&a[i]);
    }
    for (i=0;i<5;i++){
        scanf("%d",&b[i]);
    }
    for (i=0;i<5;i++){
        c[i]=a[i]+b[i];
        printf("%d",c[i]);
    }


    return 0;
}
