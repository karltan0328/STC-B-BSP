#ifndef _KARL_CALLBACK_H_
#define _KARL_CALLBACK_H_

// 时间事件
#define enumEventSys1mS             0
#define enumEventSys10mS            1
#define enumEventSys100mS           2
#define enumEventSys1S              3

// 按键事件
#define enumEventKey1_Press         4
#define enumEventKey1_Release       5
#define enumEventKey2_Press         6
#define enumEventKey2_Release       7
#define enumEventKey3_Press         8
#define enumEventKey3_Release       9
#define enumEventKeyUp_Press        10
#define enumEventKeyDown_Press      11
#define enumEventKeyLeft_Press      12
#define enumEventKeyRight_Press     13
#define enumEventKeyCenter_Press    14

// 未使用事件
#define enumEventHall               15
#define enumEventVib                16
#define enumEventNav                17
#define enumEventXADC               18
#define enumEventUart1Rxd           19
#define enumEventUart2Rxd           20
#define enumEventIrRxd              21

typedef void (*Callback)(void);

// 时间回调函数
extern Callback callback_1ms;
extern Callback callback_10ms;
extern Callback callback_100ms;
extern Callback callback_1s;

// 按键回调函数
extern Callback callback_key1_press;
extern Callback callback_key1_release;
extern Callback callback_key2_press;
extern Callback callback_key2_release;
extern Callback callback_key3_press;
extern Callback callback_key3_release;
extern Callback callback_keyUp_press;
extern Callback callback_keyDown_press;
extern Callback callback_keyLeft_press;
extern Callback callback_keyRight_press;
extern Callback callback_keyCenter_press;

// 未使用的回调函数
extern Callback callback_hall;
extern Callback callback_vib;
extern Callback callback_nav;
extern Callback callback_xadc;
extern Callback callback_uart1_rxd;
extern Callback callback_uart2_rxd;
extern Callback callback_ir_rxd;

void SetEventCallback(unsigned char event, void (*fp)());

#endif
