#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,s,proft;
    scanf ("&d",&p);
    scanf ("&d",&s);
    proft=((s-p)/p)*100;
    printf("profit percent is %d ", proft);
    return 0;
}
