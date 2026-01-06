#include <stdio.h>
#include <stdlib.h>

int main()
{
    float A,B,C,D,E,avg,per;
    float p;
    scanf("%f%f",&A,&B);
    avg=((A-B)/B)*100 ;
    printf("Average is %f",avg);
    per =((A+B+C+D+E)/500)*100;
    printf("percentage is %f",per);
    return 0;
}
