#ifndef GOODS_H_INCLUDED
#define GOODS_H_INCLUDED
#include "sale.h"
// GoodΪ������Ʒ������Ϣ�ṹ��
typedef struct Good
{
    int id;                // ��Ʒ��ţ�Ψһ��ʶ��
    char good_name[50];    // ��Ʒ����
    char category[30];     // ��Ʒ���
    char manufacturer[50]; // ��������
    char description[100]; // ��Ʒ��������ѡ��
    float price;           // ���ۼ۸񣨲����Ǵ����Լ��˿����
    int stock;             // �������
    int is_promotion;      // �Ƿ������0=��1=�ǣ�
    float promotion_price; // �����۸�����д�����
    struct Good *next;     // ָ����һ���ڵ��ָ��
} *AllGoodList, GoodNode;


void Init_AllGoodList(AllGoodList *list);
void Insert_AllGoodList(AllGoodList *list, GoodNode good);
int Delete_AllGoodList(AllGoodList *list, int id);
void Print_AllGoodList(AllGoodList list);

#endif // GOODS_H_INCLUDED
