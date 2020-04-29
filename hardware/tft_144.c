#include "tft_144.h"

unsigned short int* LCD_MEM;

void TFT_GPIO ( void ) {

	SPI_InitTypeDef MYSPI;
	GPIO_InitTypeDef TFTIO;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	
	MYSPI.SPI_Mode = SPI_Mode_Master;
	MYSPI.SPI_CPOL = SPI_CPOL_High;
	MYSPI.SPI_CPHA = SPI_CPHA_2Edge;
	MYSPI.SPI_FirstBit = SPI_FirstBit_MSB;
	MYSPI.SPI_DataSize = SPI_DataSize_8b;
	MYSPI.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	MYSPI.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	MYSPI.SPI_NSS = SPI_NSS_Soft;
	SPI_Init( SPI2, &MYSPI );
	SPI_Cmd( SPI2, ENABLE );
	
	TFTIO.GPIO_Mode = GPIO_Mode_Out_PP;
	TFTIO.GPIO_Speed = GPIO_Speed_50MHz;
	TFTIO.GPIO_Pin = LA0;
	GPIO_Init( GPIOC, &TFTIO );
	
	TFTIO.GPIO_Mode = GPIO_Mode_AF_PP;
	TFTIO.GPIO_Speed = GPIO_Speed_50MHz;
	TFTIO.GPIO_Pin = LSDI|LSCL|LCS;
	GPIO_Init( GPIOB, &TFTIO );

}

/* assemble the video memory */
void TFT_MEM  ( void ) {
	LCD_MEM = (unsigned short int*)\
			  malloc( sizeof(unsigned short int)*( WIDTH*LENGTH ) );
}

void TFT_INIT ( void ) {

	TFT_GPIO();
	//TFT_MEM();
	
	writeCmdData(0x28, LCMD);
	writeCmdData(0x11, LCMD);//Sleep exit 
		
	//ST7735R Frame Rate
	writeCmdData(0xB1, LCMD); 
	writeCmdData(0x01, LDAT); 
	writeCmdData(0x2C, LDAT); 
	writeCmdData(0x2D, LDAT); 

	writeCmdData(0xB2, LCMD); 
	writeCmdData(0x01, LDAT); 
	writeCmdData(0x2C, LDAT); 
	writeCmdData(0x2D, LDAT); 

	writeCmdData(0xB3, LCMD); 
	writeCmdData(0x01, LDAT); 
	writeCmdData(0x2C, LDAT); 
	writeCmdData(0x2D, LDAT); 
	writeCmdData(0x01, LDAT); 
	writeCmdData(0x2C, LDAT); 
	writeCmdData(0x2D, LDAT); 
	
	writeCmdData(0xB4, LCMD); //Column inversion 
	writeCmdData(0x07, LDAT); 
	
	//ST7735R Power Sequence
	writeCmdData(0xC0, LCMD); 
	writeCmdData(0xA2, LDAT); 
	writeCmdData(0x02, LDAT); 
	writeCmdData(0x84, LDAT); 
	writeCmdData(0xC1, LCMD); 
	writeCmdData(0xC5, LDAT); 

	writeCmdData(0xC2, LCMD); 
	writeCmdData(0x0A, LDAT); 
	writeCmdData(0x00, LDAT); 

	writeCmdData(0xC3, LCMD); 
	writeCmdData(0x8A, LDAT); 
	writeCmdData(0x2A, LDAT); 
	writeCmdData(0xC4, LCMD); 
	writeCmdData(0x8A, LDAT); 
	writeCmdData(0xEE, LDAT); 
	
	writeCmdData(0xC5, LCMD); //VCOM 
	writeCmdData(0x0E, LDAT); 
	
	writeCmdData(0x36, LCMD); //MX, MY, RGB mode 
	writeCmdData(0xC8, LDAT); //ÊúÆÁC8 ºáÆÁ08 A8	
	
	//ST7735R Gamma Sequence
	writeCmdData(0xe0, LCMD); 
	writeCmdData(0x0f, LDAT); 
	writeCmdData(0x1a, LDAT); 
	writeCmdData(0x0f, LDAT); 
	writeCmdData(0x18, LDAT); 
	writeCmdData(0x2f, LDAT); 
	writeCmdData(0x28, LDAT); 
	writeCmdData(0x20, LDAT); 
	writeCmdData(0x22, LDAT); 
	writeCmdData(0x1f, LDAT); 
	writeCmdData(0x1b, LDAT); 
	writeCmdData(0x23, LDAT); 
	writeCmdData(0x37, LDAT); 
	writeCmdData(0x00, LDAT); 	
	writeCmdData(0x07, LDAT); 
	writeCmdData(0x02, LDAT); 
	writeCmdData(0x10, LDAT); 

	writeCmdData(0xe1, LCMD); 
	writeCmdData(0x0f, LDAT); 
	writeCmdData(0x1b, LDAT); 
	writeCmdData(0x0f, LDAT); 
	writeCmdData(0x17, LDAT); 
	writeCmdData(0x33, LDAT); 
	writeCmdData(0x2c, LDAT); 
	writeCmdData(0x29, LDAT); 
	writeCmdData(0x2e, LDAT); 
	writeCmdData(0x30, LDAT); 
	writeCmdData(0x30, LDAT); 
	writeCmdData(0x39, LDAT); 
	writeCmdData(0x3f, LDAT); 
	writeCmdData(0x00, LDAT); 
	writeCmdData(0x07, LDAT); 
	writeCmdData(0x03, LDAT); 
	writeCmdData(0x10, LDAT);  
	
	writeCmdData(0xF0, LCMD); //Enable test command  
	writeCmdData(0x01, LDAT); 
	writeCmdData(0xF6, LCMD); //Disable ram power save mode 
	writeCmdData(0x00, LDAT); 
	
	writeCmdData(0x3A, LCMD); //65k mode 
	writeCmdData(0x05, LDAT); 
	
	writeCmdData(0x29, LCMD);//Display on
	
	writeAnColor( YELLOW );

}

void writeCmdData ( unsigned char Byte, unsigned char opt ) {
	if ( opt == LCMD ) {
		LA0_CLR();
	} else if ( opt == LDAT ) {
		LA0_SET();
	}
	LCS_CLR();
	SPI_I2S_SendData( SPI2, Byte );
	while( !( (SPI2->SR)&(SPI_I2S_FLAG_TXE) ) );
	LCS_SET();
}

void setPos( int sx, int ex, int sy, int ey ) {

	writeCmdData( 0x2a, LCMD );
	writeCmdData( 0x00, LDAT );
	writeCmdData( sx+2, LDAT );
	writeCmdData( 0x00, LDAT );
	writeCmdData( ex+2, LDAT );
	
	writeCmdData( 0x2b, LCMD );
	writeCmdData( 0x00, LDAT );
	writeCmdData( sy+3, LDAT );
	writeCmdData( 0x00, LDAT );
	writeCmdData( ey+3, LDAT );
	
	writeCmdData( 0x2c, LCMD );
}

void write2Byte( unsigned int twoByte ) {
	writeCmdData( twoByte>>8, LDAT );
	writeCmdData( twoByte, LDAT );
}

void writeAnColor( unsigned int color ) {
	unsigned char x = 0;
	unsigned char y = 0;
	setPos( 0, 127, 0, 127 );
	for ( y = 0; y < LENGTH; y++ ) {
		for ( x = 0; x < WIDTH; x++ ) {
			write2Byte( color );
		}
	}
}
