#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

typedef struct CustomerNode // �˿ͱ�š��˿��������˿����͡��˿���ϵ��ʽ
{
    int id;                    // �˿ͱ�ţ�Ψһ��ʶ��
    char name[50];             // �˿�����
    char type[30];             // �˿����ͣ�ȡֵΪ���֣�normal��vip��svip��
    char contact[50];          // �˿���ϵ��ʽ���磺�绰������ȣ�
    struct CustomerNode *next; // ָ����һ���ڵ��ָ��
} CustomerNode, *CustomerList;

void Init_CustomerList(CustomerList *list);
void Insert_CustomerList(CustomerList *list, CustomerNode customer);
int Delete_CustomerList(CustomerList *list, int id);
void Print_CustomerList(CustomerList list);

#endif // CUSTOMER_H_INCLUDED
