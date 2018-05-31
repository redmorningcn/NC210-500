
/*******************************************************************************
* Description  : modbus��ʼ��
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*/

#include <includes.h>
//#include <app_type.h>


/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* MACROS
*/

/*******************************************************************************
* TYPEDEFS
*/

/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
* GLOBAL VARIABLES
*/

/***********************************************
* ������ ������ƿ飨TCB��
*/

/***********************************************
* ������ �����ջ��STACKS��
*/

/*******************************************************************************
* LOCAL FUNCTIONS
*/
/*******************************************************************************
* ��    �ƣ� APP_ModbusInit
* ��    �ܣ� MODBUS��ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
* ��    �ߣ� ������
* �������ڣ� 2015-03-28
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� �ó�ʼ���ᴴ��Modbus����
*******************************************************************************/
void App_ModbusInit(void)
{
    MODBUS_CH   *pch;
    u8          comnum = 0;
    u32         boud   = 0;

    /***********************************************
    * ������ uCModBus��ʼ����RTUʱ��Ƶ��Ϊ1000HZ
    *        ʹ���˶�ʱ��2��TIM2��
    */
    MB_Init(1000);
    
    
    /***********************************************
    * ������ UART1��������ģ��
    *        �����ӻ���
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      = 0;                                    //���ô���
    boud        = 57600;
    pch         = MB_CfgCh( DET_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            boud,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    Ctrl.ComCtrl[DET].ConnCtrl.MB_Node      = DET_NODE;     //modbus��� 
    Ctrl.ComCtrl[DET].ConnCtrl.COM_Num      = comnum;       //���ں�
    Ctrl.ComCtrl[DET].ConnCtrl.Baud         = boud;

    Ctrl.ComCtrl[DET].RxCtrl.EvtFlag        = COMM_EVT_FLAG_DTU_RX; //os�¼���ʶ 

    pch->RxSem  = &MB_OS_RxSemTbl[comnum];              // �����ź���
    pch->TxSem  = &MB_OS_TxSemTbl[comnum];              // �����ź���
    Ctrl.ComCtrl[DET].pch  = pch;                      // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
    DtuCom = &Ctrl.ComCtrl[DET];                       //����������ڶ�Ӧ�������п��ñ���ֱ�Ӳ���
#endif
    
}   
    




