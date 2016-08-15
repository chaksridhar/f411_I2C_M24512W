#include "device.h"

#include "eepromOps.h"
#define BUF_SIZE  100



void initLED () ;
#define GPIO_PROGRESS GPIO_Pin_12
#define GPIO_FAILED GPIO_Pin_13
#define GPIO_COMPLETED GPIO_Pin_15

#define  START_EEPROM_ACCESS_ADDRESS 10
#define  END_EEPROM_ACCESS_ADDRESS 100
int main()  {

	uint16_t index ;
    int8_t value ;
	SystemInit() ;

    /*
    generate correct timings. The peripheral input clock frequency must be at least:
    • 2 MHz in Sm mode
    • 4 MHz in Fm mode
*/
    SystemCoreClockUpdate ();
    RCC_PCLK2Config(RCC_HCLK_Div4);
    initLED () ;


   //  GPIOB, GPIO_PIN_B8=>SCL  (CB.2) GPIO_PIN_B9 =SDA  (CB.3) I2C1 Pin pack -2
    //GPIO_PIN_B6=>SCL  (CB.3 ) GPIO_PIN_B7 = SDA CB.2  I2C1  Pin pack -1
    TM_I2C_Init(I2C1, TM_I2C_PinsPack_1,10000) ;
    EEPRominit ( I2C1) ;


    value = 0 ;
    uint8_t ledStatus = 0 ;

    for (index=START_EEPROM_ACCESS_ADDRESS;  index < END_EEPROM_ACCESS_ADDRESS; index ++) {
        int status = EEPRomWrite ( index,   index+10) ;
        ledStatus = !ledStatus ;

         if (status != 0) {
        	   GPIO_WriteBit(GPIOD,GPIO_FAILED, 1);
        	        	   while (1) ;

         }
         GPIO_WriteBit(GPIOD,GPIO_PROGRESS , ledStatus);
        delay(1000);

    }
    for (index=START_EEPROM_ACCESS_ADDRESS;  index < END_EEPROM_ACCESS_ADDRESS ; index ++) {
    	  value = 0 ;
    	  int status ;
          status = EEPRomRead( index,   &value) ;
          ledStatus = !ledStatus ;
           if  (status != 0 || value !=  (index +10)) {
        	   GPIO_WriteBit(GPIOD,GPIO_FAILED, 1);
        	   while (1);
           }
           GPIO_WriteBit(GPIOD,GPIO_PROGRESS , ledStatus);
           delay(500);
       }

    delay(500) ;
    GPIO_WriteBit(GPIOD,GPIO_COMPLETED, SET);
    delay(500);


    while (1);
}


void initLED ()
{
	   GPIO_InitTypeDef myGpiostruct;

	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	    myGpiostruct.GPIO_Mode=GPIO_Mode_OUT;
	    myGpiostruct.GPIO_OType=GPIO_OType_PP;
	    myGpiostruct.GPIO_Pin=GPIO_PROGRESS | GPIO_FAILED | GPIO_COMPLETED;
	    myGpiostruct.GPIO_PuPd=GPIO_PuPd_UP;
	    myGpiostruct.GPIO_Speed=GPIO_Speed_50MHz;
	    GPIO_Init(GPIOD,&myGpiostruct);

	    GPIO_WriteBit(GPIOD,GPIO_PROGRESS,Bit_SET);
	    GPIO_WriteBit(GPIOD,GPIO_FAILED,Bit_RESET);
	    GPIO_WriteBit(GPIOD,GPIO_COMPLETED,Bit_RESET);


}


