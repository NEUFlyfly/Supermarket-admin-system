#include "salesperson.h"
#include "sale.h"
#include "goods.h"
#include "purchase.h"
#include "customer.h"
#include "system.h"
#include "admin.h"
#include "search.h"
#include "sort.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern AllGoodList all_good_list;
extern SaleList sale_record;
extern PurchaseList purchase_record;
extern CustomerList customer_list;

// 销售商品
void Sale_To_Customer(int customer_id, char *good_name, int quantity)
{
    // 决策good_name应该是对应all_good_list中的哪个节点
    // 节点挑选的原则是选取所有good_name相同，quntity足够且price最高的节点
    AllGoodList p = all_good_list->next;
    AllGoodList best_good = NULL;
    int found_good = 0; // 标记是否找到商品
    while (p != NULL)   // 遍历all_good_list，找到所有good_name相同，quntity足够且售价最高的节点
    {
        if (strcmp(p->good_name, good_name) == 0)
        {
            found_good = 1; // 找到商品
            if (p->stock >= quantity)
            {
                // 根据is_promotion标志确定售价
                float current_price = p->is_promotion ? p->promotion_price : p->price;
                float best_price = best_good != NULL ? (best_good->is_promotion ? best_good->promotion_price : best_good->price) : 0;

                if (best_good == NULL || current_price > best_price)
                {
                    best_good = p;
                }
            }
        }
        p = p->next;
    }
    if (!found_good)
    {
        printf("没有找到该商品！\n");
        return; // 没有找到该商品，直接返回
    }
    if (!best_good)
    {
        printf("商品库存不足！\n");
        return; // 商品库存不足，直接返回
    }
    Sale(customer_id, best_good->id, quantity); // 调用Sale函数，将best_good的id和quantity传入
}

// 修改销售记录，操作sale_record链表，好比做假账*
void Salesperson_Modify_Sale()
{
    while (1)
    {
        system("cls"); // 清屏

        printf("销售记录管理：\n");
        printf("请输入选择：\n");
        printf("0：退出\n");
        printf("1：修改销售记录\n");
        printf("2：删除销售记录\n");
        printf("3：添加销售记录\n");

        int choice;
        // 输入选择及检测
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            while (getchar() != '\n')
                ; // 清除输入缓冲区
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;          // 等待用户按下回车键
            system("cls"); // 清屏
            printf("销售记录管理：\n");
            printf("请输入选择：\n");
            printf("0：退出\n");
            printf("1：修改销售记录\n");
            printf("2：删除销售记录\n");
            printf("3：添加销售记录\n");
        }
        if (choice == 0) // 退出
            break;       // 直接返回，不执行后面的代码
        switch (choice)
        {
        case 1: // 修改销售记录
            while (1)
            {
                system("cls");                 // 清屏
                Print_SaleRecord(sale_record); // 打印销售记录
                printf("已有的销售记录如上，请输入销售记录id（最左侧），输入#退出：\n");
                int sale_id;                 // 销售记录id
                char input[20];              // 输入的字符串
                scanf("%s", input);          // 输入销售记录id或#
                if (strcmp(input, "#") == 0) // 如果输入#，则退出
                    break;                   // 退出循环
                sale_id = atoi(input);       // 将输入的字符串转换为整数

                SaleList p = sale_record->next;            // 指向销售记录链表的第一个节点
                while (p != NULL && p->sale_id != sale_id) // 遍历销售记录链表，找到销售记录id对应的节点
                    p = p->next;
                if (p == NULL) // 没有找到销售记录id对应的节点
                {
                    printf("没有找到该销售记录！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    getchar(); // 清空输入缓冲区
                    continue;  // 继续循环
                }
                else // 找到了销售记录id对应的节点
                {
                    printf("请输入新的销售记录信息\n");
                    char new_good_name[20]; // 新的商品名称
                    float new_sale_price;   // 新的实际销售单价
                    char new_sale_time[20]; // 新的销售时间
                    int new_quantity;       // 新的销售数量
                    int new_customer_name;  // 新的顾客姓名
                    printf("请输入新的商品名称：");
                    scanf("%s", new_good_name); // 输入新的商品名称
                    printf("请输入新的实际销售单价：");
                    scanf("%f", &new_sale_price); // 输入新的实际销售单价
                    printf("请输入新的销售时间：");
                    scanf("%s", new_sale_time); // 输入新的销售时间
                    printf("请输入新的销售数量：");
                    scanf("%d", &new_quantity); // 输入新的销售数量
                    printf("请输入新的顾客姓名：");
                    scanf("%d", &new_customer_name); // 输入新的顾客姓名
                    // 修改销售记录信息

                    strcpy(p->good_name, new_good_name); // 修改商品名称
                    p->sale_price = new_sale_price;      // 修改实际销售单价
                    strcpy(p->sale_time, new_sale_time); // 修改销售时间
                    p->quantity = new_quantity;          // 修改销售数量
                    p->customer_id = new_customer_name;  // 修改顾客姓名

                    system("cls");                 // 清屏
                    Print_SaleRecord(sale_record); // 打印销售记录
                    printf("修改成功！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车键
                    getchar(); // 清空输入缓冲区
                }
            }
            break;
        case 2: // 删除销售记录
            while (1)
            {
                system("cls");                 // 清屏
                Print_SaleRecord(sale_record); // 打印销售记录
                printf("已有的销售记录如上，请输入销售记录id（最左侧），输入#退出：\n");
                int sale_id;                 // 销售记录id
                char input[20];              // 输入的字符串
                scanf("%s", input);          // 输入销售记录id或#
                if (strcmp(input, "#") == 0) // 如果输入#，则退出
                    break;                   // 退出循环
                sale_id = atoi(input);       // 将输入的字符串转换为整数

                SaleList p = sale_record->next;            // 指向销售记录链表的第一个节点
                while (p != NULL && p->sale_id != sale_id) // 遍历销售记录链表，找到销售记录id对应的节点
                    p = p->next;
                if (p == NULL) // 没有找到销售记录id对应的节点
                {
                    printf("没有找到该销售记录！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    getchar(); // 清空输入缓冲区
                    continue;  // 继续循环
                }
                else // 找到了销售记录id对应的节点，删除该节点
                {
                    SaleList q = sale_record; // 指向销售记录链表的头节点
                    while (q->next != p)      // 遍历销售记录链表，找到销售记录id对应的节点的前一个节点
                        q = q->next;
                    q->next = p->next; // 删除销售记录id对应的节点
                    free(p);           // 释放内存

                    system("cls");                 // 清屏
                    Print_SaleRecord(sale_record); // 打印销售记录
                    printf("删除成功！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车键
                    getchar(); // 清空输入缓冲区
                }
            }
            break;

        case 3: // 添加销售记录
            while (1)
            {
                system("cls");                 // 清屏
                Print_SaleRecord(sale_record); // 打印销售记录
                printf("已有的销售记录如上，请输入新销售记录的信息，输入#退出，输入其他字符继续：\n");

                char input[20];              // 输入的字符串
                scanf("%s", input);          // 输入 # 或开始输入信息
                if (strcmp(input, "#") == 0) // 如果输入#，则退出
                    break;                   // 退出循环

                int sale_id = sale_record->next->sale_id + 1; // 新销售记录的 id

                char new_good_name[20]; // 新的商品名称
                float new_sale_price;   // 新的实际销售单价
                char new_sale_time[20]; // 新的销售时间
                int new_quantity;       // 新的销售数量
                int new_customer_id;    // 新的顾客 id
                int new_good_id;        // 新的商品 id
                // 因为前面已经输入了一个字符串，这里需要跳过这个输入
                printf("请输入新的商品名称：");
                scanf("%s", new_good_name);
                printf("请输入新的商品id：");
                scanf("%d", &new_good_id);
                printf("请输入新的实际销售单价：");
                scanf("%f", &new_sale_price); // 输入新的实际销售单价
                printf("请输入新的销售时间：");
                scanf("%s", new_sale_time); // 输入新的销售时间
                printf("请输入新的销售数量：");
                scanf("%d", &new_quantity); // 输入新的销售数量
                printf("请输入新的顾客 id：");
                scanf("%d", &new_customer_id); // 输入新的顾客 id

                // 创建新的销售记录节点
                SaleNode new_sale;
                new_sale.sale_id = sale_id;
                strcpy(new_sale.good_name, new_good_name);
                new_sale.sale_price = new_sale_price;
                strcpy(new_sale.sale_time, new_sale_time);
                new_sale.quantity = new_quantity;
                new_sale.customer_id = new_customer_id;
                new_sale.good_id = new_good_id;

                // 调用 Insert_Salelist 函数添加新节点到链表
                Insert_SaleList(&sale_record, new_sale);

                system("cls");                 // 清屏
                Print_SaleRecord(sale_record); // 打印销售记录
                printf("添加成功！（在记录的最上方，拉到最顶查看）\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;      // 等待用户按下回车键
                getchar(); // 清空输入缓冲区
            }
            break;
        }
    }
}

// 显示顾客在某一段时间内的购买情况
void Caculate_Customer_Shopping_Amount()
{
    while (1)
    {
        system("cls"); // 清屏

        printf("请输入选择：\n0：退出\n1：查看某一顾客在某一段时间内的购买情况\n");
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 1)
        {
            while (getchar() != '\n')
                ; // 清除输入缓冲区
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;          // 等待用户按下回车键
            system("cls"); // 清屏
            printf("请输入选择：\n0：退出\n1：查看某一顾客在某一段时间内的购买情况\n");
        }
        if (choice == 0)      // 退出
            break;            // 直接返回，不执行后面的代码
        else if (choice == 1) // 查看某一顾客在某一段时间内的购买情况
        {
            Print_CustomerList(customer_list); // 打印顾客信息
            printf("已有的顾客信息如上，您要查看谁的？请输入顾客id：\n");
            int customer_id;
            scanf("%d", &customer_id);                    // 输入顾客id
            CustomerList ptr = customer_list->next;       // 指向顾客信息链表的第一个节点
            while (ptr != NULL && ptr->id != customer_id) // 遍历顾客信息链表，找到顾客id对应的节点
                ptr = ptr->next;
            if (ptr == NULL) // 没有找到顾客id对应的节点
            {
                printf("没有找到该顾客！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            else // 找到了顾客id对应的节点
            {

                int min_time, max_time;
                printf("请输入销售时间区间（用空格分隔两个0到10000内的整数，不规定顺序）：");
                if (scanf("%d %d", &min_time, &max_time) != 2 || min_time < 0 || min_time > 10000 || max_time < 0 || max_time > 10000)
                {
                    printf("输入无效，请输入两个0到10000内的有效整数。\n");
                    while (getchar() != '\n')
                        ;
                    getchar(); // 清空输入缓冲区
                    break;
                }
                // 确保 min_time 是较小值，max_time 是较大值
                if (min_time > max_time)
                {
                    int temp = min_time;
                    min_time = max_time;
                    max_time = temp;
                }

                SaleList p = sale_record->next;
                int found = 0;
                // 第一遍循环，先确定有没有销售时间在该区间的销售记录
                while (p != NULL)
                {
                    int current_time = atoi(p->sale_time);
                    if (current_time >= min_time && current_time <= max_time)
                    {
                        found = 1;
                        break;
                    }
                    p = p->next;
                }
                if (!found)
                {
                    printf("该顾客没有销售时间在该区间的销售记录！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                }
                else
                {
                    printf("该顾客在该时间区间内的销售记录如下：\n\n");
                    p = sale_record->next;
                    // 输出表头格式 id 商品名称 销售单价 销售数量 销售时间 顾客姓名
                    printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "销售记录id", "商品id", "商品名称", "销售时间", "销售单价", "顾客id");
                    while (p != NULL)
                    {
                        int current_time = atoi(p->sale_time);
                        if (current_time >= min_time && current_time <= max_time && p->customer_id == ptr->id)
                        {
                            // 输出销售记录信息，使用格式化输出保证对齐
                            printf("%-16d %-8d %-20s %-10s %-10.2f %-10d\n",
                                   p->sale_id, p->good_id, p->good_name, p->sale_time, p->sale_price, p->customer_id);
                        }
                        p = p->next;
                    }
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                }
            }
        }
    }
}
void SalesPerson(char *username)
{
    while (1)
    {
        int length = 0;
        CustomerList ptr = customer_list->next; // 指向customer_list的第一个节点
        AllGoodList qtr = all_good_list->next;  // 指向all_good_list的第一个节点

        system("cls");
        // 打印当前时间
        char current_time[20];
        GetCurrentTime(current_time);
        printf("当前时间：%ss\n", current_time);

        printf("【售货员】你好！\n");
        printf("请输入选择：\n");
        printf("0：退出\n");
        printf("1：增加顾客信息\n");
        printf("2：顾客信息统计\n");
        printf("3：商品信息统计\n");
        printf("4：销售\n");
        printf("5：查询\n");
        printf("6：排序\n");
        printf("7：销售记录管理\n");
        printf("8：修改自己的密码\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:     // 退出
            return; // 直接返回，不执行后面的代码
            break;
        case 1:
            system("cls");
            int choice4;
            printf("请输入选择：（0：退出，1：手动输入顾客信息，2：从文件导入顾客信息（两种方法可同时使用））\n");
            scanf("%d", &choice4);
            if (choice4 == 1) // 手动输入顾客信息
                Add_Customer_To_System();
            else if (choice4 == 0)
                break;
            else if (choice4 == 2) // 从文件导入顾客信息
            {
                FILE *fp = fopen("txt/CustomerSource.txt", "r");
                if (fp == NULL)
                {
                    printf("文件打开失败！\n");
                    break; // 打开文件失败，退出循环
                }
                char name[20], contact[20], type[50];
                int customer_id;
                int temp = 1;
                while (fscanf(fp, "%19s %19s %49s", name, type, contact) != EOF)
                {
                    CustomerNode customer;
                    customer.id = temp++;
                    strcpy(customer.name, name);
                    strcpy(customer.contact, contact);
                    strcpy(customer.type, type);
                    Insert_CustomerList(&customer_list, customer);
                }
                // 关闭文件
                fclose(fp);
                // 生成顾客信息文件
                Create_CustomerInfo_File();
                printf("顾客信息导入成功\n");
                printf("按回车键继续...\n");
                while (getchar() != '\n')
                    ;      // 清除输入缓冲区
                getchar(); // 等待用户按下回车键
            }
            break;
        case 2: // 顾客信息统计
            Caculate_Customer_Shopping_Amount();
            break;
        case 3: // 商品信息统计
            while (1)
            {
                system("cls");
                printf("请输入选择：（0：退出，1：查看某一类别商品总数，2：查看所有商品库存）\n");
                int choice3;

                while (scanf("%d", &choice3) != 1 || choice3 < 0 || choice3 > 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请输入选择：（0：退出，1：查看某一类别商品总数，2：查看所有商品库存）\n");
                }
                if (choice3 == 0)
                    break; // 退出循环
                switch (choice3)
                {
                case 0: // 退出
                    break;
                case 1: // 查看某一类别商品总数
                    Caculate_Category_Stock();
                    break;
                case 2: // 查看所有商品库存
                    Print_AllGoodList(all_good_list);
                    break;
                }
            }
            break;
        case 4: // 销售
            while (1)
            {
                system("cls");
                char good_name[50];
                int quantity;
                int customer_id;
                Print_CustomerList(customer_list);
                printf("顾客信息如上，供参考\n");

                printf("请输入选择：\n");
                printf("0：退出\n");
                printf("1：手动销售商品\n");
                printf("2：模拟销售（直接生成模拟的销售记录）\n");
                int choice5;
                // 输入选择及检测
                while (scanf("%d", &choice5) != 1 || choice5 < 0 || choice5 > 2)
                {
                    while (getchar() != '\n')
                        ; // 清除输入缓冲区
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;          // 等待用户按下回车键
                    system("cls"); // 清屏
                    Print_CustomerList(customer_list);
                    printf("顾客信息如上，供参考\n");
                    printf("请输入选择：\n");
                    printf("0：退出\n");
                    printf("1：手动销售商品\n");
                    printf("2：批量销售（直接生成模拟的销售记录）\n");
                }

                if (choice5 == 0) // 退出
                    break;        // 直接返回，不执行后面的代码
                switch (choice5)
                {
                case 1: // 手动销售商品
                    while (1)
                    {
                        printf("请输入顾客id（输入'#'退出）：");
                        char id_str[10];
                        scanf("%s", id_str);
                        if (strcmp(id_str, "#") == 0)
                            break;                  // 输入'#'结束循环
                        customer_id = atoi(id_str); // 将输入转换为整数
                        if (customer_id <= 0)
                        {
                            printf("无效的顾客id，请重新输入！\n");
                            continue; // 无效的顾客id，继续循环
                        }
                        printf("请输入商品名称：");
                        scanf("%49s", good_name);
                        printf("请输入销售数量：");
                        scanf("%d", &quantity);
                        // 调用销售函数，将顾客id、商品名称和销售数量传递给系统
                        Sale_To_Customer(customer_id, good_name, quantity);
                        printf("按回车键继续...");
                        while (getchar() != '\n')
                            ;
                        // 等待用户按下回车
                        getchar(); // 处理多余的换行符
                    }

                    break;
                case 2: // 批量销售
                    // 第一步，统计customer_list和all_good_list的长度，找到更短的那个，记为length

                    ptr = customer_list->next;         // 指向customer_list的第一个节点
                    qtr = all_good_list->next;         // 指向all_good_list的第一个节点
                    while (ptr != NULL || qtr != NULL) // 遍历两个链表，找到长度更短的那个
                    {
                        if (ptr != NULL)
                            ptr = ptr->next; // 遍历customer_list
                        if (qtr != NULL)
                            qtr = qtr->next; // 遍历all_good_list
                        length++;            // 长度加1
                    }
                    // 第二步，从customer_list和all_good_list中选择前length个顾客和商品，直接调用Sale_To_Customer函数
                    ptr = customer_list->next;       // 指向customer_list的第一个节点
                    qtr = all_good_list->next;       // 指向all_good_list的第一个节点
                    for (int i = 0; i < length; i++) // 遍历前length个顾客和商品
                    {
                        if (ptr != NULL) // 如果customer_list还有节点
                        {
                            customer_id = ptr->id; // 获取顾客id
                            ptr = ptr->next;       // 遍历customer_list
                        }
                        if (qtr != NULL) // 如果all_good_list还有节点
                        {
                            strcpy(good_name, qtr->good_name); // 获取商品名称
                            qtr = qtr->next;                   // 遍历all_good_list
                        }
                        quantity = rand() % 10 + 1; // 随机生成销售数量，范围为1到10
                        // 调用销售函数，将顾客id、商品名称和销售数量传递给系统
                        Sale_To_Customer(customer_id, good_name, quantity);
                    }
                    printf("销售成功，按回车继续...\n");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                    break;
                }
            }
            break;
        case 5: // 查询
            Salesperson_Search();
            break;
        case 6: // 排序
            Salesperson_Sort();
            break;
        case 7: // 销售记录管理
            while (1)
            {
                system("cls");
                int choice2;
                printf("请输入选择：\n0：退出\n1：查看销售记录\n2：销售记录管理\n");
                scanf("%d", &choice2);

                if (choice2 == 0)
                    break; // 退出

                else if (choice2 == 1) // 打印saleInfo.txt的内容
                {
                    system("cls");
                    Print_SaleRecord(sale_record);
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                else if (choice2 == 2) // 修改进货记录
                {
                    // 仅仅从文件中修改而不影响真实的库存状态，好比做假账
                    Salesperson_Modify_Sale();
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                else
                    printf("无效的选择，请重新输入！\n");
            }
            break;
        case 8:            // 修改自己的密码
            system("cls"); // 清屏
            printf("请输入新密码：");
            char new_password[100];                            // 存储新密码
            scanf("%s", new_password);                         // 输入新密码
            FILE *fp = fopen("txt/salespersonLogin.txt", "r"); // 打开文件，只读模式
            if (fp == NULL)
            {
                printf("文件打开失败！\n"); // 打开文件失败，提示
                break;
            }
            // 读取所有内容到内存
            char lines[100][200];
            int line_count = 0;
            while (fgets(lines[line_count], sizeof(lines[line_count]), fp) != NULL)
            {
                line_count++;
            }
            fclose(fp);

            // 查找并替换密码
            for (int i = 0; i < line_count; i++)
            {
                char username1[100], password[100];
                if (sscanf(lines[i], "%s %s", username1, password) == 2)
                {
                    if (strcmp(username, username1) == 0)
                    {
                        // 替换密码
                        snprintf(lines[i], sizeof(lines[i]), "%s %s\n", username1, new_password);
                        break;
                    }
                }
            }

            // 写回文件
            fp = fopen("txt/salespersonLogin.txt", "w"); // 打开文件，写入模式
            if (fp == NULL)
            {
                printf("文件打开失败！\n"); // 打开文件失败，提示
                break;
            }
            for (int i = 0; i < line_count; i++)
            {
                fputs(lines[i], fp);
            }
            fclose(fp);
            printf("密码修改成功！\n"); // 密码修改成功，提示
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;      // 等待用户按下回车
            getchar(); // 处理多余的换行符
            break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
            break;
        }
    }
}

char input_salesperson_name[100];
int salesperson_login()
{
    system("cls");

    char input_password[100];

    // 读取文件中的内容，存储在两个二维数组中
    char usernames[100][100]; // 存储用户名
    char passwords[100][100]; // 存储密码
    int count = 0;            // 记录读取的行数

    FILE *fp = fopen("txt/salespersonLogin.txt", "r"); // 打开文件，只读模式
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return 0; // 打开文件失败，返回0
    }
    // 逐行读取文件内容，存储到数组中
    while (fscanf(fp, "%s %s", usernames[count], passwords[count]) != EOF)
        count++; // 行数加1
    fclose(fp);  // 关闭文件

    // 提示用户输入用户名和密码
    printf("请输入销售人员用户名：");
    scanf("%s", input_salesperson_name); // 输入用户名
    printf("请输入销售人员密码：");
    scanf("%s", input_password); // 输入密码

    // 检查输入的用户名和密码是否与两个二维数组匹配
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_salesperson_name, usernames[i]) == 0 && strcmp(input_password, passwords[i]) == 0)
        {
            printf("销售人员登录成功！\n"); // 登录成功
            printf("按回车键继续...\n");
            while (getchar() != '\n')
                ;      // 清除输入缓冲区
            getchar(); // 等待用户按下回车键
            return 1;  // 返回1
        }
    }
    printf("销售人员登录失败！用户名或密码错误。\n"); // 登录失败
    printf("按回车键继续...\n");
    while (getchar() != '\n')
        ;      // 清除输入缓冲区
    getchar(); // 等待用户按下回车键
    return 0;  // 返回0
}
