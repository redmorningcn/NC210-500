/*******************************************************************************
* Description  : �����ͷ�ļ�,���к�������
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

#ifndef  TASKS_H_
#define  TASKS_H_

#include <includes.h>
#include <bsp_drives.h>


//osal
void    App_TaskOsalCreate(void);
void    TaskInitTmr(void);
osalEvt  TaskTmrEvtProcess(osalTid task_id, osalEvt task_event);

void    Bsp_ADC_Init(void);
void    Init_boardID( void );
uint8   get_boardID(void);


#endif

