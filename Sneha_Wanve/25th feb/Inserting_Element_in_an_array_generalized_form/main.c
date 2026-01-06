#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pos,scan,element,i;
    int a[5];
      scanf("%d%d%d",&scan,&pos,&element);  //scanning of all the variables
    for (i=0;i<scan;i++){                   //for loop & scanning the elements
        scanf("%d",&a[i]);
    }

    /*a[4]=a[3];
    a[3]=a[2];
    a[2]=a[1];
    a[1]=5;
*/
    for(i=scan;i>pos;i--){
        a[i]=a[i-1];
    }
    a[pos]=element;
    for (i=0;i<=scan;i++){           //total number of elements has increased by 1
      printf("%d",a[i]);
    }
    return 0;
}
