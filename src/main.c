#include "karl_timer0.h"
#include "karl_timer1.h"
#include "karl_callback.h"
#include "karl_displayer.h"
#include "karl_key.h"
#include "karl_adc.h"
#include "karl_stepmotor.h"
#include "karl_beep.h"
#include "karl_music.h"

code unsigned long SysClock = 11059200;

#ifdef _KARL_DISPLAYER_H_
code char decode_table[] =
{
		0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48,
/* 序号: 0    1    2	3    4	  5    6	7	 8	  9	   10	11	 12   13    14    15     */
/* 显示: 0    1    2	3    4	  5    6	7	 8    9   (无)  下-  中-  上-  上中-  中下-   */
			0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80
/* 带小数点     0         1         2         3         4         5         6         7         8         9        */
};
#endif

#ifdef _KARL_MUSIC_H_
code unsigned char Little_Star[] =
{
    0x12, 0x12, 0x82, 0x82, 0x92, 0x92, 0x82, 0x02,	// 一 闪 一 闪 亮 晶 晶-1 1 5 5 6 6 5
	0x62, 0x62, 0x52, 0x52, 0x32, 0x32, 0x12, 0x02,	// 满 天 都 是 小 星 星-4 4 3 3 2 2 1
	0x82, 0x82, 0x62, 0x62, 0x52, 0x52, 0x32, 0x02,	// 挂 在 天 上 放 光 明-5 5 4 4 3 3 2
	0x82, 0x82, 0x62, 0x62, 0x52, 0x52, 0x32, 0x02,	// 它 是 我 们的 小 眼 睛-5 5 4 4 3 3 2
	0x12, 0x12, 0x82, 0x82, 0x92, 0x92, 0x82, 0x02,	// 一 闪 一 闪 亮 晶 晶-1 1 5 5 6 6 5
	0x62, 0x62, 0x52, 0x52, 0x32, 0x32, 0x12, 0x02	// 满 天 都 是 小 星 星-4 4 3 3 2 2 1
};
code unsigned char Two_Tigers[] =
{
	0x12, 0x32, 0x52, 0x12,
	0x12, 0x32, 0x52, 0x12,
	0x52, 0x62, 0x82, 0x02,
	0x52, 0x62, 0x82, 0x02,
	0x82, 0xa4, 0x82, 0x64, 0x52, 0x12, 0x02,
	0x82, 0xa4, 0x82, 0x64, 0x52, 0x12, 0x02,
	0x12, 0x82, 0x12, 0x02,
	0x12, 0x82, 0x12, 0x02
};
#endif

void display()
{
	Seg7Print((Get_Speed(enumStepMotor1) / 100),	// 0
			(Get_Speed(enumStepMotor1) / 10) % 10,	// 1
			Get_Speed(enumStepMotor1) % 10,			// 2
			10,										// 3
			(Get_Beep_Frequency() / 1000),			// 4
			(Get_Beep_Frequency() / 100) % 10,		// 5
			(Get_Beep_Frequency() / 10) % 10,		// 6
			Get_Beep_Frequency() % 10);				// 7
	return;
}

void Motor_Run()
{
	StepMotor_Run(enumStepMotor1, Left);
	return;
}

void Play_Little_Star()
{
	if (Get_Play_State() == STOP)
	{
		Play_Music(CMid, Little_Star, 48);
	}
	else
	{
		Set_Play_State(STOP);
	}
	return;
}

void Play_Two_Tigers()
{
	if (Get_Play_State() == STOP)
	{
		Play_Music(CMid, Two_Tigers, 38);
	}
	else
	{
		Set_Play_State(STOP);
	}
	return;
}

void Play_Single_Tone_Half()
{
	Play_Tone(CMid, 1, 2);
	return;
}

void Beep_Frequency_Up()
{
	unsigned int beep_frequency = Get_Beep_Frequency();
	if (beep_frequency < 10000)
	{
		beep_frequency += 100;
	}
	Set_Beep(beep_frequency, 2000);
	StepMotor_SetSpeed(enumStepMotor1, beep_frequency / 10);
	return;
}

void Beep_Frequency_Down()
{
	unsigned int beep_frequency = Get_Beep_Frequency();
	if (beep_frequency >= 100)
	{
		beep_frequency -= 100;
	}
	else
	{
		beep_frequency = 0;
	}
	Set_Beep(beep_frequency, 2000);
	StepMotor_SetSpeed(enumStepMotor1, beep_frequency / 10);
	return;
}

void global_init()
{
	Timer0_Init();
	Timer1_Init();
	Displayer_Init();
	Key_Init();
	Adc_Init(Adc_except_Extension);
	StepMotor_Init();
	Beep_Init();
	Music_Init();
	return;
}

void global_set()
{
	SetDisplayerArea(0, 7);
	LedPrint(0);
	return;
}

void global_callback()
{
	SetEventCallback(enumEventSys1mS, 			display);
	SetEventCallback(enumEventSys10mS, 			Motor_Run);
	SetEventCallback(enumEventKey1_Press, 		Play_Little_Star);
	SetEventCallback(enumEventKey2_Press, 		Play_Two_Tigers);
	SetEventCallback(enumEventKey3_Press, 		Play_Single_Tone_Half);
	SetEventCallback(enumEventKeyUp_Press, 		Beep_Frequency_Up);
	SetEventCallback(enumEventKeyDown_Press, 	Beep_Frequency_Down);
	return;
}

void global_run()
{
	// Play_Little_Star();
	while(1);
	return;
}

void main()
{
	global_init();
	global_set();
	global_callback();
	global_run();
	return;
}
