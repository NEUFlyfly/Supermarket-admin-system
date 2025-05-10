#include "customer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ��������
void Init_CustomerList(CustomerList *list);
void Insert_CustomerList(CustomerList *list, CustomerNode customer);
int Delete_CustomerList(CustomerList *list, int id);
void Print_CustomerList(CustomerList list);

void Init_CustomerList(CustomerList *list)
{
    *list = (CustomerList)malloc(sizeof(CustomerNode));
    if (*list == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    (*list)->next = NULL;
}

// ÿ�μ���һ���˿͵���Ϣ��Ԫ��(name type contact)ʱ���Զ����ɹ˿ͱ��
void Insert_CustomerList(CustomerList *list, CustomerNode customer)
{
    static int id_counter = 0;
    customer.id = ++id_counter; // �Զ����ɹ˿ͱ��

    CustomerNode *newnode = (CustomerNode *)malloc(sizeof(CustomerNode));
    if (newnode == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    newnode->id = customer.id;
    strcpy(newnode->name, customer.name);
    strcpy(newnode->type, customer.type);
    strcpy(newnode->contact, customer.contact);
    newnode->next = (*list)->next;
    (*list)->next = newnode;
}

int Delete_CustomerList(CustomerList *list, int id)
{
    CustomerNode *prev = *list;
    CustomerNode *curr = (*list)->next;

    while (curr != NULL && curr->id != id)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("δ�ҵ��ù˿ͣ�\n");
        return 0;
    }

    prev->next = curr->next;
    free(curr);
    return 1;
}

void Print_CustomerList(CustomerList list)
{
    // ��ӡ��ͷ
    printf("[�˿���Ϣ�б�]��\n");
    printf("%-8s%-12s%-10s%-15s\n", "�˿�id", "�˿�����", "�˿�����", "�˿���ϵ��ʽ");
    // ��ӡ�ָ���
    CustomerNode *p = list->next;
    while (p != NULL)
    {
        // ����˿���ϵ��ʽ��ĩβ����?�������滻Ϊ�ո�
        char *contact = p->contact;
        int len = strlen(contact);
        if (len > 0 && contact[len - 1] == '?')
            contact[len - 1] = ' ';

        // ��ӡ�˿���Ϣ
        printf("    %-8d%-12s%-10s%-15s\n", p->id, p->name, p->type, p->contact);
        p = p->next;
    }
}
