#include <stdio.h>
#include <stdlib.h>

int main()
{   //int x,y,z;
    int a[5];
    int b[5];
    int c[5];
    int i;
        //scanf("%d",&x);
        //scanf("%d",&y);
        //scanf("%d",&z);

    for(i=0;i<5;i++){
         scanf("%d",&a[i]);
        scanf("%d",&b[i]);
        //scanf("%d",&c[i]);
        }
    for(i=0;i<5;i++){
        c[i]=a[i];
        a[i]=b[i];
        b[i]=c[i];

    }
    for(i=0;i<5;i++){
        printf("%d   %d \n",a[i],b[i]);
        //printf("%d",b[i]);
       // printf("%d",&c);
    }
    /*for (i=0;i<5;i++){
        c[i]=a[i]+b[i];
        printf("%d",c[i]);
    }*/
    return 0;
    }
