/*******************************************************************************
* Description  : ����ͨѶ���ƽṹ�嶨�壨APP�㣩
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/

#ifndef	__APP_COM_TYPE_H__
#define	__APP_COM_TYPE_H__
#include <includes.h>

/*********************************************************************
* INCLUDES
*/
#define COMM_RECV_DATA_MAX_LEN   128
#define COMM_SEND_DATA_MAX_LEN   128
#define COM_CONN_NUM             4     





//���ڵ�ַ����    
#define     DTU                 0               /* DTU���ÿ��ƽṹ�����         ComCtrl[]*/
#define     DTU_C0              0               /* DTU_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     DTU_NODE            1               /* DTU modebus���*/

//���ڵ�ַ����    
#define     MTR                 1               /* MTR���ÿ��ƽṹ�����         ComCtrl[]*/
#define     MTR_C0              0               /* MTR_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     MTR_NODE            1               /* MTR modebus���*/


//���ڵ�ַ����    
#define     TAX                 2               /* TAX���ÿ��ƽṹ�����         ComCtrl[]*/
#define     TAX_C0              0               /* TAX_C0��ַ��ռ�õ����ӱ��    ConnCtrl[]*/
#define     TAX_NODE            1               /* TAX modebus���*/

//csnc��ַ����
#define     LKJ_MAINBOARD_ADDR  0x84            /* LKJ�ӿ����ߴ������ CSNC Э���ַ*/
#define     DTU_ADDR            0xCA            /* ���߷���ģ�� CSNC Э���ַ */

/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/

/*******************************************************************************
* Description  : ���ڽ������ݽṹ������
��ͬЭ�飬��ָͬ������ݿɸ��á�
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef union {
    
//  ���ݽṹ1
//  ���ݽṹ2
    u16             Buf16[COMM_RECV_DATA_MAX_LEN/2];		            //	
    u8              Buf[COMM_RECV_DATA_MAX_LEN];		            //	
} uRecvData;

/*******************************************************************************
* Description  : ���ڷ�������������
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef union {
//	stcFlshRecNdp02A        sRecA;				    //���ݼ�¼     128 	
//  ���ݽṹ1
//  ���ݽṹ2
    u16             Buf16[COMM_SEND_DATA_MAX_LEN/2];		            //	
    u8              Buf[COMM_SEND_DATA_MAX_LEN];	
} uSendData;

/*******************************************************************************
* Description  : ���ӿ�����
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
typedef struct {     
    u8      ConnFlg;            //���ӿ���,1���������ӣ�0������������
    u8      RecvEndFlg;		    //���ձ�ʾ��1�����ݽ�����ɣ�0�������ݽ��ա�
    u8      TimeOut;		    //��ʱʱ�䣬��λ1s
    u8      ErrFlg;		        //�����ʾ������������0�����Ӵ���1
    
    u8      SlaveAddr;          //���յ�ַ          slave  =0xCA	   
    u8      MasterAddr;         //Դ��ַ           master   =0x80	   
    u8      SendFramNum;        //֡���   
    u8      SendFlg;            //���ͱ�ʾ��     �����ݷ��ͣ�1�������ݷ��ͣ�0
    
    u32     Baud;
    u8      Bits;
    u8      Parity;
    u8      Stops;
    
    u8      MB_Node: 5;        //modbus���ӱ��
    u8      COM_Num: 3;        //���ڱ��

} sCOMConnCtrl;		


//���տ�����
typedef struct {     
    u8                      DestAddr;       //���յ�ַ      slave  =0xA1\A2	   
    u8                      SourceAddr;     //Դ��ַ       master   =0x80	   
    u8                      FramNum;        //֡���
    u8    			        Len;			//������Ч���ݳ���
    u8                      FrameCode;       
    u8                      Tmp[3];
    u32    			        DataCode;			//���տ�����
} sCOMRecvCtrl;

/*******************************************************************************
* Description  : ���ڿ��ƽṹ�壨app�㣩
* Author       : 2018/5/11 ������, by redmorningcn
*******************************************************************************/
__packed
typedef struct {  
	uRecvData	        Rd;			//����������
	uSendData	        Wr;			//����������
    
    MODBUS_CH           *pch;                   		// MODBUS���
    
    u16                 ConnectTimeOut  : 15;     	    // ���ӳ�ʱ����������Ϊ��λ
    u16                 ConnectFlag     : 1;         	// ���ӱ�־

    /***************************************************
    * ������ ���ڿ�����
    */
	sCOMRecvCtrl    	RxCtrl;				            //���տ��ƣ�������ǰ���յ��Ŀ�����Ϣ
	sCOMConnCtrl		ConnCtrl[COM_CONN_NUM];         //���ӿ��ƣ���ÿ����ַ��Ϊ�������������ӡ�
	
} StrCOMCtrl;


#endif	
