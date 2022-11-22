#include "STC15F2K60S2.h"
#include "karl_callback.h"

// 时间回调函数
Callback callback_1ms 			= 0;
Callback callback_10ms 			= 0;
Callback callback_100ms 		= 0;
Callback callback_1s 			= 0;

// 按键回调函数
Callback callback_key1_press 		= 0;
Callback callback_key1_release 		= 0;
Callback callback_key2_press 		= 0;
Callback callback_key2_release 		= 0;
Callback callback_key3_press 		= 0;
Callback callback_key3_release 		= 0;
Callback callback_keyUp_press 		= 0;
Callback callback_keyDown_press 	= 0;
Callback callback_keyLeft_press 	= 0;
Callback callback_keyRight_press 	= 0;
Callback callback_keyCenter_press 	= 0;

// 未使用的回调函数
Callback callback_hall 		= 0;
Callback callback_vib 		= 0;
Callback callback_nav 		= 0;
Callback callback_xadc 		= 0;
Callback callback_uart1_rxd = 0;
Callback callback_uart2_rxd = 0;
Callback callback_ir_rxd 	= 0;

void SetEventCallback(unsigned char event, void (*fp)())
{
	switch(event)
	{
		// 时间回调函数
		case enumEventSys1mS:			callback_1ms 				= fp;	break;
		case enumEventSys10mS:			callback_10ms 				= fp;	break;
		case enumEventSys100mS:			callback_100ms 				= fp;	break;
		case enumEventSys1S:			callback_1s 				= fp;	break;
		// 按键回调函数
		case enumEventKey1_Press:		callback_key1_press 		= fp;	break;
		case enumEventKey1_Release:		callback_key1_release 		= fp;	break;
		case enumEventKey2_Press:		callback_key2_press 		= fp;	break;
		case enumEventKey2_Release:		callback_key2_release 		= fp;	break;
		case enumEventKey3_Press:		callback_key3_press 		= fp;	break;
		case enumEventKey3_Release:		callback_key3_release 		= fp;	break;
		case enumEventKeyUp_Press:		callback_keyUp_press 		= fp;	break;
		case enumEventKeyDown_Press:	callback_keyDown_press 		= fp;	break;
		case enumEventKeyLeft_Press:	callback_keyLeft_press 		= fp;	break;
		case enumEventKeyRight_Press:	callback_keyRight_press 	= fp;	break;
		case enumEventKeyCenter_Press:	callback_keyCenter_press 	= fp;	break;
		// 未使用的回调函数
		case enumEventHall:				callback_hall 				= fp;	break;
		case enumEventVib:				callback_vib 				= fp;	break;
		case enumEventNav:				callback_nav 				= fp;	break;
		case enumEventXADC:				callback_xadc 				= fp;	break;
		case enumEventUart1Rxd:			callback_uart1_rxd 			= fp;	break;
		case enumEventUart2Rxd:			callback_uart2_rxd 			= fp;	break;
		case enumEventIrRxd:			callback_ir_rxd 			= fp;	break;
		default:															break;
	}
	return;
}
