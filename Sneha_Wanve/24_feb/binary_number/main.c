#include <stdio.h>
#include <stdlib.h>
//Binary to decimal in loops
int main()
{
    int x,a,m=0,i=0,c,z,y=0;
    scanf("%d",&x);
    while (x>0){
        a=x%2;
        m=(m*10)+a;
        x=x/2;
        i++;
    }
    for (c=0;c<i;c++)
    {
        z=m%10;
        y=(y*10)+z;
        m=m/10;

    }
        printf("%d \n",y);
        return 0;
}
