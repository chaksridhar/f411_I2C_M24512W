#include "device.h"
#include "eepromOps.h"

I2C_TypeDef  *I2CInst ;

int16_t  EEPRominit (I2C_TypeDef  *i2c)  {
    I2CInst = i2c ;
    return 0 ;
 }

int16_t  EEPRomWrite (uint16_t address,  int8_t  value ){
	    int16_t status , count = 0 ;

	    status = TM_I2C_Start(I2CInst, EEPROM_I2C_SLAVE_ADDRESS_WRITE_ADDRESS , I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	    if (status != 0)	return status ;
		status = TM_I2C_WriteData(I2CInst, (address &0xff00)>> 8);  // Send MSB address
		if ( status != 0)  return status ;
		delay(200) ;
		status = TM_I2C_WriteData(I2CInst, (address &0xff)); //// Send LSB Addresss
		if ( status != 0)  return status ;
		delay(200) ;
		status = TM_I2C_WriteData(I2CInst,value); // Send Data
		if ( status != 0)  return status ;
		delay(200) ;
		status = TM_I2C_Stop(I2CInst);;
		if ( status != 0)  return status ;
		return 0 ;
}

int16_t  EEPRomRead (uint16_t address, int8_t *value ){

	int16_t status=0 ;

	status = TM_I2C_Start(I2CInst, EEPROM_I2C_SLAVE_ADDRESS_WRITE_ADDRESS , I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE);
	if (0 != status ) return status ;
	status = TM_I2C_WriteData(I2CInst, (address &0xff00)>> 8);  // Send MSB address
	if ( status != 0)  return status ;
	status = TM_I2C_WriteData(I2CInst, (address &0xff));  // Send LSB Addresss
	if ( status != 0)  return status ;
	delay(1000);
	status = TM_I2C_Start(I2CInst, EEPROM_I2C_SLAVE_ADDRESS_READ_ADDRESS , I2C_RECEIVER_MODE, I2C_ACK_DISABLE);
	if ( status != 0)  return status ;
	delay(300) ;
    *value  = TM_I2C_ReadNack(I2CInst);

    delay(600);
	return 0  ;
	}


// 25 Mhz clock,
// 1 instruction     4 * 10 -8 second
// 25 instruction    1 mill second

void delay (uint32_t millisec)
{
	volatile int i= 0 ;
	while (millisec != 0) {
		for (i=0 ; i<=25 ; i++) ;
	 --millisec ;
	}
}






