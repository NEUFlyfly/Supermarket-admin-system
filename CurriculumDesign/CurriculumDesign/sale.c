#include "salesperson.h"
#include "sale.h"
#include "goods.h"
#include "purchase.h"
#include "customer.h"
#include "system.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern AllGoodList all_good_list;
extern SaleList sale_record;
extern PurchaseList purchase_record;
extern CustomerList customer_list;

#define NORMAL_DISCOUNT 1.0
#define VIP_DISCOUNT 0.9
#define SVIP_DISCOUNT 0.8

static int sale_id = 1;


void ResetSaleId()
{
    sale_id = 1; // 重置sale_id为1 
}
// 创建空的Sale链表
void Init_SaleList(SaleList *list)
{
    *list = (SaleList)malloc(sizeof(SaleNode));
    if (*list == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    (*list)->next = NULL;
}

// 插入新的销售记录到Sale链表，头插法
void Insert_SaleList(SaleList *list, SaleNode sale)
{
    SaleNode *newnode = (SaleNode *)malloc(sizeof(SaleNode));
    newnode->quantity = sale.quantity;
    newnode->sale_price = sale.sale_price;
    newnode->sale_id = sale.sale_id; 
    newnode->customer_id = sale.customer_id;
    newnode->good_id = sale.good_id;

    strcpy(newnode->sale_time, sale.sale_time);
    strcpy(newnode->good_name, sale.good_name);

    if (newnode == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    newnode->next = (*list)->next;
    (*list)->next = newnode;
}

// 向id为customer_id的顾客一次销售商品good_name，数量为quantity
// 需要进行更抽象的封装，由Sale_To_Customer函数根据good_name推测出good_id，然后调用Sale函数
void Sale(int customer_id, int good_id, int quantity)
{
    static int opened = 0; // 用于判断是否第一次调用Sale函数，如果是第一次调用，则清空saleInfo.txt文件
    if (opened == 0)
    {
        FILE *fp = fopen("txt/saleInfo.txt", "w");
        if (fp == NULL)
        {
            printf("文件打开失败！\n");
            exit(1);
        }
        fclose(fp);
        opened = 1; // 设置为1，表示已经清空过文件
    }

    char current_time[10];
    GetCurrentTime(current_time); // 获取当前时间

    // 0. 函数合法性检查，检查顾客id是否存在，商品id是否存在，商品库存是否足够
    int customer_exist = 0, good_exist = 0, stock_enough = 0;
    CustomerNode *customer_ptr = customer_list->next;
    while (customer_ptr != NULL) // 若顾客id存在，则customer_ptr指向该顾客，否则指向NULL
    {
        if (customer_ptr->id == customer_id)
        {
            customer_exist = 1; // 顾客id存在
            break;
        }
        customer_ptr = customer_ptr->next;
    }
    if (customer_ptr == NULL)
    {
        printf("顾客id不存在！\n");
        return;
    }
    AllGoodList good_ptr = all_good_list->next;
    while (good_ptr != NULL) // 若商品id存在，则good_ptr指向该商品，否则指向NULL
    {
        if (good_ptr->id == good_id)
        {
            good_exist = 1; // 商品id存在
            break;
        }
        good_ptr = good_ptr->next;
    }
    if (good_ptr == NULL)
    {
        printf("商品id不存在！\n");
        return;
    }

    if (good_ptr->stock < quantity) // 检查库存是否足够
    {
        printf("库存不足！\n");
        return;
    }
    else
    {
        stock_enough = 1; // 库存足够
    }
    if (customer_exist == 0 || good_exist == 0 || stock_enough == 0) // 若顾客id不存在、商品id不存在、库存不足，则返回
    {
        return;
    }
    // 1. 创建新的销售记录
    SaleNode sale;
    strcpy(sale.good_name, good_ptr->good_name);
    strcpy(sale.sale_time, current_time); // 使用当前时间
    // 检查该商品是否促销，如果是促销，则销售价格为促销价格，否则为原价
    // 并且检查顾客类型,vip打折0.9，svip打折0.8，普通不打折
    if (good_ptr->is_promotion == 1)
    {
        if (strcmp(customer_ptr->type, "vip") == 0)
            sale.sale_price = good_ptr->promotion_price * VIP_DISCOUNT;
        else if (strcmp(customer_ptr->type, "svip") == 0)
            sale.sale_price = good_ptr->promotion_price * SVIP_DISCOUNT;
        else
            sale.sale_price = good_ptr->promotion_price;
    }
    else
    {
        if (strcmp(customer_ptr->type, "vip") == 0)
            sale.sale_price = good_ptr->price * VIP_DISCOUNT;
        else if (strcmp(customer_ptr->type, "svip") == 0)
            sale.sale_price = good_ptr->price * SVIP_DISCOUNT;
        else
            sale.sale_price = good_ptr->price;
    }
    sale.quantity = quantity;
    sale.sale_id = sale_id;
    sale.customer_id = customer_id;
    sale.good_id = good_id;
    Insert_SaleList(&sale_record, sale);
    // 2. 更新商品库存

    good_ptr->stock -= quantity;
    printf("销售成功！\n");

    // 3. 保存销售记录到saleInfo.txt，格式：顾客id 顾客姓名 商品名称 销售单价 销售数量 销售时间
    FILE *fp = fopen("txt/saleInfo.txt", "a");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return;
    }
    // 写入文件
    // 格式：商品编号、商品名称、销售时间、销售价格、销售数量、顾客姓名
    fprintf(fp, "%d %s %s %.2f %d %s\n", sale_id,
            sale.good_name, sale.sale_time, sale.sale_price, sale.quantity, customer_ptr->name);
    fclose(fp);
    sale_id++;
}

void Print_SaleRecord(SaleList list)
{
    SaleNode *p = list->next; // 指向第一个节点
    if (p == NULL)
        printf("销售记录为空！\n");
    else
        printf("%-8s %-8s %-20s %-15s %-16s %-16s %-20s\n","记录编号",
               "商品id", "商品名称", "销售时间", "销售价格", "销售数量", "顾客id"); 
    while (p!= NULL) // 遍历链表，打印每个节点的信息
    {
        printf("%-8d %-8d %-20s %-15s %-16.2f %-16d %-20d\n",p->sale_id,
            p->good_id, p->good_name, p->sale_time, p->sale_price, p->quantity, p->customer_id);
     p = p->next; // 指向下一个节点 
    }
}


// 打印saleInfo.txt文件
// 格式：记录编号、商品名称、销售时间、销售价格、销售数量、顾客姓名
// 1 Apple 0056 135.00 11 Mike
void Print_SaleList()
{
    FILE *fp = fopen("txt/saleInfo.txt", "r");
    if (fp == NULL)
    {
        perror("文件打开失败");
        while (1)
        {
            /* code */
        }

        return;
    }
    // 打印表头，指定每个字段的宽度
    printf("%-10s %-20s %-15s %-10s %-10s %-20s\n",
           "记录编号", "商品名称", "销售时间", "销售价格", "销售数量", "顾客姓名");
    char line[100]; // 用于存储每一行的内容
    int sale_id;
    char good_name[50];
    char sale_time[20];
    float sale_price;
    int quantity;
    char customer_name[50];
    int has_records = 0; // 用于标记文件中是否有记录

    while (fgets(line, sizeof(line), fp) != NULL) // 逐行读取文件内容
    {
        sscanf(line, "%d %49s %19s %f %d %49s", &sale_id, good_name,
               sale_time, &sale_price, &quantity, customer_name);
        // 格式化输出，指定每个字段的宽度
        printf("%-10d %-20s %-15s %-10.2f %-10d %-20s\n",
               sale_id, good_name, sale_time, sale_price, quantity, customer_name);
        has_records = 1; // 标记文件中有记录
    }

    if (!has_records)
    {
        printf("销售记录文件为空。\n");
    }

    fclose(fp);
}