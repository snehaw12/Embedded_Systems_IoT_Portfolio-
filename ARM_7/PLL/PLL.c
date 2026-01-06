#include <lpc214x.h>
void PLL0(void);
int main(){
	PLL0 ();
}
void PLL0(void)
{
	PLL0CON=0x01;
	PLL0CFG=0x24;
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	while((PLL0STAT & (1<<10)) == 0);
	PLL0CON = 0x03;
	PLL0FEED= 0xAA;
	PLL0FEED= 0x55;
	VPBDIV = 0x00;
}
