#include "STC15F2K60S2.h"
#include "karl_stepmotor.h"
#include "karl_displayer.h"

xdata unsigned char speed[3]      = {0, 0, 0};
xdata unsigned char speed_up[3]   = {0, 0, 0};
xdata unsigned char speed_down[3] = {0, 0, 0};
xdata unsigned char speed_direction[3];

xdata unsigned char SM_SB;
xdata unsigned char SM_Control_Seq;
xdata unsigned char SM_timer;

void StepMotor_Init()
{
    P4 &= 0xe1;
    P4M1 &= 0xe1;
	P4M0 |= 0x1e;
    SM_Control_Seq = 0x88;
    SM_timer = 0;
    return;
}

void SM_Print(unsigned char StepMotor, unsigned char SM_val)
{
    if (StepMotor == enumStepMotor1)
    {
        LedPrint(SM_val & 0xf0);
    }
    else if (StepMotor == enumStepMotor2)
    {
        LedPrint(SM_val & 0x0f);
    }
    else
    {
        P41 = (SM_val >> 3) & 0x01;
        P42 = (SM_val >> 2) & 0x01;
        P43 = (SM_val >> 1) & 0x01;
        P44 = SM_val & 0x01;
    }
    return;
}

void StepMotor_Run(unsigned char StepMotor, unsigned char Direction)
{
    speed_direction[StepMotor] = Direction;
    SM_Print(StepMotor, SM_Control_Seq);
    SM_timer ++;
    if (speed[StepMotor] > 0)
    {
        if (SM_timer % ((unsigned char)255 * 5 / speed[StepMotor]) == 0)
        {
            if (Direction == Left)
            {
                SM_SB = SM_Control_Seq & 0x80;
                SM_Control_Seq <<= 1;
                SM_Control_Seq |= (SM_SB >> 7);
            }
            else
            {
                SM_SB = SM_Control_Seq & 0x01;
                SM_Control_Seq >>= 1;
                SM_Control_Seq |= (SM_SB << 7);
            }
        }
    }
    if (speed_up[StepMotor] && speed[StepMotor] < 255)
    {
        speed[StepMotor] ++;
    }
    if (speed_down[StepMotor] && speed[StepMotor] > 2)
    {
        speed[StepMotor] -= 2;
    }
    else if (speed_down[StepMotor] && speed[StepMotor] > 0)
    {
        speed[StepMotor] --;
    }
    return;
}

void StepMotor_SetSpeed(unsigned char StepMotor, unsigned char Speed)
{
    speed[StepMotor] = Speed;
    return;
}

void StepMotor_SpeedUP(unsigned char StepMotor)
{
    speed_up[StepMotor] = 1;
    speed_down[StepMotor] = 0;
    return;
}

void StepMotor_SpeedDown(unsigned char StepMotor)
{
    speed_down[StepMotor] = 1;
    speed_up[StepMotor] = 0;
    return;
}

void StepMotor_SpeedHold(unsigned char StepMotor)
{
    speed_up[StepMotor] = 0;
    speed_down[StepMotor] = 0;
    return;
}

unsigned char Get_Speed(unsigned char StepMotor)
{
    return speed[StepMotor];
}

unsigned char Get_Speed_UP(unsigned char StepMotor)
{
    return speed_up[StepMotor];
}

unsigned char Get_Speed_Down(unsigned char StepMotor)
{
    return speed_down[StepMotor];
}

unsigned char Get_Speed_Direction(unsigned char StepMotor)
{
    return speed_direction[StepMotor];
}
