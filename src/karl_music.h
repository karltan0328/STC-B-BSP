#ifndef _KARL_MUSIC_H_
#define _KARL_MUSIC_H_

#define CLow    0
#define CMid    1
#define CHigh   2

#define START   1
#define STOP    0

extern void Music_Init();
/**
 * @brief 播放一个音符
 * 注意：每拍的长度是固定的500ms，不可修改
 * @param Tone_Level 是CLow，CMid还是CHigh
 * @param Tone_Kind 是哪个音符，0, 1, 1#, 2, 2#, 3, 4, 4#, 5, 5#, 6, 6#, 7  注意这里传入的是下标
 * @param Tone_Relative_Duration 音符相对长度，64, 32, 16, 8, 4, 2, 1       注意这里传入的是下标
 * 64为全音符，32为二分音符，16为四分音符，8为八分音符，4为十六分音符，2为三十二分音符，1为六十四分音符
 * 一个全音符占一整拍，一个二分音符占半拍，一个四分音符占四分之一拍，以此类推
 */
extern unsigned char Play_Tone(unsigned char Tone_Level, unsigned char Tone_Kind, unsigned char Tone_Relative_Duration);

/**
 * @brief 播放一首歌
 * 注意：每拍的长度是固定的500ms，不可修改
 * @param Tone_Level 是CLow，CMid还是CHigh
 * @param Music 歌的位置
 * 这里对歌的格式做说明：
 * 相比于Play_Tone()来说，Play_Music()缺少的是音符的种类和音符的长度，那么都需要在Music中指定
 * 种类有12种，需要4bit，而长度有7种，需要3bit，所以每个音符需要7bit
 * 规定高4bit为音符的种类，低4bit为音符的长度（低4bit的最高bit弃用）
 * @param Music_Length 歌曲音符的个数
 */
extern void Play_Music(unsigned char Tone_Level, unsigned char *Music, unsigned int Music_Length);

extern unsigned char Get_Time_By_Tone_Length(unsigned char Tone_Relative_Duration);

extern unsigned int Get_Music_Curr_Index();
extern void Set_Music_Curr_Index(unsigned int Index);

extern unsigned char Get_Music_Wait_To_Play_Tone_Level();

extern unsigned char Get_Play_State();
extern void Set_Play_State(unsigned char Control);

extern unsigned int Get_Music_Wait_To_Play_Length();

// 弃用
// extern void Play_Little_Star();

#endif
