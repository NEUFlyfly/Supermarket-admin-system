#ifndef SALE_H_INCLUDED
#define SALE_H_INCLUDED

typedef struct SaleNode
{
    char good_name[20]; // ��Ʒ����
    float sale_price;   // ʵ�����۵��ۣ������ۿۻ������
    char sale_time[20]; // ����ʱ�䣨��ʽ����λʮ����������
    int quantity;       // ��������
    int sale_id;        // ���ۼ�¼��ţ�Ψһ��ʶ��
    int customer_id;    // �˿ͱ�ţ������
    int good_id;        // ��Ʒ��ţ������

    struct SaleNode *next;
} SaleNode, *SaleList;
void Sale(int customer_id, int good_id, int quantity);
void Init_SaleList(SaleList *list);
void Insert_SaleList(SaleList *list, SaleNode sale);
void ResetSaleId();
void Print_SaleList();
void Print_SaleRecord(SaleList list);
#endif // SALE_H_INCLUDED
