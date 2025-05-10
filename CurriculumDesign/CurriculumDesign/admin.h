#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

typedef struct Adminster
{
    char username[50]; // 用户名
    char password[50]; // 密码
} Adminster;

typedef struct AdminNode
{
    Adminster data;
    struct AdminNode *next;
} AdminNode;


void ResetGoodPurchaseId();
void Purchase(char *category, char *good_name, float cost_price, int quantity, char *supplier);
void Delete_PurchaseRecord(int id);
void Add_PurchaseRecord(char *category, char *good_name, float cost_price, int quantity, char *supplier);
void CustomerInfo_Generate();
void Create_CustomerInfo_File();
void Add_Customer_To_System();
void Delete_Customer_From_System();
void Adjust_Customer_Type();
void Delete_Good_From_System();
void Set_Good_Price();
void Set_Good_Promotion_Info();
void Get_Good_Category(char category[][100]);
void View_Good_Category();
void Adjust_Good_Category();
void Delete_Good_Category();
void Add_Good_Description();
void Adjust_Customer_Contact();
void Admin_Modify_Purchase();// 做假账
void Admin();
int admin_login();
void Caculate_Category_Stock();
void ResetAdmin();


int add_admin(const char *filename);

AdminNode *load_admin_list(const char *filename);
void save_admin_list(AdminNode *head, const char *filename);
void free_admin_list(AdminNode *head);
int delete_admin(AdminNode **head_ref, const char *username);
int backup_admin_file(const char *source, const char *backup);
int restore_admin_file(const char *backup, const char *target);
#endif // ADMIN_H_INCLUDED
