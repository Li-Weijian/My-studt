#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 20

void cheak_in();				//��סģ��
void seekID();					//ID��ѯģ��
void seekAll();					//��ʾ������Ϣ
void seekRoom();				//���Ų�ѯģ��
void seekName();				//������ѯģ��
void RoomChange(int id, int NewRoom);	//��������ģ��
void CheakOut(int id);					//�˷�ģ��



typedef struct hotal
{
	int id;
	char name[NAME_MAX];
	int roomNum;
	struct hotal *pnext;				//�������һ���ṹ
}Hotal;									//����ڵ�

Hotal* photal = NULL;					//��������
FILE *fp;

int main(void)
{
	/*Ҫ����һ����������Ϊ������ڴ棬���ҽ���һ���ṹͷָ���ʼ��Ϊnull*/
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

void cheak_in()							//��סģ��
{
	int number;
	Hotal* pNew;
	Hotal* pTemp = photal;

	while (pTemp->pnext != NULL)		//�ҵ�����ĩβ
	{
		pTemp = pTemp->pnext;
	}

	printf("������Ҫ��ס��������\n");
	scanf("%d", &number);

	for (int i = 1; i <= number; i++)
	{
		pNew = (Hotal *)malloc(sizeof(Hotal));
		pNew->pnext = NULL;				//����һ������ͷָ���ʼ��Ϊ��
		
		printf("������� %d λ�˿͵�������", i);
		scanf("%s", &pNew->name);
		printf("������� %d λ�˿͵�ID��", i);
		scanf("%d", &pNew->id);
		printf("��������ס����ţ�");
		scanf("%d", &pNew->roomNum);

		pTemp->pnext = pNew;
		pTemp = pTemp->pnext;
	}
	printf("��ס�ɹ���\n");

}

void seekID()						//ID��ѯģ��
{
	////����һ�������ͷָ�븳ֵ��ptemp�������Ϳ����ж������Ƿ����
	Hotal* pTemp = photal->pnext;		
	int id;

	printf("������Ҫ���ҵ�ID�ţ�");
	scanf("%d", &id);
	printf("\t\t\t-ID -----����-----�����-----\n");

	while (pTemp != NULL)
	{
		if (pTemp->id == id)
		{
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
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
	printf("\t\t\t-ID -----����-----�����-----\n");

	while (pTemp != NULL)
	{
		if (pTemp->roomNum == roomNum)
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
		pTemp = pTemp->pnext;
	}
}

void seekAll()					//��ʾ������Ϣ
{
	Hotal* pTemp = photal->pnext;
	printf("\t\t\t-ID -----����-----�����-----\n");

	if (pTemp == NULL)
		printf("\t\t\t��ǰ��ס����Ϊ�գ�\n");
	while (pTemp != NULL)
	{
		printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
		pTemp = pTemp->pnext;
	}
}

void seekName()					//������ѯģ��
{
	Hotal* pTemp = photal->pnext;
	char name[NAME_MAX];

	printf("��������Ҫ���ҵĿ���������");
	scanf("%s", &name);
	printf("\t\t\t-ID -----����-----�����-----\n");

	while (pTemp != NULL)
	{
		if (strcmp(name, pTemp->name) == 0)
		{
			printf("\t\t\t-%-3d-----%s----%4d -----\n", pTemp->id, pTemp->name, pTemp->roomNum);
			return;
		}
		pTemp = pTemp->pnext;
	}
	printf("\t\t\t���޴˿��ˣ�\n");
}


void RoomChange(int id, int NewRoom)	//��������ģ��
{
	/*
		��������ģ����Է�Ϊ��	1.����ID��ѯ����
							2.���շ���Ų�ѯ����
							3.����������ѯ����

		��ˣ�������RoomChange�����е�������������

	*/
}