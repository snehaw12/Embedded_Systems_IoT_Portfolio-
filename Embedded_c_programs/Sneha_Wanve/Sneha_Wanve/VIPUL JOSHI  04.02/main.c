#include <stdio.h>
#include <stdlib.h>

int main()
{
    float p,s,proft;
    scanf ("&f",&p);
    scanf ("&f",&s);
    proft=((s-p)*100);
    printf("profit percent is %f ", proft);
    return 0;
}
