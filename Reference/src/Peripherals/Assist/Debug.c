#include <stdlib.h>
#include "Debug.h"
#include "error.h"


CMD_Str String = {NULL, NULL, NULL, NULL, NULL};

List_TypeDef * Debuglist = NULL;

/***********************************************************************
	[��	       ��	]��������(��д�Ĵ�����DDRֵ)��ʼ��
	[��            ��	]��
	[��    ��    ֵ	]�����Ƿ�ɹ�
***********************************************************************/
s32 Debug_Init(void)
{
	Debuglist = CreatList();
	if(Debuglist == NULL)
		return FAILURE;
	return SUCCESS;
}

/***********************************************************************
	[��	       ��	]�ҵ��ַ����еĵ�һ���ǿո��ַ�
	[��            ��	]Str:Ŀ���ַ���
	[��    ��    ֵ	]�ǿո��ַ���ַ
***********************************************************************/
char *Get_Non_space(char *Str)
{
	char * ptr = Str;
	while((*ptr) == ' ')
		ptr += 1;
	return ptr;
}

/***********************************************************************
	[��	       ��	]��������Э��,�õ�"str1 str2 str3 str4 str5",��5���ַ�����ִ������
	[��            ��	]��
	[��    ��    ֵ	]���������ַ�������
***********************************************************************/
s32 Analyze_Str(void)
{
	char *endstr = ((char *)Rx_buf) + count -1;		//ָ�����һ���ַ�

	Rx_buf[count] = '\0';							//�������һ���ַ�����ӽ�����

	String.Str1 = (char *)Rx_buf;					//�ҵ���һ���ַ���str1
	String.Str1 = Get_Non_space(String.Str1);
	xil_printf("[UartOpt: %s]\n", String.Str1);
	if(NULL == String.Str1)
		return 1;

	String.Str2 = strstr(String.Str1, " ");
	if(NULL == String.Str2)
		return 2;
	*(String.Str2) = '\0';							//����һ���ַ�����ӽ�����
	String.Str2 = Get_Non_space((String.Str2) + 1);	//�ҵ��ڶ����ַ���


	String.Str3 = strstr(String.Str2, " ");
	if(NULL == String.Str3)
		return 3;
	*String.Str3 = '\0';							//���ڶ����ַ�����ӽ�����
	String.Str3 = Get_Non_space((String.Str3) + 1);	//�ҵ��������ַ���


	String.Str4 = strstr(String.Str3, " ");
	if(NULL == String.Str4)
		return 4;
	*String.Str4 = '\0';							//���������ַ�����ӽ�����
	String.Str4 = Get_Non_space((String.Str4) + 1);	//�ҵ����ĸ��ַ���


	String.Str5 = strstr(String.Str4, " ");
	if(NULL == String.Str5)
		return 5;
	*String.Str5 = '\0';							//�����ĸ��ַ�����ӽ�����
	String.Str5 = Get_Non_space((String.Str5) + 1); //�ҵ�������ַ���
	endstr = strstr(String.Str5, " ");
	if(endstr != NULL)
		*endstr = '\0';

	Subj_Debug();

	return 0;
}

/***********************************************************************
	[��	       ��	]�ȼ�1����(���߳�ִ��)
	[��            ��	]��
	[��    ��    ֵ	]��
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
	[��	       ��	]���������Ϣ
	[��            ��	]��
	[��    ��    ֵ	]ִ�н��
***********************************************************************/
s32 Analyze_Debug(void)
{
	Debug_TypeDef node;
	if(Decr_Node(Debuglist, &node))//����Ϊ��(û������)
		return 1;
	if(0x1 == node.Order)
	{

	}

	return 0;
}








