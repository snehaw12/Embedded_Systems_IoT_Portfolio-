#include <stdio.h>
#include <stdlib.h>
// deleting an element from array
int main()
{   int a[7],i,j,k,n=5,c;

    printf("enter elements in an array \n ");
    for (i=0;i<n;i++){
            scanf("%d",&a[i]);
    }

    for (i=0;i<n;i++){
        for(j=(i+1);j<n;j++){
                if(a[i]==a[j]){
                  for(k=j;k<(n-1);k++){
                    a[k]=a[k+1];           // (==);- is a comparison operator
//So, instead of just comparing them, you need to use the assignment operator =.
//This tells the computer to put the value of a[k + 1] into a[k], effectively shifting all the elements after a[k] one step to the left.
//(== checks if two things are equal). (= puts the value of one thing into another.)
                  }
                  n--;
                  j--;
                }
        }
    }
        printf("enter elements in an array \n ");
    for(i=0;i<n;i++){
         printf("%d",a[i]);
    }
    return 0;
}
