#include "purchase.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
// 创建空的Purchase链表
void Init_PurchaseList(PurchaseList *list)
{
    *list = (PurchaseList)malloc(sizeof(PurchaseNode));
    if (*list == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    (*list)->next = NULL;
}

// 插入新的进货记录到Purchase链表，头插法
// 插入新的进货记录到Purchase链表，头插法
int Insert_PurchaseList(PurchaseList *list, PurchaseNode purchase)
{
    // 检查传入的链表指针是否为 NULL
    if (list == NULL)
    {
        return -1; // 传入的链表指针无效
    }

    // 为新节点分配内存
    PurchaseNode *newnode = malloc(sizeof(PurchaseNode));
    if (newnode == NULL)
    {
        return -2; // 内存分配失败
    }

    // 复制节点信息
    newnode->quantity = purchase.quantity;
    newnode->cost_price = purchase.cost_price;
    newnode->id = purchase.id;
    strcpy(newnode->category, purchase.category);
    strcpy(newnode->good_name, purchase.good_name);
    strcpy(newnode->purchase_time, purchase.purchase_time);
    strcpy(newnode->supplier, purchase.supplier);

    // 头插法插入节点
    newnode->next = (*list)->next;
    (*list)->next = newnode;

    return 0; // 插入成功
}

// 打印purchaseInfo.txt文件中的所有进货记录
// 格式为：
// 记录编号 类别 商品名称 进价 进货数量 进货时间(s) 供应商
// 1 Fruit Apple 150.00 110 0021 SupplierA
// 2 Fruit Apple 100.00 80 0021 SupplierA
// 3 Electronics Laptop 820.00 25 0021 TechWorld

void Print_PurchaseRecord(PurchaseList list)
{
    PurchaseList p = list->next; // 指向第一个节点
    if (p == NULL)
        printf("进货记录为空！\n");
    else
        printf("%-10s %-15s %-20s %-10s %-10s %-15s %-20s\n",
               "记录编号", "类别", "商品名称", "进价", "进货数量", "进货时间(s)", "供应商");
    while (p != NULL) // 遍历链表，打印每个节点的信息
    {
        printf("%-10d %-15s %-20s %-10.2f %-10d %-15s %-20s\n",
               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
        p = p->next; // 指向下一个节点
    }
}

void Print_PurchaseList()
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return; // 打开文件失败，直接返回
    }

    char line[200]; // 用于存储每一行的内容
    int id;
    char purchase_time[20];
    char category[50];
    char good_name[50];
    int quantity;
    float cost_price;
    char supplier[50];
    int has_records = 0; // 用于标记文件中是否有记录

    // 打印表头，按照格式要求调整
    printf("%-10s %-15s %-20s %-10s %-10s %-15s %-20s\n",
           "记录编号", "类别", "商品名称", "进价", "进货数量", "进货时间(s)", "供应商");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // 解析每一行内容，按照格式要求调整
        sscanf(line, "%d %49s %49s %f %d %19s %49s", &id, category, good_name, &cost_price, &quantity, purchase_time, supplier);
        // 按照指定格式输出，按照格式要求调整
        printf("%-10d %-15s %-20s %-10.2f %-10d %-15s %-20s\n",
               id, category, good_name, cost_price, quantity, purchase_time, supplier);
        has_records = 1; // 标记文件中有记录
    }

    if (!has_records)
    {
        printf("进货记录文件为空。\n");
    }

    fclose(fp); // 关闭文件
}
