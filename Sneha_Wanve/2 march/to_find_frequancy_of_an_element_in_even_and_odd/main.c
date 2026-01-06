#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[5];
    int i,x=0,y=0,e[5],o[5];

    printf("Enter 5 numbers in an array\n :");

    for (i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
    for (i=0;i<5;i++){
        if ((a[i]%2)==0){
            e[x]=a[i];
            x++;
        }
        else {
            o[y]=a[i];
            y++;
        }
    }

     for (i=0;i<5;i++){
          printf(" %d     %d\n",e[i],o[i]);
    }



    return 0;
}

//garbage value shouldnt be included in even & odd
//frequancy of odd even
