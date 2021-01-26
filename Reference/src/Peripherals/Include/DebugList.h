#ifndef _DEBUGLIST_H
#define _DEBUGLIST_H


#include "xil_io.h"

//操作来源
typedef enum {
	UART,
	NET,
}Opt_S;

//调试寄存器
typedef struct {
	u8 Order;
	union {
		struct {
			u8 First:	4;	//一级序号
			u8 Second:	4;	//二级序号
		};
		u8 Serial;			//普通序号
	};						//序号类
	u32 addr;
	u32 data;
	Opt_S path;
}Debug_TypeDef;	//调试数据类型

typedef struct Node{
	Debug_TypeDef Data;
	struct Node * Next;
}List_TypeDef;



List_TypeDef * CreatList(void);							 //创建链表

u8 Free_List(List_TypeDef * list);						 //删除链表

u8 Subj_Node(List_TypeDef * list, Debug_TypeDef *Data);  //增加结点

u8 Decr_Node(List_TypeDef * list, Debug_TypeDef *Data);	 //(从头结点)减少结点，并返回数据















#endif







