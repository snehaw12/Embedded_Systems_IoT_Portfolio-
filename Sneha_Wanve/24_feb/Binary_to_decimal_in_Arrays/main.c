#include <stdio.h>
#include <stdlib.h>
//Binary to decimal in arrays
int main()
{
    int x,a,m=0,i=0,c,z,y=0;
    int k[5];

    scanf("%d",&x);

    while (x>0){
       k[i]=x%2;
    //   m=(m*10)+a;
       x=x/2;
       i++;
   }
    for (c=(i-1);c>=0;c--)
   // {
        //z=m%10;
       // y=(y*10)+z;
       // m=m/10;
       // scanf("%d",&k[i]);
   // }
    //for (i=0;i<5;i++){
      //  printf("%d",k);
   // }
        printf("%d",k[c]);
        return 0;
}
