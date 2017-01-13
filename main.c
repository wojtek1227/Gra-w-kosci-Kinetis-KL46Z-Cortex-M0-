#include "MKL46Z4.h"
#include "slcd.h"
#include "tpm.h"
#include "buttons.h"

int main(void)
{
	slcdInitialize();
	while(1)
	{
		slcdDisplay(1234,10);
	}
}
