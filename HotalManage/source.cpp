#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 20
#define ROOM_MAX 10

int welcome();					//欢迎界面
void seek();					//查询管理总模块
void cheak_in();				//入住模块
void hotalType(int *, int *);	//旅馆类型
void seekID();					//ID查询模块
void seekAll();					//显示所有信息
void seekRoom();				//房号查询模块
void seekName();				//姓名查询模块
void RoomChange(int id, int NewRoom);	//更换房间模块
void CheakOut(int id);					//退房模块

struct Room
{
	char small_room[ROOM_MAX] = { "小房" };			//类型
	int small_price = 50;							//价格
	int small_count = 30;							//剩余数量

	char medium_room[ROOM_MAX] = { "中房" };
	int medium_price = 100;
	int medium_count = 20;

	char big_room[ROOM_MAX] = { "大房" };
	int big_price = 150;
	int big_count = 10;

	char luxu_room[ROOM_MAX] = { "豪华房" };
	int luxu_price = 200;
	int luxu_count = 5;
};

typedef struct hotal
{
	int id;
	char name[NAME_MAX];
	char roomType[ROOM_MAX];
	int roomNum;
	int price;
	struct hotal *pnext;				//链表的下一个结构
}Hotal;									//链表节点

Hotal* photal = NULL;					//定义链表
FILE *fp;

int main(void)
{
	/*要建立一个链表，必须为其分配内存，并且将下一个结构头指针初始化为null*/
	photal = (Hotal*)malloc(sizeof(Hotal));
	photal->pnext = NULL;
	int choice;

	while (1)
	{
		choice = welcome();
		switch (choice)
		{
		case 1:cheak_in(); break;
		case 2:seek(); break;
		case 3://更换房间
		case 4://退房管理
		case 5:printf("感谢使用本系统！祝生活愉快！\n");
			system("pause");
			exit(EXIT_SUCCESS);

		}
	}
	//	cheak_in();
	//	seekID();
	//	seekRoom();
	//	seekAll();
	//	seekName();

	system("pause");
	return 0;
}

void cheak_in()							//入住模块
{
	int person;
	int roomCount;						//定义两个指针变量供hotalType函数操作
	int roomType;
	Room room;
	Hotal* pNew;
	Hotal* pTemp = photal;
	bool flat = true;					//此变量为判断while循环的标志
	system("cls");

	while (pTemp->pnext != NULL)		//找到链表末尾
	{
		pTemp = pTemp->pnext;
	}

	printf("请输入要入住的人数：");
	scanf("%d", &person);
	hotalType(&roomType, &roomCount);

	while (flat)
	{
		switch (roomType)
		{
		case 1:
			if (room.small_count < roomCount)
			{
				printf("房间数量不足，请重新选择！\n");
				hotalType(&roomType, &roomCount);
				break;
			}
			else
			{
				room.small_count = room.small_count - roomCount;
				flat = false;		//当符合条件时跳出while循环
				break;
			}
		case 2:
			if (room.medium_count < roomCount)
			{
				printf("房间数量不足，请重新选择！\n");
				hotalType(&roomType, &roomCount);
				break;
			}
			else
			{
				room.medium_count = room.medium_count - roomCount;
				flat = false;
				break;
			}
		case 3:
			if (room.big_count < roomCount)
			{
				printf("房间数量不足，请重新选择！\n");
				hotalType(&roomType, &roomCount);
				break;
			}
			else
			{
				room.big_count = room.big_count - roomCount;
				flat = false;
				break;
			}
		case 4:
			if (room.luxu_count < roomCount)
			{
				printf("房间数量不足，请重新选择！\n");
				hotalType(&roomType, &roomCount);
				break;
			}
			else
			{
				room.luxu_count = room.luxu_count - roomCount;
				flat = false;
				break;
			}
		}
	}

	for (int i = 1; i <= person; i++)
	{
		pNew = (Hotal *)malloc(sizeof(Hotal));
		pNew->pnext = NULL;				//将下一个链表头指针初始化为空

		printf("请输入第 %d 位顾客的姓名：", i);
		scanf("%s", &pNew->name);
		printf("请输入第 %d 位顾客的ID：", i);
		scanf("%d", &pNew->id);
		printf("请输入入住房间号：");
		scanf("%d", &pNew->roomNum);

		switch (roomType)
		{
		case 1:strcpy(pNew->roomType, "小房");				//pNew->roomType = {"小房"};  为什么不可以？
			pNew->price = room.small_price;
			break;
		case 2:strcpy(pNew->roomType, "中房");
			pNew->price = room.medium_price;
			break;
		case 3:strcpy(pNew->roomType, "大房");
			pNew->price = room.big_price;
			break;
		case 4:strcpy(pNew->roomType, "豪华房");
			pNew->price = room.luxu_price;
			break;
		}
		pTemp->pnext = pNew;
		pTemp = pTemp->pnext;
	}
	system("cls");
	printf("入住成功！\n");

}

void seekID()						//ID查询模块
{
	////将下一个链表的头指针赋值给ptemp，这样就可以判断链表是否结束
	Hotal* pTemp = photal->pnext;
	int id;

	printf("请输入要查找的ID号：");
	scanf("%d", &id);
	printf("\t\t\t-ID -----姓名-----类型------房间号-----价格------\n");

	while (pTemp != NULL)
	{
		if (pTemp->id == id)
		{
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
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
	printf("\t\t\t-ID -----姓名-----类型------房间号-----价格------\n");

	while (pTemp != NULL)
	{
		if (pTemp->roomNum == roomNum)
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
		pTemp = pTemp->pnext;
	}
}

void seekAll()					//显示所有信息
{
	Hotal* pTemp = photal->pnext;
	printf("\t\t\t-ID -----姓名-----类型------房间号-----价格------\n");

	if (pTemp == NULL)
		printf("\t\t\t当前入住人数为空！\n");
	while (pTemp != NULL)
	{
		printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
		pTemp = pTemp->pnext;
	}
}

void seekName()					//姓名查询模块
{
	Hotal* pTemp = photal->pnext;
	char name[NAME_MAX];

	printf("请输入你要查找的客人姓名：");
	scanf("%s", &name);
	printf("\t\t\t-ID -----姓名-----类型------房间号-----价格------\n");

	while (pTemp != NULL)
	{
		if (strcmp(name, pTemp->name) == 0)
		{
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t查无此客人！\n");
}


void RoomChange(int id, int NewRoom)	//更换房间模块
{
	/*
	更换房间模块可以分为：1.按照ID查询更换
	2.按照房间号查询更换
	3.按照姓名查询更换

	因此：可以在RoomChange函数中调用三个函数。

	*/
}

void hotalType(int *roomType, int *roomCount)		//旅馆类型
{
	Room room;

	printf("\t\t\t----类型------价格------剩余房间------|\n");
	printf("\t\t\t1.--%s------ %d ------   %d   ------|\n", room.small_room, room.small_price, room.small_count);
	printf("\t\t\t2.--%s------ %d ------  %d   ------|\n", room.medium_room, room.medium_price, room.medium_count);
	printf("\t\t\t3.--%s------ %d ------  %d   ------|\n", room.big_room, room.big_price, room.big_count);
	printf("\t\t\t4.--%s---- %d ------   %d   ------|\n", room.luxu_room, room.luxu_price, room.luxu_count);
	printf("请选择需要入住的房间类型(1--4)：");
	scanf("%d", roomType);			//此处需注意！！！因为roomType和roomCount变量为指针，加上&后操作的就是地址，所以无法正确赋值，用指针名即可正确赋值
	printf("请输入需要的房间数：");
	scanf("%d", roomCount);

	while ((*roomType < 1) && (*roomType > 4))
	{
		printf("输入有误，请重新输入：\n");
		scanf("%d", roomType);
	}
}

int welcome()						//欢迎界面
{
	int choice;

	printf("\t\t欢迎使用小建旅馆管理系统\n");
	printf("\t\t\t|--------------------|\n");
	printf("\t\t\t|-----1.入住管理-----|\n");
	printf("\t\t\t|-----2.查询管理-----|\n");
	printf("\t\t\t|-----3.更换房间-----|\n");
	printf("\t\t\t|-----4.退房管理-----|\n");
	printf("\t\t\t|-----5.退出系统-----|\n");
	printf("\t\t\t|--------------------|\n");
	printf("请选择对应序号进行操作：");
	scanf("%d", &choice);

	while (choice > 5 && choice < 1)
	{
		printf("选项错误！请重新选择！\n");
		scanf("%d", &choice);
	}
	return choice;
}

void seek()						//查询管理总模块
{
	int choice;
	system("cls");
	do
	{

		printf("\n\t\t\t|--------------------|\n");
		printf("\t\t\t|-----1.查询全部-----|\n");
		printf("\t\t\t|-----2.I D 查找-----|\n");
		printf("\t\t\t|-----3.姓名查找-----|\n");
		printf("\t\t\t|-----4.房号查找-----|\n");
		printf("\t\t\t|-----5.返回菜单-----|\n");
		printf("\t\t\t|--------------------|\n");
		printf("请输入对应序号进行查找：");
		scanf("%d", &choice);

		while (choice > 5 && choice < 1)
		{
			printf("选项错误！请重新选择！\n");
			scanf("%d", &choice);
		}

		system("cls");
		switch (choice)
		{
		case 1:seekAll();
			break;
		case 2:seekID();
			break;
		case 3:seekName();
			break;
		case 4:seekRoom();
			break;
		}
	} while (choice != 5);
}
