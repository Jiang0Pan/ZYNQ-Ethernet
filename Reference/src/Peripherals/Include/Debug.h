#ifndef _DEBUG_H
#define _DEBUG_H


#include "uart1.h"
#include "timer.h"
#include "DebugList.h"


//µ˜ ‘√¸¡Ó
typedef struct {
	char *Str1;
	char *Str2;
	char *Str3;
	char *Str4;
	char *Str5;
}CMD_Str;


//////////////////////////////////////////////////////////////////////////
s32 Debug_Init(void);

s32 Analyze_Str(void);

void Subj_Debug(void);

s32 Analyze_Debug(void);















#endif
