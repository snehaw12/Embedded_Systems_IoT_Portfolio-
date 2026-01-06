#include <stdio.h>
#include <stdlib.h>
//printing how many numbers are odd or even in arrays
int main()
{   int e=0,o=0,i=0,number;
    int a[5];
    for(i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
     for(i=0;i<5;i++){
         if(a[i]%2){
            e++;
         }
    else
        o++;
     }
        printf("%d %d",e,o);
    return 0;
}
