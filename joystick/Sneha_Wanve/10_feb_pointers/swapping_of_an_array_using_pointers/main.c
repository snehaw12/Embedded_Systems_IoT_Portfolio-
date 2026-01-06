#include <stdio.h>
#include <stdlib.h>

int main()
{
    int y[5],x[5],z[5],*p,i,*q,*r; //declaration
    r=&z;//initialization
    q=&x;
    p=&y;
    printf("Enter the value of 5 numbers: \n");
    for (i=0;i<5;i++)
    {
        scanf("%d",q);
        q++;
    }
    //q=&x;
    for (i=0;i<5;i++)
    {
        scanf("%d",p);
        p++;
    }

  p=&y;
  q=&x;
  r=&z;

   for (i=0;i<5;i++)
    {
      *r=*p;
      *p=*q;
      *q=*r;
      p++;
      q++;
      r++;

    }
    p=&y;
    q=&x;
    for (i=0;i<5;i++)
    {
        printf("%d\n",*q);
        q++;
    }

    for (i=0;i<5;i++)
    {
        printf("%d\n",*p);
        p++;
    }

    return 0;
}
