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
    uint32  id;                             // 产品id       0
    uint32  num;                            // 产品编号     4
    
    union{
        struct{
            u8  sysflg      :1;             // 存系统参数 
            u8  califlg     :1;             // 存校准参数
            u8  rev         :6;             // 预留
        };
        u8  flags;
    }paraflg;
    uint8   buf[63];                        // 预留         8
    uint32  cpu_freq;                       // cpu频率      72
    uint32  time;                           // 系统全局时间(系统时钟(1/72Mhz) *65536)=约1ms   76
}strSysPara;    

__packed
typedef union _Unnctrl_ {
    struct{
        strSysPara          sys;            //公共参数
        strLocoRunStatus    loco;           //产品特有参数    
        strCaliTable        calitab;        //修正系数
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

