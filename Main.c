#include <reg52.h>
#include <stdio.h>
#include <MCP2515.h>

#define uchar unsigned char
#define uint unsigned int

uchar CAN_Flag=0;							//CAN接收到数据标志
uchar CAN_R_Buffer[8];						//CAN接收数据保存缓冲区

void init(void)
{
    TMOD = 0x20;	//0010 0001 T1定时器工作方式2 T0定时器工作方式1
    TH1 = 0xfd;		//波特率9600
    TL1 = 0xfd;
    TR1 = 1;	//启动定时器1
    SM1 = 1;	//串口工作方式1 10位异步 8位数据 波特率可变
    REN = 1;	//允许串行口接收数据
    EA = 1;		//开总中断
    ES = 1;		//开串口中断
}

void Exint1_Init(void)
{
    PX1=1;		//设置外部中断1的中断优先级为高优先级
    IT1 = 1;	//设置INT1的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX1 = 1;	//使能INT1中断
    EA = 1; 	//使能总中断
}

void main()
{
		init();
    Exint1_Init();
    MCP2515_Init();
    while(1)
    {
        while(CAN_Flag==1)
        {
            uchar len;
            len = CAN_Receive_Buffer(CAN_R_Buffer);
            if(len!=0)
            {
                ES=0;
                TI=1;
                printf(CAN_R_Buffer);
								TI=0;
								ES=1;
            }
        }
    }//eilhw
}//End of main()
void Exint1_ISR(void) interrupt 2 using 1
{
    CAN_Flag=1;//CAN接收到数据标志
}
void ser() interrupt 4
{
}