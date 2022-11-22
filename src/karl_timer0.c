#include "STC15F2K60S2.h"
#include "karl_timer0.h"
#include "karl_displayer.h"
#include "karl_callback.h"
#include "karl_key.h"
#include "karl_adc.h"
#include "karl_beep.h"
#include "karl_music.h"

#define KEY_ANTI_SHAKE_TIME 20

// 时钟频率
extern code unsigned long SysClock;

// 按键
// 按键是否按下
extern bit key1_curr_act;
extern bit key2_curr_act;

extern bit key1_last_act;
extern bit key2_last_act;

extern unsigned char key1_press_counter;
extern unsigned char key1_release_counter;
extern unsigned char key2_press_counter;
extern unsigned char key2_release_counter;

extern bit Adc_Key_Is_Sampled;

extern unsigned char *Music_Wait_To_Play;
extern bit Sem_Beep;

unsigned short timer0_count;
unsigned short music_count;

void Timer0_Init()
{
	timer0_count = 0;
	music_count = 0;
	// P498
	// TCON
	TF0 = 0;	// 清除TF0标志
	TR0 = 1;	// 启动定时器0
	// TMOD
	TMOD &= 0xf0;	// 清除定时器0模式位
	// AUXR
	AUXR |= 0x80;	// 定时器0工作在1T, 16位自动重装初值, 1mS定时模式
	// IE
	ET0 = 1;	// 定时器0中断允许
	EA = 1;		// 全局中断允许
	// 装载初值
	TL0 = 65536 - (SysClock / 1000);
	TH0 = (65536 - SysClock / 1000) >> 8;
	return;
}

// 程序基本架构/任务调度/OS
void Timer0_Rountine() interrupt 1
{
	// 显示驱动函数
	Display_Driver();
	// 计数器++
	timer0_count ++;
	if (Adc_Key_Is_Sampled == 0
	&& (timer0_count % KEY_ANTI_SHAKE_TIME == 0))
		Adc_Key_Sample();
	//-------------------- 计时回调函数 --------------------
	// 如果1ms事件对应的函数指针不为空, 则调用
	if (callback_1ms != 0)
	{
		callback_1ms();
	}
	// 如果10ms事件对应的函数指针不为空, 则调用
	if (timer0_count % 10 == 0)
	{
		if (callback_10ms != 0)
		{
			callback_10ms();
		}
	}
	// 如果100ms事件对应的函数指针不为空, 则调用
	if (timer0_count % 100 == 0)
	{
		if (callback_100ms != 0)
		{
			callback_100ms();
		}
	}
	// 如果1s事件对应的函数指针不为空, 则调用
	if (timer0_count >= 1000)
	{
		// 并将计数器清零
		timer0_count = 0;
		if (callback_1s != 0)
		{
			callback_1s();
		}
	}
	//-------------------- 计时回调函数 --------------------
	//-------------------- 按键回调函数 --------------------
	// 按键计数
	if (key1_curr_act == enumKeyPress)
	{
		key1_press_counter ++;
	}
	else if (key1_curr_act == enumKeyRelease)
	{
		key1_release_counter ++;
	}
	if (key2_curr_act == enumKeyPress)
	{
		key2_press_counter ++;
	}
	else if (key2_curr_act == enumKeyRelease)
	{
		key2_release_counter ++;
	}
	//----------------------- key1 ------------------------
	if (key1_press_counter + key1_release_counter
	>= KEY_ANTI_SHAKE_TIME)
	{
		if (key1_press_counter > key1_release_counter
		&& key1_last_act == enumKeyRelease)
		{
			key1_last_act = enumKeyPress;
			if (callback_key1_press != 0)
			{
				callback_key1_press();
			}
		}
		else if (key1_press_counter < key1_release_counter
		&& key1_last_act == enumKeyPress)
		{
			key1_last_act = enumKeyRelease;
			if (callback_key1_release != 0)
			{
				callback_key1_release();
			}
		}
		key1_press_counter = 0;
		key1_release_counter = 0;
	}
	//----------------------- key2 ------------------------
	if (key2_press_counter + key2_release_counter
	>= KEY_ANTI_SHAKE_TIME)
	{
		if (key2_press_counter > key2_release_counter
		&& key2_last_act == enumKeyRelease)
		{
			key2_last_act = enumKeyPress;
			if (callback_key2_press != 0)
			{
				callback_key2_press();
			}
		}
		else if (key2_press_counter < key2_release_counter
		&& key2_last_act == enumKeyPress)
		{
			key2_last_act = enumKeyRelease;
			if (callback_key2_release != 0)
			{
				callback_key2_release();
			}
		}
		key2_press_counter = 0;
		key2_release_counter = 0;
	}
	//-------------------- 按键回调函数 --------------------
	//---------------------- 音乐部分 ----------------------
	if (Get_Play_State())
	{
		unsigned char curr_tone;
		unsigned char curr_tone_kind;
		unsigned char curr_tone_duration;
		music_count ++;
		curr_tone = Music_Wait_To_Play[Get_Music_Curr_Index()];
		curr_tone_kind = (curr_tone >> 4) & 0x0f;
		curr_tone_duration = curr_tone & 0x07;
		Play_Tone(Get_Music_Wait_To_Play_Tone_Level(), curr_tone_kind, curr_tone_duration);
		if (music_count > Get_Time_By_Tone_Length(curr_tone_duration) * 3)
		{
			music_count = 0;
			Set_Music_Curr_Index(Get_Music_Curr_Index() + 1);
		}
		if (Get_Music_Curr_Index() == Get_Music_Wait_To_Play_Length())
		{
			music_count = 0;
			Sem_Beep = 1;
			Set_Play_State(STOP);
		}
	}
	//---------------------- 音乐部分 ----------------------
	return;
}
