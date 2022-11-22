#ifndef _KARL_STEPMOTOR_H_
#define _KARL_STEPMOTOR_H_

#define enumStepMotor1 0   // 左4LED
#define enumStepMotor2 1   // 右4LED
#define enumStepMotor3 2   // SM接口上的实体motor

#define Left    0
#define Right   1

extern void StepMotor_Init();
extern void StepMotor_Run(unsigned char StepMotor, unsigned char Direction);
extern void StepMotor_SetSpeed(unsigned char StepMotor, unsigned char Speed);
extern void StepMotor_SpeedUP(unsigned char StepMotor);
extern void StepMotor_SpeedDown(unsigned char StepMotor);
extern void StepMotor_SpeedHold(unsigned char StepMotor);

extern unsigned char Get_Speed(unsigned char StepMotor);
extern unsigned char Get_Speed_UP(unsigned char StepMotor);
extern unsigned char Get_Speed_Down(unsigned char StepMotor);
extern unsigned char Get_Speed_Direction(unsigned char StepMotor);

#endif
