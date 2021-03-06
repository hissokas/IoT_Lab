/********************************************************************************
* Copyright (c) 2015,联创中控（北京）科技有限公司
* All rights reserved.
* 文件名称：main.c
* 摘    要：完成函数初始化，信号采集，并通过串口2将数据上传到PC机。
* 当前版本: V1.3
* 作    者：张仁旺
* 完成日期：2017年2月7日
* 修改摘要：将传感器数据由串口1，RS232（USB3.0口）输出修改为由串口2，RS485（RJ11口）输出
********************************************************************************/

#include"main.h"

uint32_t delaytime = 0;								// 延时变量;

/***************************************************/
/*函数名称 : McuInit();                            */
/*输入参数 ：无                                    */
/*输出参数 ：无                                    */
/*功能说明 : 1) 完成系统时钟初始化，倍频72MHz;     */
/*           2) LED端口初始化；                    */
/* 			     3）串口初始化；                           */
/*	         4) 芯片状态处理，初值设定;		         */
/***************************************************/
void McuInit(void)
{
	RCC_Configuration();      						// clock config,打开相应外设时钟;
	LedGpioInit('B',4,5,6,7); 						// Led灯初始化;
	Sm_GPIOInit(10);          						// 选择传感器输入端口号
	UartInit(2,115200);								    // 串口2初始化
}

///**************************************************
//*函数名称 : main();
//*输入参数 ：无
//*输出参数 ：无
//*功能说明 : 1) McuInit函数初始化，之后进入死循环；
//*           2) 每隔1秒查询一次传感器数据，并通过串口2上传数据;
//**************************************************/
int main(void)
{
	McuInit();
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	printf("\r\n震动传感器采集实验r\n");
	while(1)
	{
		if(delaytime==500000)
			LedOff(6);
		if((delaytime++)>=1000000)
		{
			delaytime=0;
			LedOn(6);
			if(GetInput(10)==1)
			{
				LedOn(7);
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				printf("震动！！\r\n");
			}
			else
			{
				LedOff(7);
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				printf("静止！！\r\n");
				
			}
		}
	}
}
/**********************end_file@*****************************************/







