#ifndef _TFT_144_H_
#define _TFT_144_H_

#include "stm32f10x_conf.h"
#include <stdlib.h>

/* parameters */
#define WIDTH  128
#define LENGTH 128

/* pins definitions */
#define LA0	GPIO_Pin_6		// GPIOC
#define LSDI GPIO_Pin_15	// GPIOB
#define LSCL GPIO_Pin_13	// GPIOB
#define LCS GPIO_Pin_12		// GPIOB

#define LA0_SET() GPIOC->BSRR = 1<<6
#define LA0_CLR() GPIOC->BRR = 1<<6

#define LCS_SET() GPIOB->BSRR = 1<<12
#define LCS_CLR() GPIOB->BRR = 1<<12

/* functions */
void TFT_GPIO ( void );		// TFT的GPIO初始化
void TFT_MEM  ( void );		// 显存的分配
void TFT_INIT ( void );		// TFT初始化

#define LCMD 0		// 命令
#define LDAT 1		// 数据
void writeCmdData ( unsigned char Byte, unsigned char opt );

#define RED		0xf800
#define GREEN	0x07e0
#define BLUE	0x001f
#define YELLOW	0xffe0
#define BLACK	0x0000
#define WHITE	0xffff
void setPos( int sx, int ex, int sy, int ey );	// 设置绘图区域
void write2Byte( unsigned int twoByte );		// 写两个字节，因为color数据是16位
void writeAnColor( unsigned int color );		// 填充全屏

#endif
