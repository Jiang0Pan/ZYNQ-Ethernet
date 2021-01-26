#include "DebugList.h"
#include <malloc.h>






/*
	��������
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
	�ͷ�����
*/
u8 Free_List(List_TypeDef * list)
{
	List_TypeDef * fnode = list->Next;		//�ͷŽ���ָ�룬ָ���һ����Ч���
	List_TypeDef * nnode = list;			//�ͷŽ�����һ�����ָ��
	list->Next = NULL;
	if(NULL == list)
		return 1;

	while(NULL != fnode)
	{
		nnode = fnode->Next;
		free(fnode);
		fnode = nnode;
	}
	free(list);								//�ͷ�ͷ���
	return 0;
}

/*
	�������ݵ�β���
*/
u8 Subj_Node(List_TypeDef * list, Debug_TypeDef *Data)
{
	List_TypeDef *p = list;
	if(NULL == list)
		return 1;

	while((p->Next) != NULL)				//�ҵ����һ�����
		p = p->Next;

	List_TypeDef * node = (List_TypeDef *)malloc(sizeof(List_TypeDef));
	if(NULL == node)
		return 1;

	memcpy(&(node->Data), Data, sizeof(Debug_TypeDef));//���ݸ�ֵ
	node->Next = NULL;
	p->Next = node;

	return 0;
}

/*
	ȡ����һ����Ч���,����������
*/
u8 Decr_Node(List_TypeDef * list, Debug_TypeDef * Rdata)
{
	if(NULL == list || NULL == list->Next)
		return 1;

	List_TypeDef * rnode = list->Next;
	List_TypeDef * nnode = rnode->Next;
	list->Next = nnode;
	memcpy(Rdata, &(rnode->Data), sizeof(Debug_TypeDef));//��������

	free(rnode);

	return 0;
}


