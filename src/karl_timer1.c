#include "STC15F2K60S2.h"
#include "karl_timer1.h"
#include "karl_beep.h"

extern code unsigned long SysClock;

extern unsigned int Beep_Frequency_In_Timer1;
extern unsigned short Beep_Time_In_Timer1;

extern bit Sem_Beep;

unsigned short timer1_count;

void Timer1_Init()
{
    timer1_count = 0;
    // P498
    // TCON
    TF1 = 0;    // 清除TF1标志
    TR1 = 1;    // 启动定时器1
    // TMOD
    TMOD &= 0x0f;   // 清除定时器1模式位，将定时器1设置为16位自动重装载模式
    // AUXR
    AUXR |= 0x40;   // 定时器1工作在1T
    // IE
    ET1 = 1;    // 定时器1中断允许
    EA = 1;     // 全局中断允许
    // 装载初值，如下装载的值为1ms一次中断
    TL1 = 65536 - (SysClock / 1000);
    TH1 = (65536 - SysClock / 1000) >> 8;
    /**
     * @brief 时钟输出
     * 但是这样的话不符合要求，并且在初始化的时候还需要传入是否启动定时器1
     * 不如传频率来的快
     */
    // INT_CLKO |= 0x02;   // 定时器1时钟输出
    return;
}

void Reload_Timer1()
{
    if (Beep_Frequency_In_Timer1 == 0)
    {
        TR1 = 0;
        TL1 = 65536 - (SysClock / 1000);
        TH1 = (65536 - SysClock / 1000) >> 8;
        TR1 = 1;
        return;
    }
    else
    {
        TR1 = 0;
        // 装载初值
        // 以下装载的值为 (1 / Beep_Frequency_In_Timer1) 一次中断
        TL1 = 65536 - (SysClock / Beep_Frequency_In_Timer1);
        TH1 = (65536 - SysClock / Beep_Frequency_In_Timer1) >> 8;
        TR1 = 1;
    }
    return;
}

void Reset_Beep_Time()
{
    timer1_count = 0;
    return;
}

void Timer1_Rountine() interrupt 3
{
    timer1_count ++;
    if (Beep_Time_In_Timer1 == Endless_Beep
    || timer1_count < Beep_Time_In_Timer1)
    {
        if (Beep_Frequency_In_Timer1 != 0)
        P34 = ~P34;
    }
    else
    {
        Sem_Beep = 1;
        P34 = 0;
        TR1 = 0;
    }
    return;
}
