#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"
#include "goods.h"
#include "sale.h"
#include "system.h"
#include "sort.h"
#include "purchase.h"

extern AllGoodList all_good_list;    // ��Ʒ����
extern PurchaseList purchase_record; // ������¼����
extern SaleList sale_record;         // ���ۼ�¼����
extern CustomerList customer_list;   // �˿�����

// ����Ʒ�������
void sort_good_by_name()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е���Ʒ��Ϣ��������
    p = all_good_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // ���Ĳ������� good_name ��Ա��������
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

    // ���岽��������Ԫ���е���Ʒ��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}

// ����Ʒ�������
void sort_good_by_category()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е���Ʒ��Ϣ��������
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

    // ���Ĳ������� category ��Ա��������
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

    // ���岽��������Ԫ���е���Ʒ��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}

// ����Ʒ�������
void sort_good_by_stock()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct Good *arr = (struct Good *)malloc(count * sizeof(struct Good));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е���Ʒ��Ϣ��������
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

    // ���Ĳ������� stock ��Ա��������
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

    // ���岽��������Ԫ���е���Ʒ��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}



// ���˿���������
void sort_customer_by_name()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    CustomerList p = customer_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct CustomerNode *arr = (struct CustomerNode *)malloc(count * sizeof(struct CustomerNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��еĹ˿���Ϣ��������
    p = customer_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].name, p->name);
        strcpy(arr[i].type, p->type);
        // ������Լ������������Ա��ֵ������������Ա�Ļ�
        i++;
        p = p->next;
    }

    // ���Ĳ������� name ��Ա��������
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

    // ���岽��������Ԫ���еĹ˿���Ϣ���¸�ֵ������ڵ�
    p = customer_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->name, arr[i].name);
        strcpy(p->type, arr[i].type);
        // ������Լ������������Ա��ֵ������������Ա�Ļ�
        i++;
        p = p->next;
    }

    // ���������ͷ������ڴ�
    free(arr);
}

// ���˿���������
void sort_customer_by_type()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    CustomerList p = customer_list->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct CustomerNode *arr = (struct CustomerNode *)malloc(count * sizeof(struct CustomerNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��еĹ˿���Ϣ��������
    p = customer_list->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i].id = p->id;
        strcpy(arr[i].name, p->name);
        strcpy(arr[i].type, p->type);
        // ������Լ������������Ա��ֵ������������Ա�Ļ�
        i++;
        p = p->next;
    }

    // ���Ĳ������� type ��Ա��������
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

    // ���岽��������Ԫ���еĹ˿���Ϣ���¸�ֵ������ڵ�
    p = customer_list->next;
    i = 0;
    while (p != NULL)
    {
        p->id = arr[i].id;
        strcpy(p->name, arr[i].name);
        strcpy(p->type, arr[i].type);
        // ������Լ������������Ա��ֵ������������Ա�Ļ�
        i++;
        p = p->next;
    }

    // ���������ͷ������ڴ�
    free(arr);
}





// ��������������
void sort_purchase_record_by_quantity()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��еĽ�����¼��Ϣ��������
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {

        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // ���Ĳ������� quantity ��Ա��������
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

    // ���岽��������Ԫ���еĽ�����¼��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}

// �������۸�����
void sort_purchase_record_by_price()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��еĽ�����¼��Ϣ��������
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // ���Ĳ������� price ��Ա��������
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

    // ���岽��������Ԫ���еĽ�����¼��Ϣ���¸�ֵ������ڵ�
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





// ������ʱ������
void sort_purchase_record_by_time()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    PurchaseList p = purchase_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct PurchaseNode *arr = (struct PurchaseNode *)malloc(count * sizeof(struct PurchaseNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��еĽ�����¼��Ϣ��������
    p = purchase_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *(p);
        i++;
        p = p->next;
    }

    // ���Ĳ������� purchase_time ��Ա��������
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

    // ���岽��������Ԫ���еĽ�����¼��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}





// ��������������
void sort_sale_record_by_quantity()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е����ۼ�¼��Ϣ��������
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // ���Ĳ������� quantity ��Ա��������
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

    // ���岽��������Ԫ���е����ۼ�¼��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}

// �����ۼ۸�����
void sort_sale_record_by_price()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е����ۼ�¼��Ϣ��������
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // ���Ĳ������� sale_price ��Ա��������
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

    // ���岽��������Ԫ���е����ۼ�¼��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}

// ������ʱ������
void sort_sale_record_by_time()
{
    // ��һ����ͳ������ڵ�����
    int count = 0;
    SaleList p = sale_record->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // �ڶ�������������������
    struct SaleNode *arr = (struct SaleNode *)malloc(count * sizeof(struct SaleNode));
    if (arr == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ��������������ڵ��е����ۼ�¼��Ϣ��������
    p = sale_record->next;
    int i = 0;
    while (p != NULL)
    {
        arr[i] = *p;
        i++;
        p = p->next;
    }

    // ���Ĳ������� sale_time ��Ա��������
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

    // ���岽��������Ԫ���е����ۼ�¼��Ϣ���¸�ֵ������ڵ�
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

    // ���������ͷ������ڴ�
    free(arr);
}



void Admin_Sort()
{
    while (1)
    {
        system("cls");
        printf("��ѡ������Ķ���0���˳���1����Ʒ��2���˿ͣ�3��������¼��4�����ۼ�¼����\n");
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 4)
        {
            while (getchar() != '\n')
                ;
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            system("cls"); // ����
            printf("��ѡ������Ķ���0���˳���1����Ʒ��2���˿ͣ�3��������¼��4�����ۼ�¼����\n");
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
                printf("��ѡ������ķ�ʽ��0���˳���1������Ʒ��������2������Ʒ�������3������Ʒ������򣩣�\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("��ѡ������ķ�ʽ��0���˳���1������Ʒ��������2������Ʒ�������3������Ʒ������򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_good_by_category();
                    Print_AllGoodList(all_good_list);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_good_by_stock();
                    Print_AllGoodList(all_good_list);
                    printf("���������ϣ����س�����...");
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
                printf("��ѡ������ķ�ʽ��0���˳���1�����˿���������2�����˿��������򣩣�\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("��ѡ������ķ�ʽ��0���˳���1�����˿���������2�����˿��������򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_customer_by_type();
                    Print_CustomerList(customer_list);
                    printf("���������ϣ����س�����...");
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
                printf("��ѡ�������¼����ķ�ʽ��0���˳���1����������������2���������۸�����3��������ʱ�����򣩣�\n");
                int choice;
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("��ѡ�������¼����ķ�ʽ��0���˳���1����������������2���������۸�����3��������ʱ�����򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_purchase_record_by_price();
                    Print_PurchaseRecord(purchase_record);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_purchase_record_by_time();
                    Print_PurchaseRecord(purchase_record);
                    printf("���������ϣ����س�����...");
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
                printf("��ѡ�����ۼ�¼����ķ�ʽ��0���˳���1����������������2�������ۼ۸�����3��������ʱ�����򣩣�\n");
                int choice;
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("��ѡ�����ۼ�¼����ķ�ʽ��0���˳���1����������������2�������ۼ۸�����3��������ʱ�����򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 2:
                    sort_sale_record_by_price();
                    Print_SaleRecord(sale_record);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 3:
                    sort_sale_record_by_time();
                    Print_SaleRecord(sale_record);
                    printf("���������ϣ����س�����...");
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
        printf("��ѡ������Ķ���0���˳���1����Ʒ��2���˿ͣ�3�����ۼ�¼����\n");
        int choice;
        while (scanf("%d", &choice) != 1 || (choice < 0 || choice > 3))
        {
            while (getchar() != '\n');
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n');
            system("cls"); // ����
            printf("��ѡ������Ķ���0���˳���1����Ʒ��2���˿ͣ�3�����ۼ�¼����\n");
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
                printf("��ѡ������ķ�ʽ��0���˳���1������Ʒ��������2������Ʒ�������3������Ʒ������򣩣�\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n');
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n');
                    system("cls"); // ����
                    printf("��ѡ������ķ�ʽ��0���˳���1������Ʒ��������2������Ʒ�������3������Ʒ������򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_good_by_category();
                    Print_AllGoodList(all_good_list);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 3:
                    sort_good_by_stock();
                    Print_AllGoodList(all_good_list);
                    printf("���������ϣ����س�����...");
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
                printf("��ѡ������ķ�ʽ��0���˳���1�����˿���������2�����˿��������򣩣�\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
                {
                    while (getchar() != '\n');
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n');
                    system("cls"); // ����
                    printf("��ѡ������ķ�ʽ��0���˳���1�����˿���������2�����˿��������򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_customer_by_type();
                    Print_CustomerList(customer_list);
                    printf("���������ϣ����س�����...");
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
                printf("��ѡ�����ۼ�¼����ķ�ʽ��0���˳���1����������������2�������ۼ۸�����3��������ʱ�����򣩣�\n");
                while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
                {
                    while (getchar() != '\n');
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n');
                    system("cls"); // ����
                    printf("��ѡ�����ۼ�¼����ķ�ʽ��0���˳���1����������������2�������ۼ۸�����3��������ʱ�����򣩣�\n");
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
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 2:
                    sort_sale_record_by_price();
                    Print_SaleRecord(sale_record);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                case 3:
                    sort_sale_record_by_time();
                    Print_SaleRecord(sale_record);
                    printf("���������ϣ����س�����...");
                    while (getchar() != '\n');
                    getchar();
                    break;
                }
            }
            break;
        }
    }
}

