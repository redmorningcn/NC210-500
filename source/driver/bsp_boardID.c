/*******************************************************************************
* Description  : ���豸���
* Author       : 2018/4/12 ������, by redmorningcn
*******************************************************************************/


/*******************************************************************************
* INCLUDES
*/
#include <bsp_boardID.h>


/*******************************************************************************
 * 				                    ��ʱ����                                   *
 *******************************************************************************/
/*******************************************************************************
* ��    �ƣ� Delay_Nus()
* ��    �ܣ� ��ʱ���1us
* ��ڲ����� dly		��ʱ������ֵԽ����ʱԽ��
* ���ڲ����� ��
* ���� ���ߣ� ������
* �������ڣ� 2009-01-03
* ��    �ģ�
* �޸����ڣ�
*******************************************************************************/
OPTIMIZE_NONE void  Delay_Nus( INT32U  dly )
{
    /***********************************************
    * ��������ʱ����ʼ��
    *       72000000��ѭ��  = 6.9999999583333333333333333333333��
    *       һ��ѭ�� = 6.9999999583333333333333333333333 / 72000000
    *       = 97.222221643518518518518518518519 ns
    *       ~= 0.1 us
    *       ��ʱ1us  dly  = 9
    *       dly = 0ʱ��ѭ��һ��
    *
    while(dly--);
    *//***********************************************
    * ��������ʱ����ʼ��
    *       1000000��ѭ��  = 1027.7778611111111111111111111111ms
    *       ƽ��һ��ѭ�� = 1.02777786111111111111111111111us
    *       dly = 1ʱ��= 1.1111111111111111111111111111111us
    *       dly = 2ʱ  = 2.1388888888888888888888888888889us
    *       dly ÿ����1 ����-1.0277777777777777777777777777778us
    */
    INT32U  i;

    while(dly--) {
        for(i=0; i<7; i++);             // clk = 72000000 1027.7778611111111111111111111111
    }
}

/*******************************************************************************
* Description  : �˿ڳ�ʼ��
* Author       : 2018/4/12 ������, by redmorningcn
*******************************************************************************/
void Init_boardID( void )
{
    GPIO_InitTypeDef gpio_init;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    gpio_init.GPIO_Pin  =    GPIO_Pin_11
                            |GPIO_Pin_12;
    
    gpio_init.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &gpio_init);
}

/*******************************************************************************
* Description  : ȡ��·��ID��
* Author       : 2018/4/12 ������, by redmorningcn
*******************************************************************************/
uint8   get_boardID(void)
{
	uint8 id = 0;
	Delay_Nus(10);
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11))
	{
		id |= 0x2;
	}
    
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
	{
		id |= 0x01;
	}
    
	return id;
}

/*******************************************************************************
* 				end of file
*******************************************************************************/