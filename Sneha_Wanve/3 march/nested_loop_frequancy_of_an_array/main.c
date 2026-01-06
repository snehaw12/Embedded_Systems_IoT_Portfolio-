#include <stdio.h>
#include <stdlib.h>
//printing repeated value
int main()
{   int a[5],c=1,i,j;
    printf("Enter the 5 elements;\n");

    //initialization of an array
    for(i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
//logic
    for(i=0;i<5;i++){
        for(j=i+1;j<5;j++){
            if(a[i]==a[j])
            {
                c++;
                i++;
            }
        }
        printf("%d is repeated %d times  \n",a[i],c);
        c=1;
    }

    return 0;


}

