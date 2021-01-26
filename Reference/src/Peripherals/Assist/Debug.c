#include <stdlib.h>
#include "Debug.h"
#include "error.h"


CMD_Str String = {NULL, NULL, NULL, NULL, NULL};

List_TypeDef * Debuglist = NULL;

/***********************************************************************
	[功	       能	]调试数据(读写寄存器、DDR值)初始化
	[参            数	]无
	[返    回    值	]操作是否成功
***********************************************************************/
s32 Debug_Init(void)
{
	Debuglist = CreatList();
	if(Debuglist == NULL)
		return FAILURE;
	return SUCCESS;
}

/***********************************************************************
	[功	       能	]找到字符串中的第一个非空格字符
	[参            数	]Str:目标字符串
	[返    回    值	]非空格字符地址
***********************************************************************/
char *Get_Non_space(char *Str)
{
	char * ptr = Str;
	while((*ptr) == ' ')
		ptr += 1;
	return ptr;
}

/***********************************************************************
	[功	       能	]解析串口协议,得到"str1 str2 str3 str4 str5",找5个字符串并执行命令
	[参            数	]无
	[返    回    值	]解析到的字符串数量
***********************************************************************/
s32 Analyze_Str(void)
{
	char *endstr = ((char *)Rx_buf) + count -1;		//指向最后一个字符

	Rx_buf[count] = '\0';							//给第最后一个字符串添加结束符

	String.Str1 = (char *)Rx_buf;					//找到第一个字符串str1
	String.Str1 = Get_Non_space(String.Str1);
	xil_printf("[UartOpt: %s]\n", String.Str1);
	if(NULL == String.Str1)
		return 1;

	String.Str2 = strstr(String.Str1, " ");
	if(NULL == String.Str2)
		return 2;
	*(String.Str2) = '\0';							//给第一个字符串添加结束符
	String.Str2 = Get_Non_space((String.Str2) + 1);	//找到第二个字符串


	String.Str3 = strstr(String.Str2, " ");
	if(NULL == String.Str3)
		return 3;
	*String.Str3 = '\0';							//给第二个字符串添加结束符
	String.Str3 = Get_Non_space((String.Str3) + 1);	//找到第三个字符串


	String.Str4 = strstr(String.Str3, " ");
	if(NULL == String.Str4)
		return 4;
	*String.Str4 = '\0';							//给第三个字符串添加结束符
	String.Str4 = Get_Non_space((String.Str4) + 1);	//找到第四个字符串


	String.Str5 = strstr(String.Str4, " ");
	if(NULL == String.Str5)
		return 5;
	*String.Str5 = '\0';							//给第四个字符串添加结束符
	String.Str5 = Get_Non_space((String.Str5) + 1); //找到第五个字符串
	endstr = strstr(String.Str5, " ");
	if(endstr != NULL)
		*endstr = '\0';

	Subj_Debug();

	return 0;
}

/***********************************************************************
	[功	       能	]等级1调试(主线程执行)
	[参            数	]无
	[返    回    值	]无
***********************************************************************/
void Subj_Debug(void)
{
	Debug_TypeDef Data;

	Data.path 	= UART;
	if(0 == strcmp(String.Str1, "write"))
	{

	}
	else if(0 == strcmp(String.Str1, "read"))
	{

	}
	Subj_Node(Debuglist, &Data);
}


/***********************************************************************
	[功	       能	]处理调试信息
	[参            数	]无
	[返    回    值	]执行结果
***********************************************************************/
s32 Analyze_Debug(void)
{
	Debug_TypeDef node;
	if(Decr_Node(Debuglist, &node))//链表为空(没有数据)
		return 1;
	if(0x1 == node.Order)
	{

	}

	return 0;
}








