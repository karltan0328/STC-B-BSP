#ifndef _KARL_BEEP_H
#define _KARL_BEEP_H

#define Endless_Beep 0xffff

extern void Beep_Init();
extern unsigned char Set_Beep(unsigned int Beep_Frequency, unsigned char Beep_Time);

extern unsigned int Get_Beep_Frequency();
extern unsigned char Get_Beep_Time();

#endif
