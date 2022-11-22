#include "STC15F2K60S2.h"
#include "karl_music.h"
#include "karl_timer1.h"
#include "karl_beep.h"

bit Is_Playing = 0;
unsigned int Music_Curr_Index;
unsigned char Music_Wait_To_Play_Tone_Level;
unsigned char *Music_Wait_To_Play = 0;
unsigned int Music_Wait_To_Play_Length;

/**
 * @brief 音符构成规定
 * 一首歌首先确定调号，这里提供的调号是C低中高三个调号
 * 其次是每个音符的音阶，音阶这里提供了12个音阶
 * 最后是每个音的时值，时值这里提供了7个时值，每一拍的长度为一个全音符
 */

/**
 * @brief C低音对应的12个音阶的频率表
 */
code unsigned short C_Tone_Tab[3][13] =
{
// 下标
/*   0      1      2       3       4       5       6       7       8       9       10      11      12       */
// 音符种类
/* silence  1      1#      2       2#      3       4       4#      5       5#      6       6#      7        */
    {0,     262,   277,    294,    311,    330,    349,    370,    392,    415,    440,    466,    494},    // Low
    {0,     523,   554,    587,    622,    659,    698,    740,    784,    831,    880,    932,    988},    // Middle
    {0,     1047,  1109,   1175,   1245,   1319,   1397,   1480,   1568,   1661,   1760,   1865,   1976}    // High
};

/**
 * @brief 音符相对长度
 */
code unsigned char Tone_Length_Tab[] =
{
    64, // 全音符
    32, // 二分音符
    16, // 四分音符
    8,  // 八分音符
    4,  // 十六分音符
    2,  // 三十二分音符
    1   // 六十四分音符
};

void Music_Init()
{
    Beep_Init();
    Timer1_Init();
    Music_Curr_Index = 0;
    return;
}

unsigned char Play_Tone(unsigned char Tone_Level, unsigned char Tone_Kind, unsigned char Tone_Relative_Duration)
{
    unsigned int Play_Tone_Frequency;
    unsigned char Play_Tone_Time;
    Play_Tone_Frequency = C_Tone_Tab[Tone_Level][Tone_Kind];
    Play_Tone_Time = 500 / (64 / Tone_Length_Tab[Tone_Relative_Duration]);
    return Set_Beep(Play_Tone_Frequency, Play_Tone_Time);
}

void Play_Music(unsigned char Tone_Level, unsigned char *Music, unsigned int Music_Length)
{
    Is_Playing = START;
    Music_Curr_Index = 0;
    Music_Wait_To_Play_Tone_Level = Tone_Level;
    Music_Wait_To_Play = Music;
    Music_Wait_To_Play_Length = Music_Length;
    return;
}

unsigned char Get_Time_By_Tone_Length(unsigned char Tone_Relative_Duration)
{
    return 500 / (64 / Tone_Length_Tab[Tone_Relative_Duration]);
}

unsigned int Get_Music_Curr_Index()
{
    return Music_Curr_Index;
}

void Set_Music_Curr_Index(unsigned int Index)
{
    Music_Curr_Index = Index;
    return;
}

unsigned char Get_Music_Wait_To_Play_Tone_Level()
{
    return Music_Wait_To_Play_Tone_Level;
}

unsigned char Get_Play_State()
{
    return Is_Playing;
}

void Set_Play_State(unsigned char Control)
{
    if (Control == START)
    {
        Is_Playing = START;
    }
    else
    {
        Is_Playing = STOP;
    }
    return;
}

unsigned int Get_Music_Wait_To_Play_Length()
{
    return Music_Wait_To_Play_Length;
}
