#include "UART.h"

void USARTNV(){
	
	GPIO_InitTypeDef PIN;
	NVIC_InitTypeDef NV;
	USART_InitTypeDef US;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE );
	USART_DeInit( USART1 );
	
	PIN.GPIO_Mode = GPIO_Mode_AF_PP;
	PIN.GPIO_Pin = GPIO_Pin_9;
	PIN.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &PIN );
	
	PIN.GPIO_Mode = GPIO_Mode_IPU;
	PIN.GPIO_Pin = GPIO_Pin_10;
	PIN.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &PIN );
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1 );
	NV.NVIC_IRQChannel = USART1_IRQn;
	NV.NVIC_IRQChannelPreemptionPriority = 1;
	NV.NVIC_IRQChannelSubPriority = 1;
	NV.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NV );
	
	US.USART_BaudRate = BOUND;
	US.USART_Parity = USART_Parity_No;
	US.USART_StopBits = USART_StopBits_1;
	US.USART_WordLength = USART_WordLength_8b;
	US.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	US.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( USART1, &US );
	USART_Cmd( USART1, ENABLE );
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );
	USART_ClearITPendingBit( USART1, USART_IT_RXNE );
	
}

void USART_SEND_DATA( USART_TypeDef* USARTx, uint8_t * dat ){
	
	while( *dat != '\0' ){
		while( USART_GetFlagStatus( USARTx, USART_FLAG_TC ) == 0 );
		USARTx -> DR = *dat;
		dat++;
		
	}
	
}
