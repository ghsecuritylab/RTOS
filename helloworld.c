

/***************************** Include Files **********************************/

#include "xparameters.h"
#include "xspips.h"
#include "xil_printf.h"
#include "spi.h"
#include "pwm.h"
#include "platform.h"
#include "xil_io.h"

#include <stdio.h>
#include<stdlib.h>

/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define SPI_DEVICE_ID_0		XPAR_XSPIPS_0_DEVICE_ID
#define SPI_DEVICE_ID_1		XPAR_XSPIPS_1_DEVICE_ID
#define SENSOR_DATA_LEN 3
#define PWM_BASE XPAR_AXI_TIMER_0_BASEADDR

/************************** Variable Definitions ******************************/

XSpiPs Spi;			/* The instance of the SPI device */

u8 buff[3] = {1, 2, 3};

/******************************************************************************/
int main(void)
{
	spi_init(SPI_DEVICE_ID_1, &Spi);
	volatile u32 value;

	set_tare(Spi, buff, SENSOR_DATA_LEN);

	set_frequency( PWM_BASE, 2e-3);
	while (1)
	{
		value = sensor_read(Spi, buff, SENSOR_DATA_LEN);
		weight_pwm(PWM_BASE, 2e-3, value);
		//sleep(1);
		usleep(180000);
	}
	return 0;
}
