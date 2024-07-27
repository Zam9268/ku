#ifndef drv_spi_h
#define drv_spi_h



#define OLED_RST_Clr() DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_16)
#define OLED_RST_Set() DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_16)

#define OLED_DC_Clr() DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_17)
#define OLED_DC_Set() DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_17)


#define OLED_CS_Clr()  DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_20)
#define OLED_CS_Set()  DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_20)


void SPI_LCD_WrDat(unsigned char dat);
void SPI_LCD_WrCmd(unsigned char cmd);


#endif






