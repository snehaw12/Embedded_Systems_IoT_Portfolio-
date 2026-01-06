#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20],i,n,garbage_value;
    int j=0,k=0,e[20],o[20];

    printf("entering the value of 30 elements \n ;");

    for (i=0;i<20;i++){
        scanf("%d",&a[i]);
    }
    for (i=0;i<20;i++){
        if((a[i]%2)== 0){
        e[j]=a[i];
        j++;
        }
    else {
        o[k]=a[i];
        k++;
    }
}
    printf("print even numbers;");
    for (i=0;i<j;i++){
        printf("%d\n",e[i]);
    }
    printf("print odd number:");
      for (i=0;i<k;i++){
        printf("%d\n",o[i]);
    }


    return 0;
}
