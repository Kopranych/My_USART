#include "usart.h"




//---------------------------------------------------------------------------------
void usart_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	GPIO_InitTypeDef usart_bus;
	USART_InitTypeDef usart1;
	
	usart_bus.GPIO_Pin = TX|RX;
	usart_bus.GPIO_Mode = GPIO_Mode_AF;
	usart_bus.GPIO_Speed = GPIO_Speed_50MHz;
	usart_bus.GPIO_OType = GPIO_OType_PP;
	usart_bus.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(USART_BUS, &usart_bus);
	GPIO_PinAFConfig(USART_BUS, GPIO_PinSource8, GPIO_AF_USART1);
	GPIO_PinAFConfig(USART_BUS, GPIO_PinSource9, GPIO_AF_USART1);
	
	usart1.USART_BaudRate = 9600;//
	usart1.USART_WordLength = USART_WordLength_8b;//
	usart1.USART_StopBits = USART_StopBits_1;
	usart1.USART_Parity = USART_Parity_No;//бит четности
	usart1.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//аппаратный контроль потока RTS CTS

	USART_Init(USART3, &usart1);
	USART_Cmd(USART3, ENABLE);
	
	
	NVIC_EnableIRQ(USART3_IRQn);//разрешаем обшие прерывания


	
}
//---------------------------------------------------------------------------------
void usart_txstr(char* str)
{
	while(*str)
	{
		while(!(USART_GetFlagStatus(USART3, USART_FLAG_TC)));
		USART_SendData(USART3, *str);	
		str++;
	}
}
//---------------------------------------------------------------------------------



