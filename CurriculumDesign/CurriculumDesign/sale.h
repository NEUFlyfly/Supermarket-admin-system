#ifndef SALE_H_INCLUDED
#define SALE_H_INCLUDED

typedef struct SaleNode
{
    char good_name[20]; // 商品名称
    float sale_price;   // 实际销售单价（考虑折扣或促销）
    char sale_time[20]; // 销售时间（格式：四位十进制整数）
    int quantity;       // 销售数量
    int sale_id;        // 销售记录编号（唯一标识）
    int customer_id;    // 顾客编号（外键）
    int good_id;        // 商品编号（外键）

    struct SaleNode *next;
} SaleNode, *SaleList;
void Sale(int customer_id, int good_id, int quantity);
void Init_SaleList(SaleList *list);
void Insert_SaleList(SaleList *list, SaleNode sale);
void ResetSaleId();
void Print_SaleList();
void Print_SaleRecord(SaleList list);
#endif // SALE_H_INCLUDED
