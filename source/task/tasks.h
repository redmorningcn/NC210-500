/*******************************************************************************
* Description  : �����ͷ�ļ�,���к�������
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

#ifndef  TASKS_H_
#define  TASKS_H_

#include    <includes.h>
#include    <app_loco_runstatus.h>


/*******************************************************************************
 * TYPEDEFS
 */ 
#define     STORE_ADDR_SYS      (0)                                     /* ��sys��ַ     */
#define     STORE_ADDR_CALI     (STORE_ADDR_SYS + sizeof(strSysPara))   /* ��У���ַ    */

//osal
void  App_TaskOsalCreate(void);
void TaskInitTmr(void);
osalEvt  TaskTmrEvtProcess(osalTid task_id, osalEvt task_event);

//
void    app_calc_locovoltage(void);


#endif

