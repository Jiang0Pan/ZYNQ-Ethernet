#ifndef _DEBUGLIST_H
#define _DEBUGLIST_H


#include "xil_io.h"

//������Դ
typedef enum {
	UART,
	NET,
}Opt_S;

//���ԼĴ���
typedef struct {
	u8 Order;
	union {
		struct {
			u8 First:	4;	//һ�����
			u8 Second:	4;	//�������
		};
		u8 Serial;			//��ͨ���
	};						//�����
	u32 addr;
	u32 data;
	Opt_S path;
}Debug_TypeDef;	//������������

typedef struct Node{
	Debug_TypeDef Data;
	struct Node * Next;
}List_TypeDef;



List_TypeDef * CreatList(void);							 //��������

u8 Free_List(List_TypeDef * list);						 //ɾ������

u8 Subj_Node(List_TypeDef * list, Debug_TypeDef *Data);  //���ӽ��

u8 Decr_Node(List_TypeDef * list, Debug_TypeDef *Data);	 //(��ͷ���)���ٽ�㣬����������















#endif







