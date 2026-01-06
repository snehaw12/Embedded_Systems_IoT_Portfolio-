#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[9],i,*p,c=0,n=0,sc=0;
    gets(a);
    p=&a;

    for (i=0;i<5;i++)
    {

     if  ( (a[i]>='A' && a[i]<='Z') ||  (a[i]>='a' && a[i]<='z') )
    {
       c++;
    }

    else if ((a[i]>='0') && (a[i]<='9'))
    {
            n++;
    }

    else
    {
            sc++;
    }
    }


      printf(" numbers:%d;\n",n);

      printf("alphabets:%d;\n",c);

      printf("special charactors:%d;\n",sc);
    /*for (i=0;i<5;i++)
    {
        scanf("%c",&a);
    }

    printf("enter alhabet/n");
    if ((a>='0')&&(a<='9'))
    {
        printf("number /n;");
    }

    else if  ((a>='A')&&(a<='Z'))
    {
        printf("letter is an alphabet/n;");
    }

    else
        printf("number is an speial charactors/n;");

    for (i=0;i<5;i++)
    {
        printf("%c",a);
    }
*/
    return 0;
}
