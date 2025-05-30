#ifndef PURCHASE_H_INCLUDED
#define PURCHASE_H_INCLUDED

// 进货record格式：商品名称 进货时间（格式：四位十进制整数）进货单价 进货数量 供应商名称 商品类别
typedef struct PurchaseNode
{
    int id;                 // 进货编号（唯一标识）
    char good_name[50];     // 商品名称（冗余存储，方便直接查询）
    char purchase_time[20]; // 进货时间（格式：四位十进制整数）
    float cost_price;       // 进货单价
    int quantity;           // 进货数量与Good库存成员关联
    char supplier[50];      // 供应商名称
    char category[50];      // 商品类别
    struct PurchaseNode *next;
} PurchaseNode, *PurchaseList;

void Init_PurchaseList(PurchaseList *list);
int Insert_PurchaseList(PurchaseList *list, PurchaseNode purchase);
void Print_PurchaseList();
void Print_PurchaseRecord(PurchaseList list);
#endif // PURCHASE_H_INCLUDED
