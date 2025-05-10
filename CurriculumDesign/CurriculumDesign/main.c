#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "system.h"
#include "purchase.h"
#include "goods.h"
#include "admin.h"
#include "sale.h"
#include "customer.h"
#include "salesperson.h"
AllGoodList all_good_list;
PurchaseList purchase_record;
SaleList sale_record;
CustomerList customer_list;

extern char input_salesperson_name[100];

int choice;

int main()
{
	// ��ӡһЩ������Ϣ����ʽ�ǣ���Ʒ��� ��Ʒ���� ��Ʒ���� ��Ʒ���� ��Ӧ��

	TimerStart(); // ������ʱ��
	Init_PurchaseList(&purchase_record);
	Init_CustomerList(&customer_list);
	Init_SaleList(&sale_record);
	Init_AllGoodList(&all_good_list);
	while (1)
	{
		// ��ӡһ���б߿�Ľ���
		system("cls");
		printf("+------------------------------------------------+\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                С�ͳ��й���ϵͳ                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("+------------------------------------------------+\n");
		printf("��������ǣ�0����λϵͳ��1������Ա��2���ۻ�Ա����\n");
		scanf("%d", &choice);
		if(choice == 0)
		{
			ResetSystem(); // ��λϵͳ
			printf("ϵͳ�Ѹ�λ��\n");
			printf("���س�����...");
			while (getchar()!= '\n')
				;
			continue;
		}
		if (choice == 1) // ����Ա
		{
			// ��¼
			while (!admin_login())
				;
			Admin(); // ���ù���Ա����
			printf("���س�����...");
			while (getchar() != '\n')
				;
			getchar(); // �ȴ��û�����س�
		}
		else if (choice == 2) // �ۻ�Ա
		{
			while (!salesperson_login())
				;
			SalesPerson(input_salesperson_name); // �����ۻ�Ա����
			printf("���س�����...");
			while (getchar() != '\n')
				;
			getchar(); // �ȴ��û�����س�
		}
		else // �������
		{
			printf("����������������룡\n");
			printf("���س�����...");
			while (getchar() != '\n')
				;
			getchar(); // �ȴ��û�����س�
		}
	}
}