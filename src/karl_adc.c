#include "STC15F2K60S2.h"
#include "karl_adc.h"
#include "karl_callback.h"

#define ADC_POWER   0x80
#define ADC_SPEEDLL 0x00
#define ADC_SPEEDL  0x20
#define ADC_SPEEDH  0x40
#define ADC_SPEEDHH 0x60
#define ADC_FLAG    0x10
#define ADC_START   0x08

unsigned char channel = 7;
char Adc_Init_Sel;
xdata struct_Adc res;
unsigned char last_adc = 0x07;
unsigned char real_last_adc = 0x07;
bit Adc_Key_Is_Sampled = 0;

void Adc_Init(char Adc_sel)
{
    Adc_Init_Sel = Adc_sel;
    // P761
    // P1ASF
    P1ASF |= 0xfc;  // P1.2, P1.3, P1.4, P1.5, P1.6, P1.7设置为模拟输入
    // ADRJ
    CLK_DIV &= 0xdf;    // 将ADRJ置0
    // ADC_RES
    ADC_RES = 0;    // 清零
    // IE
    EADC = 1;   // 使能ADC中断
    if (Adc_sel == Adc_include_Extension)
    {
        // P323
        P1M1 |= 0xff;
        P1M0 &= 0x00;
        // P761
        // P1ASF
        P1ASF |= 0x03;  // P1.0, P1.1设置为模拟输入
    }
    else
    {
        // P323
        P1M1 |= 0xfc;   // 1111 1100
        P1M0 &= 0x03;   // 0000 0011
    }
    return;
}

struct_Adc Get_Adc()
{
    return res;
}

void Adc_Key_Sample()
{
    channel = 7;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | channel;
    Adc_Key_Is_Sampled = 1;
    return;
}

void ADC_Routine() interrupt 5
{
    unsigned char Adc_Key;
    ADC_CONTR &= ~ADC_FLAG; // 清除ADC中断标志
    switch (channel)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
        {
            Adc_Key = (ADC_RES >> 5) & 0x07;
            if (last_adc == Adc_Key && real_last_adc != Adc_Key)
            {
                switch (Adc_Key)
                {
                    case 0:
                        if (real_last_adc == 7
                            && callback_key3_press != 0)
                        {
                            callback_key3_press();
                        }
                        break;
                    case 1:
                        if (real_last_adc != 0
                            && callback_keyRight_press != 0)
                        {
                            callback_keyRight_press();
                        }
                        break;
                    case 2:
                        if (real_last_adc != 0
                            && callback_keyDown_press != 0)
                        {
                            callback_keyDown_press();
                        }
                        break;
                    case 3:
                        if (real_last_adc != 0
                            && callback_keyCenter_press != 0)
                        {
                            callback_keyCenter_press();
                        }
                        break;
                    case 4:
                        if (real_last_adc != 0
                            && callback_keyLeft_press != 0)
                        {
                            callback_keyLeft_press();
                        }
                        break;
                    case 5:
                        if (real_last_adc != 0
                            && callback_keyUp_press != 0)
                        {
                            callback_keyUp_press();
                        }
                        break;
                    case 7:
                        if (real_last_adc == 0
                            && callback_key3_release != 0)
                        {
                            callback_key3_release();
                        }
                        break;
                    default:
                        break;
                }
                real_last_adc = last_adc;
            }
            last_adc = Adc_Key;
            Adc_Key_Is_Sampled = 0;
            break;
        }
        default:
            break;
    }
    return;
}
