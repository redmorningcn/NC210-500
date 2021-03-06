/*******************************************************************************
* Description  : 通用系统或文件中定制的内容移到此处（便于移植）
如：操作系统中的钩子函数
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/
#include <tasks.h>
#include <includes.h>
#include  <drives.h>

extern  void App_ModbusInit(void);
extern  void  App_OS_SetAllHooks (void);
void    Bsp_ADC_Init(void);
void    Init_boardID( void );
uint8   get_boardID(void);
void    app_init_sctrl(void);

/*******************************************************************************
* Description  : BSP初始化钩子函数，在任务执行前运行
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/
void    BSP_Init_Hook(void)
{
    app_init_sctrl();
    
    App_ModbusInit();                                   //初始化串口及串口控制信息
    
    /*******************************************************************************
    * Description  : 信号幅值及工作电源电压检测初始化化
    * Author       : 2018/4/12 星期四, by redmorningcn
    *******************************************************************************/
	Bsp_ADC_Init();
    
    /*******************************************************************************
    * Description  : 设备ID号获取初始化
    * Author       : 2018/4/13 星期五, by redmorningcn
    *******************************************************************************/
    Init_boardID();
    Ctrl.sys.id = get_boardID();
}

/*******************************************************************************
* Description  : 操作系统任务创建钩子函数
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/
void OS_TaskCreateHook(void)
{     
    /***********************************************
    * 描述： 设置UCOS钩子函数
    */
    App_OS_SetAllHooks();
    
    App_TaskOsalCreate();                           //创建osal任务。           
}

/*******************************************************************************
* Description  : 在创建OSA任务时，调用的钩子函数。
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/
void OSAL_TaskCreateHook(void)
{
    osal_add_Task(TaskInitTmr,                      // 任务初始化函数指针
                  TaskTmrEvtProcess,                // 任务事件处理函数指针
                  OS_TASK_PRO_TMR,                  // 任务优先级
                  OS_TASK_ID_TMR);                  // 任务ID
}

