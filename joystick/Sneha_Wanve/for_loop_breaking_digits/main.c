#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 1234;
    int a,b,c,d,i;

    for(i=1 ; i<=4 ; i++)
    {
        a=x%10;
        b=x/10;
        printf("%d \n",a);

    }
    return 0;

}
