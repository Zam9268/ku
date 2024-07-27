#include "ti_msp_dl_config.h"
#include "drv_spi.h"


uint8_t SPI_WriteByte(uint8_t Byte)
{
	while (DL_SPI_isBusy(SPI1));
	DL_SPI_transmitData8(SPI1, Byte);
	while(  DL_SPI_isRXFIFOEmpty(SPI1));
	//while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_RBNE));
	return DL_SPI_receiveData8(SPI1);
}


/****************SPI***************************/
/*------------D¡ä¨°???¨ºy?Y¡êo????¨¤-??-----------*/
void SPI_LCD_WrDat(unsigned char dat)
{
	OLED_CS_Clr();
  OLED_DC_Set();
  SPI_WriteByte(dat);//¡ä??¨ª8??¨ºy?Y¡êo¨º¡À?¨®??¨¤-¦Ì¨ª¨®DD¡ì
	OLED_CS_Set();
}


/*------------D¡ä?¨¹¨¢?¡êo????¨¤-¦Ì¨ª-------------*/
void SPI_LCD_WrCmd(unsigned char cmd)
{
	OLED_CS_Clr();
  OLED_DC_Clr();
	SPI_WriteByte(cmd);
  OLED_DC_Set();
	OLED_CS_Set();
}

