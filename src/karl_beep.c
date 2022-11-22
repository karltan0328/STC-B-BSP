#include "STC15F2K60S2.h"
#include "karl_beep.h"
#include "karl_timer1.h"

bit Sem_Beep = 1;

unsigned int Beep_Frequency_In_Timer1;
unsigned short Beep_Time_In_Timer1;

void Beep_Init()
{
    P3M1 &= 0xef;
    P3M0 |= 0x10;
    P34 = 0;
    Beep_Frequency_In_Timer1 = 0;
    Beep_Time_In_Timer1 = 0;
    return;
}

unsigned char Set_Beep(unsigned int Beep_Frequency, unsigned char Beep_Time)
{
    if (Sem_Beep == 1)
    {
        Sem_Beep = 0;
        Beep_Frequency_In_Timer1 = Beep_Frequency;
        Beep_Time_In_Timer1 = Beep_Time;
        Reload_Timer1();
        Reset_Beep_Time();
        return 1;
    }
    return 0;
}

unsigned int Get_Beep_Frequency()
{
    return Beep_Frequency_In_Timer1;
}

unsigned char Get_Beep_Time()
{
    return Beep_Time_In_Timer1;
}
