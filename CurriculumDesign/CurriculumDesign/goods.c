#include "goods.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��ʼ����ͷ������Ʒ����
void Init_AllGoodList(AllGoodList *list)
{
    *list = (AllGoodList)malloc(sizeof(GoodNode)); // ����ͷ����ڴ�
    if (*list == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    (*list)->next = NULL; // ��ʼ��ͷ����ָ����ΪNULL
}

// ������Ʒ�ڵ㵽�����У�ͷ�巨
void Insert_AllGoodList(AllGoodList *list, GoodNode good)
{
    GoodNode *new_node = (GoodNode *)malloc(sizeof(GoodNode)); // �����½ڵ��ڴ�
    if (new_node == NULL)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    *new_node = good;               // ������Ʒ��Ϣ���½ڵ�
    new_node->next = (*list)->next; // �½ڵ��ָ����ָ��ͷ������һ���ڵ�
    (*list)->next = new_node;       // ͷ����ָ����ָ���½ڵ�
}

// ɾ����Ʒ�����е�ָ����Ʒ�ڵ�
// �ɹ�����1��ʧ�ܷ���0
// ... existing code ...
int Delete_AllGoodList(AllGoodList *list, int id)
{
    GoodNode *p = *list; // pָ��ͷ��㣬�����޸�Ϊָ��ͷ��������ͷ������һ���ڵ�
    while (p->next != NULL)
    { // ��������
        if (p->next->id == id)
        {                             // ����ҵ�Ҫɾ���Ľڵ�
            GoodNode *temp = p->next; // ��ʱ����Ҫɾ���Ľڵ�
            p->next = temp->next;     // �޸�ָ��������Ҫɾ���Ľڵ�
            free(temp);               // �ͷ��ڴ�
            return 1;                 // ɾ���ɹ������� 1
        }
        p = p->next; // ����������һ���ڵ�
    }
    return 0; // δ�ҵ�Ҫɾ���Ľڵ㣬���� 0
}

// ��ӡ��Ʒ�����е�������Ʒ��Ϣ
void Print_AllGoodList(AllGoodList list)
{
    GoodNode *p = list->next; // pָ��ͷ���
    if (p == NULL)
    { // �������Ϊ��
        printf("��Ʒ��ϢΪ�գ�\n");
        return; // �˳�����
    }
    printf("��Ʒ��Ϣ���£�\n");
    // ������Ʒ�����ı���
    printf("%-5s %-13s %-15s %-20s %-8s %-6s %-12s %-10s %-15s\n", "���",
           "����", "���", "��������", "�۸�", "���", "����״̬", "�����۸�", "��Ʒ����");
    while (p != NULL)
    { // ��������һ��һ����Ʒ�ڵ�
        // ������Ʒ�����Ĵ�ӡ
        printf("%-5d %-13s %-15s %-20s %-8.2f %-6d %-12d %-10.2f %-15s\n", p->id, p->good_name, p->category,
               p->manufacturer, p->price, p->stock, p->is_promotion, p->promotion_price, p->description);
        p = p->next; // �ƶ�����һ���ڵ�
    }
}