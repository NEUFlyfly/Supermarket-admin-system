#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"
#include "goods.h"
#include "sale.h"
#include "system.h"
#include "sort.h"
#include "purchase.h"

extern AllGoodList all_good_list;    // 商品链表
extern PurchaseList purchase_record; // 进货记录链表
extern SaleList sale_record;         // 销售记录链表
extern CustomerList customer_list;   // 顾客链表

// 按商品编号排序
void sort_good_by_name()
{
    // 第一步：统计链表节点数量
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的商品信息存入数组
    p = all_good_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // 第四步：依据 good_name 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].good_name, arr[j + 1].good_name) > 0)
            {
                struct Good temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的商品信息重新赋值给链表节点
    p = all_good_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);
        strcpy(p->manufacturer, arr[i].manufacturer);
        strcpy(p->description, arr[i].description);
        p->price = arr[i].price;
        p->stock = arr[i].stock;
        p->is_promotion = arr[i].is_promotion;
        p->promotion_price = arr[i].promotion_price;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按商品类别排序
void sort_good_by_category()
{
    // 第一步：统计链表节点数量
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的商品信息存入数组
    p = all_good_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].good_name, p->good_name);
        strcpy(arr[i].category, p->category);
        strcpy(arr[i].manufacturer, p->manufacturer);
        strcpy(arr[i].description, p->description);
        arr[i].price = p->price;
        arr[i].stock = p->stock;
        arr[i].is_promotion = p->is_promotion;
        arr[i].promotion_price = p->promotion_price;
        i++;
        p = p->next;
    }

    // 第四步：依据 category 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].category, arr[j + 1].category) > 0)
            {
                struct Good temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的商品信息重新赋值给链表节点
    p = all_good_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);
        strcpy(p->manufacturer, arr[i].manufacturer);
        strcpy(p->description, arr[i].description);
        p->price = arr[i].price;
        p->stock = arr[i].stock;
        p->is_promotion = arr[i].is_promotion;
        p->promotion_price = arr[i].promotion_price;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按商品库存排序
void sort_good_by_stock()
{
    // 第一步：统计链表节点数量
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的商品信息存入数组
    p = all_good_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].good_name, p->good_name);
        strcpy(arr[i].category, p->category);
        strcpy(arr[i].manufacturer, p->manufacturer);
        strcpy(arr[i].description, p->description);
        arr[i].price = p->price;
        arr[i].stock = p->stock;
        arr[i].is_promotion = p->is_promotion;
        arr[i].promotion_price = p->promotion_price;
        i++;
        p = p->next;
    }

    // 第四步：依据 stock 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].stock > arr[j + 1].stock)
            {
                struct Good temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的商品信息重新赋值给链表节点
    p = all_good_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);
        strcpy(p->manufacturer, arr[i].manufacturer);
        strcpy(p->description, arr[i].description);
        p->price = arr[i].price;
        p->stock = arr[i].stock;
        p->is_promotion = arr[i].is_promotion;
        p->promotion_price = arr[i].promotion_price;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}



// 按顾客姓名排序
void sort_customer_by_name()
{
    // 第一步：统计链表节点数量
    int count = 0;
    CustomerList p = customer_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct CustomerNode *arr = (struct CustomerNode *)malloc(count * sizeof(struct CustomerNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的顾客信息存入数组
    p = customer_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].name, p->name);
        strcpy(arr[i].type, p->type);
        // 这里可以继续添加其他成员赋值，若有其他成员的话
        i++;
        p = p->next;
    }

    // 第四步：依据 name 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0)
            {
                struct CustomerNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的顾客信息重新赋值给链表节点
    p = customer_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->name, arr[i].name);
        strcpy(p->type, arr[i].type);
        // 这里可以继续添加其他成员赋值，若有其他成员的话
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按顾客类型排序
void sort_customer_by_type()
{
    // 第一步：统计链表节点数量
    int count = 0;
    CustomerList p = customer_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct CustomerNode *arr = (struct CustomerNode *)malloc(count * sizeof(struct CustomerNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的顾客信息存入数组
    p = customer_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].name, p->name);
        strcpy(arr[i].type, p->type);
        // 这里可以继续添加其他成员赋值，若有其他成员的话
        i++;
        p = p->next;
    }

    // 第四步：依据 type 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].type, arr[j + 1].type) > 0)
            {
                struct CustomerNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的顾客信息重新赋值给链表节点
    p = customer_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->name, arr[i].name);
        strcpy(p->type, arr[i].type);
        // 这里可以继续添加其他成员赋值，若有其他成员的话
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}





// 按进货数量排序
void sort_purchase_record_by_quantity()
{
    // 第一步：统计链表节点数量
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的进货记录信息存入数组
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {

        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // 第四步：依据 quantity 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].quantity > arr[j + 1].quantity)
            {
                struct PurchaseNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的进货记录信息重新赋值给链表节点
    p = purchase_record->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        p->cost_price = arr[i].cost_price;
        p->quantity = arr[i].quantity;
        strcpy(p->supplier, arr[i].supplier);
        strcpy(p->purchase_time, arr[i].purchase_time);
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);

        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按进货价格排序
void sort_purchase_record_by_price()
{
    // 第一步：统计链表节点数量
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的进货记录信息存入数组
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // 第四步：依据 price 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].cost_price > arr[j + 1].cost_price)
            {
                struct PurchaseNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的进货记录信息重新赋值给链表节点
    p = purchase_record->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        p->cost_price = arr[i].cost_price;
        p->quantity = arr[i].quantity;
        strcpy(p->supplier, arr[i].supplier);
        strcpy(p->purchase_time, arr[i].purchase_time);
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);
        i++;
        p = p->next;
    }

    free(arr);
}





// 按进货时间排序
void sort_purchase_record_by_time()
{
    // 第一步：统计链表节点数量
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的进货记录信息存入数组
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // 第四步：依据 purchase_time 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].purchase_time, arr[j + 1].purchase_time) > 0)
            {
                struct PurchaseNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的进货记录信息重新赋值给链表节点
    p = purchase_record->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        p->cost_price = arr[i].cost_price;
        p->quantity = arr[i].quantity;
        strcpy(p->supplier, arr[i].supplier);
        strcpy(p->purchase_time, arr[i].purchase_time);
        strcpy(p->good_name, arr[i].good_name);
        strcpy(p->category, arr[i].category);
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}





// 按销售数量排序
void sort_sale_record_by_quantity()
{
    // 第一步：统计链表节点数量
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的销售记录信息存入数组
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // 第四步：依据 quantity 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].quantity > arr[j + 1].quantity)
            {
                struct SaleNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的销售记录信息重新赋值给链表节点
    p = sale_record->next;
    i = 0;
    while (p != NULL)
    {
        p->good_id = arr[i].good_id;
        strcpy(p->good_name, arr[i].good_name);
        p->sale_price = arr[i].sale_price;
        strcpy(p->sale_time, arr[i].sale_time);
        p->quantity = arr[i].quantity;
        p->sale_id = arr[i].sale_id;
        p->customer_id = arr[i].customer_id;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按销售价格排序
void sort_sale_record_by_price()
{
    // 第一步：统计链表节点数量
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的销售记录信息存入数组
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // 第四步：依据 sale_price 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].sale_price > arr[j + 1].sale_price)
            {
                struct SaleNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的销售记录信息重新赋值给链表节点
    p = sale_record->next;
    i = 0;
    while (p != NULL)
    {
        p->good_id = arr[i].good_id;
        strcpy(p->good_name, arr[i].good_name);
        p->sale_price = arr[i].sale_price;
        strcpy(p->sale_time, arr[i].sale_time);
        p->quantity = arr[i].quantity;
        p->sale_id = arr[i].sale_id;
        p->customer_id = arr[i].customer_id;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}

// 按销售时间排序
void sort_sale_record_by_time()
{
    // 第一步：统计链表节点数量
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 第二步：创建不定长数组
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 第三步：将链表节点中的销售记录信息存入数组
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // 第四步：依据 sale_time 成员进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(arr[j].sale_time, arr[j + 1].sale_time) > 0)
            {
                struct SaleNode temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 第五步：将数组元素中的销售记录信息重新赋值给链表节点
    p = sale_record->next;
    i = 0;
    while (p != NULL)
    {
        p->good_id = arr[i].good_id;
        strcpy(p->good_name, arr[i].good_name);
        p->sale_price = arr[i].sale_price;
        strcpy(p->sale_time, arr[i].sale_time);
        p->quantity = arr[i].quantity;
        p->sale_id = arr[i].sale_id;
        p->customer_id = arr[i].customer_id;
        i++;
        p = p->next;
    }

    // 第六步：释放数组内存
    free(arr);
}



void Admin_Sort()
{
    while (1)
    {
        system("cls");
        printf("请选择排序的对象（0：退出，1：商品，2：顾客，3：进货记录，4：销售记录）：\n");
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 4)
        {
            while (getchar() != '\n')
                ;
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            system("cls"); // 清屏
            printf("请选择排序的对象（0：退出，1：商品，2：顾客，3：进货记录，4：销售记录）：\n");
        }
        switch (choice)
        {
        case 0:
            return;
            break;
        case 1:
            while (1)
            {
                system("cls");
                printf("请选择排序的方式（0：退出，1：按商品名称排序，2：按商品类别排序，3：按商品库存排序）：\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请选择排序的方式（0：退出，1：按商品名称排序，2：按商品类别排序，3：按商品库存排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_good_by_name();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_good_by_category();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_good_by_stock();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                }
            }
            break;
        case 2:
            while (1)
            {
                system("cls");
                printf("请选择排序的方式（0：退出，1：按顾客姓名排序，2：按顾客类型排序）：\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请选择排序的方式（0：退出，1：按顾客姓名排序，2：按顾客类型排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_customer_by_name();
                    Print_CustomerList(customer_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_customer_by_type();
                    Print_CustomerList(customer_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                }
            }
            break;
        
        case 3:
            while (1)
            {
                system("cls");
                printf("请选择进货记录排序的方式（0：退出，1：按进货数量排序，2：按进货价格排序，3：按进货时间排序）：\n");
                int choice;
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请选择进货记录排序的方式（0：退出，1：按进货数量排序，2：按进货价格排序，3：按进货时间排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_purchase_record_by_quantity();
                    Print_PurchaseRecord(purchase_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_purchase_record_by_price();
                    Print_PurchaseRecord(purchase_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_purchase_record_by_time();
                    Print_PurchaseRecord(purchase_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                }
            }
            break;
        case 4:
            while (1)
            {
                system("cls");
                printf("请选择销售记录排序的方式（0：退出，1：按销售数量排序，2：按销售价格排序，3：按销售时间排序）：\n");
                int choice;
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请选择销售记录排序的方式（0：退出，1：按销售数量排序，2：按销售价格排序，3：按销售时间排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_sale_record_by_quantity();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_sale_record_by_price();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_sale_record_by_time();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                }
            }
            break;
            
        }
    }
}



void Salesperson_Sort()
{
    while (1)
    {
        system("cls");
        printf("请选择排序的对象（0：退出，1：商品，2：顾客，3：销售记录）：\n");
        int choice;
        while (scanf("%d", &choice) != 1 || (choice < 0 || choice > 3))
        {
            while (getchar() != '\n');
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n');
            system("cls"); // 清屏
            printf("请选择排序的对象（0：退出，1：商品，2：顾客，3：销售记录）：\n");
        }
        switch (choice)
        {
        case 0:
            return;
            break;
        case 1:
            while (1)
            {
                system("cls");
                printf("请选择排序的方式（0：退出，1：按商品名称排序，2：按商品类别排序，3：按商品库存排序）：\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n');
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n');
                    system("cls"); // 清屏
                    printf("请选择排序的方式（0：退出，1：按商品名称排序，2：按商品类别排序，3：按商品库存排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_good_by_name();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_good_by_category();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 3:
                    sort_good_by_stock();
                    Print_AllGoodList(all_good_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                }
            }
            break;
        case 2:
            while (1)
            {
                system("cls");
                printf("请选择排序的方式（0：退出，1：按顾客姓名排序，2：按顾客类型排序）：\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
                {
                    while (getchar() != '\n');
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n');
                    system("cls"); // 清屏
                    printf("请选择排序的方式（0：退出，1：按顾客姓名排序，2：按顾客类型排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_customer_by_name();
                    Print_CustomerList(customer_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_customer_by_type();
                    Print_CustomerList(customer_list);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                }
            }
            break;
        case 3:
            while (1)
            {
                system("cls");
                printf("请选择销售记录排序的方式（0：退出，1：按销售数量排序，2：按销售价格排序，3：按销售时间排序）：\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n');
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n');
                    system("cls"); // 清屏
                    printf("请选择销售记录排序的方式（0：退出，1：按销售数量排序，2：按销售价格排序，3：按销售时间排序）：\n");
                }
                if (choice == 0)
                    break;
                switch (choice)
                {
                case 0:
                    break;
                case 1:
                    sort_sale_record_by_quantity();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_sale_record_by_price();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 3:
                    sort_sale_record_by_time();
                    Print_SaleRecord(sale_record);
                    printf("排序结果如上，按回车继续...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                }
            }
            break;
        }
    }
}

