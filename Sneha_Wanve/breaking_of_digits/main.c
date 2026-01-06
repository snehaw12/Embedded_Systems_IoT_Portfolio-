#include <stdio.h>
#include <stdlib.h>

int main()
{int x = 1234;
int a,b,c,d;

    //scanf("%d",&a);
    a=x%10;         //a=4
    x=x/10;
printf("%d",a);
    b=x%10;        //b=3
    x=x/10;
printf("%d",b);
    c=x%10;        //c=2
    x=x/10;
printf("%d",c);
    d=x%10;
    x=x/10;      //d=1
printf("%d",d);
}
