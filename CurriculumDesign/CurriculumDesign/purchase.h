#ifndef PURCHASE_H_INCLUDED
#define PURCHASE_H_INCLUDED

// ����record��ʽ����Ʒ���� ����ʱ�䣨��ʽ����λʮ������������������ �������� ��Ӧ������ ��Ʒ���
typedef struct PurchaseNode
{
    int id;                 // ������ţ�Ψһ��ʶ��
    char good_name[50];     // ��Ʒ���ƣ�����洢������ֱ�Ӳ�ѯ��
    char purchase_time[20]; // ����ʱ�䣨��ʽ����λʮ����������
    float cost_price;       // ��������
    int quantity;           // ����������Good����Ա����
    char supplier[50];      // ��Ӧ������
    char category[50];      // ��Ʒ���
    struct PurchaseNode *next;
} PurchaseNode, *PurchaseList;

void Init_PurchaseList(PurchaseList *list);
int Insert_PurchaseList(PurchaseList *list, PurchaseNode purchase);
void Print_PurchaseList();
void Print_PurchaseRecord(PurchaseList list);
#endif // PURCHASE_H_INCLUDED
