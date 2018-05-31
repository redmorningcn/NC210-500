/*******************************************************************************
* Description  : ����ȫ�ֶ�ʱ��
* Author       : 2018/4/18 ������, by redmorningcn
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*/
#include <bsp_timer.h>


/*******************************************************************************
* Description  : ȫ��ʱ���ۻ�����ʵʱ�� time = strSys.time * 65536 + TIM_GetCounter  
                              �ٳ��Ե�����ʱ�䡣
* Author       : 2018/3/13 ���ڶ�, by redmorningcn
*******************************************************************************/
void TIM8_OVER_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8,TIM_IT_Update)!=RESET)              //����������ж�
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);              //����жϱ�־
        Ctrl.sys.time++;                                             //ϵͳ��ʱ���ۼ�
	}
}

/*******************************************************************************
* Description  : ȫ��ʱ�ӣ�Ϊ�����ź��ṩͳһʱ���׼
* Author       : 2018/3/13 ���ڶ�, by redmorningcn
*******************************************************************************/
void Timer8_Iint(void)
{
	TIM_TimeBaseInitTypeDef	TIM_BaseInitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);         //ʹ�ܶ�ʱ��ʱ��
	//��ʼ����ʱ��8
	TIM_BaseInitStructure.TIM_Period = 65535;                   //�������Զ���װֵ
	TIM_BaseInitStructure.TIM_Prescaler = 0;                    //����Ƶ
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�Ӳ��ָ�
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ���������
    
	TIM_TimeBaseInit(TIM8,&TIM_BaseInitStructure);              //��ʼ��ʱ��
    
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);                       //����жϱ�־λ
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);                    //����������ж�
	TIM_Cmd(TIM8,ENABLE);
    
	BSP_IntVectSet(TIM8_UP_IRQn, TIM8_OVER_IRQHandler);
	BSP_IntEn(TIM8_UP_IRQn);
    //BSP_INT_ID_TIM8
    Ctrl.sys.time = 0;                                               //ϵͳʱ����0
}


/*******************************************************************************
* 				end of file
*******************************************************************************/
