/*******************************************************************************
* Description  : ����ͨ�ýṹ��
* Author       : 2018/5/10 ������, by redmorningcn
*******************************************************************************/
#ifndef  APP_TYPE_H_
#define  APP_TYPE_H_

#include    "stm32f10x_type.h"
#include    <app_com_type.h>
#include    <app_loco_runstatus.h>


/*******************************************************************************
* Description  : ϵͳ���в���
* Author       : 2018/3/14 ������, by redmorningcn
*******************************************************************************/
typedef struct  
{
    uint32  id;                             // ��Ʒid       0
    uint32  num;                            // ��Ʒ���     4
    
    union{
        struct{
            u8  sysflg      :1;             // ��ϵͳ���� 
            u8  califlg     :1;             // ��У׼����
            u8  rev         :6;             // Ԥ��
        };
        u8  flags;
    }paraflg;
    uint8   buf[63];                        // Ԥ��         8
    uint32  cpu_freq;                       // cpuƵ��      72
    uint32  time;                           // ϵͳȫ��ʱ��(ϵͳʱ��(1/72Mhz) *65536)=Լ1ms   76
}strSysPara;    

__packed
typedef union _Unnctrl_ {
    struct{
        strSysPara          sys;            //��������
        strLocoRunStatus    loco;           //��Ʒ���в���    
        strCaliTable        calitab;        //����ϵ��
        StrCOMCtrl          ComCtrl[4];     //���ڿ��ƽṹ��
    };
    uint16   buf[1024];
        
}Unnctrl;


//��������
extern    Unnctrl     Ctrl;

extern    StrCOMCtrl  * DtuCom;
extern    StrCOMCtrl  * MtrCom;
extern    StrCOMCtrl  * TaxCom;

#endif                                                          /* End of  include.                       */

