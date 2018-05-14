
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
    
    comnum      =   0;                                  //���ô���
    
    pch         = MB_CfgCh( DTU_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            57600,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    sCtrl.ComCtrl[DTU].ConnCtrl[DTU_C0].MB_Node     = DTU_NODE;     //modbus��� 
    sCtrl.ComCtrl[DTU].ConnCtrl[DTU_C0].COM_Num     = comnum;       //���ں�
    sCtrl.ComCtrl[DTU].ConnCtrl[DTU_C0].MasterAddr  = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ
    sCtrl.ComCtrl[DTU].ConnCtrl[DTU_C0].SlaveAddr   = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ
    
    sCtrl.ComCtrl[DTU].pch  = pch;                      // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
    DtuCom = &sCtrl.ComCtrl[DTU];                       //����������ڶ�Ӧ�������п��ñ���ֱ�Ӳ���
#endif
    
    
    /***********************************************
    * ������ UART2���ӹ������弰�ٶ��źż��塣modbusͨѶ
    *        ����������
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      =   1;                                  //���ô���
    
    pch         = MB_CfgCh( MTR_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            57600,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    sCtrl.ComCtrl[MTR].ConnCtrl[MTR_C0].MB_Node     = MTR_NODE;             //modbus��� 
    sCtrl.ComCtrl[MTR].ConnCtrl[MTR_C0].COM_Num     = comnum;               //���ں�
    sCtrl.ComCtrl[MTR].ConnCtrl[MTR_C0].MasterAddr  = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ����MTR��Ч��
    sCtrl.ComCtrl[MTR].ConnCtrl[MTR_C0].SlaveAddr   = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ����MTR��Ч��
    
    sCtrl.ComCtrl[MTR].pch  = pch;                      // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
    MtrCom = &sCtrl.ComCtrl[MTR];                       //����������ڶ�Ӧ�������п��ñ���ֱ�Ӳ���
#endif    



    /***********************************************
    * ������ UART2���ӹ������弰�ٶ��źż��塣modbusͨѶ
    *        ����������
    */
#if MODBUS_CFG_MASTER_EN == DEF_TRUE
    
    comnum      =   3;                                  //���ô���
    
    pch         = MB_CfgCh( TAX_NODE,                   // ... Modbus Node # for this slave channel
                            MODBUS_SLAVE,               // ... This is a MASTER
                            200,                        // ... 0 when a slave
                            MODBUS_MODE_RTU,            // ... Modbus Mode (_ASCII or _RTU)
                            comnum,                     // ... Specify UART #1
                            57600,                       // ... Baud Rate
                            USART_WordLength_8b,        // ... Number of data bits 7 or 8
                            USART_Parity_No,            // ... Parity: _NONE, _ODD or _EVEN
                            USART_StopBits_1,           // ... Number of stop bits 1 or 2
                            MODBUS_WR_EN);              // ... Enable (_EN) or disable (_DIS) writes

    sCtrl.ComCtrl[TAX].ConnCtrl[TAX_C0].MB_Node     = TAX_NODE;             //modbus��� 
    sCtrl.ComCtrl[TAX].ConnCtrl[TAX_C0].COM_Num     = comnum;               //���ں�
    sCtrl.ComCtrl[TAX].ConnCtrl[TAX_C0].MasterAddr  = LKJ_MAINBOARD_ADDR;   //���߷���ģ���ַ����MTR��Ч��
    sCtrl.ComCtrl[TAX].ConnCtrl[TAX_C0].SlaveAddr   = DTU_ADDR;             //LKJ�ӿڰ�csnc��ַ����MTR��Ч��
    
    sCtrl.ComCtrl[TAX].pch  = pch;                      // ... modbus���ƿ��ȫ�ֽṹ�彨������
    
    TaxCom = &sCtrl.ComCtrl[TAX];                       //����������ڶ�Ӧ�������п��ñ���ֱ�Ӳ���
#endif    


}   


    




