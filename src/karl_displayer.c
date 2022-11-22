#include "STC15F2K60S2.h"
#include "karl_displayer.h"

extern code char decode_table[];

typedef struct
{
	char Begin_of_Scan;		  	//数码管动态扫描开始位
	char Ending_of_Scan;	  	//结束位
	char Text[9];				//显示内容
	char Current_of_Scan;		//动态扫描当前位
}struct_Disp;
xdata struct_Disp sys_Disp;

// 动态扫描控制函数, 针对Disp所描述。每1mS调用一次	// 硬件驱动程序
void Display_Driver()
{
	// 关闭段选，消影
	P0 = 0;
	switch (sys_Disp.Current_of_Scan)
	{
		case  0:    P23 = 0; P22 = 0; P21 = 0; P20 = 0; break;
		case  1:    P23 = 0; P22 = 0; P21 = 0; P20 = 1; break;
		case  2:    P23 = 0; P22 = 0; P21 = 1; P20 = 0; break;
		case  3:    P23 = 0; P22 = 0; P21 = 1; P20 = 1; break;
		case  4:    P23 = 0; P22 = 1; P21 = 0; P20 = 0; break;
		case  5:    P23 = 0; P22 = 1; P21 = 0; P20 = 1; break;
		case  6:    P23 = 0; P22 = 1; P21 = 1; P20 = 0; break;
		case  7:    P23 = 0; P22 = 1; P21 = 1; P20 = 1; break;
		default:    P23 = 1; break;
	}
	if (sys_Disp.Current_of_Scan < 8)
		// 段选：数码管时需译码，LED时不需译码
		P0 = decode_table[sys_Disp.Text[sys_Disp.Current_of_Scan]];
	else
	{
		if (sys_Disp.Current_of_Scan == 8)
			// 段选：流水灯时
			P0 = sys_Disp.Text[sys_Disp.Current_of_Scan];
		else
			// 段选: 空
			P0 = 0;
	}
	//计算下一次要显示的位
	if ( ++sys_Disp.Current_of_Scan > sys_Disp.Ending_of_Scan )
		if (sys_Disp.Current_of_Scan <= 8)
			sys_Disp.Current_of_Scan = 8;
		else
			sys_Disp.Current_of_Scan = sys_Disp.Begin_of_Scan;
	return;
}

// 模块初始化
void Displayer_Init(void)
{
	// 设置P0为推挽模式:段选
	P0M1 =  0x00;
	P0M0 =  0xff;
	// 设置P2为推挽模式:位选
	P2M1 &= 0xf0;
	P2M0 |= 0x0f;
	// 初始化显示内容及位置
	sys_Disp.Text[0] = 0x00;
	sys_Disp.Text[1] = 0x00;
	sys_Disp.Text[2] = 0x00;
	sys_Disp.Text[3] = 0x00;
	sys_Disp.Text[4] = 0x00;
	sys_Disp.Text[5] = 0x00;
	sys_Disp.Text[6] = 0x00;
	sys_Disp.Text[7] = 0x00;
	sys_Disp.Text[8] = 0x00;
	sys_Disp.Begin_of_Scan = 0;
	sys_Disp.Ending_of_Scan = 0;
	sys_Disp.Current_of_Scan = 0;
	return;
}

// 应用程序接口API
void SetDisplayerArea(char Begin_of_scan, char Ending_of_Scan)
{
	sys_Disp.Begin_of_Scan  = Begin_of_scan;
	sys_Disp.Ending_of_Scan = Ending_of_Scan;
	return;
}

// 应用程序接口API
void Seg7Print(char d0, char d1, char d2, char d3, char d4, char d5, char d6, char d7)
{
	sys_Disp.Text[0] = d0;
	sys_Disp.Text[1] = d1;
	sys_Disp.Text[2] = d2;
	sys_Disp.Text[3] = d3;
	sys_Disp.Text[4] = d4;
	sys_Disp.Text[5] = d5;
	sys_Disp.Text[6] = d6;
	sys_Disp.Text[7] = d7;
	return;
}

// 应用程序接口API
void LedPrint(char led_val)
{
	sys_Disp.Text[8] = led_val;
	return;
}
