#ifndef _KARL_KEY_H_
#define _KARL_KEY_H_

// 按键名
#define enumKey1 0
#define enumKey2 1

// 按键动作
#define enumKeyPress 0
#define enumKeyRelease 1

extern void Key_Init();
extern unsigned char GetKeyAct(char Key);

#endif
