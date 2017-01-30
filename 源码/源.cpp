#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 20

void cheak_in();				//入住模块
void seekID();					//ID查询模块
void seekAll();					//显示所有信息
void seekRoom();				//房号查询模块
void seekName();				//姓名查询模块
void RoomChange(int id, int NewRoom);	//更换房间模块
void CheakOut(int id);					//退房模块



typedef struct hotal
{
	int id;
	char name[NAME_MAX];
	int roomNum;
	struct hotal *pnext;				//链表的下一个结构
}Hotal;									//链表节点

Hotal* photal = NULL;					//定义链表
FILE *fp;

int main(void)
{
	/*要建立一个链表，必须为其分配内存，并且将下一个结构头指针初始化为null*/
	photal = (Hotal*)malloc(sizeof(Hotal));		
	photal->pnext = NULL;
	
	cheak_in();
	seekID();
	seekRoom();
	seekAll();
	seekName();

	system("pause");
	return 0;
}

void cheak_in()							//入住模块
{
	int number;
	Hotal* pNew;
	Hotal* pTemp = photal;

	while (pTemp->pnext != NULL)		//找到链表末尾
	{
		pTemp = pTemp->pnext;
	}

	printf("请输入要入住的人数：\n");
	scanf("%d", &number);

	for (int i = 1; i <= number; i++)
	{
		pNew = (Hotal *)malloc(sizeof(Hotal));
		pNew->pnext = NULL;				//将下一个链表头指针初始化为空
		
		printf("请输入第 %d 位顾客的姓名：", i);
		scanf("%s", &pNew->name);
		printf("请输入第 %d 位顾客的ID：", i);
		scanf("%d", &pNew->id);
		printf("请输入入住房间号：");
		scanf("%d", &pNew->roomNum);

		pTemp->pnext = pNew;
		pTemp = pTemp->pnext;
	}
	printf("入住成功！\n");

}

void seekID()						//ID查询模块
{
	////将下一个链表的头指针赋值给ptemp，这样就可以判断链表是否结束
	Hotal* pTemp = photal->pnext;		
	int id;

	printf("请输入要查找的ID号：");
	scanf("%d", &id);
	printf("\t\t\t-ID -----姓名-----房间号-----\n");

	while (pTemp != NULL)
	{
		if (pTemp->id == id)
		{
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t暂无此ID客户入住！\n");
}


/*
	此模块有问题：
	需要实现遍历完所有的客人后再将房间号符合要求的客户显示出来
	待解决：1.如果遍历到符合要求的房间号，那么显示，可以用return来结束遍历，
			 但是只能输出一个信息。
		   2.如果不使用return结束遍历，可以查找到所有符合要求的房间号，
			 但是当遍历完链表没有查找到需要的房间号时，无法给出错误提示。【这是待解决的】
*/
void seekRoom()					//房号查询模块
{
	Hotal* pTemp = photal->pnext;
	int roomNum;

	printf("请输入要查找的房间号：");
	scanf("%d", &roomNum);
	printf("\t\t\t-ID -----姓名-----房间号-----\n");

	while (pTemp != NULL)
	{
		if (pTemp->roomNum == roomNum)
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
		pTemp = pTemp->pnext;
	}
}

void seekAll()					//显示所有信息
{
	Hotal* pTemp = photal->pnext;
	printf("\t\t\t-ID -----姓名-----房间号-----\n");

	if (pTemp == NULL)
		printf("\t\t\t当前入住人数为空！\n");
	while (pTemp != NULL)
	{
		printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
		pTemp = pTemp->pnext;
	}
}

void seekName()					//姓名查询模块
{
	Hotal* pTemp = photal->pnext;
	char name[NAME_MAX];

	printf("请输入你要查找的客人姓名：");
	scanf("%s", &name);
	printf("\t\t\t-ID -----姓名-----房间号-----\n");

	while (pTemp != NULL)
	{
		if (strcmp(name, pTemp->name) == 0)
		{
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t查无此客人！\n");
}


void RoomChange(int id, int NewRoom)	//更换房间模块
{
	/*
		更换房间模块可以分为：	1.按照ID查询更换
							2.按照房间号查询更换
							3.按照姓名查询更换

		因此：可以在RoomChange函数中调用三个函数。

	*/
}