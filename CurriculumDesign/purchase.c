#include "purchase.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
// �����յ�Purchase����
void Init_PurchaseList(PurchaseList *list)
{
    *list = (PurchaseList)malloc(sizeof(PurchaseNode));
    if (*list == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    (*list)->next = NULL;
}

// �����µĽ�����¼��Purchase����ͷ�巨
// �����µĽ�����¼��Purchase����ͷ�巨
int Insert_PurchaseList(PurchaseList *list, PurchaseNode purchase)
{
    // ��鴫�������ָ���Ƿ�Ϊ NULL
    if (list == NULL)
    {
        return -1; // ���������ָ����Ч
    }

    // Ϊ�½ڵ�����ڴ�
    PurchaseNode *newnode = malloc(sizeof(PurchaseNode));
    if (newnode == NULL)
    {
        return -2; // �ڴ����ʧ��
    }

    // ���ƽڵ���Ϣ
    newnode->quantity = purchase.quantity;
    newnode->cost_price = purchase.cost_price;
    newnode->id = purchase.id;
    strcpy(newnode->category, purchase.category);
    strcpy(newnode->good_name, purchase.good_name);
    strcpy(newnode->purchase_time, purchase.purchase_time);
    strcpy(newnode->supplier, purchase.supplier);

    // ͷ�巨����ڵ�
    newnode->next = (*list)->next;
    (*list)->next = newnode;

    return 0; // ����ɹ�
}

// ��ӡpurchaseInfo.txt�ļ��е����н�����¼
// ��ʽΪ��
// ��¼��� ��� ��Ʒ���� ���� �������� ����ʱ��(s) ��Ӧ��
// 1 Fruit Apple 150.00 110 0021 SupplierA
// 2 Fruit Apple 100.00 80 0021 SupplierA
// 3 Electronics Laptop 820.00 25 0021 TechWorld

void Print_PurchaseRecord(PurchaseList list)
{
    PurchaseList p = list->next; // ָ���һ���ڵ�
    if (p == NULL)
        printf("������¼Ϊ�գ�\n");
    else
        printf("%-10s %-15s %-20s %-10s %-10s %-15s %-20s\n",
               "��¼���", "���", "��Ʒ����", "����", "��������", "����ʱ��(s)", "��Ӧ��");
    while (p != NULL) // ����������ӡÿ���ڵ����Ϣ
    {
        printf("%-10d %-15s %-20s %-10.2f %-10d %-15s %-20s\n",
               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
        p = p->next; // ָ����һ���ڵ�
    }
}

void Print_PurchaseList()
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "r");
    if (fp == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        return; // ���ļ�ʧ�ܣ�ֱ�ӷ���
    }

    char line[200]; // ���ڴ洢ÿһ�е�����
    int id;
    char purchase_time[20];
    char category[50];
    char good_name[50];
    int quantity;
    float cost_price;
    char supplier[50];
    int has_records = 0; // ���ڱ���ļ����Ƿ��м�¼

    // ��ӡ��ͷ�����ո�ʽҪ�����
    printf("%-10s %-15s %-20s %-10s %-10s %-15s %-20s\n",
           "��¼���", "���", "��Ʒ����", "����", "��������", "����ʱ��(s)", "��Ӧ��");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // ����ÿһ�����ݣ����ո�ʽҪ�����
        sscanf(line, "%d %49s %49s %f %d %19s %49s", &id, category, good_name, &cost_price, &quantity, purchase_time, supplier);
        // ����ָ����ʽ��������ո�ʽҪ�����
        printf("%-10d %-15s %-20s %-10.2f %-10d %-15s %-20s\n",
               id, category, good_name, cost_price, quantity, purchase_time, supplier);
        has_records = 1; // ����ļ����м�¼
    }

    if (!has_records)
    {
        printf("������¼�ļ�Ϊ�ա�\n");
    }

    fclose(fp); // �ر��ļ�
}
