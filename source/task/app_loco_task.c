/*******************************************************************************
* Description  : 采集工况信号电压
* Author       : 2018/4/17 星期二, by redmorningcn
*******************************************************************************/



/*******************************************************************************
* INCLUDES
*/
#include <app_loco_task.h>


/*******************************************************************************
* Description  : 计算工况电源电压
* Author       : 2018/4/17 星期二, by redmorningcn
*******************************************************************************/
void    app_calc_locovoltage(void)
{
    uint8   i;
    uint16  p_wr;
    uint16  p_rd;
    
    /*******************************************************************************
    * Description  : 取ADC采样值
    * Author       : 2018/4/17 星期二, by redmorningcn
    *******************************************************************************/
    static  uint32  tick;
    if(Ctrl.sys.time > tick+100 ||  Ctrl.sys.time < tick) //100ms
    {
        tick = Ctrl.sys.time;
        
        p_wr = Ctrl.loco.p_wr_vol;
        
        for( i = 0;i< 6;i++)
        {
             Ctrl.loco.vol[p_wr].buf[i] =  Get_ADC(ADC_Channel_0+i);
        }
        p_wr++;
        Ctrl.loco.p_wr_vol = p_wr % VOLTAGE_BUF_SIZE;
    }
    
    
    /*******************************************************************************
    * Description  : 计算电压值
    * Author       : 2018/4/17 星期二, by redmorningcn
    *******************************************************************************/
    
    p_wr = Ctrl.loco.p_wr_vol;
    p_rd = Ctrl.loco.p_rd_vol;
    
    if(     ( p_wr > p_rd) &&  (p_wr > p_rd+10)           
       ||   ( p_wr < p_rd) &&  (p_wr + VOLTAGE_BUF_SIZE > p_rd+10)           
           )  
    {
        uint32  sum;
        uint16  max,min;
        uint8   tmp8;
        uint16  tmp16;
        u32     vol;
        for(i = 0;i< 6;i++)
        {
            /*******************************************************************************
            * Description  : 在10个数中，除去最大值、最小值，再取平均
            * Author       : 2018/4/17 星期二, by redmorningcn
            *******************************************************************************/
            //计算低电平
            tmp8 = 0;
            sum  = 0;
            max  = Ctrl.loco.vol[p_rd].buf[i];
            min  = max;
            for(tmp8 = 0;tmp8< 10;tmp8++)
            {
                tmp16 = Ctrl.loco.vol[(p_rd + tmp8)%VOLTAGE_BUF_SIZE].buf[i];
                    
                if(tmp16 > max)
                    max = tmp16;
                
                if(tmp16 < min)
                    min = tmp16;
                
                sum += tmp16;
            }
            //Ctrl.loco.para.parabuf[i] = (sum - max - min)/8;                     //
            /**************************************************************
            * Description  : 加入线性修正
            * Author       : 2018/5/31 星期四, by redmorningcn
            */
            vol = (sum - max - min)/8;                     //
            vol = (vol * Ctrl.calitab.CaliBuf[i].line / CALI_LINE_BASE) + Ctrl.calitab.CaliBuf[i].Delta;
            Ctrl.loco.para.parabuf[i] =  vol;
        }
        
        /*******************************************************************************
        * Description  : 调整读指针
        * Author       : 2018/4/17 星期二, by redmorningcn
        *******************************************************************************/
        Ctrl.loco.p_rd_vol = (p_rd + tmp8) % VOLTAGE_BUF_SIZE;
    }
    
}




/*******************************************************************************
* 				end of file
*******************************************************************************/
