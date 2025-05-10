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

extern AllGoodList all_good_list;    // ��Ʒ����
extern SaleList sale_record;         // ���ۼ�¼����
extern PurchaseList purchase_record; // �ɹ���¼����
extern CustomerList customer_list;   // �˿�����

void good_search()
{
    while (1)
    {
        system("cls"); // ����
        // ѡ���ѯ�������ʽ
        printf("����������[����]��ʽ��\n");
        printf("0��������\n");
        printf("1������Ʒ[����]����\n");
        printf("2������Ʒ[���]����\n");
        printf("3������Ʒ[���]����\n");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("������������� 0 - 3 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
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

        system("cls"); // ����
        char name[50]; // ��Ʒ����
        printf("�������ѯ��ʽ��\n");
        printf("0���˳�\n");
        printf("1������Ʒ[����]��ѯ���򵥲�ѯ��\n");
        printf("2������Ʒ[���]��ѯ���򵥲�ѯ��\n");
        printf("3������Ʒ[���]��ѯ��ģ����ѯ��\n");
        printf("4������Ʒ[�ۼ�]��ѯ��ģ����ѯ��\n");
        printf("5������Ʒ[���]��[���]��ѯ����ϲ�ѯ��\n");
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5)
        {
            printf("������������� 0 - 5 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ����Ʒ���Ʋ�ѯ���򵥲�ѯ��
        {
            printf("��������Ʒ���ƣ�");          // ��ʾ�û�������Ʒ����
            scanf("%s", name);                   // ������Ʒ����
            AllGoodList p = all_good_list->next; // ����all_good_list���ҵ�������Ʒ������ͬ�Ľڵ�
            int found = 0;                       // ����Ƿ��ҵ���Ʒ
            while (p != NULL)
            {                                        // ��һ��ѭ������ȷ����û�������Ʒ
                if (strcmp(p->good_name, name) == 0) // �ҵ���Ʒ������ͬ�Ľڵ�
                {
                    found = 1;
                    break;
                } // �ҵ���Ʒ������ѭ��
                p = p->next; // ��������
            }
            if (!found) // û���ҵ���Ʒ����ʾ�û�
            {
                printf("û�и���Ʒ��\n");  // ��ʾ�û�û���ҵ�����Ʒ
                printf("���س�������..."); // ��ʾ�û����س�������
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else // �ҵ���Ʒ�����ı�ͷ
            {
                p = all_good_list->next;
                // �����ͷ

                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "��Ʒid", "��Ʒ���", "��Ʒ����", "��������", "�궨�۸�", "�����۸�", "�������", "��Ʒ����");
                while (p != NULL)
                {
                    if (strcmp(p->good_name, name) == 0) // �ҵ���Ʒ������ͬ�Ľڵ�
                    {
                        // �����Ʒ��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("���س�������..."); // ��ʾ�û����س�������
                while (getchar() != '\n')
                    ;
                getchar(); // �ȴ��û����»س���
            }
        }
        break;
        case 2: // ����Ʒ����ѯ���򵥲�ѯ��
        {
            AllGoodList p = all_good_list->next;
            char category[50];
            printf("��������Ʒ���");
            scanf("%s", category);
            p = all_good_list->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û�����������Ʒ
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
                printf("û�и�������Ʒ��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // �����ͷ
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "��Ʒid", "��Ʒ���", "��Ʒ����", "��������", "�궨�۸�", "�����۸�", "�������", "��Ʒ����");
                while (p != NULL)
                {
                    if (strcmp(p->category, category) == 0)
                    {
                        // �����Ʒ��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 3: // ����Ʒ��۲�ѯ��ģ����ѯ��
        {
            float min_price, max_price;
            printf("�����������䣨�ÿո�ָ������۸񣬲��涨˳�򣩣�");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("������Ч��������������Ч�ļ۸�\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_price �ǽ�Сֵ��max_price �ǽϴ�ֵ
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û�н����ڸ��������Ʒ
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
                printf("û�б���ڸ��������Ʒ��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // �����ͷ
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "��Ʒid", "��Ʒ���", "��Ʒ����", "��������", "�궨�۸�", "�����۸�", "�������", "��Ʒ����");
                while (p != NULL)
                {
                    if (p->price >= min_price && p->price <= max_price)
                    {
                        // �����Ʒ��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 4: // ����Ʒ�ۼ۲�ѯ��ģ����ѯ��
        {
            float min_price, max_price;
            printf("�������ۼ����䣨�ÿո�ָ������۸񣬲��涨˳�򣩣�");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("������Ч��������������Ч�ļ۸�\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_price �ǽ�Сֵ��max_price �ǽϴ�ֵ
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û���ۼ��ڸ��������Ʒ
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
                printf("û���ۼ��ڸ��������Ʒ��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // �����ͷ
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "��Ʒid", "��Ʒ���", "��Ʒ����", "��������", "�궨�۸�", "�����۸�", "�������", "��Ʒ����");
                while (p != NULL)
                {
                    float current_price = p->is_promotion ? p->promotion_price : p->price;
                    if (current_price >= min_price && current_price <= max_price)
                    {
                        // �����Ʒ��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 5: // ����Ʒ���ͱ�۲�ѯ����ϲ�ѯ��
        {
            char category[50];
            float min_price, max_price;
            printf("��������Ʒ���");
            scanf("%s", category);
            printf("�����������䣨�ÿո�ָ������۸񣬲��涨˳�򣩣�");
            if (scanf("%f %f", &min_price, &max_price) != 2)
            {
                printf("������Ч��������������Ч�ļ۸�\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_price �ǽ�Сֵ��max_price �ǽϴ�ֵ
            if (min_price > max_price)
            {
                float temp = min_price;
                min_price = max_price;
                max_price = temp;
            }
            AllGoodList p = all_good_list->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û�и�����ұ���ڸ��������Ʒ
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
                printf("û�и�����ұ���ڸ��������Ʒ��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = all_good_list->next;
                // �����ͷ
                printf("%-8s %-16s %-16s %-16s %-8s %-8s %-8s %20s\n",
                       "��Ʒid", "��Ʒ���", "��Ʒ����", "��������", "�궨�۸�", "�����۸�", "�������", "��Ʒ����");
                while (p != NULL)
                {
                    if (strcmp(p->category, category) == 0 && p->price >= min_price && p->price <= max_price)
                    {
                        // �����Ʒ��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-16s %-8.2f %-8.2f %-8d %-20s\n",
                               p->id, p->category, p->good_name, p->manufacturer, p->price, p->promotion_price, p->stock, p->description);
                    }
                    p = p->next;
                }
                printf("���س�������...");
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
        system("cls"); // ����
        char name[50]; // �˿�����
        printf("�������ѯ��ʽ��\n");
        printf("0���˳�\n");
        printf("1�����˿�[����]��ѯ��\n");
        printf("2�����˿�[�Ǽ�]��ѯ��\n");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("������������� 0 - 3 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ���˿�������ѯ���򵥲�ѯ��
        {
            printf("������˿�������");           // ��ʾ�û�����˿�����
            scanf("%s", name);                    // ����˿�����
            CustomerList p = customer_list->next; // ����customer_list���ҵ����й˿�������ͬ�Ľڵ�
            int found = 0;                        // ����Ƿ��ҵ��˿�
            while (p != NULL)
            {                                   // ��һ��ѭ������ȷ����û������˿�
                if (strcmp(p->name, name) == 0) // �ҵ��˿�������ͬ�Ľڵ�
                {
                    found = 1;
                    break;
                }
                p = p->next; // ��������
            }
            if (!found) // û���ҵ��˿ͣ���ʾ�û�
            {
                printf("û�иù˿ͣ�\n");  // ��ʾ�û�û���ҵ��ù˿�
                printf("���س�������..."); // ��ʾ�û����س�������
                while (getchar() != '\n')
                    ;
                getchar(); // �ȴ��û����»س���
            }
            else // �ҵ��˿ͣ����ı�ͷ
            {
                p = customer_list->next;
                // �����ͷ
                printf("%-20s %-20s %-20s\n", "�˿�����", "�˿͵绰", "�˿��Ǽ�");
                while (p != NULL)
                {
                    if (strcmp(p->name, name) == 0) // �ҵ��˿�������ͬ�Ľڵ�
                    {
                        // ����˿���Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-20s %-20s %-20s\n", p->name, p->contact, p->type);
                    }
                    p = p->next;
                }
                printf("���س�������..."); // ��ʾ�û����س�������
                while (getchar() != '\n')
                    ;
                getchar(); // �ȴ��û����»س���
            }
        }
        break;
        case 2: // ���˿��Ǽ���ѯ���򵥲�ѯ��
        {
            char star[20];
            printf("������˿��Ǽ���vip, svip, normal����");
            scanf("%s", star);

            CustomerList p = customer_list->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û������Ǽ��Ĺ˿�
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
                printf("û�и��Ǽ��Ĺ˿ͣ�\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = customer_list->next;
                // �����ͷ
                printf("%-20s %-20s %-20s\n", "�˿�����", "�˿͵绰", "�˿��Ǽ�");
                while (p != NULL)
                {
                    if (!strcmp(star, p->type))
                    {
                        // ����˿���Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-20s %-20s %-20s\n", p->name, p->contact, p->type);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void purchase_search() // ����purchase_record�����ҵ����вɹ���¼
{
    while (1)
    {
        system("cls"); // ����
        printf("�������ѯ��ʽ��\n");
        printf("0���˳�\n");
        printf("1��������ʱ���ѯ��ģ����ѯ��\n");
        printf("2������������ѯ��ģ����ѯ��\n");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
        {
            printf("������������� 0 - 2 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ������ʱ�������ѯ��ģ����ѯ��
        {
            int min_time, max_time;
            printf("���������ʱ�����䣨�ÿո�ָ�����0��10000�ڵ����������涨˳�򣩣�");
            if (scanf("%d %d", &min_time, &max_time) != 2 || min_time < 0 || min_time > 10000 || max_time < 0 || max_time > 10000)
            {
                printf("������Ч������������0��10000�ڵ���Ч������\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_time �ǽ�Сֵ��max_time �ǽϴ�ֵ
            if (min_time > max_time)
            {
                int temp = min_time;
                min_time = max_time;
                max_time = temp;
            }

            PurchaseList p = purchase_record->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û������ʱ���ڸ�����Ĳɹ���¼
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
                printf("û������ʱ���ڸ�����Ĳɹ���¼��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = purchase_record->next;
                // �����ͷ��ʽid ��� ���� �ۼ� �������� ����ʱ�� ��Ӧ��
                printf("%-8s %-16s %-16s %-10s %-10s %-10s %-20s\n",
                       "id", "���", "����", "�ۼ�", "��������", "����ʱ��", "��Ӧ��");
                while (p != NULL)
                {
                    int current_time = atoi(p->purchase_time);
                    if (current_time >= min_time && current_time <= max_time)
                    {
                        // ����ɹ���¼��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-10.2f %-10d %-10s %-20s\n",
                               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 2: // ����������ѯ��ģ����ѯ��
        {
            int min_quantity, max_quantity;
            printf("��������������䣨�ÿո�ָ������Ǹ����������涨˳�򣩣�");
            if (scanf("%d %d", &min_quantity, &max_quantity) != 2 || min_quantity < 0 || max_quantity < 0)
            {
                printf("������Ч�������������Ǹ�����Ч������\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_quantity �ǽ�Сֵ��max_quantity �ǽϴ�ֵ
            if (min_quantity > max_quantity)
            {
                int temp = min_quantity;
                min_quantity = max_quantity;
                max_quantity = temp;
            }

            PurchaseList p = purchase_record->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û�н������ڸ�����Ĳɹ���¼
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
                printf("û�н������ڸ�����Ĳɹ���¼��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = purchase_record->next;
                // �����ͷ��ʽid ��� ���� �ۼ� �������� ����ʱ�� ��Ӧ��
                printf("%-8s %-16s %-16s %-10s %-10s %-10s %-20s\n", "id",
                       "���", "����", "�ۼ�", "��������", "ʱ��", "��Ӧ��");
                while (p != NULL)
                {
                    if (p->quantity >= min_quantity && p->quantity <= max_quantity)
                    {
                        // ����ɹ���¼��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-8d %-16s %-16s %-10.2f %-10d %-10s %-20s\n",
                               p->id, p->category, p->good_name, p->cost_price, p->quantity, p->purchase_time, p->supplier);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void sale_search() // ����sale_record�����ҵ��������ۼ�¼
{
    while (1)
    {
        system("cls"); // ����
        printf("�������ѯ��ʽ��\n");
        printf("0���˳�\n");
        printf("1��������ʱ�������ѯ��ģ����ѯ��\n");
        printf("2�����������������ѯ��ģ����ѯ��\n");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2)
        {
            printf("������������� 0 - 2 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ������ʱ�������ѯ��ģ����ѯ��
        {
            int min_time, max_time;
            printf("����������ʱ�����䣨�ÿո�ָ�����0��10000�ڵ����������涨˳�򣩣�");
            if (scanf("%d %d", &min_time, &max_time) != 2 || min_time < 0 || min_time > 10000 || max_time < 0 || max_time > 10000)
            {
                printf("������Ч������������0��10000�ڵ���Ч������\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_time �ǽ�Сֵ��max_time �ǽϴ�ֵ
            if (min_time > max_time)
            {
                int temp = min_time;
                min_time = max_time;
                max_time = temp;
            }

            SaleList p = sale_record->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û������ʱ���ڸ���������ۼ�¼
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
                printf("û������ʱ���ڸ���������ۼ�¼��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = sale_record->next;
                // �����ͷ��ʽ id ��Ʒ���� ���۵��� �������� ����ʱ�� �˿�����
                printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "���ۼ�¼id", "��Ʒid", "��Ʒ����", "����ʱ��", "���۵���", "�˿�id");
                while (p != NULL)
                {
                    int current_time = atoi(p->sale_time);
                    if (current_time >= min_time && current_time <= max_time)
                    {
                        // ������ۼ�¼��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-16d %-8d %-20s %-10s %-10.2f %-10d\n",
                               p->sale_id, p->good_id, p->good_name, p->sale_time, p->sale_price, p->customer_id);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        case 2: // ���������������ѯ��ģ����ѯ��
        {
            int min_quantity, max_quantity;
            printf("�����������������䣨�ÿո�ָ������Ǹ����������涨˳�򣩣�");
            if (scanf("%d %d", &min_quantity, &max_quantity) != 2 || min_quantity < 0 || max_quantity < 0)
            {
                printf("������Ч�������������Ǹ�����Ч������\n");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            // ȷ�� min_quantity �ǽ�Сֵ��max_quantity �ǽϴ�ֵ
            if (min_quantity > max_quantity)
            {
                int temp = min_quantity;
                min_quantity = max_quantity;
                max_quantity = temp;
            }

            SaleList p = sale_record->next;
            int found = 0;
            // ��һ��ѭ������ȷ����û�����������ڸ���������ۼ�¼
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
                printf("û�����������ڸ���������ۼ�¼��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                p = sale_record->next;
                // �����ͷ��ʽ id ��Ʒ���� ���۵��� �������� ����ʱ�� �˿�����
                printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "���ۼ�¼id", "��Ʒid", "��Ʒ����", "����ʱ��", "���۵���", "�˿�id");
                while (p != NULL)
                {
                    if (p->quantity >= min_quantity && p->quantity <= max_quantity)
                    {
                        // ������ۼ�¼��Ϣ��ʹ�ø�ʽ�������֤����
                        printf("%-16d %-8d %-20s %-10s %-10.2f %-10d\n",
                               p->sale_id, p->good_id, p->good_name, p->sale_time, p->sale_price, p->customer_id);
                    }
                    p = p->next;
                }
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar();
            }
        }
        break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

// ��������Ľṹ�Ƚ϶���
void search_max_good_sales_in_time_range()
{
    while (1)
    {
        system("cls"); // ����
        int min_time, max_time;
        printf("����������ʱ�����䣨�ÿո�ָ�����0��10000�ڵ����������涨˳������-1 -1�˳�����\n");
        if ((scanf("%d %d", &min_time, &max_time) != 2 || min_time < 0 || min_time > 10000 || max_time < 0 || max_time > 10000 )&& !(min_time == -1 && max_time == -1))
        {
            printf("������Ч������������0��10000�ڵ���Ч���������س�����...\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
            continue;
        }
        if (min_time == -1 && max_time == -1)
            return;
        // ȷ�� min_time �ǽ�Сֵ��max_time �ǽϴ�ֵ
        if (min_time > max_time)
        {
            int temp = min_time;
            min_time = max_time;
            max_time = temp;
        }

        SaleList p = sale_record->next;
        int found = 0;
        // ��һ��ѭ������ȷ����û������ʱ���ڸ���������ۼ�¼
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
            printf("û������ʱ���ڸ���������ۼ�¼��\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }

        else
        {
            p = sale_record->next;
            // �ҵ�����ʱ���ڸ����䣬����������������Ʒ
            // ��һ����ͳ��ÿ����Ʒ������good_name��ͬ���quantity��ӵ�ԭ�򣩵���������
            // ����һ���ṹ�����飬���ڴ洢ÿ����Ʒ����������
            struct GoodSales
            {
                char good_name[50]; // ��Ʒ����
                int quantity;       // ��������
            };
            struct GoodSales good_sales[200]; // ���������200����Ʒ
            int good_sales_count = 0;         // ��¼��Ʒ��������
            while (p != NULL)
            {
                int current_time = atoi(p->sale_time);
                if (current_time >= min_time && current_time <= max_time)
                {
                    // ����good_sales���飬�����Ƿ��Ѿ��и���Ʒ�ļ�¼
                    int i;
                    for (i = 0; i < good_sales_count; i++)
                    {
                        if (strcmp(good_sales[i].good_name, p->good_name) == 0)
                        {
                            good_sales[i].quantity += p->quantity; // �ۼ���������
                            break;
                        }
                    }
                    if (i == good_sales_count) // ���û���ҵ�����Ʒ�ļ�¼�������һ���¼�¼
                    {
                        strcpy(good_sales[good_sales_count].good_name, p->good_name); // ������Ʒ����
                        good_sales[good_sales_count].quantity = p->quantity;          // ��ʼ����������
                        good_sales_count++;                                           // ��Ʒ����������1
                    }
                }
                p = p->next; // ��������
            }
            // �ڶ������ҵ���������������Ʒ
            int max_quantity = 0; // ��¼�����������
            int max_index = 0;    // ��¼���������������Ʒ����
            for (int i = 0; i < good_sales_count; i++)
            {
                if (good_sales[i].quantity > max_quantity) // �����ǰ��Ʒ�������������������������
                {
                    max_quantity = good_sales[i].quantity; // ���������������
                    max_index = i;                         // �������������������Ʒ����
                }
            }
            // ��������������
            printf("����ʱ����%ds��%ds֮�䣬��������������Ʒ�ǣ�%s����������Ϊ��%d\n", min_time, max_time, good_sales[max_index].good_name, max_quantity);
            printf("���س�������...");
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
        system("cls"); // ����
        printf("�������ѯѡ�\n");
        printf("0���˳�\n");
        printf("1��[��Ʒ]��ѯ\n");
        printf("2��[�˿�]��ѯ\n");
        printf("3��[�ɹ���¼]��ѯ\n");
        printf("4��[���ۼ�¼]��ѯ\n");
        printf("5����ѯ[ĳ��ʱ�����������]����Ʒ");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5)
        {
            printf("������������� 0 - 4 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ��Ʒ��ѯ
            good_search();
            break;
        case 2: // �˿Ͳ�ѯ
            customer_search();
            break;
        case 3: // �ɹ���ѯ
            purchase_search();
            break;
        case 4: // ���۲�ѯ
            sale_search();
            break;
        case 5: // ��ѯĳ��ʱ��������������Ʒ
            search_max_good_sales_in_time_range();
            break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

void Salesperson_Search() // �ۻ�Ա��ѯ
{
    while (1)
    {
        system("cls"); // ����
        printf("�������ѯѡ�\n");
        printf("0���˳�\n");
        printf("1����Ʒ��ѯ\n");
        printf("2���˿Ͳ�ѯ\n");
        printf("3�����۲�ѯ\n");
        int choice; // ѡ��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            printf("������������� 0 - 3 ֮���������\n");
            while (getchar() != '\n')
                ;
            getchar(); // ������뻺����
        }
        switch (choice)
        {
        case 0:     // �˳�
            return; // �������˵�
        case 1:     // ��Ʒ��ѯ
            good_search();
            break;
        case 2: // �˿Ͳ�ѯ
            customer_search();
            break;
        case 3: // ���۲�ѯ
            sale_search();
            break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}