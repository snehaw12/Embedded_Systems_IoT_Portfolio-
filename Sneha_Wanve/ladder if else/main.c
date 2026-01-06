#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a;
    scanf("%c",&a);
    if ((a>='0')&&(a<='9'))
    {
       printf("a is num");
    }
    else if ((a>='A')&&(a<='Z') ||  (a>='a')&&(a<='z'))
    {
        printf("a is aul");
    }
    else
        printf("a is special");

    return 0;

}
