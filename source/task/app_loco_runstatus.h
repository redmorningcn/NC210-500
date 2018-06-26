/*******************************************************************************
* Description  : 波形检测结构体定义
* Author       : 2018/4/12 星期四, by redmorningcn
*******************************************************************************/

#ifndef	APP_LOCO_RUNSTATUS_H
#define	APP_LOCO_RUNSTATUS_H

/*******************************************************************************
 * INCLUDES
 */
#include <global.h>
#include <bsp.h>


/*******************************************************************************
 * CONSTANTS
 */

 /*******************************************************************************
 * 				            系统参数相关宏定义                                  *
 *******************************************************************************/

/*******************************************************************************
 * MACROS
 */
//参数缓冲区大小
#define VOLTAGE_BUF_SIZE     20
     
/**************************************************************
* Description  : 校准额定值
* Author       : 2018/5/30 星期三, by redmorningcn
*/
#define     CALI_LINE_BASE      (10000)         /*  线性度基准        */
#define     CALI_LINE_MIN       (9500)          /*  线性度最小偏大-5% */
#define     CALI_LINE_MAX       (10500)         /*  线性度最大偏大 5% */  
#define     CALI_DELTA_BASE     (0)             /*  偏差基准          */      
#define     CALI_DELTA_MIN      (-500)          /*  允许调整的偏差-0.5*/    
#define     CALI_DELTA_MAX      (500)           /*  允许调整的偏差 0.5*/    
     
 

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
* Description  : 工况信号结构体
* Author       : 2018/4/17 星期二, by redmorningcn
*******************************************************************************/
typedef struct
{
    /*******************************************************************************
    * Description  : 辅助运算
    * Author       : 2018/4/17 星期三, by redmorningcn
    *******************************************************************************/
    //电平指标
    union  
    {
        struct {
            uint16              vcc;                           //预留
            uint16              qy;                             //牵引
            uint16              zd;                             //制动
            uint16              xq;                             //向前
            uint16              xh;                             //向后
            uint16              lw;                             //零位
        }adc;
        uint16  buf[6];
    }vol[VOLTAGE_BUF_SIZE];       
    
    
    uint16  p_wr_vol;                                   //电平写，指针
    uint16  p_rd_vol;                                   //电平读，指针
    
    uint32              status;                         //状态
    
    /*******************************************************************************
    * Description  : 通道具体指标
    * Author       : 2018/3/14 星期三, by redmorningcn
    *******************************************************************************/
    union  
    {
        struct _strpara_ {          
            uint16              vcc;            //预留
            uint16              qy;             //牵引
            uint16              zd;             //制动
            uint16              xq;             //向前
            uint16              xh;             //向后
            uint16              lw;             //零位
        }loco;
        uint16  parabuf[6];
    }para;
    
}strLocoRunStatus;


//calibration
/**************************************************************
* Description  : 校准参数
* Author       : 2018/5/22 星期二, by redmorningcn
*/
typedef struct {
    u32         line;                       //修正线性度  
    int16       Delta;                      //修正偏差
    int16       tmp;                        //预留
}strCalibration;


/**************************************************************
* Description  : 修正参数表
* Author       : 2018/5/22 星期二, by redmorningcn
*/
typedef struct{
    union   {
        struct{
            strCalibration  VccVol;         //电平
            strCalibration  QY_Vol;         //
            strCalibration  ZD_Vol;         //
            strCalibration  XQ_Vol;         //
            strCalibration  XH_Vol;         //
            strCalibration  LW_Vol;         //
        };
        strCalibration      CaliBuf[20];
    };
}strCaliTable;


/*******************************************************************************
 * GLOBAL VARIABLES
 */
extern  strLocoRunStatus    loco;                            //机车信号


/*******************************************************************************
 * 				end of file                                                    *
 *******************************************************************************/
#endif	/* GLOBLES_H */
