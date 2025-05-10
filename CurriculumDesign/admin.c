#include "admin.h"
#include "goods.h"
#include "purchase.h"
#include "customer.h"
#include "stdlib.h"
#include "system.h"
#include "math.h"
#include "search.h"
#include "sale.h"
#include "sort.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

extern AllGoodList all_good_list;
extern PurchaseList purchase_record;
extern CustomerList customer_list;

static int good_id_counter = 1;     // �����Զ�������Ʒ��ţ���ʼֵΪ1
static int purchase_id_counter = 1; // �����Զ����ɽ�����¼��ţ���ʼֵΪ1
static int first_time = 1; // �����ж��Ƿ��һ�ε���Purchase����������ǵ�һ�ε��ã������purchaseInfo.txt�ļ�


void ResetAdmin()
{
    good_id_counter = 1;
    purchase_id_counter = 1;
    first_time = 1;
}

// ��������

/// ��������
// ��������Ʒ��Ϣ
void Purchase(char *category, char *good_name, float cost_price, int quantity, char *supplier)
{

    if (first_time)
    {
        FILE *fp = fopen("txt/purchaseInfo.txt", "w");
        if (fp == NULL)
        {
            printf("�ļ���ʧ�ܣ�\n");
            exit(1);
        }
        fclose(fp);
        first_time = 0; // ����Ϊ0����ʾ�Ѿ���չ��ļ�
    }

    char current_time[10];
    GetCurrentTime(current_time);

    // 1. �����µĽ�����¼
    PurchaseNode purchase;
    strcpy(purchase.good_name, good_name);
    strcpy(purchase.purchase_time, current_time); // �޸�Ϊʹ��purchase_time
    strcpy(purchase.supplier, supplier);
    strcpy(purchase.category, category);
    purchase.id = purchase_id_counter++;
    purchase.quantity = quantity;
    purchase.cost_price = cost_price;
    Insert_PurchaseList(&purchase_record, purchase);

    // 2. ������Ʒ���
    // ������Ʒ�Ƿ��Ѿ����ڣ������������¿�棬���򴴽��µ���Ʒ�ڵ�
    GoodNode *p = all_good_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good_name, good_name) == 0 && strcmp(p->category, category) == 0 && strcmp(p->manufacturer, supplier) == 0 && p->price == cost_price)
        {
            p->stock += quantity; // ���¿��
            break;
        }
        p = p->next;
    }
    if (p == NULL) // �����Ʒ�����ڣ��򴴽��µ���Ʒ�ڵ�
    {
        GoodNode new_good;
        strcpy(new_good.good_name, good_name);
        strcpy(new_good.category, category);
        strcpy(new_good.manufacturer, supplier);
        new_good.price = cost_price;
        new_good.stock = quantity;
        new_good.is_promotion = 0; // Ĭ�ϲ�����
        new_good.promotion_price = 0;
        new_good.id = good_id_counter++; // ������Ʒ���
        Insert_AllGoodList(&all_good_list, new_good);
    }
    // 3. ���������־��purchaseInfo.txt����ʽ����Ʒ��� ��Ʒ���� �������� �������� ʵ��ʱ�� ��Ӧ������
    // ��ȡ��ǰʱ�䲢��ʽ��Ϊ�ַ���

    FILE *fp = fopen("txt/purchaseInfo.txt", "a");
    if (fp == NULL)
    {
        perror("�ļ���ʧ��");
        return;
    }
    // ��ʽ����Ʒid ��Ʒ��� ��Ʒ���� �������� �������� ʵ��ʱ�� ��Ӧ������
    fprintf(fp, "%d %s %s %.2f %d %s %s\n", purchase.id, purchase.category, purchase.good_name,
            purchase.cost_price, purchase.quantity, current_time, purchase.supplier);
    fclose(fp);
}

// ɾ��ָ����Ʒ�Ľ�����¼
// �����ɾ����ָ��txt�ļ�����ɾ��ָ����Ʒ���ƵĽ�����¼��������ɾ����Ʒ����Ҳ���Ǵ�������ɾ��
void Delete_PurchaseRecord(int id)
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "r+");
    if (fp == NULL)
    {
        perror("�ļ���ʧ��");
        return;
    }

    FILE *temp_fp = fopen("txt/temp.txt", "w");
    if (temp_fp == NULL)
    {
        perror("��ʱ�ļ���ʧ��");
        fclose(fp);
        return;
    }

    char line[256];
    int found = 0; // ����Ƿ��ҵ�Ҫɾ������Ʒ���
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int current_id;
        // �����н�������һ��������Ϊ��Ʒ���
        if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
        {
            found = 1; // �ҵ�Ҫɾ������Ʒ��ţ���������
            continue;
        }
        // �����ǰ�в�����Ҫɾ������Ʒ��ţ���д����ʱ�ļ�
        fputs(line, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    // ����ҵ�Ҫɾ������Ʒ��ţ����滻ԭ�ļ�
    if (found)
    {
        remove("txt/purchaseInfo.txt");                 // ɾ��ԭ�ļ�
        rename("txt/temp.txt", "txt/purchaseInfo.txt"); // ��������ʱ�ļ�Ϊԭ�ļ���
    }
    else
    {
        remove("txt/temp.txt"); // ɾ����ʱ�ļ�
        printf("δ�ҵ�����Ʒ��ŵĽ�����¼��\n");
    }
}

// ����һ����Ʒ�Ľ�����¼
// �����������ָ��txt�ļ������ӽ�����¼��������������Ʒ����idΪ0����¶����
// ��ʽ����Ʒid ��Ʒ��� ��Ʒ���� �������� �������� ʵ��ʱ�� ��Ӧ������
void Add_PurchaseRecord(char *category, char *good_name, float cost_price, int quantity, char *supplier)
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "a");
    if (fp == NULL)
    {
        perror("�ļ���ʧ��");
        return;
    }

    char current_time[9];
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    snprintf(current_time, sizeof(current_time), "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);

    // ��Ʒ������Ϣ��������Ʒ��š���Ʒ���ơ�����ʱ�䡢�����۸񡢽���������������Դ��
    // ������� id Ϊ 0 ��ʾ�����������ע�����ᵽ�ı�¶���ˣ�
    fprintf(fp, "0 %s %s %.2f %d %s\n", good_name, current_time, cost_price, quantity, supplier);
    fclose(fp);
}

// ����˿���Ϣ
void CustomerInfo_Generate()
{
    char name[50], type[20], contact[50]; // ʹ���������δ��ʼ����ָ��

    // ѭ������˿���Ϣ������'#'��������
    while (1)
    {
        CustomerNode customer;
        printf("������˿�����������'#'��������");
        scanf("%49s", name); // �������볤�ȣ����⻺�������
        if (strcmp(name, "#") == 0)
        {
            break; // ����'#'����ѭ��
        }
        while (1)
        {
            printf("������˿����ͣ�normal vip svip����");
            scanf("%19s", type); // �������볤��
            if (strcmp(type, "normal") == 0 || strcmp(type, "vip") == 0 || strcmp(type, "svip") == 0)
                break; // ����Ϸ����˳�ѭ��
            else
                printf("����Ĺ˿�������Ч�����������룡\n");
        }
        printf("������˿���ϵ��ʽ��");
        scanf("%49s", contact); // �������볤��
        printf("�˿���Ϣ����ӵ�ϵͳ��\n\n");
        strcpy(customer.name, name);
        strcpy(customer.type, type);
        strcpy(customer.contact, contact);
        Insert_CustomerList(&customer_list, customer);
    }
    // ���ɹ˿���Ϣ�ļ�
    Create_CustomerInfo_File();
}

void Create_CustomerInfo_File()
{
    // ������ļ�
    FILE *fp = fopen("txt/customerInfo.txt", "w");
    if (fp == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(1);
    }
    fclose(fp);

    // ����customer_list��˳��д���ļ�
    CustomerNode *p = customer_list->next;
    FILE *fp1 = fopen("txt/customerInfo.txt", "a");
    if (fp1 == NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(1);
    }

    while (p != NULL)
    {
        // ȷ����ϵ��ʽ�ַ����� '\0' ��β
        size_t len = strlen(p->contact);
        if (len > 0 && p->contact[len - 1] == '\n')
        {
            p->contact[len - 1] = '\0';
        }
        fprintf(fp1, "%d %s %s %s\n", p->id, p->name, p->type, p->contact);
        p = p->next;
    }

    fclose(fp1);
    printf("�˿���Ϣ�Ѹ���\n");
}

void Add_Customer_To_System()
{
    system("cls");
    printf("��������ӵĹ˿���Ϣ��\n");
    CustomerInfo_Generate();
}

void Delete_Customer_From_System()
{

    while (1)
    {

        Print_CustomerList(customer_list);
        printf("�Ѵ洢�Ĺ˿���Ϣ���ϣ����ο�\n");
        int id;
        printf("������Ҫɾ���Ĺ˿ͱ�ţ�����'#'�˳�ɾ������");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // �˳�ɾ��ģʽ
        }
        id = atoi(input); // ������ת��Ϊ����
        if (Delete_CustomerList(&customer_list, id) == 1)
        {
            printf("�˿���Ϣ��ɾ����\n\n");
        }
        else
            printf("����������\n\n");
    }
    Create_CustomerInfo_File();
}

void Adjust_Customer_Type()
{

    while (1)
    {
        int id;
        char new_type[30];
        printf("������Ҫ�޸ĵĹ˿�id������'#'�˳���������");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // �˳�����ģʽ
        }
        id = atoi(input); // ������ת��Ϊ����
        CustomerNode *p = customer_list->next;
        while (p != NULL && p->id != id)
        {
            p = p->next;
        }
        if (p == NULL)
        {
            printf("δ�ҵ��ù˿ͣ�\n");
            continue;
        }

        printf("�������µĹ˿����ͣ�normal vip svip����");
        scanf("%s", new_type);
        strcpy(p->type, new_type);

        printf("�˿��������޸ģ�\n\n");
    }
    Create_CustomerInfo_File();
}

// ��all_good_list��ɾ����Ʒ��Ϣ
void Delete_Good_From_System()
{
    while (1)
    {
        system("cls");
        char input[100];
        int id;
        Print_AllGoodList(all_good_list);
        printf("���µ�������Ʒ��Ϣ������ʾ�����ο���\n");
        printf("������Ҫɾ������ƷID������ '#' �˳�����");
        scanf("%s", input);
        // �������뻺����
        while (getchar() != '\n')
            ;

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("�������ƷID��Ч�����������롣\n");
            continue;
        }

        // ���� Delete_GoodList ����ɾ����Ʒ
        if (Delete_AllGoodList(&all_good_list, id))
        {
            printf("��ƷIDΪ %d ����Ʒ�ѳɹ�ɾ����\n", id);
        }
        else
        {
            printf("δ�ҵ���ƷIDΪ %d ����Ʒ�����������롣\n", id);
        }
        printf("���س�������...");
        while (getchar() != '\n')
            ;
        getchar();
    }
}

// ������Ʒ�ۼ�
void Set_Good_Price()
{
    while (1)
    {
        char input[100];
        int id;
        float new_price;

        printf("������Ҫ�޸��ۼ۵���ƷID������ '#' �˳�����");
        scanf("%s", input);
        // �������뻺����
        while (getchar() != '\n')
            ;

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("�������ƷID��Ч�����������롣\n");
            continue;
        }

        printf("�������µ���Ʒ�ۼۣ�");
        if (scanf("%f", &new_price) != 1)
        {
            printf("������ۼ���Ч�����������롣\n");
            // �������뻺����
            while (getchar() != '\n')
                ;
            continue;
        }
        // �������뻺����
        while (getchar() != '\n')
            ;

        // ������Ʒ�������ۼ�
        GoodNode *p = all_good_list->next;
        while (p != NULL)
        {
            if (p->id == id)
            {
                p->price = new_price;
                printf("��ƷIDΪ %d ����Ʒ�ۼ��Ѹ���Ϊ %.2f��\n", id, new_price);
                break;
            }
            p = p->next;
        }
        if (p == NULL)
        {
            printf("δ�ҵ���ƷIDΪ %d ����Ʒ�����������롣\n", id);
        }
    }
}

// ������Ʒ������Ϣ
void Set_Good_Promotion_Info()
{
    // ����ʾ������Ʒ��Ϣ
    Print_AllGoodList(all_good_list);
    printf("���е�������Ʒ��Ϣ������ʾ�����ο���\n");
    // ѭ����������#�˳�
    while (1)
    {
        int id;
        printf("������Ҫ���ô�����Ϣ����Ʒid������'#'�˳�����");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // �˳����ô�����Ϣģʽ
        }
        id = atoi(input); // ������ת��Ϊ����
        // �ҵ�id��Ӧ����Ʒ
        GoodNode *p = all_good_list->next;
        while (p != NULL && p->id != id)
        {
            p = p->next;
        }
        if (p == NULL)
        {
            printf("δ�ҵ�����Ʒ��\n");
            continue;
        }
        // �ҵ���Ʒ�����ô�����Ϣ
        char promotion_info[20];
        printf("�������Ƿ������1����Ϊ������0����Ϊ��������");
        int is_promotion;
        scanf("%d", &is_promotion);
        if (is_promotion == 1)
        {
            p->is_promotion = 1; // ����Ϊ����
            printf("�����������������������0.8��ʾ��8�ۣ���");
            float promotion_rate;
            scanf("%f", &promotion_rate);
            p->promotion_price = p->price * promotion_rate;       // ��������۸�
            sprintf(promotion_info, "%.2f", promotion_rate * 10); // ����һλС��
            strcat(promotion_info, "��");                         // ����ۺ�
        }
        else
        {
            p->is_promotion = 0;              // ����Ϊ������
            p->promotion_price = 0.0;         // �����۸�Ϊ0
            strcpy(promotion_info, "������"); // ���ô�����ϢΪ������
        }
        printf("%s������Ϣ������Ϊ��%s\n\n", p->good_name, promotion_info); // ���������Ϣ
    }
}

// ����ͬ����Ʒ���洢��һ�������У���ͬ�����ֻ�洢һ��
void Get_Good_Category(char category[][100])
{
    // ��ʼ�� category ����Ϊ���ַ���
    for (int i = 0; i < 100; i++)
    {
        category[i][0] = '\0';
    }

    GoodNode *p = all_good_list->next; // ָ��ͷ������һ���ڵ�
    if (p == NULL)
    { // �������Ϊ��
        printf("��Ʒ�����ϢΪ�գ�\n");
        return; // �˳�����
    }
    printf("��Ʒ�����Ϣ���£�\n");
    int count = 0; // ��¼���е��������
    while (p != NULL)
    { // ��������һ��һ����Ʒ�ڵ�
        int i;
        for (i = 0; i < count; i++)
            if (strcmp(category[i], p->category) == 0)
                break;
        if (i == count)
        {                                         // ���û���ҵ���ͬ�����
            strcpy(category[count], p->category); // ���������Ϣ������
            count++;                              // ���������1
        }
        p = p->next; // ����������һ���ڵ�
    }
}

// �鿴���е���Ʒ�����ͬ������ӡһ��
// ÿ�д�����ͻ���
void View_Good_Category()
{
    char category[100][100]; // �洢��ͬ����Ʒ���
    Get_Good_Category(category);
    int count = 0; // ��¼���е��������
    while (count < 100)
    { // �������飬һ��һ�����
        if (strcmp(category[count], "") == 0)
            break;                        // �������Ϊ�գ����˳�ѭ��
        printf("%-20s", category[count]); // ��������Ϣ
        count++;                          // ���������1
        if (count % 5 == 0)               // ����Ѿ����������������
            printf("\n");
    }
    printf("\n"); // ����
    printf("���س�����...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

/// ������Ʒ���ຯ��
/// ���ܣ���ָ����Ʒ�ӵ�ǰ�����ƶ����µķ���
void Adjust_Good_Category()
{
    while (1)
    {
        system("cls"); // ����
        char input[100];
        int id;
        char new_category[50];
        Print_AllGoodList(all_good_list);
        printf("���е�������Ʒ��Ϣ������ʾ�����ο���\n\n");
        printf("������Ҫ�����������ƷID������ '#' �˳�����");
        scanf("%s", input);

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("�������ƷID��Ч�����������롣\n");
            continue;
        }

        printf("�������µ���Ʒ���ࣺ");
        scanf("%s", new_category);

        // ������Ʒ�Ƿ���ڣ������������·��࣬������ʾ��Ʒ������
        GoodNode *p = all_good_list->next;
        while (p != NULL)
        {
            if (p->id == id)
            {
                strcpy(p->category, new_category); // ���·���
                printf("��Ʒ�����Ѹ���Ϊ %s��\n\n", new_category);
                printf("���س�����...\n");
                while (getchar() != '\n')
                    ;      // ������뻺����
                getchar(); // �ȴ��û����س�
                break;
            }
            p = p->next;
        }
        if (p == NULL)
        { // �����Ʒ�����ڣ�����ʾ��Ʒ������
            printf("��Ʒ�����ڣ����������롣\n\n");
        }
    }
}

// ͳ��ÿ���������Ʒ����
void Caculate_Category_Stock()
{
    while (1)
    {
        system("cls"); // ����
        View_Good_Category();
        printf("���е�������Ʒ���������ʾ�����ο���\n\n");
        printf("������Ҫͳ�Ƶ���Ʒ������� '#' �˳�����");
        char category[50];
        scanf("%s", category); // ������Ʒ���
        if (strcmp(category, "#") == 0)
            break;
        int count = 0;                     // ��¼��Ʒ����
        GoodNode *p = all_good_list->next; // ָ��ͷ������һ���ڵ�
        while (p != NULL)
        { // ��������ͳ����Ʒ����
            if (strcmp(p->category, category) == 0)
            {                      // ����ҵ���Ʒ���
                count += p->stock; // �ۼ���Ʒ����
            }
            p = p->next; // ����������һ���ڵ�
        }
        if (count == 0)
        { // ���û���ҵ���Ʒ
            printf("δ�ҵ� %s ��𣬰��س�����...\n", category);
            while (getchar() != '\n')
                ;
            getchar(); // �ȴ��û����س�
        }
        else
        { // ����ҵ���Ʒ
            printf("%s �����Ʒ����Ϊ %d ��\n", category, count);
            printf("���س�����...\n");
            while (getchar() != '\n')
                ;      // ������뻺����
            getchar(); // �ȴ��û����س�
        }
    }
}

// ɾ�����еķ���Ϊcategory����Ʒ
void Delete_Good_Category()
{
    while (1)
    {
        system("cls"); // ����
        View_Good_Category();
        printf("���е�������Ʒ���������ʾ�����ο���\n\n");
        printf("������Ҫɾ������Ʒ������� '#' �˳�����");
        char category[50];
        scanf("%s", category);

        if (strcmp(category, "#") == 0)
        {
            break; // �˳�ѭ��
        }

        int found = 0;
        GoodNode *prev = all_good_list;
        GoodNode *p = all_good_list->next; // ָ��ͷ������һ���ڵ�
        while (p != NULL)
        {
            if (strcmp(p->category, category) == 0)
            {
                prev->next = p->next;
                free(p);
                p = prev->next;
                found = 1;
            }
            else
            {
                prev = p;
                p = p->next;
            }
        }

        if (found)
        {
            printf("%s �����Ʒɾ���ɹ�\n", category);
        }
        else
        {
            printf("δ�ҵ� %s ���\n", category);
        }

        printf("���س�����...");
        while (getchar() != '\n')
            ;      // ������뻺����
        getchar(); // �ȴ��û����س�
    }
}

// �����Ʒ����// ... existing code ...
void Add_Good_Description()
{
    while (1)
    {
        system("cls");                    // ����
        Print_AllGoodList(all_good_list); // ��ʾ������Ʒ��Ϣ
        printf("���е�������Ʒ��Ϣ������ʾ�����ο���\n\n");
        printf("������Ҫ�����������ƷID������ '#' �˳�����");
        char input[100];
        scanf("%s", input); // ������ƷID
        // ������뻺����
        while (getchar() != '\n')
            ;
        if (strcmp(input, "#") == 0)
        { // ������� '#'���˳�ѭ��
            break;
        }
        int id = atoi(input);              // ������ת��Ϊ����
        GoodNode *p = all_good_list->next; // ָ��ͷ������һ���ڵ�
        while (p != NULL)
        { // ��������������ƷID
            if (p->id == id)
            { // ����ҵ���ƷID
                printf("��������Ʒ������");
                // ʹ�� fgets ��ȡ�����ո����������
                fgets(p->description, sizeof(p->description), stdin);
                // �Ƴ� fgets ���ܶ�ȡ�Ļ��з�
                size_t len = strlen(p->description);
                if (len > 0 && p->description[len - 1] == '\n')
                {
                    p->description[len - 1] = '\0';
                }
                printf("��Ʒ��������ӣ����س�����\n");
                while (getchar() != '\n')
                    ;      // ������뻺����
                getchar(); // �ȴ��û����س�
                break;     // �˳�ѭ��
            }
            p = p->next; // ����������һ���ڵ�
        }
        if (p == NULL)
        { // ���δ�ҵ���ƷID
            printf("δ�ҵ�����Ʒ�����������룬���س�����\n");
            while (getchar() != '\n')
                ;      // ������뻺����
            getchar(); // �ȴ��û����س�
        }
    }
}

void Adjust_Customer_Contact()
{
    while (1)
    {
        system("cls"); // ����
        Print_CustomerList(customer_list);
        printf("���е����й˿���Ϣ������ʾ�����ο���\n");
        printf("������Ҫ�޸���ϵ��ʽ�Ĺ˿�id������'#'�˳�����");
        char input[10];
        scanf("%s", input); // ����˿�ID
        if (strcmp(input, "#") == 0)
        { // ������� '#'���˳�ѭ��
            break;
        }
        int id = atoi(input);                  // ������ת��Ϊ����
        CustomerNode *p = customer_list->next; // ָ��ͷ������һ���ڵ�
        while (p != NULL)
        { // �����������ҹ˿�ID
            if (p->id == id)
            { // ����ҵ��˿�ID
                printf("�������µ���ϵ��ʽ��");
                scanf("%s", p->contact); // �����µ���ϵ��ʽ
                printf("��ϵ��ʽ���޸ģ����س�����\n");
                while (getchar() != '\n')
                    ;      // ������뻺����
                getchar(); // �ȴ��û����س�
                break;     // �˳�ѭ��
            }
            p = p->next; // ����������һ���ڵ�
        }
        if (p == NULL)
        { // ���δ�ҵ��˿�ID
            printf("δ�ҵ��ù˿ͣ����������룬���س�����\n");
            while (getchar() != '\n')
                ;      // ������뻺����
            getchar(); // �ȴ��û����س�
        }
    }
}

void Admin_Modify_Purchase()
{
    // ��purchaseInfo.txt�ļ���
    while (1)
    {
        system("cls");        // ����
        Print_PurchaseList(); // ��ʾ���н�����Ϣ
        // ���purchaseInfo.txt�еĵ�һ�У���id���洢��������
        int purchase_id[1000];                         // �洢id������
        int count = 0;                                 // ��¼id������
        FILE *fp = fopen("txt/purchaseInfo.txt", "r"); // ���ļ�
        if (fp == NULL)
        { // ������ļ�ʧ��
            printf("�ļ���ʧ�ܣ�\n");
            exit(1); // �˳�����
        }
        while (1)
        {
            int result = fscanf(fp, "%d", &purchase_id[count]);
            if (result == EOF)
                break; // �����ļ�ĩβ���˳�ѭ��
            else if (result == 0)
                while (fgetc(fp) != '\n' && !feof(fp))
                    ;
            else
                count++; // �ɹ���ȡһ��������id������1
        }
        fclose(fp); // �ر��ļ�

        printf("���е����н�����Ϣ������ʾ�����ο���\n");
        printf("������ѡ��0���˳���1���޸ļ�¼��2��ɾ����¼��3�����Ӽ�¼����");
        int choice;
        scanf("%d", &choice); // ����ѡ��
        if (choice == 0)      // �������0���˳�ѭ��
            break;
        else if (choice == 1)
        {
            printf("������Ҫ�޸ĵļ�¼id������'#'�˳�����");
            char input[10];
            scanf("%s", input);
            if (strcmp(input, "#") == 0)
            {
                break;
            }
            int id = atoi(input);
            int found = 0;
            // ����id���飬����id
            for (int i = 0; i < count; i++)
            {
                if (purchase_id[i] == id)
                {
                    found = 1;
                    break;
                }
            }
            if (found)
            {
                // ��ԭ�ļ����ڶ�ȡ
                FILE *fp = fopen("txt/purchaseInfo.txt", "r");
                if (fp == NULL)
                {
                    perror("�ļ���ʧ��");
                    continue;
                }
                // ����ʱ�ļ�����д��
                FILE *temp_fp = fopen("txt/temp.txt", "w");
                if (temp_fp == NULL)
                {
                    perror("��ʱ�ļ���ʧ��");
                    fclose(fp);
                    continue;
                }

                char line[256];
                int current_id;
                while (fgets(line, sizeof(line), fp) != NULL)
                {
                    // �����н�������һ��������Ϊ��Ʒ���
                    if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
                    {
                        // ����Ҫ�޸ĵļ�¼
                        continue;
                    }
                    // �����ǰ�в���Ҫ�޸ĵļ�¼����д����ʱ�ļ�
                    fputs(line, temp_fp);
                }
                fclose(fp);
                fclose(temp_fp);

                // ɾ��ԭ�ļ�
                remove("txt/purchaseInfo.txt");
                // ��������ʱ�ļ�Ϊԭ�ļ���
                rename("txt/temp.txt", "txt/purchaseInfo.txt");

                // �����µļ�¼��Ϣ
                printf("�������µļ�¼��Ϣ��\n");
                char category[20], good_name[50], supplier[50];
                float cost_price;
                int quantity;
                printf("��������Ʒ���");
                scanf("%19s", category);
                printf("��������Ʒ���ƣ�");
                scanf("%49s", good_name);
                printf("��������Ʒ���ۣ�");
                scanf("%f", &cost_price);
                printf("��������Ʒ������");
                scanf("%d", &quantity);
                printf("�����빩Ӧ�̣�");
                scanf("%49s", supplier);

                // ���´��ļ���׷���¼�¼
                fp = fopen("txt/purchaseInfo.txt", "a");
                if (fp == NULL)
                {
                    perror("�ļ���ʧ��");
                    continue;
                }

                // current_time���޸ĵ�id����һ�е�ʱ��һ��
                char current_time[10]; // �������

                // ����idΪ0
                fprintf(fp, "%d %s %s %.2f %d %s %s\n", 0, category, good_name, cost_price, quantity, current_time, supplier);
                fclose(fp);

                printf("��¼�޸ĳɹ�\n");
                printf("���س�������...\n");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                printf("δ�ҵ��ü�¼��ŵĽ�����¼��\n");
            }
        }
        else if (choice == 2)                                // �������2��ɾ����¼
        {                                                    // ����
            printf("������Ҫɾ���ļ�¼id������'#'�˳�����"); // ����Ҫɾ���ļ�¼id
            char input[10];                                  // �����������
            scanf("%s", input);                              // ����
            if (strcmp(input, "#") == 0)
                break;
            int id = atoi(input); // ������ת��Ϊ����
            int found = 0;
            // ����id���飬����id
            for (int i = 0; i < count; i++)
                if (purchase_id[i] == id) // ����ҵ�id
                    found = 1;
            if (found) // ����ҵ�id
            {
                // ���ļ�����idΪid��һ����ɾ��
                FILE *fp = fopen("txt/purchaseInfo.txt", "r"); // ���ļ�
                FILE *fp2 = fopen("txt/temp.txt", "w");        // ���ļ�
                if (fp == NULL || fp2 == NULL)                 // ������ļ�ʧ��
                {                                              // ������ļ�ʧ��
                    printf("�ļ���ʧ�ܣ�\n");                // ���
                    exit(1);                                   // �˳�����
                }
                char line[100];                               // �������
                int current_id;                               // ������ʱ�洢�����н�������id
                while (fgets(line, sizeof(line), fp) != NULL) // ��ȡ�ļ�
                {
                    if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
                    {
                        // �����ǰ�е�id����Ҫɾ����id������������
                        continue;
                    }
                    // ���򣬽�����д����ʱ�ļ�
                    fprintf(fp2, "%s", line);
                }
                fclose(fp);                                     // �ر��ļ�
                fclose(fp2);                                    // �ر��ļ�
                remove("txt/purchaseInfo.txt");                 // ɾ���ļ�
                rename("txt/temp.txt", "txt/purchaseInfo.txt"); // �������ļ�
                printf("��¼ɾ���ɹ�\n");                       // ���
                printf("���س�������...\n");                    // ���
                while (getchar() != '\n')                       // ������뻺����
                    ;
                getchar();
            }
        }
        else if (choice == 3) // �������3�����Ӽ�¼
        {
            char category[20], good_name[50], supplier[50]; // �������
            float cost_price;                               // �������
            int quantity;                                   // �������
            printf("��������Ʒ���");                     // ������Ʒ���
            scanf("%19s", category);                        // ����
            printf("��������Ʒ���ƣ�");                     // ������Ʒ����
            scanf("%49s", good_name);                       // ����
            printf("��������Ʒ���ۣ�");                     // ������Ʒ����
            scanf("%f", &cost_price);                       // ����
            printf("��������Ʒ������");                     // ������Ʒ����
            scanf("%d", &quantity);                         // ����
            printf("�����빩Ӧ�̣�");                       //
            scanf("%49s", supplier);                        // ����
            printf("��¼���ӳɹ�\n");                       // ���
            printf("���س�������...\n");                    // ���
            // ���ո�ʽ��ӡ���ļ����һ��
            FILE *fp = fopen("txt/purchaseInfo.txt", "a"); // ���ļ�
            if (fp == NULL)                                // ������ļ�ʧ��
            {                                              // ������ļ�ʧ��
                printf("�ļ���ʧ�ܣ�\n");                // ���
                exit(1);                                   // �˳�����
            }
            char current_time[20];
            GetCurrentTime(current_time);
            // ����idΪ0
            fprintf(fp, "%d %s %s %.2f %d %s %s\n", 0, category, good_name, cost_price, quantity, current_time, supplier);
            fclose(fp); // ������뻺����
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

// ����Ա����
void Admin()
{
    while (1)
    {
        system("cls");
        // ��ӡ��ǰʱ��
        char current_time[20];
        GetCurrentTime(current_time);
        printf("��ǰʱ�䣺%ss\n", current_time);

        printf("������Ա����ã�\n");
        printf("������ѡ��\n");
        printf("0���˳�\n");
        printf("1����Ʒ����&ͳ��\n");
        printf("2���˿���Ϣ����\n");
        printf("3��������¼����&����\n");
        printf("4����ѯ\n");
        printf("5������\n");
        printf("6�����&ɾ���˻�\n");
        printf("7������&�ָ�����\n\n");

        // ����all_good_list�����п�����ѣ�������Ʒ���С��50�ģ�һ�Ǽ����ѣ�
        // ������Ʒ���С��25�ģ����Ǽ����ѣ�������Ʒ���С��10�ģ����Ǽ�����
        // ������Ƿ��ű�ʾ���յ�λ���ÿ�����Ƿ��ű�ʾ
        GoodNode *p = all_good_list->next; // ָ��ͷ������һ���ڵ�
        int flag10 = 0, flag25 = 0, flag50 = 0, flag_sum;
        while (p != NULL)
        { // ��������������ƷID
            if (p->stock < 50)
            {               // ����ҵ���ƷID
                flag50 = 1; // ��治��
            }
            if (p->stock < 25)
            {               // ����ҵ���ƷID
                flag25 = 1; // ��治��
            }
            if (p->stock < 10)
            {               // ����ҵ���ƷID
                flag10 = 1; // ��治��
            }
            p = p->next; // ����������һ���ڵ�
        }
        flag_sum = flag10 + flag25 + flag50;
        switch(flag_sum)
        {
        case 0:
            printf("��Ʒ�����㣨�����̶ȣ��� �� �\n");
            break;
        case 1:
            printf("������Ʒ���С��50����ǰ�����������̶ȣ��� �� �\n");
            break;
        case 2:
            printf("������Ʒ���С��25����ǰ�����������̶ȣ��� �� �\n");
            break;
        case 3:
            printf("������Ʒ���С��10����ǰ�����������̶ȣ��� �� �\n");
            break;
        }

        int choice;
        int choice1;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            return;
            
            break; // ����ѭ��
        case 1:
            while (1)
            {
                int choice2;
                system("cls");
                printf("��Ʒ����\n");
                printf("0.�˳�\n");
                printf("1.����\n");
                printf("2.�鿴��Ʒ��Ϣ\n");
                printf("3.�޸���Ʒ�۸�\n");
                printf("4.�޸���Ʒ������Ϣ\n");
                printf("5.ɾ����Ʒ��Ϣ\n");
                printf("6.�鿴������Ʒ���\n");
                printf("7.������Ʒ���\n");
                printf("8.ɾ��ĳһ������������Ʒ\n");
                printf("9.ͳ��ĳһ����Ʒ������Ʒ����\n");
                printf("10.�����Ʒ����\n");
                scanf("%d", &choice2);
                switch (choice2)
                {
                case 1: // ����
                    system("cls");
                    while (1) // ���Ͻ�����ֱ������#�˳�
                    {
                        int choice2;
                        printf("������ѡ�񣺣�0���˳���1���ֶ����������2�����ļ�������������ַ�����ͬʱʹ�ã���\n");
                        scanf("%d", &choice2);
                        if (choice2 == 1) // �ֶ��������
                        {
                            char category[20], good_name[50], supplier[50];
                            float cost_price;
                            int quantity;
                            printf("��������Ʒ�������'#'�˳�����");
                            scanf("%19s", category);
                            if (strcmp(category, "#") == 0)
                            {
                                break; // ����'#'����ѭ��
                            }
                            printf("��������Ʒ���ƣ�");
                            scanf("%49s", good_name);
                            printf("��������Ʒ���ۣ�");
                            scanf("%f", &cost_price);
                            printf("��������Ʒ������");
                            scanf("%d", &quantity);
                            printf("�����빩Ӧ�̣�");
                            scanf("%49s", supplier);
                            printf("�����ɹ�");
                            printf("\n\n");
                            Purchase(category, good_name, cost_price, quantity, supplier);
                        }
                        else if (choice2 == 2) // ���ļ��������
                        {
                            // ��ȡsource.txt�ļ������ļ��еĽ�����Ϣ���뵽ϵͳ��
                            FILE *fp = fopen("txt/GoodSource.txt", "r");
                            if (fp == NULL)
                            {
                                printf("�ļ���ʧ�ܣ�\n");
                                break; // ���ļ�ʧ�ܣ��˳�ѭ��
                            }
                            char category[20], good_name[50], supplier[50];
                            float cost_price;
                            int quantity;

                            while (fscanf(fp, "%19s %49s %f %d %49s", category, good_name, &cost_price, &quantity, supplier) != EOF)
                            {
                                float discount;
                                // cost_price����Ϊ�ļ�GoodSource�е��������۵�30%���¸���
                                // discount = 0.3*sin(current_time*2*3.14/60)��sin����������Ϊ60�룬���Ϊ0.3
                                float current_time_float = atof(current_time);
                                discount = 0.3 * sin(current_time_float * 2 * 3.14 / 60);
                                cost_price *= (1 + discount);
                                Purchase(category, good_name, cost_price, quantity, supplier);
                            }
                            fclose(fp); // �ر��ļ�
                            printf("�����ɹ�\n");
                            printf("���س�������...\n");
                            while (getchar() != '\n')
                                ;      // ������뻺����
                            getchar(); // �ȴ��û����»س���
                        }
                        else if (choice2 == 0) // �˳�
                        {
                            break; // �˳�ѭ��
                        }
                    }
                    break;
                case 2:
                    system("cls");
                    printf("������Ʒ��Ϣ���£�\n");
                    // ���س�����
                    Print_AllGoodList(all_good_list);
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                    break;
                case 3:
                    system("cls");
                    Print_AllGoodList(all_good_list);
                    printf("�Ѵ洢����Ʒ��Ϣ���ϣ����ο�\n");
                    Set_Good_Price();
                    break;
                case 4:
                    system("cls");
                    Set_Good_Promotion_Info();
                    break;
                case 5:
                    Delete_Good_From_System(); // ������������н��湦��
                    break;
                case 6:
                    system("cls");
                    View_Good_Category();
                    break;
                case 7: // ������Ʒ���
                    Adjust_Good_Category();
                    break;
                case 8:
                    Delete_Good_Category();
                    break;
                case 9:
                    Caculate_Category_Stock();
                    break;
                case 10:
                    Add_Good_Description();
                    break;
                case 0:
                    break; // �˳���Ʒ��Ϣ����
                default:
                    printf("��Ч��ѡ�����������룡\n");
                    break;
                }
                if (choice2 == 0)
                    // ���ѡ���˳���Ʒ��Ϣ����������ѭ��
                    break;
            }
            break;
        case 2:
            while (1)
            {
                system("cls");
                printf("�˿���Ϣ����\n");
                printf("0.�˳�\n");
                printf("1.��ӹ˿���Ϣ\n");
                printf("2.�����˿ͷ���\n");
                printf("3.�����˿��ֻ���\n");
                printf("4.�鿴���й˿���Ϣ\n");
                printf("5.ɾ���˿���Ϣ\n");

                scanf("%d", &choice1);
                switch (choice1)
                {
                case 1:
                    system("cls");
                    int choice4;
                    printf("������ѡ�񣺣�0���˳���1���ֶ�����˿���Ϣ��2�����ļ�����˿���Ϣ�����ַ�����ͬʱʹ�ã���\n");
                    scanf("%d", &choice4);
                    if (choice4 == 1) // �ֶ�����˿���Ϣ
                        Add_Customer_To_System();
                    else if (choice4 == 0) // �˳�
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

                case 2:
                    system("cls");
                    Print_CustomerList(customer_list);
                    printf("�Ѵ洢�Ĺ˿���Ϣ���ϣ����ο�\n");
                    Adjust_Customer_Type();
                    break;
                case 3:                        // �����˿��ֻ���
                    Adjust_Customer_Contact(); // �������ڲ�ʵ��
                    printf("���س�������...\n");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 4:
                    system("cls");
                    if (customer_list->next == NULL)
                    {
                        printf("�˿���ϢΪ�գ�\n");
                        printf("���س�������...");
                        while (getchar() != '\n')
                            ;      // �ȴ��û����»س�
                        getchar(); // �������Ļ��з�

                        break;
                    }
                    else
                        Print_CustomerList(customer_list);
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                    break;
                case 5:
                    system("cls");
                    Delete_Customer_From_System();
                    break;
                case 0:
                    break; // �˳��˿���Ϣ����
                default:
                    printf("��Ч��ѡ�����������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                    break;
                }
                if (choice1 == 0)
                    // ���ѡ���˳��˿���Ϣ����������ѭ��
                    break;
            }
            break;
        case 3: // ������¼�����ۼ�¼
            while (1)
            {
                system("cls");
                int choice2;
                printf("������ѡ��\n0���˳�\n1���鿴������¼\n2���鿴���ۼ�¼\n3���޸Ľ�����¼\n");
                scanf("%d", &choice2);
                if (choice2 == 1) // ��ӡpurchaseInfo.txt������
                {
                    system("cls");
                    Print_PurchaseList();
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                else if (choice2 == 0)
                    break; // �˳�

                else if (choice2 == 2) // ��ӡsaleInfo.txt������
                {
                    system("cls");
                    Print_SaleList();
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                else if (choice2 == 3) // �޸Ľ�����¼
                {
                    // �������ļ����޸Ķ���Ӱ����ʵ�Ŀ��״̬���ñ�������
                    Admin_Modify_Purchase();
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                else
                    printf("��Ч��ѡ�����������룡\n");
            }
            break;
        case 4:
            Admin_Search();
            break;
        case 5:
            Admin_Sort();
            break;
        case 6: // ���&ɾ���˻�
            while (1)
            {
                system("cls");
                printf("������ѡ�񣺣�0���˳���1����ӹ���Ա��2������ۻ�Ա��3��ɾ������Ա��4:ɾ���ۻ�Ա)\n");
                int choice2;
                while (scanf("%d", &choice2) != 1 || choice2 < 0 || choice2 > 4)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("������ѡ�񣺣�0���˳���1����ӹ���Ա��2������ۻ�Ա��3��ɾ������Ա��4:ɾ���ۻ�Ա)\n");
                }
                if (choice2 == 0)
                    break;
                else if (choice2 == 1)
                    add_admin("txt/adminLogin.txt");
                else if (choice2 == 2)
                    add_admin("txt/salespersonLogin.txt");
                else if (choice2 == 3)
                {
                    AdminNode *admin_list = load_admin_list("txt/adminLogin.txt");
                    if (!admin_list)
                        return;
                    char target[50];
                    printf("������Ҫɾ���Ĺ���Ա�û�����");
                    scanf("%s", target);

                    if (delete_admin(&admin_list, target))
                    {
                        save_admin_list(admin_list, "txt/adminLogin.txt");
                        printf("����Աɾ���ɹ���\n");
                    }
                    else
                        printf("δ�ҵ��ù���Ա��\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�

                    free_admin_list(admin_list);
                }
                else if (choice2 == 4)
                {
                    AdminNode *admin_list = load_admin_list("txt/salespersonLogin.txt");
                    if (!admin_list)
                        return;
                    char target[50];
                    printf("������Ҫɾ���Ĺ���Ա�û�����");
                    scanf("%s", target);

                    if (delete_admin(&admin_list, target))
                    {
                        save_admin_list(admin_list, "txt/salespersonLogin.txt");
                        printf("����Աɾ���ɹ���\n");
                    }
                    else
                        printf("δ�ҵ��ù���Ա��\n");

                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�

                    free_admin_list(admin_list);
                }
            }
            break;
        case 7: // ����&�ָ�����
            while (1)
            {
                int choice2;
                system("cls");

                printf("������ѡ�񣺣�0���˳���1:�������룬2���ָ�����)\n");
                while (scanf("%d", &choice2) != 1 || choice2 < 0 || choice2 > 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("����������������룡\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // ����
                    printf("������ѡ�񣺣�0���˳���1:�������룬2���ָ�����)\n");
                }
                if (choice2 == 0)
                    break;
                else if (choice2 == 1)
                { // ����
                    if (backup_admin_file("txt/adminLogin.txt", "txt/adminLogin_backup.txt") &&
                        backup_admin_file("txt/salespersonLogin.txt", "txt/salespersonLogin_backup.txt"))

                        printf("���ݳɹ���\n");
                    else

                        printf("����ʧ�ܣ�\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
                if (choice2 == 2)
                { // �ָ�
                    if (restore_admin_file("txt/adminLogin_backup.txt", "txt/adminLogin.txt") &&
                        restore_admin_file("txt/salespersonLogin_backup.txt", "txt/salespersonLogin.txt"))
                        printf("�ָ��ɹ���\n");
                    else
                        printf("�ָ�ʧ�ܣ�\n");
                    printf("���س�������...");
                    while (getchar() != '\n')
                        ;      // �ȴ��û����»س�
                    getchar(); // �������Ļ��з�
                }
            }
            break;
        default:
            printf("��Ч��ѡ�����������룬���س�������...\n");
            while (getchar() != '\n')
                ;      // �ȴ��û����»س�
            getchar(); // �������Ļ��з�
            break;
        }
    }
}

// ����Ա��¼����
// ��¼�ɹ�����1����¼ʧ�ܷ���0
int admin_login()
{
    system("cls");
    char input_username[100];
    char input_password[100];

    // ��ȡ�ļ��е����ݣ��洢��������ά������
    char usernames[100][100]; // �洢�û���
    char passwords[100][100]; // �洢����
    int count = 0;            // ��¼��ȡ������

    FILE *fp = fopen("txt/adminLogin.txt", "r"); // ���ļ���ֻ��ģʽ
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
    printf("�������û�����");
    scanf("%s", input_username); // �����û���
    printf("���������룺");
    scanf("%s", input_password); // ��������

    // ���������û����������Ƿ���������ά����ƥ��
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_username, usernames[i]) == 0 && strcmp(input_password, passwords[i]) == 0)
        {
            printf("��¼�ɹ���\n"); // ��¼�ɹ�
            printf("���س�������...\n");
            while (getchar() != '\n')
                ;      // �ȴ��û����»س�
            getchar(); // �������Ļ��з�
            return 1;  // ����1
        }
    }
    printf("��¼ʧ�ܣ��û������������\n"); // ��¼ʧ��
    printf("���س�������...\n");
    while (getchar() != '\n')
        ;      // �ȴ��û����»س�
    getchar(); // �������Ļ��з�
    return 0;  // ����0
}

int add_admin(const char *filename)
{
    char username[50];
    char password[50];
    printf("�������û�����");
    scanf("%s", username);

    // ����Ƿ��ظ�
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        Adminster temp;
        while (fscanf(fp, "%s %s", temp.username, temp.password) != EOF)
        {
            if (strcmp(temp.username, username) == 0)
            {
                printf("���û����Ѵ��ڣ������ظ���ӣ�\n");
                printf("���س�������...\n");
                while (getchar() != '\n')
                    ;      // �ȴ��û����»س�
                getchar(); // �������Ļ��з�
                fclose(fp);
                return 0;
            }
        }
        fclose(fp);
    }

    printf("���������룺");
    scanf("%s", password);

    // д���ļ�
    fp = fopen(filename, "a"); // ׷��д��
    if (!fp)
    {
        printf("�޷����ļ� %s\n", filename);
        printf("���س�������...\n");
        while (getchar() != '\n')
            ;      // �ȴ��û����»س�
        getchar(); // �������Ļ��з�
        return 0;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    if (strcmp(filename, "txt/adminLogin.txt") == 0)
        printf("����Ա��ӳɹ���\n");
    else if (strcmp(filename, "txt/salespersonLogin.txt") == 0)
        printf("�ۻ�Ա��ӳɹ���\n");

    printf("���س�������...\n");
    while (getchar() != '\n')
        ;      // �ȴ��û����»س�
    getchar(); // �������Ļ��з�
    return 1;
}

AdminNode *load_admin_list(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("�޷����ļ� %s\n", filename);
        return NULL;
    }

    AdminNode *head = NULL, *tail = NULL;
    Adminster temp;

    while (fscanf(fp, "%s %s", temp.username, temp.password) != EOF)
    {
        AdminNode *new_node = (AdminNode *)malloc(sizeof(AdminNode));
        new_node->data = temp;
        new_node->next = NULL;

        if (!head)
        {
            head = new_node;
        }
        else
        {
            tail->next = new_node;
        }
        tail = new_node;
    }

    fclose(fp);
    return head;
}

// �������Ա����
void save_admin_list(AdminNode *head, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("�޷�д���ļ� %s\n", filename);
        return;
    }

    while (head)
    {
        fprintf(fp, "%s %s\n", head->data.username, head->data.password);
        head = head->next;
    }

    fclose(fp);
}

// �ͷ������ڴ�
void free_admin_list(AdminNode *head)
{
    AdminNode *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ɾ������Ա
int delete_admin(AdminNode **head_ref, const char *username)
{
    AdminNode *prev = NULL, *curr = *head_ref;

    while (curr)
    {
        if (strcmp(curr->data.username, username) == 0)
        {
            if (prev == NULL)
            {
                *head_ref = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            return 1; // ɾ���ɹ�
        }
        prev = curr;
        curr = curr->next;
    }

    return 0; // δ�ҵ�
}

int backup_admin_file(const char *source, const char *backup)
{
    FILE *src = fopen(source, "r");
    if (!src)
    {
        printf("�޷���Դ�ļ���%s\n", source);
        return 0;
    }

    FILE *dest = fopen(backup, "w");
    if (!dest)
    {
        printf("�޷����������ļ���%s\n", backup);
        fclose(src);
        return 0;
    }

    char ch;
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    return 1;
}
int restore_admin_file(const char *backup, const char *target)
{
    FILE *src = fopen(backup, "r");
    if (!src)
    {
        printf("�޷��򿪱����ļ���%s\n", backup);
        return 0;
    }

    FILE *dest = fopen(target, "w");
    if (!dest)
    {
        printf("�޷�д��Ŀ���ļ���%s\n", target);
        fclose(src);
        return 0;
    }

    char ch;
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    return 1;
}
