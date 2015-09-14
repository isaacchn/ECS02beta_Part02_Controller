#include <reg52.h>
#include <stdio.h>
#include <MCP2515.h>

#define uchar unsigned char
#define uint unsigned int

uchar CAN_Flag=0;							//CAN���յ����ݱ�־
uchar CAN_R_Buffer[8];						//CAN�������ݱ��滺����

void init(void)
{
    TMOD = 0x20;	//0010 0001 T1��ʱ��������ʽ2 T0��ʱ��������ʽ1
    TH1 = 0xfd;		//������9600
    TL1 = 0xfd;
    TR1 = 1;	//������ʱ��1
    SM1 = 1;	//���ڹ�����ʽ1 10λ�첽 8λ���� �����ʿɱ�
    REN = 1;	//�������пڽ�������
    EA = 1;		//�����ж�
    ES = 1;		//�������ж�
}

void Exint1_Init(void)
{
    PX1=1;		//�����ⲿ�ж�1���ж����ȼ�Ϊ�����ȼ�
    IT1 = 1;	//����INT1���ж����� (1:���½��� 0:�����غ��½���)
    EX1 = 1;	//ʹ��INT1�ж�
    EA = 1; 	//ʹ�����ж�
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
    CAN_Flag=1;//CAN���յ����ݱ�־
}
void ser() interrupt 4
{
}