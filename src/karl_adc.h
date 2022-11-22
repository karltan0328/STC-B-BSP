#ifndef _KARL_ADC_H_
#define _KARL_ADC_H_

// EXT接口上的P10和P11是否用做功能
/**
 * @brief 对EXT接口加入AD转换的结果进行说明
 * 如果在Adc_Init()函数中传入Adc_include_Extension
 * 那么P10和P11将不能再作为IO口使用
 */
/**
 * @brief 对EXT接口 不 加入AD转换的结果进行说明
 * 如果在Adc_Init()函数中传入Adc_except_Extension
 * 那么P10和P11将可以作为IO口使用
 */
#define Adc_include_Extension   0x9B
#define Adc_except_Extension    0x98

// 按键名
#define enumAdcNavKey3      0
#define enumAdcNavKeyUp     1
#define enumAdcNavKeyDown   2
#define enumAdcNavKeyLeft   3
#define enumAdcNavKeyRight  4
#define enumAdcNavKeyCenter 5

// 按键动作
#define enumKeyPress      0
#define enumKeyRelease    1

typedef struct
{
    unsigned short EXT_P10; // 10bit
    unsigned short EXT_P11; // 10bit
    unsigned short Rt;      // 10bit
    unsigned short Rop;     // 10bit
    unsigned short Nav;     // 10bit
} struct_Adc;

extern void Adc_Init(char Adc_sel);
extern struct_Adc Get_Adc();
extern void Adc_Key_Sample();

#endif
