#include <stdio.h>
#include <stdlib.h>

int main()
{

    int pos,scan,element,i;
    scanf("%d%d",&scan,&pos);

    /*a[2]=a[3];
    a[3]=a[4];
*/
 for (i=0;i<scan;i++){
        scanf("%d",&a[i])

    }
     for (i=pos;i<(scan-1);i++){
        a[i]=a[i+1];
    }

    for(i=0;i<scan;i++){
        printf("%d",a[i]);
    }
    return 0;
}
