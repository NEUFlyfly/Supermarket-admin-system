#include "search.h"
#include "customer.h"
#include "goods.h"
#include "sale.h"
#include "purchase.h"
#include "salesperson.h"
#include "sort.h"

#include "admin.h"
#include "system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern AllGoodList all_good_list;    // 商品链表
extern SaleList sale_record;         // 销售记录链表
extern PurchaseList purchase_record; // 采购记录链表
extern CustomerList customer_list;   // 顾客链表

void good_search()
{
    while (1)
    {
        system("cls"); // 清屏
        // 选择查询结果排序方式
        printf("请输入结果的[排序]方式：\n");
        printf("0：不排序\n");
        printf("1：按商品[名称]排序\n");
        printf("2：按商品[类别]排序\n");
        printf("3：按商品[库存]排序\n");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("输入错误，请输入 0 - 3 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:
            break;
        case 1:
            sort_good_by_name();
            break;
        case 2:
            sort_good_by_category();
            break;
        case 3:
            sort_good_by_stock();
            break;
        }

        system("cls"); // 清屏
        char name[50]; // 商品名称
        printf("请输入查询方式：\n");
        printf("0：退出\n");
        printf("1：按商品[名称]查询（简单查询）\n");
        printf("2：按商品[类别]查询（简单查询）\n");
        printf("3：按商品[标价]查询（模糊查询）\n");
        printf("4：按商品[售价]查询（模糊查询）\n");
        printf("5：按商品[类别]和[标价]查询（组合查询）\n");
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5)
        {
            printf("输入错误，请输入 0 - 5 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 按商品名称查询（简单查询）
        {
            printf("请输入商品名称：");          // 提示用户输入商品名称
            scanf("%s", name);                   // 输入商品名称
            AllGoodList p = all_good_list->next; // 遍历all_good_list，找到所有商品名称相同的节点
            int found = 0;                       // 标记是否找到商品
            while (p != NULL)
            {                                        // 第一遍循环，先确定有没有这个商品
                if (strcmp(p->good_name, name) == 0) // 找到商品名称相同的节点
                {
                    found = 1;
                    break;
                } // 找到商品，跳出循环
                p = p->next; // 继续遍历
            }
            if (!found) // 没有找到商品，提示用户
            {
                printf("没有该商品！\n");  // 提示用户没有找到该商品
                printf("按回车键继续..."); // 提示用户按回车键继续
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else // 找到商品，中文表头
            {
                p = all_good_list->next;
                // 输出表头

                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "商品id", "商品类别", "商品名称", "生产厂家", "标定价格", "促销价格", "库存数量", "商品描述");
                while (p != NULL)
                {
                    if (strcmp(p->good_name, name) == 0) // 找到商品名称相同的节点
                    {
                        // 输出商品信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("按回车键继续..."); // 提示用户按回车键继续
                while (getchar() != '\n')
                    ;
                getchar(); // 等待用户按下回车键
            }
        }
        break;
        case 2: // 按商品类别查询（简单查询）
        {
            AllGoodList p = all_good_list->next;
            char category[50];
            printf("请输入商品类别：");
            scanf("%s", category);
            p = all_good_list->next;
            int found = 0;
            // 第一遍循环，先确定有没有这个类别的商品
            while (p != NULL)
            {
                if (strcmp(p->category, category) == 0)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有该类别的商品！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // 输出表头
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "商品id", "商品类别", "商品名称", "生产厂家", "标定价格", "促销价格", "库存数量", "商品描述");
                while (p != NULL)
                {
                    if (strcmp(p->category, category) == 0)
                    {
                        // 输出商品信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 3: // 按商品标价查询（模糊查询）
        {
            float min_price, max_price;
            printf("请输入标价区间（用空格分隔两个价格，不规定顺序）：");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("输入无效，请输入两个有效的价格。\n");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            // 确保 min_price 是较小值，max_price 是较大值
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // 第一遍循环，先确定有没有进价在该区间的商品
            while (p != NULL)
            {
                if (p->price >= min_price && p->price <= max_price)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有标价在该区间的商品！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // 输出表头
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "商品id", "商品类别", "商品名称", "生产厂家", "标定价格", "促销价格", "库存数量", "商品描述");
                while (p != NULL)
                {
                    if (p->price >= min_price && p->price <= max_price)
                    {
                        // 输出商品信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 4: // 按商品售价查询（模糊查询）
        {
            float min_price, max_price;
            printf("请输入售价区间（用空格分隔两个价格，不规定顺序）：");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("输入无效，请输入两个有效的价格。\n");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            // 确保 min_price 是较小值，max_price 是较大值
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // 第一遍循环，先确定有没有售价在该区间的商品
            while (p != NULL)
            {
                float current_price = p->is_promotion ? p->promotion_price : p->price;
                if (current_price >= min_price && current_price <= max_price)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有售价在该区间的商品！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // 输出表头
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "商品id", "商品类别", "商品名称", "生产厂家", "标定价格", "促销价格", "库存数量", "商品描述");
                while (p != NULL)
                {
                    float current_price = p->is_promotion ? p->promotion_price : p->price;
                    if (current_price >= min_price && current_price <= max_price)
                    {
                        // 输出商品信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 5: // 按商品类别和标价查询（组合查询）
        {
            char category[50];
            float min_price, max_price;
            printf("请输入商品类别：");
            scanf("%s", category);
            printf("请输入标价区间（用空格分隔两个价格，不规定顺序）：");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("输入无效，请输入两个有效的价格。\n");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            // 确保 min_price 是较小值，max_price 是较大值
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // 第一遍循环，先确定有没有该类别且标价在该区间的商品
            while (p != NULL)
            {
                if (strcmp(p->category, category) == 0 && p->price >= min_price && p->price <= max_price)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有该类别且标价在该区间的商品！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // 输出表头
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "商品id", "商品类别", "商品名称", "生产厂家", "标定价格", "促销价格", "库存数量", "商品描述");
                while (p != NULL)
                {
                    if (strcmp(p->category, category) == 0 && p->price >= min_price && p->price <= max_price)
                    {
                        // 输出商品信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        }
    }
}

void customer_search()
{
    while (1)
    {
        system("cls"); // 清屏
        char name[50]; // 顾客名称
        printf("请输入查询方式：\n");
        printf("0：退出\n");
        printf("1：按顾客[姓名]查询）\n");
        printf("2：按顾客[星级]查询）\n");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("输入错误，请输入 0 - 3 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 按顾客姓名查询（简单查询）
        {
            printf("请输入顾客姓名：");           // 提示用户输入顾客姓名
            scanf("%s", name);                    // 输入顾客姓名
            CustomerList p = customer_list->next; // 遍历customer_list，找到所有顾客姓名相同的节点
            int found = 0;                        // 标记是否找到顾客
            while (p != NULL)
            {                                   // 第一遍循环，先确定有没有这个顾客
                if (strcmp(p->name, name) == 0) // 找到顾客姓名相同的节点
                {
                    found = 1;
                    break;
                }
                p = p->next; // 继续遍历
            }
            if (!found) // 没有找到顾客，提示用户
            {
                printf("没有该顾客！\n");  // 提示用户没有找到该顾客
                printf("按回车键继续..."); // 提示用户按回车键继续
                while (getchar() != '\n')
                    ;
                getchar(); // 等待用户按下回车键
            }
            else // 找到顾客，中文表头
            {
                p = customer_list->next;
                // 输出表头
                printf("%-20s %-20s %-20s\n", "顾客姓名", "顾客电话", "顾客星级");
                while (p != NULL)
                {
                    if (strcmp(p->name, name) == 0) // 找到顾客姓名相同的节点
                    {
                        // 输出顾客信息，使用格式化输出保证对齐
                        printf("%-20s %-20s %-20s\n", p->name, p->contact, p->type);
                    }
                    p = p->next;
                }
                printf("按回车键继续..."); // 提示用户按回车键继续
                while (getchar() != '\n')
                    ;
                getchar(); // 等待用户按下回车键
            }
        }
        break;
        case 2: // 按顾客星级查询（简单查询）
        {
            char star[20];
            printf("请输入顾客星级（vip, svip, normal）：");
            scanf("%s", star);

            CustomerList p = customer_list->next;
            int found = 0;
            // 第一遍循环，先确定有没有这个星级的顾客
            while (p != NULL)
            {
                if (!strcmp(star, p->type))
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有该星级的顾客！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = customer_list->next;
                // 输出表头
                printf("%-20s %-20s %-20s\n", "顾客姓名", "顾客电话", "顾客星级");
                while (p != NULL)
                {
                    if (!strcmp(star, p->type))
                    {
                        // 输出顾客信息，使用格式化输出保证对齐
                        printf("%-20s %-20s %-20s\n", p->name, p->contact, p->type);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void purchase_search() // 遍历purchase_record链表，找到所有采购记录
{
    while (1)
    {
        system("cls"); // 清屏
        printf("请输入查询方式：\n");
        printf("0：退出\n");
        printf("1：按进货时间查询（模糊查询）\n");
        printf("2：按进货量查询（模糊查询）\n");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
        {
            printf("输入错误，请输入 0 - 2 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 按销售时间区间查询（模糊查询）
        {
            int min_time, max_time;
            printf("请输入进货时间区间（用空格分隔两个0到10000内的整数，不规定顺序）：");
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

            PurchaseList p = purchase_record->next;
            int found = 0;
            // 第一遍循环，先确定有没有销售时间在该区间的采购记录
            while (p != NULL)
            {
                int current_time = atoi(p->purchase_time);
                if (current_time >= min_time && current_time <= max_time)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有销售时间在该区间的采购记录！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = purchase_record->next;
                // 输出表头格式id 类别 名称 售价 销售数量 销售时间 供应商
                printf("%-8s %-16s %-16s %-10s %-10s %-10s %-20s\n",
                       "id", "类别", "名称", "售价", "进货数量", "进货时间", "供应商");
                while (p != NULL)
                {
                    int current_time = atoi(p->purchase_time);
                    if (current_time >= min_time && current_time <= max_time)
                    {
                        // 输出采购记录信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-10.2f %-10d %-10s %-20s\n",
                               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 2: // 按进货量查询（模糊查询）
        {
            int min_quantity, max_quantity;
            printf("请输入进货量区间（用空格分隔两个非负整数，不规定顺序）：");
            if (scanf("%d %d", &min_quantity, &max_quantity) != 2 || min_quantity < 0 || max_quantity < 0)
            {
                printf("输入无效，请输入两个非负的有效整数。\n");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            // 确保 min_quantity 是较小值，max_quantity 是较大值
            if (min_quantity > max_quantity)
            {
                int temp = min_quantity;
                min_quantity = max_quantity;
                max_quantity = temp;
            }

            PurchaseList p = purchase_record->next;
            int found = 0;
            // 第一遍循环，先确定有没有进货量在该区间的采购记录
            while (p != NULL)
            {
                if (p->quantity >= min_quantity && p->quantity <= max_quantity)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有进货量在该区间的采购记录！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = purchase_record->next;
                // 输出表头格式id 类别 名称 售价 销售数量 销售时间 供应商
                printf("%-8s %-16s %-16s %-10s %-10s %-10s %-20s\n", "id",
                       "类别", "名称", "售价", "进货数量", "时间", "供应商");
                while (p != NULL)
                {
                    if (p->quantity >= min_quantity && p->quantity <= max_quantity)
                    {
                        // 输出采购记录信息，使用格式化输出保证对齐
                        printf("%-8d %-16s %-16s %-10.2f %-10d %-10s %-20s\n",
                               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
                    }
                    p = p->next;
                }
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void sale_search() // 遍历sale_record链表，找到所有销售记录
{
    while (1)
    {
        system("cls"); // 清屏
        printf("请输入查询方式：\n");
        printf("0：退出\n");
        printf("1：按销售时间区间查询（模糊查询）\n");
        printf("2：按销售数量区间查询（模糊查询）\n");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
        {
            printf("输入错误，请输入 0 - 2 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 按销售时间区间查询（模糊查询）
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
                printf("没有销售时间在该区间的销售记录！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = sale_record->next;
                // 输出表头格式 id 商品名称 销售单价 销售数量 销售时间 顾客姓名
                printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "销售记录id", "商品id", "商品名称", "销售时间", "销售单价", "顾客id");
                while (p != NULL)
                {
                    int current_time = atoi(p->sale_time);
                    if (current_time >= min_time && current_time <= max_time)
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
        break;
        case 2: // 按销售数量区间查询（模糊查询）
        {
            int min_quantity, max_quantity;
            printf("请输入销售数量区间（用空格分隔两个非负整数，不规定顺序）：");
            if (scanf("%d %d", &min_quantity, &max_quantity) != 2 || min_quantity < 0 || max_quantity < 0)
            {
                printf("输入无效，请输入两个非负的有效整数。\n");
                while (getchar() != '\n')
                    ;
                getchar(); // 清空输入缓冲区
                break;
            }
            // 确保 min_quantity 是较小值，max_quantity 是较大值
            if (min_quantity > max_quantity)
            {
                int temp = min_quantity;
                min_quantity = max_quantity;
                max_quantity = temp;
            }

            SaleList p = sale_record->next;
            int found = 0;
            // 第一遍循环，先确定有没有销售数量在该区间的销售记录
            while (p != NULL)
            {
                if (p->quantity >= min_quantity && p->quantity <= max_quantity)
                {
                    found = 1;
                    break;
                }
                p = p->next;
            }
            if (!found)
            {
                printf("没有销售数量在该区间的销售记录！\n");
                printf("按回车键继续...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = sale_record->next;
                // 输出表头格式 id 商品名称 销售单价 销售数量 销售时间 顾客姓名
                printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "销售记录id", "商品id", "商品名称", "销售时间", "销售单价", "顾客id");
                while (p != NULL)
                {
                    if (p->quantity >= min_quantity && p->quantity <= max_quantity)
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
        break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

// 这个函数的结构比较独特
void search_max_good_sales_in_time_range()
{
    while (1)
    {
        system("cls"); // 清屏
        int min_time, max_time;
        printf("请输入销售时间区间（用空格分隔两个0到10000内的整数，不规定顺序，输入-1 -1退出）：\n");
        if ((scanf("%d %d", &min_time, &max_time) != 2 || min_time < 0 || min_time > 10000 || max_time < 0 || max_time > 10000 )&& !(min_time == -1 && max_time == -1))
        {
            printf("输入无效，请输入两个0到10000内的有效整数，按回车继续...\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
            continue;
        }
        if (min_time == -1 && max_time == -1)
            return;
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
            printf("没有销售时间在该区间的销售记录！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

        else
        {
            p = sale_record->next;
            // 找到销售时间在该区间，且销售数量最大的商品
            // 第一步，统计每种商品（按照good_name相同则把quantity相加的原则）的销售数量
            // 定义一个结构体数组，用于存储每种商品的销售数量
            struct GoodSales
            {
                char good_name[50]; // 商品名称
                int quantity;       // 销售数量
            };
            struct GoodSales good_sales[200]; // 假设最多有200种商品
            int good_sales_count = 0;         // 记录商品种类数量
            while (p != NULL)
            {
                int current_time = atoi(p->sale_time);
                if (current_time >= min_time && current_time <= max_time)
                {
                    // 遍历good_sales数组，查找是否已经有该商品的记录
                    int i;
                    for (i = 0; i < good_sales_count; i++)
                    {
                        if (strcmp(good_sales[i].good_name, p->good_name) == 0)
                        {
                            good_sales[i].quantity += p->quantity; // 累加销售数量
                            break;
                        }
                    }
                    if (i == good_sales_count) // 如果没有找到该商品的记录，则添加一条新记录
                    {
                        strcpy(good_sales[good_sales_count].good_name, p->good_name); // 复制商品名称
                        good_sales[good_sales_count].quantity = p->quantity;          // 初始化销售数量
                        good_sales_count++;                                           // 商品种类数量加1
                    }
                }
                p = p->next; // 继续遍历
            }
            // 第二步，找到销售数量最大的商品
            int max_quantity = 0; // 记录最大销售数量
            int max_index = 0;    // 记录最大销售数量的商品索引
            for (int i = 0; i < good_sales_count; i++)
            {
                if (good_sales[i].quantity > max_quantity) // 如果当前商品的销售数量大于最大销售数量
                {
                    max_quantity = good_sales[i].quantity; // 更新最大销售数量
                    max_index = i;                         // 更新最大销售数量的商品索引
                }
            }
            // 第三步，输出结果
            printf("销售时间在%ds到%ds之间，销售数量最多的商品是：%s，销售数量为：%d\n", min_time, max_time, good_sales[max_index].good_name, max_quantity);
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}
void Admin_Search()
{
    while (1)
    {
        system("cls"); // 清屏
        printf("请输入查询选项：\n");
        printf("0：退出\n");
        printf("1：[商品]查询\n");
        printf("2：[顾客]查询\n");
        printf("3：[采购记录]查询\n");
        printf("4：[销售记录]查询\n");
        printf("5：查询[某段时间内销量最大]的商品");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5)
        {
            printf("输入错误，请输入 0 - 4 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 商品查询
            good_search();
            break;
        case 2: // 顾客查询
            customer_search();
            break;
        case 3: // 采购查询
            purchase_search();
            break;
        case 4: // 销售查询
            sale_search();
            break;
        case 5: // 查询某段时间内销量最大的商品
            search_max_good_sales_in_time_range();
            break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void Salesperson_Search() // 售货员查询
{
    while (1)
    {
        system("cls"); // 清屏
        printf("请输入查询选项：\n");
        printf("0：退出\n");
        printf("1：商品查询\n");
        printf("2：顾客查询\n");
        printf("3：销售查询\n");
        int choice; // 选择
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("输入错误，请输入 0 - 3 之间的整数！\n");
            while (getchar() != '\n')
                ;
            getchar(); // 清空输入缓冲区
        }
        switch (choice)
        {
        case 0:     // 退出
            return; // 返回主菜单
        case 1:     // 商品查询
            good_search();
            break;
        case 2: // 顾客查询
            customer_search();
            break;
        case 3: // 销售查询
            sale_search();
            break;
        default: // 其他情况，提示输入错误
            printf("输入错误，请重新输入！\n");
            printf("按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}