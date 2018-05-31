/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/

static  OS_TCB   AppTaskStartTCB;


/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskCreate (void);
static  void  AppObjCreate  (void);
static  void  AppTaskStart  (void *p_arg);

/*******************************************************************************
* Description  :  ָʾ�������ֱ�����λ��û�źţ��������������������ڵ��ã�100ms��
* Author       : 2018/4/13 ������, by redmorningcn
*******************************************************************************/
void    led_task(void)
{
    static  uint8   blinkcnt= 0;
    
    blinkcnt++;
    
    if(Ctrl.loco.para.loco.lw )   //����������   
    {
        blinkcnt %= 20;                                     //����ͨ�����źţ�����  
    }
    else
    {
        blinkcnt %= 2;                                      //����ͨ�����źţ�����
    }
    
    if(blinkcnt == 0)                                       //�������
    {
        BSP_LED_On(1);
    }
    else
    {
        BSP_LED_Off(1);
    }
}

u16     BSP_FlashWriteBytes     (u32 addr, u8 *pbuf, u16 len);

/**************************************************************
* Description  : �������
* Author       : 2018/5/30 ������, by redmorningcn
*/
void    store_para(void)
{
    if(Ctrl.sys.paraflg.califlg == 1){
        Ctrl.sys.paraflg.califlg = 0; 
        
        BSP_FlashWriteBytes(STORE_ADDR_CALI,
                        (u8 *)&Ctrl.calitab,
                        sizeof(Ctrl.calitab));
    }
    
    if(Ctrl.sys.paraflg.sysflg == 1){
        Ctrl.sys.paraflg.sysflg = 0;
        
        BSP_FlashWriteBytes(STORE_ADDR_SYS,
                            (u8 *)&Ctrl.sys,
                            sizeof(Ctrl.sys));
    }
}

/*******************************************************************************
* Description  : ��������ʱ�䲻���ȵĹ����ڴ�����
* Author       : 2018/4/16 ����һ, by redmorningcn
*******************************************************************************/
void    idle_task(void)      
{
    static  uint32  tick;
    if(Ctrl.sys.time > tick+100 ||  Ctrl.sys.time < tick)   //100ms
    {
        tick = Ctrl.sys.time;                               //ʱ��
        
        led_task();                                         //ָʾ�ƿ���
        
        store_para();                                       //�������
    }
}

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;

    BSP_IntDisAll();                                            /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) AppTaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;

   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    CPU_IntDisMeasMaxCurReset();
    
    AppTaskCreate();                                            /* Create Application Tasks                             */
    
    AppObjCreate();                                             /* Create Application Objects                           */
    
    BSP_LED_Off(0);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */

        /*******************************************************************************
        * Description  : �ɼ����㹤����ѹ
        * Author       : 2018/4/17 ���ڶ�, by redmorningcn
        *******************************************************************************/
        app_calc_locovoltage();
        
        /*******************************************************************************
        * Description  : ��������ʱ�䲻���еĵĹ����ڴ����У�ÿ100ms����һ��
        * Author       : 2018/4/16 ����һ, by redmorningcn
        *******************************************************************************/
        idle_task();

        OSTimeDlyHMSM(0, 0, 0, 100,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_TaskCreateHook();
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION EVENTS
*
* Description:  This function creates the application kernel objects.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppObjCreate (void)
{
}
