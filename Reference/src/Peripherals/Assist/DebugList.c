#include "DebugList.h"
#include <malloc.h>






/*
	创建链表
*/
List_TypeDef * CreatList(void)
{
	List_TypeDef * list = (List_TypeDef *)malloc(sizeof(List_TypeDef));
	if(NULL == list)
		return NULL;
	list->Data.Order = 0;
	list->Data.addr  = 0;
	list->Data.data  = 0;
	list->Next = NULL;
	return list;
}

/*
	释放链表
*/
u8 Free_List(List_TypeDef * list)
{
	List_TypeDef * fnode = list->Next;		//释放结点的指针，指向第一个有效结点
	List_TypeDef * nnode = list;			//释放结点的下一个结点指针
	list->Next = NULL;
	if(NULL == list)
		return 1;

	while(NULL != fnode)
	{
		nnode = fnode->Next;
		free(fnode);
		fnode = nnode;
	}
	free(list);								//释放头结点
	return 0;
}

/*
	插入数据到尾结点
*/
u8 Subj_Node(List_TypeDef * list, Debug_TypeDef *Data)
{
	List_TypeDef *p = list;
	if(NULL == list)
		return 1;

	while((p->Next) != NULL)				//找到最后一个结点
		p = p->Next;

	List_TypeDef * node = (List_TypeDef *)malloc(sizeof(List_TypeDef));
	if(NULL == node)
		return 1;

	memcpy(&(node->Data), Data, sizeof(Debug_TypeDef));//数据赋值
	node->Next = NULL;
	p->Next = node;

	return 0;
}

/*
	取出第一个有效结点,并返回数据
*/
u8 Decr_Node(List_TypeDef * list, Debug_TypeDef * Rdata)
{
	if(NULL == list || NULL == list->Next)
		return 1;

	List_TypeDef * rnode = list->Next;
	List_TypeDef * nnode = rnode->Next;
	list->Next = nnode;
	memcpy(Rdata, &(rnode->Data), sizeof(Debug_TypeDef));//复制数据

	free(rnode);

	return 0;
}


