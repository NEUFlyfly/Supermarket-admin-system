#include "system.h"
#include "sale.h"
#include "purchase.h"
#include "customer.h"
#include "salesperson.h"
#include "goods.h"
#include "admin.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
static time_t start_time; // ���ڴ洢ϵͳ����ʱ��

extern AllGoodList all_good_list;
extern SaleList sale_record;
extern PurchaseList purchase_record;
extern CustomerList customer_list;

// ������ʱ������¼��ǰʱ��
void TimerStart()
{
    start_time = time(NULL); // ��ȡ��ǰʱ���
}

// ��ȡ��ϵͳ��ʼ���е�����������λʮ������������
void GetCurrentTime(char *time_str)
{
    time_t current_time = time(NULL);                    // ��ȡ��ǰʱ���
    int elapsed_time = (int)(current_time - start_time); // ���㾭��������

    // ȡ����λʮ������
    elapsed_time %= 10000;

    // ��ʽ��Ϊ��λʮ�����ַ���
    snprintf(time_str, 5, "%04d", elapsed_time);
}

// ��λϵͳ
void ResetSystem()
{
    // ����ϵͳ״̬��������ݵȲ���
    // �����������
    AllGoodList p = all_good_list->next;
    while (p != NULL)
    {
        AllGoodList temp = p;
        p = p->next;
        free(temp);
    }
    all_good_list->next = NULL;

    SaleList s = sale_record->next;
    while (s != NULL)
    {
        SaleList temp = s;
        s = s->next;
        free(temp);
    }
    sale_record->next = NULL;

    PurchaseList pu = purchase_record->next;
    while (pu != NULL)
    {
        PurchaseList temp = pu;
        pu = pu->next;
        free(temp);
    }
    purchase_record->next = NULL;

    CustomerList c = customer_list->next;
    while (c != NULL)
    {
        CustomerList temp = c;
        c = c->next;
        free(temp);
    }
    customer_list->next = NULL;

    Init_AllGoodList(&all_good_list);    // ���³�ʼ����Ʒ����
    Init_SaleList(&sale_record);         // ���³�ʼ�����ۼ�¼����
    Init_PurchaseList(&purchase_record); // ���³�ʼ��������¼����
    Init_CustomerList(&customer_list);   // ���³�ʼ���˿�����

    // ���ü�ʱ��
    TimerStart();

    // ����ȫ��id����
    ResetSaleId();
    ResetAdmin(); // ������Ʒ����id

    // ���customerInfo��purchaseInfo��saleInfo�ļ�����
    FILE *fp1 = fopen("txt/customerInfo.txt", "w"); // ���ļ����������
    FILE *fp2 = fopen("txt/purchaseInfo.txt", "w"); // ���ļ����������
    FILE *fp3 = fopen("txt/saleInfo.txt", "w");     // ���ļ����������
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
    { // ����ļ���ʧ�ܣ����������Ϣ���˳�
        printf("�ļ���ʧ�ܣ�\n");
        exit(1); // �˳�����
    }
    fclose(fp1); // �ر��ļ�
    fclose(fp2); // �ر��ļ�
    fclose(fp3); // �ر��ļ�

    printf("ϵͳ�Ѹ�λ��\n");
    // ����س�����
    getchar();
}