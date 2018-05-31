/*******************************************************************************
* Description  : 任务的头文件,进行函数声明
* Author       : 2018/5/11 星期五, by redmorningcn
*******************************************************************************/

#ifndef  TASKS_H_
#define  TASKS_H_

#include    <includes.h>
#include    <app_loco_runstatus.h>


/*******************************************************************************
 * TYPEDEFS
 */ 
#define     STORE_ADDR_SYS      (0)                                     /* 存sys地址     */
#define     STORE_ADDR_CALI     (STORE_ADDR_SYS + sizeof(strSysPara))   /* 存校验地址    */

//osal
void  App_TaskOsalCreate(void);
void TaskInitTmr(void);
osalEvt  TaskTmrEvtProcess(osalTid task_id, osalEvt task_event);

//
void    app_calc_locovoltage(void);


#endif

