#include "STC15F2K60S2.h"
#include "karl_key.h"

// key动作
bit key1_curr_act = enumKeyRelease;
bit key2_curr_act = enumKeyRelease;

bit key1_last_act = enumKeyRelease;
bit key2_last_act = enumKeyRelease;

bit int0, int1;

// 按键计时器
unsigned char key1_press_counter;
unsigned char key1_release_counter;
unsigned char key2_press_counter;
unsigned char key2_release_counter;

/**
 * @brief 按键初始化
 * KEY1对应的是INT0，P3.2
 * KEY2对应的是INT1，P3.3
 */
void Key_Init()
{
    // P323
    // 将P3.2和P3.1设置为输入模式
    P3M1 |= 0x0c;
    P3M0 &= 0xf3;
    // P458
    // IE
    //// Key1
    EX0 = 1; // 外部中断0使能，对应Key1
    //// Key2
    EX1 = 1; // 外部中断1使能，对应Key2
    // TCON
    //// Key1
    IT0 = 0; // 外部中断0触发方式为上升沿和下降沿均可触发
    //// Key2
    IT1 = 0; // 外部中断1触发方式为上升沿和下降沿均可触发
    return;
}

unsigned char GetKeyAct(char Key)
{
    if (Key == enumKey1)
    {
        return key1_curr_act;
    }
    else if (Key == enumKey2)
    {
        return key2_curr_act;
    }
    else
    {
        return enumKeyRelease;
    }
}

void Int0_Rountine() interrupt 0
{
    int0 = P32;
    if (int0 == 0)
    {
        key1_curr_act = enumKeyPress;
    }
    else
    {
        key1_curr_act = enumKeyRelease;
    }
    return;
}

void Int1_Rountine() interrupt 2
{
    int1 = P33;
    if (int1 == 0)
    {
        key2_curr_act = enumKeyPress;
    }
    else
    {
        key2_curr_act = enumKeyRelease;
    }
    return;
}
