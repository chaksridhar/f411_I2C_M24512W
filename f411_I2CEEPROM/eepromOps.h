#ifndef __EEPROMOPS_H__
#define __EEPROMOPS_H__
int16_t  EEPRomWrite (uint16_t address,  int8_t  value )  ;
int16_t  EEPRomRead (uint16_t address, int8_t *value) ;
uint8_t  EEPRomReset();
/*
b7   b6   b5   b4   b3     b2    b1   b0
1    0    1    0    E2     E1    E0    RW
*/
#define EEPROM_I2C_SLAVE_ADDRESS_WRITE_ADDRESS  0xA0
#define EEPROM_I2C_SLAVE_ADDRESS_READ_ADDRESS  0xA1
void delay (uint32_t millsecsec) ;
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0
#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0
#endif
