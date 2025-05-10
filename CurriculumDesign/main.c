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
	// 打印一些货物信息，格式是：商品类别 商品名称 商品进价 商品数量 供应商

	TimerStart(); // 启动计时器
	Init_PurchaseList(&purchase_record);
	Init_CustomerList(&customer_list);
	Init_SaleList(&sale_record);
	Init_AllGoodList(&all_good_list);
	while (1)
	{
		// 打印一个有边框的界面
		system("cls");
		printf("+------------------------------------------------+\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                小型超市管理系统                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("|                                                |\n");
		printf("+------------------------------------------------+\n");
		printf("您的身份是（0：复位系统，1：管理员，2：售货员）：\n");
		scanf("%d", &choice);
		if(choice == 0)
		{
			ResetSystem(); // 复位系统
			printf("系统已复位！\n");
			printf("按回车继续...");
			while (getchar()!= '\n')
				;
			continue;
		}
		if (choice == 1) // 管理员
		{
			// 登录
			while (!admin_login())
				;
			Admin(); // 调用管理员函数
			printf("按回车继续...");
			while (getchar() != '\n')
				;
			getchar(); // 等待用户输入回车
		}
		else if (choice == 2) // 售货员
		{
			while (!salesperson_login())
				;
			SalesPerson(input_salesperson_name); // 调用售货员函数
			printf("按回车继续...");
			while (getchar() != '\n')
				;
			getchar(); // 等待用户输入回车
		}
		else // 输入错误
		{
			printf("输入错误，请重新输入！\n");
			printf("按回车继续...");
			while (getchar() != '\n')
				;
			getchar(); // 等待用户输入回车
		}
	}
}