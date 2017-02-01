#include "main.h"


char usart_buf[16];
char str[17];
int count = 0;

//--------------------------------------------------------------------------
void USART3_IRQHandler(void) 
{
//	if(USART_GetITStatus(USART3, USART_IT_TXE))//���� ���������� �� ��������
//	{
//	USART_ClearITPendingBit(USART3, USART_IT_TXE);//������� ����
//		usart_buf = USART_ReceiveData(USART3);		
/*		if(usart_buf[count]!= 0)
		{
			USART_SendData(USART3, usart_buf[count]);
			count++;
		}
		else 
				count = 0;
				USART_ITConfig(USART3, USART_IT_TXE, DISABLE);//��������� ���������� �� ��������
*/		
	if(USART_GetITStatus(USART3, USART_IT_RXNE))//���� ���������� �� ��������
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);//������� ����
		if(count<16)
		{
			usart_buf[count] = USART_ReceiveData(USART3);
			USART_SendData(USART3, usart_buf[count]);	
			count++;
		}
		else
		{			
			count = 0;
			USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
		}
	}

}
//--------------------------------------------------------------------------

int main()
{

	init_delay();
//	init_perif();
	LCD_init_pin();
	LCD_init();
	LCD_write_str("Hello!");
	usart_init();
//	sprintf(usart_buf, "Hi Lapa! ");
//	USART_SendData(USART3, *usart_buf);
	while(1)
	{
		delay_ms(50);
		kursor_adress(SEC_LINE);
		LCD_write_str(usart_buf);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������� ���������� �� ������
//		usart_txstr(str);
//		USART_SendData(USART3, usart_buf[count]);
//		count++;
//		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//�������� ���������� �� ��������
	}
	
}
