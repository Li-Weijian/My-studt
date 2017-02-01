#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 20
#define ROOM_MAX 10

int welcome();					//��ӭ����
void seek();					//��ѯ������ģ��
void cheak_in();				//��סģ��
void hotalType(int *, int *);	//�ù�����
void seekID();					//ID��ѯģ��
void seekAll();					//��ʾ������Ϣ
void seekRoom();				//���Ų�ѯģ��
void seekName();				//������ѯģ��
void RoomChange(int id, int NewRoom);	//��������ģ��
void CheakOut(int id);					//�˷�ģ��

struct Room
{
	char small_room[ROOM_MAX] = { "С��" };			//����
	int small_price = 50;							//�۸�
	int small_count = 30;							//ʣ������

	char medium_room[ROOM_MAX] = { "�з�" };
	int medium_price = 100;
	int medium_count = 20;

	char big_room[ROOM_MAX] = { "��" };
	int big_price = 150;
	int big_count = 10;

	char luxu_room[ROOM_MAX] = { "������" };
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
	struct hotal *pnext;				//�������һ���ṹ
}Hotal;									//����ڵ�

Hotal* photal = NULL;					//��������
FILE *fp;

int main(void)
{
	/*Ҫ����һ����������Ϊ������ڴ棬���ҽ���һ���ṹͷָ���ʼ��Ϊnull*/
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
		case 3://��������
		case 4://�˷�����
		case 5:printf("��лʹ�ñ�ϵͳ��ף������죡\n");
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

void cheak_in()							//��סģ��
{
	int person;
	int roomCount;						//��������ָ�������hotalType��������
	int roomType;
	Room room;
	Hotal* pNew;
	Hotal* pTemp = photal;
	bool flat = true;					//�˱���Ϊ�ж�whileѭ���ı�־
	system("cls");

	while (pTemp->pnext != NULL)		//�ҵ�����ĩβ
	{
		pTemp = pTemp->pnext;
	}

	printf("������Ҫ��ס��������");
	scanf("%d", &person);
	hotalType(&roomType, &roomCount);

	while (flat)
	{
		switch (roomType)
		{
		case 1:
			if (room.small_count < roomCount)
			{
				printf("�����������㣬������ѡ��\n");
				hotalType(&roomType, &roomCount);
				break;
			}
			else
			{
				room.small_count = room.small_count - roomCount;
				flat = false;		//����������ʱ����whileѭ��
				break;
			}
		case 2:
			if (room.medium_count < roomCount)
			{
				printf("�����������㣬������ѡ��\n");
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
				printf("�����������㣬������ѡ��\n");
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
				printf("�����������㣬������ѡ��\n");
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
		pNew->pnext = NULL;				//����һ������ͷָ���ʼ��Ϊ��

		printf("������� %d λ�˿͵�������", i);
		scanf("%s", &pNew->name);
		printf("������� %d λ�˿͵�ID��", i);
		scanf("%d", &pNew->id);
		printf("��������ס����ţ�");
		scanf("%d", &pNew->roomNum);

		switch (roomType)
		{
		case 1:strcpy(pNew->roomType, "С��");				//pNew->roomType = {"С��"};  Ϊʲô�����ԣ�
			pNew->price = room.small_price;
			break;
		case 2:strcpy(pNew->roomType, "�з�");
			pNew->price = room.medium_price;
			break;
		case 3:strcpy(pNew->roomType, "��");
			pNew->price = room.big_price;
			break;
		case 4:strcpy(pNew->roomType, "������");
			pNew->price = room.luxu_price;
			break;
		}
		pTemp->pnext = pNew;
		pTemp = pTemp->pnext;
	}
	system("cls");
	printf("��ס�ɹ���\n");

}

void seekID()						//ID��ѯģ��
{
	////����һ�������ͷָ�븳ֵ��ptemp�������Ϳ����ж������Ƿ����
	Hotal* pTemp = photal->pnext;
	int id;

	printf("������Ҫ���ҵ�ID�ţ�");
	scanf("%d", &id);
	printf("\t\t\t-ID -----����-----����------�����-----�۸�------\n");

	while (pTemp != NULL)
	{
		if (pTemp->id == id)
		{
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t���޴�ID�ͻ���ס��\n");
}


/*
��ģ�������⣺
��Ҫʵ�ֱ��������еĿ��˺��ٽ�����ŷ���Ҫ��Ŀͻ���ʾ����
�������1.�������������Ҫ��ķ���ţ���ô��ʾ��������return������������
����ֻ�����һ����Ϣ��
2.�����ʹ��return�������������Բ��ҵ����з���Ҫ��ķ���ţ�
���ǵ�����������û�в��ҵ���Ҫ�ķ����ʱ���޷�����������ʾ�������Ǵ�����ġ�
*/
void seekRoom()					//���Ų�ѯģ��
{
	Hotal* pTemp = photal->pnext;
	int roomNum;

	printf("������Ҫ���ҵķ���ţ�");
	scanf("%d", &roomNum);
	printf("\t\t\t-ID -----����-----����------�����-----�۸�------\n");

	while (pTemp != NULL)
	{
		if (pTemp->roomNum == roomNum)
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
		pTemp = pTemp->pnext;
	}
}

void seekAll()					//��ʾ������Ϣ
{
	Hotal* pTemp = photal->pnext;
	printf("\t\t\t-ID -----����-----����------�����-----�۸�------\n");

	if (pTemp == NULL)
		printf("\t\t\t��ǰ��ס����Ϊ�գ�\n");
	while (pTemp != NULL)
	{
		printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
		pTemp = pTemp->pnext;
	}
}

void seekName()					//������ѯģ��
{
	Hotal* pTemp = photal->pnext;
	char name[NAME_MAX];

	printf("��������Ҫ���ҵĿ���������");
	scanf("%s", &name);
	printf("\t\t\t-ID -----����-----����------�����-----�۸�------\n");

	while (pTemp != NULL)
	{
		if (strcmp(name, pTemp->name) == 0)
		{
			printf("\t\t\t-%-3d-----%s----%4s------%4d -----%d------\n", pTemp->id, pTemp->name, pTemp->roomType, pTemp->roomNum, pTemp->price);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t���޴˿��ˣ�\n");
}


void RoomChange(int id, int NewRoom)	//��������ģ��
{
	/*
	��������ģ����Է�Ϊ��1.����ID��ѯ����
	2.���շ���Ų�ѯ����
	3.����������ѯ����

	��ˣ�������RoomChange�����е�������������

	*/
}

void hotalType(int *roomType, int *roomCount)		//�ù�����
{
	Room room;

	printf("\t\t\t----����------�۸�------ʣ�෿��------|\n");
	printf("\t\t\t1.--%s------ %d ------   %d   ------|\n", room.small_room, room.small_price, room.small_count);
	printf("\t\t\t2.--%s------ %d ------  %d   ------|\n", room.medium_room, room.medium_price, room.medium_count);
	printf("\t\t\t3.--%s------ %d ------  %d   ------|\n", room.big_room, room.big_price, room.big_count);
	printf("\t\t\t4.--%s---- %d ------   %d   ------|\n", room.luxu_room, room.luxu_price, room.luxu_count);
	printf("��ѡ����Ҫ��ס�ķ�������(1--4)��");
	scanf("%d", roomType);			//�˴���ע�⣡������ΪroomType��roomCount����Ϊָ�룬����&������ľ��ǵ�ַ�������޷���ȷ��ֵ����ָ����������ȷ��ֵ
	printf("��������Ҫ�ķ�������");
	scanf("%d", roomCount);

	while ((*roomType < 1) && (*roomType > 4))
	{
		printf("�����������������룺\n");
		scanf("%d", roomType);
	}
}

int welcome()						//��ӭ����
{
	int choice;

	printf("\t\t��ӭʹ��С���ùݹ���ϵͳ\n");
	printf("\t\t\t|--------------------|\n");
	printf("\t\t\t|-----1.��ס����-----|\n");
	printf("\t\t\t|-----2.��ѯ����-----|\n");
	printf("\t\t\t|-----3.��������-----|\n");
	printf("\t\t\t|-----4.�˷�����-----|\n");
	printf("\t\t\t|-----5.�˳�ϵͳ-----|\n");
	printf("\t\t\t|--------------------|\n");
	printf("��ѡ���Ӧ��Ž��в�����");
	scanf("%d", &choice);

	while (choice > 5 && choice < 1)
	{
		printf("ѡ�����������ѡ��\n");
		scanf("%d", &choice);
	}
	return choice;
}

void seek()						//��ѯ������ģ��
{
	int choice;
	system("cls");
	do
	{

		printf("\n\t\t\t|--------------------|\n");
		printf("\t\t\t|-----1.��ѯȫ��-----|\n");
		printf("\t\t\t|-----2.I D ����-----|\n");
		printf("\t\t\t|-----3.��������-----|\n");
		printf("\t\t\t|-----4.���Ų���-----|\n");
		printf("\t\t\t|-----5.���ز˵�-----|\n");
		printf("\t\t\t|--------------------|\n");
		printf("�������Ӧ��Ž��в��ң�");
		scanf("%d", &choice);

		while (choice > 5 && choice < 1)
		{
			printf("ѡ�����������ѡ��\n");
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
