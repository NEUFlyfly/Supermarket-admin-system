#include "salesperson.h"
#include "sale.h"
#include "goods.h"
#include "purchase.h"
#include "customer.h"
#include "system.h"
#include "admin.h"
#include "search.h"
#include "sort.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern AllGoodList all_good_list;
extern SaleList sale_record;
extern PurchaseList purchase_record;
extern CustomerList customer_list;

// ������Ʒ
void Sale_To_Customer(int customer_id, char *good_name, int quantity)
{
    // ����good_nameӦ���Ƕ�Ӧall_good_list�е��ĸ��ڵ�
    // �ڵ���ѡ��ԭ����ѡȡ����good_name��ͬ��quntity�㹻��price��ߵĽڵ�
    AllGoodList p = all_good_list->next;
    AllGoodList best_good = NULL;
    int found_good = 0; // ����Ƿ��ҵ���Ʒ
    while (p != NULL)   // ����all_good_list���ҵ�����good_name��ͬ��quntity�㹻���ۼ���ߵĽڵ�
    {
        if (strcmp(p->good_name, good_name) == 0)
        {
            found_good = 1; // �ҵ���Ʒ
            if (p->stock >= quantity)
            {
                // ����is_promotion��־ȷ���ۼ�
                float current_price = p->is_promotion ? p->promotion_price : p->price;
                float best_price = best_good != NULL ? (best_good->is_promotion ? best_good->promotion_price : best_good->price) : 0;

                if (best_good == NULL || current_price > best_price)
                {
                    best_good = p;
                }
            }
        }
        p = p->next;
    }
    if (!found_good)
    {
        printf("û���ҵ�����Ʒ��\n");
        return; // û���ҵ�����Ʒ��ֱ�ӷ���
    }
    if (!best_good)
    {
        printf("��Ʒ��治�㣡\n");
        return; // ��Ʒ��治�㣬ֱ�ӷ���
    }
    Sale(customer_id, best_good->id, quantity); // ����Sale��������best_good��id��quantity����
}

// �޸����ۼ�¼������sale_record�����ñ�������*
void Salesperson_Modify_Sale()
{
    while (1)
    {
        system("cls"); // ����

        printf("���ۼ�¼����\n");
        printf("������ѡ��\n");
        printf("0���˳�\n");
        printf("1���޸����ۼ�¼\n");
        printf("2��ɾ�����ۼ�¼\n");
        printf("3��������ۼ�¼\n");

        int choice;
        // ����ѡ�񼰼��
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            while (getchar() != '\n')
                ; // ������뻺����
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;          // �ȴ��û����»س���
            system("cls"); // ����
            printf("���ۼ�¼����\n");
            printf("������ѡ��\n");
            printf("0���˳�\n");
            printf("1���޸����ۼ�¼\n");
            printf("2��ɾ�����ۼ�¼\n");
            printf("3��������ۼ�¼\n");
        }
        if (choice == 0) // �˳�
            break;       // ֱ�ӷ��أ���ִ�к���Ĵ���
        switch (choice)
        {
        case 1: // �޸����ۼ�¼
            while (1)
            {
                system("cls");                 // ����
                Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                printf("���е����ۼ�¼���ϣ����������ۼ�¼id������ࣩ������#�˳���\n");
                int sale_id;                 // ���ۼ�¼id
                char input[20];              // ������ַ���
                scanf("%s", input);          // �������ۼ�¼id��#
                if (strcmp(input, "#") == 0) // �������#�����˳�
                    break;                   // �˳�ѭ��
                sale_id = atoi(input);       // ��������ַ���ת��Ϊ����

                SaleList p = sale_record->next;            // ָ�����ۼ�¼����ĵ�һ���ڵ�
                while (p != NULL && p->sale_id != sale_id) // �������ۼ�¼�����ҵ����ۼ�¼id��Ӧ�Ľڵ�
                    p = p->next;
                if (p == NULL) // û���ҵ����ۼ�¼id��Ӧ�Ľڵ�
                {
                    printf("û���ҵ������ۼ�¼��\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    getchar(); // ������뻺����
                    continue;  // ����ѭ��
                }
                else // �ҵ������ۼ�¼id��Ӧ�Ľڵ�
                {
                    printf("�������µ����ۼ�¼��Ϣ\n");
                    char new_good_name[20]; // �µ���Ʒ����
                    float new_sale_price;   // �µ�ʵ�����۵���
                    char new_sale_time[20]; // �µ�����ʱ��
                    int new_quantity;       // �µ���������
                    int new_customer_name;  // �µĹ˿�����
                    printf("�������µ���Ʒ���ƣ�");
                    scanf("%s", new_good_name); // �����µ���Ʒ����
                    printf("�������µ�ʵ�����۵��ۣ�");
                    scanf("%f", &new_sale_price); // �����µ�ʵ�����۵���
                    printf("�������µ�����ʱ�䣺");
                    scanf("%s", new_sale_time); // �����µ�����ʱ��
                    printf("�������µ�����������");
                    scanf("%d", &new_quantity); // �����µ���������
                    printf("�������µĹ˿�������");
                    scanf("%d", &new_customer_name); // �����µĹ˿�����
                    // �޸����ۼ�¼��Ϣ

                    strcpy(p->good_name, new_good_name); // �޸���Ʒ����
                    p->sale_price = new_sale_price;      // �޸�ʵ�����۵���
                    strcpy(p->sale_time, new_sale_time); // �޸�����ʱ��
                    p->quantity = new_quantity;          // �޸���������
                    p->customer_id = new_customer_name;  // �޸Ĺ˿�����

                    system("cls");                 // ����
                    Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                    printf("�޸ĳɹ���\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س���
                    getchar(); // ������뻺����
                }
            }
            break;
        case 2: // ɾ�����ۼ�¼
            while (1)
            {
                system("cls");                 // ����
                Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                printf("���е����ۼ�¼���ϣ����������ۼ�¼id������ࣩ������#�˳���\n");
                int sale_id;                 // ���ۼ�¼id
                char input[20];              // ������ַ���
                scanf("%s", input);          // �������ۼ�¼id��#
                if (strcmp(input, "#") == 0) // �������#�����˳�
                    break;                   // �˳�ѭ��
                sale_id = atoi(input);       // ��������ַ���ת��Ϊ����

                SaleList p = sale_record->next;            // ָ�����ۼ�¼����ĵ�һ���ڵ�
                while (p != NULL && p->sale_id != sale_id) // �������ۼ�¼�����ҵ����ۼ�¼id��Ӧ�Ľڵ�
                    p = p->next;
                if (p == NULL) // û���ҵ����ۼ�¼id��Ӧ�Ľڵ�
                {
                    printf("û���ҵ������ۼ�¼��\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    getchar(); // ������뻺����
                    continue;  // ����ѭ��
                }
                else // �ҵ������ۼ�¼id��Ӧ�Ľڵ㣬ɾ���ýڵ�
                {
                    SaleList q = sale_record; // ָ�����ۼ�¼�����ͷ�ڵ�
                    while (q->next != p)      // �������ۼ�¼�����ҵ����ۼ�¼id��Ӧ�Ľڵ��ǰһ���ڵ�
                        q = q->next;
                    q->next = p->next; // ɾ�����ۼ�¼id��Ӧ�Ľڵ�
                    free(p);           // �ͷ��ڴ�

                    system("cls");                 // ����
                    Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                    printf("ɾ���ɹ���\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س���
                    getchar(); // ������뻺����
                }
            }
            break;

        case 3: // ������ۼ�¼
            while (1)
            {
                system("cls");                 // ����
                Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                printf("���е����ۼ�¼���ϣ������������ۼ�¼����Ϣ������#�˳������������ַ�������\n");

                char input[20];              // ������ַ���
                scanf("%s", input);          // ���� # ��ʼ������Ϣ
                if (strcmp(input, "#") == 0) // �������#�����˳�
                    break;                   // �˳�ѭ��

                int sale_id = sale_record->next->sale_id + 1; // �����ۼ�¼�� id

                char new_good_name[20]; // �µ���Ʒ����
                float new_sale_price;   // �µ�ʵ�����۵���
                char new_sale_time[20]; // �µ�����ʱ��
                int new_quantity;       // �µ���������
                int new_customer_id;    // �µĹ˿� id
                int new_good_id;        // �µ���Ʒ id
                // ��Ϊǰ���Ѿ�������һ���ַ�����������Ҫ�����������
                printf("�������µ���Ʒ���ƣ�");
                scanf("%s", new_good_name);
                printf("�������µ���Ʒid��");
                scanf("%d", &new_good_id);
                printf("�������µ�ʵ�����۵��ۣ�");
                scanf("%f", &new_sale_price); // �����µ�ʵ�����۵���
                printf("�������µ�����ʱ�䣺");
                scanf("%s", new_sale_time); // �����µ�����ʱ��
                printf("�������µ�����������");
                scanf("%d", &new_quantity); // �����µ���������
                printf("�������µĹ˿� id��");
                scanf("%d", &new_customer_id); // �����µĹ˿� id

                // �����µ����ۼ�¼�ڵ�
                SaleNode new_sale;
                new_sale.sale_id = sale_id;
                strcpy(new_sale.good_name, new_good_name);
                new_sale.sale_price = new_sale_price;
                strcpy(new_sale.sale_time, new_sale_time);
                new_sale.quantity = new_quantity;
                new_sale.customer_id = new_customer_id;
                new_sale.good_id = new_good_id;

                // ���� Insert_Salelist ��������½ڵ㵽����
                Insert_SaleList(&sale_record, new_sale);

                system("cls");                 // ����
                Print_SaleRecord(sale_record); // ��ӡ���ۼ�¼
                printf("��ӳɹ������ڼ�¼�����Ϸ���������鿴��\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;      // �ȴ��û����»س���
                getchar(); // ������뻺����
            }
            break;
        }
    }
}

// ��ʾ�˿���ĳһ��ʱ���ڵĹ������
void Caculate_Customer_Shopping_Amount()
{
    while (1)
    {
        system("cls"); // ����

        printf("������ѡ��\n0���˳�\n1���鿴ĳһ�˿���ĳһ��ʱ���ڵĹ������\n");
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 1)
        {
            while (getchar() != '\n')
                ; // ������뻺����
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;          // �ȴ��û����»س���
            system("cls"); // ����
            printf("������ѡ��\n0���˳�\n1���鿴ĳһ�˿���ĳһ��ʱ���ڵĹ������\n");
        }
        if (choice == 0)      // �˳�
            break;            // ֱ�ӷ��أ���ִ�к���Ĵ���
        else if (choice == 1) // �鿴ĳһ�˿���ĳһ��ʱ���ڵĹ������
        {
            Print_CustomerList(customer_list); // ��ӡ�˿���Ϣ
            printf("���еĹ˿���Ϣ���ϣ���Ҫ�鿴˭�ģ�������˿�id��\n");
            int customer_id;
            scanf("%d", &customer_id);                    // ����˿�id
            CustomerList ptr = customer_list->next;       // ָ��˿���Ϣ����ĵ�һ���ڵ�
            while (ptr != NULL && ptr->id != customer_id) // �����˿���Ϣ�����ҵ��˿�id��Ӧ�Ľڵ�
                ptr = ptr->next;
            if (ptr == NULL) // û���ҵ��˿�id��Ӧ�Ľڵ�
            {
                printf("û���ҵ��ù˿ͣ�\n");
                printf("���س�������...");
                while (getchar() != '\n')
                    ;
                getchar(); // ������뻺����
                break;
            }
            else // �ҵ��˹˿�id��Ӧ�Ľڵ�
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
                    printf("�ù˿�û������ʱ���ڸ���������ۼ�¼��\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    getchar();
                }
                else
                {
                    printf("�ù˿��ڸ�ʱ�������ڵ����ۼ�¼���£�\n\n");
                    p = sale_record->next;
                    // �����ͷ��ʽ id ��Ʒ���� ���۵��� �������� ����ʱ�� �˿�����
                    printf("%-16s %-8s %-20s %-10s %-10s %-10s\n", "���ۼ�¼id", "��Ʒid", "��Ʒ����", "����ʱ��", "���۵���", "�˿�id");
                    while (p != NULL)
                    {
                        int current_time = atoi(p->sale_time);
                        if (current_time >= min_time && current_time <= max_time && p->customer_id == ptr->id)
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
        }
    }
}
void SalesPerson(char *username)
{
    while (1)
    {
        int length = 0;
        CustomerList ptr = customer_list->next; // ָ��customer_list�ĵ�һ���ڵ�
        AllGoodList qtr = all_good_list->next;  // ָ��all_good_list�ĵ�һ���ڵ�

        system("cls");
        // ��ӡ��ǰʱ��
        char current_time[20];
        GetCurrentTime(current_time);
        printf("��ǰʱ�䣺%ss\n", current_time);

        printf("���ۻ�Ա����ã�\n");
        printf("������ѡ��\n");
        printf("0���˳�\n");
        printf("1�����ӹ˿���Ϣ\n");
        printf("2���˿���Ϣͳ��\n");
        printf("3����Ʒ��Ϣͳ��\n");
        printf("4������\n");
        printf("5����ѯ\n");
        printf("6������\n");
        printf("7�����ۼ�¼����\n");
        printf("8���޸��Լ�������\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:     // �˳�
            return; // ֱ�ӷ��أ���ִ�к���Ĵ���
            break;
        case 1:
            system("cls");
            int choice4;
            printf("������ѡ�񣺣�0���˳���1���ֶ�����˿���Ϣ��2�����ļ�����˿���Ϣ�����ַ�����ͬʱʹ�ã���\n");
            scanf("%d", &choice4);
            if (choice4 == 1) // �ֶ�����˿���Ϣ
                Add_Customer_To_System();
            else if (choice4 == 0)
                break;
            else if (choice4 == 2) // ���ļ�����˿���Ϣ
            {
                FILE *fp = fopen("txt/CustomerSource.txt", "r");
                if (fp == NULL)
                {
                    printf("�ļ���ʧ�ܣ�\n");
                    break; // ���ļ�ʧ�ܣ��˳�ѭ��
                }
                char name[20], contact[20], type[50];
                int customer_id;
                int temp = 1;
                while (fscanf(fp, "%19s %19s %49s", name, type, contact) != EOF)
                {
                    CustomerNode customer;
                    customer.id = temp++;
                    strcpy(customer.name, name);
                    strcpy(customer.contact, contact);
                    strcpy(customer.type, type);
                    Insert_CustomerList(&customer_list, customer);
                }
                // �ر��ļ�
                fclose(fp);
                // ���ɹ˿���Ϣ�ļ�
                Create_CustomerInfo_File();
                printf("�˿���Ϣ����ɹ�\n");
                printf("���س�������...\n");
                while (getchar() != '\n')
                    ;      // ������뻺����
                getchar(); // �ȴ��û����»س���
            }
            break;
        case 2: // �˿���Ϣͳ��
            Caculate_Customer_Shopping_Amount();
            break;
        case 3: // ��Ʒ��Ϣͳ��
            while (1)
            {
                system("cls");
                printf("������ѡ�񣺣�0���˳���1���鿴ĳһ�����Ʒ������2���鿴������Ʒ��棩\n");
                int choice3;

                while (scanf("%d", &choice3) != 1 || choice3 < 0 || choice3 > 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("������ѡ�񣺣�0���˳���1���鿴ĳһ�����Ʒ������2���鿴������Ʒ��棩\n");
                }
                if (choice3 == 0)
                    break; // �˳�ѭ��
                switch (choice3)
                {
                case 0: // �˳�
                    break;
                case 1: // �鿴ĳһ�����Ʒ����
                    Caculate_Category_Stock();
                    break;
                case 2: // �鿴������Ʒ���
                    Print_AllGoodList(all_good_list);
                    break;
                }
            }
            break;
        case 4: // ����
            while (1)
            {
                system("cls");
                char good_name[50];
                int quantity;
                int customer_id;
                Print_CustomerList(customer_list);
                printf("�˿���Ϣ���ϣ����ο�\n");

                printf("������ѡ��\n");
                printf("0���˳�\n");
                printf("1���ֶ�������Ʒ\n");
                printf("2��ģ�����ۣ�ֱ������ģ������ۼ�¼��\n");
                int choice5;
                // ����ѡ�񼰼��
                while (scanf("%d", &choice5) != 1 || choice5 < 0 || choice5 > 2)
                {
                    while (getchar() != '\n')
                        ; // ������뻺����
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;          // �ȴ��û����»س���
                    system("cls"); // ����
                    Print_CustomerList(customer_list);
                    printf("�˿���Ϣ���ϣ����ο�\n");
                    printf("������ѡ��\n");
                    printf("0���˳�\n");
                    printf("1���ֶ�������Ʒ\n");
                    printf("2���������ۣ�ֱ������ģ������ۼ�¼��\n");
                }

                if (choice5 == 0) // �˳�
                    break;        // ֱ�ӷ��أ���ִ�к���Ĵ���
                switch (choice5)
                {
                case 1: // �ֶ�������Ʒ
                    while (1)
                    {
                        printf("������˿�id������'#'�˳�����");
                        char id_str[10];
                        scanf("%s", id_str);
                        if (strcmp(id_str, "#") == 0)
                            break;                  // ����'#'����ѭ��
                        customer_id = atoi(id_str); // ������ת��Ϊ����
                        if (customer_id <= 0)
                        {
                            printf("��Ч�Ĺ˿�id�����������룡\n");
                            continue; // ��Ч�Ĺ˿�id������ѭ��
                        }
                        printf("��������Ʒ���ƣ�");
                        scanf("%49s", good_name);
                        printf("����������������");
                        scanf("%d", &quantity);
                        // �������ۺ��������˿�id����Ʒ���ƺ������������ݸ�ϵͳ
                        Sale_To_Customer(customer_id, good_name, quantity);
                        printf("���س�������...");
                        while (getchar() != '\n')
                            ;
                        // �ȴ��û����»س�
                        getchar(); // �������Ļ��з�
                    }

                    break;
                case 2: // ��������
                    // ��һ����ͳ��customer_list��all_good_list�ĳ��ȣ��ҵ����̵��Ǹ�����Ϊlength

                    ptr = customer_list->next;         // ָ��customer_list�ĵ�һ���ڵ�
                    qtr = all_good_list->next;         // ָ��all_good_list�ĵ�һ���ڵ�
                    while (ptr != NULL || qtr != NULL) // �������������ҵ����ȸ��̵��Ǹ�
                    {
                        if (ptr != NULL)
                            ptr = ptr->next; // ����customer_list
                        if (qtr != NULL)
                            qtr = qtr->next; // ����all_good_list
                        length++;            // ���ȼ�1
                    }
                    // �ڶ�������customer_list��all_good_list��ѡ��ǰlength���˿ͺ���Ʒ��ֱ�ӵ���Sale_To_Customer����
                    ptr = customer_list->next;       // ָ��customer_list�ĵ�һ���ڵ�
                    qtr = all_good_list->next;       // ָ��all_good_list�ĵ�һ���ڵ�
                    for (int i = 0; i < length; i++) // ����ǰlength���˿ͺ���Ʒ
                    {
                        if (ptr != NULL) // ���customer_list���нڵ�
                        {
                            customer_id = ptr->id; // ��ȡ�˿�id
                            ptr = ptr->next;       // ����customer_list
                        }
                        if (qtr != NULL) // ���all_good_list���нڵ�
                        {
                            strcpy(good_name, qtr->good_name); // ��ȡ��Ʒ����
                            qtr = qtr->next;                   // ����all_good_list
                        }
                        quantity = rand() % 10 + 1; // �������������������ΧΪ1��10
                        // �������ۺ��������˿�id����Ʒ���ƺ������������ݸ�ϵͳ
                        Sale_To_Customer(customer_id, good_name, quantity);
                    }
                    printf("���۳ɹ������س�����...\n");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                    break;
                }
            }
            break;
        case 5: // ��ѯ
            Salesperson_Search();
            break;
        case 6: // ����
            Salesperson_Sort();
            break;
        case 7: // ���ۼ�¼����
            while (1)
            {
                system("cls");
                int choice2;
                printf("������ѡ��\n0���˳�\n1���鿴���ۼ�¼\n2�����ۼ�¼����\n");
                scanf("%d", &choice2);

                if (choice2 == 0)
                    break; // �˳�

                else if (choice2 == 1) // ��ӡsaleInfo.txt������
                {
                    system("cls");
                    Print_SaleRecord(sale_record);
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                else if (choice2 == 2) // �޸Ľ�����¼
                {
                    // �������ļ����޸Ķ���Ӱ����ʵ�Ŀ��״̬���ñ�������
                    Salesperson_Modify_Sale();
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                else
                    printf("��Ч��ѡ�����������룡\n");
            }
            break;
        case 8:            // �޸��Լ�������
            system("cls"); // ����
            printf("�����������룺");
            char new_password[100];                            // �洢������
            scanf("%s", new_password);                         // ����������
            FILE *fp = fopen("txt/salespersonLogin.txt", "r"); // ���ļ���ֻ��ģʽ
            if (fp == NULL)
            {
                printf("�ļ���ʧ�ܣ�\n"); // ���ļ�ʧ�ܣ���ʾ
                break;
            }
            // ��ȡ�������ݵ��ڴ�
            char lines[100][200];
            int line_count = 0;
            while (fgets(lines[line_count], sizeof(lines[line_count]), fp) != NULL)
            {
                line_count++;
            }
            fclose(fp);

            // ���Ҳ��滻����
            for (int i = 0; i < line_count; i++)
            {
                char username1[100], password[100];
                if (sscanf(lines[i], "%s %s", username1, password) == 2)
                {
                    if (strcmp(username, username1) == 0)
                    {
                        // �滻����
                        snprintf(lines[i], sizeof(lines[i]), "%s %s\n", username1, new_password);
                        break;
                    }
                }
            }

            // д���ļ�
            fp = fopen("txt/salespersonLogin.txt", "w"); // ���ļ���д��ģʽ
            if (fp == NULL)
            {
                printf("�ļ���ʧ�ܣ�\n"); // ���ļ�ʧ�ܣ���ʾ
                break;
            }
            for (int i = 0; i < line_count; i++)
            {
                fputs(lines[i], fp);
            }
            fclose(fp);
            printf("�����޸ĳɹ���\n"); // �����޸ĳɹ�����ʾ
            printf("���س�������...");
            while (getchar() != '\n')
                ;      // �ȴ��û����»س�
            getchar(); // �������Ļ��з�
            break;
        default: // �����������ʾ�������
            printf("����������������룡\n");
            printf("���س�������...");
            while (getchar() != '\n')
                ;
            getchar();
            break;
        }
    }
}

char input_salesperson_name[100];
int salesperson_login()
{
    system("cls");

    char input_password[100];

    // ��ȡ�ļ��е����ݣ��洢��������ά������
    char usernames[100][100]; // �洢�û���
    char passwords[100][100]; // �洢����
    int count = 0;            // ��¼��ȡ������

    FILE *fp = fopen("txt/salespersonLogin.txt", "r"); // ���ļ���ֻ��ģʽ
    if (fp == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        return 0; // ���ļ�ʧ�ܣ�����0
    }
    // ���ж�ȡ�ļ����ݣ��洢��������
    while (fscanf(fp, "%s %s", usernames[count], passwords[count]) != EOF)
        count++; // ������1
    fclose(fp);  // �ر��ļ�

    // ��ʾ�û������û���������
    printf("������������Ա�û�����");
    scanf("%s", input_salesperson_name); // �����û���
    printf("������������Ա���룺");
    scanf("%s", input_password); // ��������

    // ���������û����������Ƿ���������ά����ƥ��
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_salesperson_name, usernames[i]) == 0 && strcmp(input_password, passwords[i]) == 0)
        {
            printf("������Ա��¼�ɹ���\n"); // ��¼�ɹ�
            printf("���س�������...\n");
            while (getchar() != '\n')
                ;      // ������뻺����
            getchar(); // �ȴ��û����»س���
            return 1;  // ����1
        }
    }
    printf("������Ա��¼ʧ�ܣ��û������������\n"); // ��¼ʧ��
    printf("���س�������...\n");
    while (getchar() != '\n')
        ;      // ������뻺����
    getchar(); // �ȴ��û����»س���
    return 0;  // ����0
}
