/*******************************************************************************
* Description  : 定义通用结构体
* Author       : 2018/5/10 星期四, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include    "stm32f10x_type.h"
#include    <app_com_type.h>
#include    <app_loco_runstatus.h>


/*******************************************************************************
* Description  : 系统运行参数
* Author       : 2018/3/14 星期三, by redmorningcn
*******************************************************************************/
typedef struct  
{
    uint32  id;             //产品id
    uint32  addr;           //通讯地址
    uint8   buf[64];        //预留
    uint32  cpu_freq;       //cpu频率
    uint32  time;           //系统全局时间(系统时钟(1/72Mhz) *65536)=约1ms
}strSysPara;    
    
__packed
typedef union _Unnctrl_ {
    struct{
        strSysPara          sys;            //公共参数
        strLocoRunStatus    loco;           //产品特有参数    
        //strCaliTable        calitab;      //修正系数
        StrCOMCtrl          ComCtrl[4];     //串口控制结构体
    };
    uint16   buf[1024];
        
}Unnctrl;


//变量声明
extern    Unnctrl     Ctrl;

extern    StrCOMCtrl  * DtuCom;
extern    StrCOMCtrl  * MtrCom;
extern    StrCOMCtrl  * TaxCom;

#endif                                                          /* End of  include.                       */

