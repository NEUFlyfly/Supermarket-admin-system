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

static int good_id_counter = 1;     // 用于自动生成商品编号，初始值为1
static int purchase_id_counter = 1; // 用于自动生成进货记录编号，初始值为1
static int first_time = 1; // 用于判断是否第一次调用Purchase函数，如果是第一次调用，则清空purchaseInfo.txt文件


void ResetAdmin()
{
    good_id_counter = 1;
    purchase_id_counter = 1;
    first_time = 1;
}

// 函数声明

/// 进货函数
// 即增加商品信息
void Purchase(char *category, char *good_name, float cost_price, int quantity, char *supplier)
{

    if (first_time)
    {
        FILE *fp = fopen("txt/purchaseInfo.txt", "w");
        if (fp == NULL)
        {
            printf("文件打开失败！\n");
            exit(1);
        }
        fclose(fp);
        first_time = 0; // 设置为0，表示已经清空过文件
    }

    char current_time[10];
    GetCurrentTime(current_time);

    // 1. 创建新的进货记录
    PurchaseNode purchase;
    strcpy(purchase.good_name, good_name);
    strcpy(purchase.purchase_time, current_time); // 修改为使用purchase_time
    strcpy(purchase.supplier, supplier);
    strcpy(purchase.category, category);
    purchase.id = purchase_id_counter++;
    purchase.quantity = quantity;
    purchase.cost_price = cost_price;
    Insert_PurchaseList(&purchase_record, purchase);

    // 2. 更新商品库存
    // 查找商品是否已经存在，如果存在则更新库存，否则创建新的商品节点
    GoodNode *p = all_good_list->next;
    while (p != NULL)
    {
        if (strcmp(p->good_name, good_name) == 0 && strcmp(p->category, category) == 0 && strcmp(p->manufacturer, supplier) == 0 && p->price == cost_price)
        {
            p->stock += quantity; // 更新库存
            break;
        }
        p = p->next;
    }
    if (p == NULL) // 如果商品不存在，则创建新的商品节点
    {
        GoodNode new_good;
        strcpy(new_good.good_name, good_name);
        strcpy(new_good.category, category);
        strcpy(new_good.manufacturer, supplier);
        new_good.price = cost_price;
        new_good.stock = quantity;
        new_good.is_promotion = 0; // 默认不促销
        new_good.promotion_price = 0;
        new_good.id = good_id_counter++; // 分配商品编号
        Insert_AllGoodList(&all_good_list, new_good);
    }
    // 3. 保存进货日志到purchaseInfo.txt，格式：商品类别 商品名称 进货单价 进货数量 实际时间 供应商名称
    // 获取当前时间并格式化为字符串

    FILE *fp = fopen("txt/purchaseInfo.txt", "a");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return;
    }
    // 格式：商品id 商品类别 商品名称 进货单价 进货数量 实际时间 供应商名称
    fprintf(fp, "%d %s %s %.2f %d %s %s\n", purchase.id, purchase.category, purchase.good_name,
            purchase.cost_price, purchase.quantity, current_time, purchase.supplier);
    fclose(fp);
}

// 删除指定商品的进货记录
// 这里的删除是指从txt文件中中删除指定商品名称的进货记录，而不是删除商品本身，也不是从链表中删除
void Delete_PurchaseRecord(int id)
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "r+");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return;
    }

    FILE *temp_fp = fopen("txt/temp.txt", "w");
    if (temp_fp == NULL)
    {
        perror("临时文件打开失败");
        fclose(fp);
        return;
    }

    char line[256];
    int found = 0; // 标记是否找到要删除的商品编号
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int current_id;
        // 从行中解析出第一个整数作为商品编号
        if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
        {
            found = 1; // 找到要删除的商品编号，跳过该行
            continue;
        }
        // 如果当前行不包含要删除的商品编号，则写入临时文件
        fputs(line, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    // 如果找到要删除的商品编号，则替换原文件
    if (found)
    {
        remove("txt/purchaseInfo.txt");                 // 删除原文件
        rename("txt/temp.txt", "txt/purchaseInfo.txt"); // 重命名临时文件为原文件名
    }
    else
    {
        remove("txt/temp.txt"); // 删除临时文件
        printf("未找到该商品编号的进货记录！\n");
    }
}

// 增加一条商品的进货记录
// 这里的增加是指从txt文件中增加进货记录，而不是增加商品本身，id为0，暴露假账
// 格式：商品id 商品类别 商品名称 进货单价 进货数量 实际时间 供应商名称
void Add_PurchaseRecord(char *category, char *good_name, float cost_price, int quantity, char *supplier)
{
    FILE *fp = fopen("txt/purchaseInfo.txt", "a");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return;
    }

    char current_time[9];
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    snprintf(current_time, sizeof(current_time), "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);

    // 商品进货信息包括：商品编号、商品名称、进货时间、进货价格、进货数量、进货来源。
    // 这里假设 id 为 0 表示特殊情况（如注释中提到的暴露假账）
    fprintf(fp, "0 %s %s %.2f %d %s\n", good_name, current_time, cost_price, quantity, supplier);
    fclose(fp);
}

// 输入顾客信息
void CustomerInfo_Generate()
{
    char name[50], type[20], contact[50]; // 使用数组代替未初始化的指针

    // 循环输入顾客信息，输入'#'结束输入
    while (1)
    {
        CustomerNode customer;
        printf("请输入顾客姓名（输入'#'结束）：");
        scanf("%49s", name); // 限制输入长度，避免缓冲区溢出
        if (strcmp(name, "#") == 0)
        {
            break; // 输入'#'结束循环
        }
        while (1)
        {
            printf("请输入顾客类型（normal vip svip）：");
            scanf("%19s", type); // 限制输入长度
            if (strcmp(type, "normal") == 0 || strcmp(type, "vip") == 0 || strcmp(type, "svip") == 0)
                break; // 输入合法，退出循环
            else
                printf("输入的顾客类型无效，请重新输入！\n");
        }
        printf("请输入顾客联系方式：");
        scanf("%49s", contact); // 限制输入长度
        printf("顾客信息已添加到系统！\n\n");
        strcpy(customer.name, name);
        strcpy(customer.type, type);
        strcpy(customer.contact, contact);
        Insert_CustomerList(&customer_list, customer);
    }
    // 生成顾客信息文件
    Create_CustomerInfo_File();
}

void Create_CustomerInfo_File()
{
    // 先清空文件
    FILE *fp = fopen("txt/customerInfo.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        exit(1);
    }
    fclose(fp);

    // 按照customer_list的顺序写入文件
    CustomerNode *p = customer_list->next;
    FILE *fp1 = fopen("txt/customerInfo.txt", "a");
    if (fp1 == NULL)
    {
        printf("文件打开失败！\n");
        exit(1);
    }

    while (p != NULL)
    {
        // 确保联系方式字符串以 '\0' 结尾
        size_t len = strlen(p->contact);
        if (len > 0 && p->contact[len - 1] == '\n')
        {
            p->contact[len - 1] = '\0';
        }
        fprintf(fp1, "%d %s %s %s\n", p->id, p->name, p->type, p->contact);
        p = p->next;
    }

    fclose(fp1);
    printf("顾客信息已更新\n");
}

void Add_Customer_To_System()
{
    system("cls");
    printf("请输入添加的顾客信息：\n");
    CustomerInfo_Generate();
}

void Delete_Customer_From_System()
{

    while (1)
    {

        Print_CustomerList(customer_list);
        printf("已存储的顾客信息如上，供参考\n");
        int id;
        printf("请输入要删除的顾客编号（输入'#'退出删除）：");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // 退出删除模式
        }
        id = atoi(input); // 将输入转换为整数
        if (Delete_CustomerList(&customer_list, id) == 1)
        {
            printf("顾客信息已删除！\n\n");
        }
        else
            printf("请重新输入\n\n");
    }
    Create_CustomerInfo_File();
}

void Adjust_Customer_Type()
{

    while (1)
    {
        int id;
        char new_type[30];
        printf("请输入要修改的顾客id（输入'#'退出调整）：");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // 退出调整模式
        }
        id = atoi(input); // 将输入转换为整数
        CustomerNode *p = customer_list->next;
        while (p != NULL && p->id != id)
        {
            p = p->next;
        }
        if (p == NULL)
        {
            printf("未找到该顾客！\n");
            continue;
        }

        printf("请输入新的顾客类型（normal vip svip）：");
        scanf("%s", new_type);
        strcpy(p->type, new_type);

        printf("顾客类型已修改！\n\n");
    }
    Create_CustomerInfo_File();
}

// 从all_good_list中删除商品信息
void Delete_Good_From_System()
{
    while (1)
    {
        system("cls");
        char input[100];
        int id;
        Print_AllGoodList(all_good_list);
        printf("最新的所有商品信息如上所示，供参考：\n");
        printf("请输入要删除的商品ID（输入 '#' 退出）：");
        scanf("%s", input);
        // 清理输入缓冲区
        while (getchar() != '\n')
            ;

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("输入的商品ID无效，请重新输入。\n");
            continue;
        }

        // 调用 Delete_GoodList 函数删除商品
        if (Delete_AllGoodList(&all_good_list, id))
        {
            printf("商品ID为 %d 的商品已成功删除。\n", id);
        }
        else
        {
            printf("未找到商品ID为 %d 的商品，请重新输入。\n", id);
        }
        printf("按回车键继续...");
        while (getchar() != '\n')
            ;
        getchar();
    }
}

// 管理商品售价
void Set_Good_Price()
{
    while (1)
    {
        char input[100];
        int id;
        float new_price;

        printf("请输入要修改售价的商品ID（输入 '#' 退出）：");
        scanf("%s", input);
        // 清理输入缓冲区
        while (getchar() != '\n')
            ;

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("输入的商品ID无效，请重新输入。\n");
            continue;
        }

        printf("请输入新的商品售价：");
        if (scanf("%f", &new_price) != 1)
        {
            printf("输入的售价无效，请重新输入。\n");
            // 清理输入缓冲区
            while (getchar() != '\n')
                ;
            continue;
        }
        // 清理输入缓冲区
        while (getchar() != '\n')
            ;

        // 查找商品并更新售价
        GoodNode *p = all_good_list->next;
        while (p != NULL)
        {
            if (p->id == id)
            {
                p->price = new_price;
                printf("商品ID为 %d 的商品售价已更新为 %.2f。\n", id, new_price);
                break;
            }
            p = p->next;
        }
        if (p == NULL)
        {
            printf("未找到商品ID为 %d 的商品，请重新输入。\n", id);
        }
    }
}

// 管理商品促销信息
void Set_Good_Promotion_Info()
{
    // 先显示所有商品信息
    Print_AllGoodList(all_good_list);
    printf("已有的所有商品信息如上所示，供参考：\n");
    // 循环处理，输入#退出
    while (1)
    {
        int id;
        printf("请输入要设置促销信息的商品id（输入'#'退出）：");
        char input[10];
        scanf("%s", input);
        if (strcmp(input, "#") == 0)
        {
            break; // 退出设置促销信息模式
        }
        id = atoi(input); // 将输入转换为整数
        // 找到id对应的商品
        GoodNode *p = all_good_list->next;
        while (p != NULL && p->id != id)
        {
            p = p->next;
        }
        if (p == NULL)
        {
            printf("未找到该商品！\n");
            continue;
        }
        // 找到商品后，设置促销信息
        char promotion_info[20];
        printf("请输入是否促销，1设置为促销，0设置为不促销：");
        int is_promotion;
        scanf("%d", &is_promotion);
        if (is_promotion == 1)
        {
            p->is_promotion = 1; // 设置为促销
            printf("请输入促销比例（例如输入0.8表示打8折）：");
            float promotion_rate;
            scanf("%f", &promotion_rate);
            p->promotion_price = p->price * promotion_rate;       // 计算促销价格
            sprintf(promotion_info, "%.2f", promotion_rate * 10); // 保留一位小数
            strcat(promotion_info, "折");                         // 添加折号
        }
        else
        {
            p->is_promotion = 0;              // 设置为不促销
            p->promotion_price = 0.0;         // 促销价格为0
            strcpy(promotion_info, "不促销"); // 设置促销信息为不促销
        }
        printf("%s促销信息已设置为：%s\n\n", p->good_name, promotion_info); // 输出促销信息
    }
}

// 将不同的商品类别存储到一个数组中，相同的类别只存储一次
void Get_Good_Category(char category[][100])
{
    // 初始化 category 数组为空字符串
    for (int i = 0; i < 100; i++)
    {
        category[i][0] = '\0';
    }

    GoodNode *p = all_good_list->next; // 指向头结点的下一个节点
    if (p == NULL)
    { // 如果链表为空
        printf("商品类别信息为空！\n");
        return; // 退出函数
    }
    printf("商品类别信息如下：\n");
    int count = 0; // 记录已有的类别数量
    while (p != NULL)
    { // 遍历链表，一行一个商品节点
        int i;
        for (i = 0; i < count; i++)
            if (strcmp(category[i], p->category) == 0)
                break;
        if (i == count)
        {                                         // 如果没有找到相同的类别
            strcpy(category[count], p->category); // 复制类别信息到数组
            count++;                              // 类别数量加1
        }
        p = p->next; // 继续遍历下一个节点
    }
}

// 查看已有的商品类别，相同类别仅打印一次
// 每行打五个就换行
void View_Good_Category()
{
    char category[100][100]; // 存储不同的商品类别
    Get_Good_Category(category);
    int count = 0; // 记录已有的类别数量
    while (count < 100)
    { // 遍历数组，一行一个类别
        if (strcmp(category[count], "") == 0)
            break;                        // 如果数组为空，则退出循环
        printf("%-20s", category[count]); // 输出类别信息
        count++;                          // 类别数量加1
        if (count % 5 == 0)               // 如果已经输出了五个类别，则换行
            printf("\n");
    }
    printf("\n"); // 换行
    printf("按回车继续...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

/// 调整商品分类函数
/// 功能：将指定商品从当前分类移动到新的分类
void Adjust_Good_Category()
{
    while (1)
    {
        system("cls"); // 清屏
        char input[100];
        int id;
        char new_category[50];
        Print_AllGoodList(all_good_list);
        printf("已有的所有商品信息如上所示，供参考：\n\n");
        printf("请输入要调整分类的商品ID（输入 '#' 退出）：");
        scanf("%s", input);

        if (strcmp(input, "#") == 0)
        {
            break;
        }

        id = atoi(input);
        if (id == 0 && strcmp(input, "0") != 0)
        {
            printf("输入的商品ID无效，请重新输入。\n");
            continue;
        }

        printf("请输入新的商品分类：");
        scanf("%s", new_category);

        // 查找商品是否存在，如果存在则更新分类，否则提示商品不存在
        GoodNode *p = all_good_list->next;
        while (p != NULL)
        {
            if (p->id == id)
            {
                strcpy(p->category, new_category); // 更新分类
                printf("商品分类已更新为 %s。\n\n", new_category);
                printf("按回车继续...\n");
                while (getchar() != '\n')
                    ;      // 清空输入缓冲区
                getchar(); // 等待用户按回车
                break;
            }
            p = p->next;
        }
        if (p == NULL)
        { // 如果商品不存在，则提示商品不存在
            printf("商品不存在！请重新输入。\n\n");
        }
    }
}

// 统计每个分类的商品数量
void Caculate_Category_Stock()
{
    while (1)
    {
        system("cls"); // 清屏
        View_Good_Category();
        printf("已有的所有商品类别如上所示，供参考：\n\n");
        printf("请输入要统计的商品类别（输入 '#' 退出）：");
        char category[50];
        scanf("%s", category); // 输入商品类别
        if (strcmp(category, "#") == 0)
            break;
        int count = 0;                     // 记录商品数量
        GoodNode *p = all_good_list->next; // 指向头结点的下一个节点
        while (p != NULL)
        { // 遍历链表，统计商品数量
            if (strcmp(p->category, category) == 0)
            {                      // 如果找到商品类别
                count += p->stock; // 累加商品数量
            }
            p = p->next; // 继续遍历下一个节点
        }
        if (count == 0)
        { // 如果没有找到商品
            printf("未找到 %s 类别，按回车继续...\n", category);
            while (getchar() != '\n')
                ;
            getchar(); // 等待用户按回车
        }
        else
        { // 如果找到商品
            printf("%s 类别商品数量为 %d 件\n", category, count);
            printf("按回车继续...\n");
            while (getchar() != '\n')
                ;      // 清空输入缓冲区
            getchar(); // 等待用户按回车
        }
    }
}

// 删除所有的分类为category的商品
void Delete_Good_Category()
{
    while (1)
    {
        system("cls"); // 清屏
        View_Good_Category();
        printf("已有的所有商品类别如上所示，供参考：\n\n");
        printf("请输入要删除的商品类别（输入 '#' 退出）：");
        char category[50];
        scanf("%s", category);

        if (strcmp(category, "#") == 0)
        {
            break; // 退出循环
        }

        int found = 0;
        GoodNode *prev = all_good_list;
        GoodNode *p = all_good_list->next; // 指向头结点的下一个节点
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
            printf("%s 类别商品删除成功\n", category);
        }
        else
        {
            printf("未找到 %s 类别\n", category);
        }

        printf("按回车继续...");
        while (getchar() != '\n')
            ;      // 清空输入缓冲区
        getchar(); // 等待用户按回车
    }
}

// 添加商品描述// ... existing code ...
void Add_Good_Description()
{
    while (1)
    {
        system("cls");                    // 清屏
        Print_AllGoodList(all_good_list); // 显示所有商品信息
        printf("已有的所有商品信息如上所示，供参考：\n\n");
        printf("请输入要添加描述的商品ID（输入 '#' 退出）：");
        char input[100];
        scanf("%s", input); // 输入商品ID
        // 清空输入缓冲区
        while (getchar() != '\n')
            ;
        if (strcmp(input, "#") == 0)
        { // 如果输入 '#'，退出循环
            break;
        }
        int id = atoi(input);              // 将输入转换为整数
        GoodNode *p = all_good_list->next; // 指向头结点的下一个节点
        while (p != NULL)
        { // 遍历链表，查找商品ID
            if (p->id == id)
            { // 如果找到商品ID
                printf("请输入商品描述：");
                // 使用 fgets 读取包含空格的整行输入
                fgets(p->description, sizeof(p->description), stdin);
                // 移除 fgets 可能读取的换行符
                size_t len = strlen(p->description);
                if (len > 0 && p->description[len - 1] == '\n')
                {
                    p->description[len - 1] = '\0';
                }
                printf("商品描述已添加，按回车继续\n");
                while (getchar() != '\n')
                    ;      // 清空输入缓冲区
                getchar(); // 等待用户按回车
                break;     // 退出循环
            }
            p = p->next; // 继续遍历下一个节点
        }
        if (p == NULL)
        { // 如果未找到商品ID
            printf("未找到该商品，请重新输入，按回车继续\n");
            while (getchar() != '\n')
                ;      // 清空输入缓冲区
            getchar(); // 等待用户按回车
        }
    }
}

void Adjust_Customer_Contact()
{
    while (1)
    {
        system("cls"); // 清屏
        Print_CustomerList(customer_list);
        printf("已有的所有顾客信息如上所示，供参考：\n");
        printf("请输入要修改联系方式的顾客id（输入'#'退出）：");
        char input[10];
        scanf("%s", input); // 输入顾客ID
        if (strcmp(input, "#") == 0)
        { // 如果输入 '#'，退出循环
            break;
        }
        int id = atoi(input);                  // 将输入转换为整数
        CustomerNode *p = customer_list->next; // 指向头结点的下一个节点
        while (p != NULL)
        { // 遍历链表，查找顾客ID
            if (p->id == id)
            { // 如果找到顾客ID
                printf("请输入新的联系方式：");
                scanf("%s", p->contact); // 输入新的联系方式
                printf("联系方式已修改，按回车继续\n");
                while (getchar() != '\n')
                    ;      // 清空输入缓冲区
                getchar(); // 等待用户按回车
                break;     // 退出循环
            }
            p = p->next; // 继续遍历下一个节点
        }
        if (p == NULL)
        { // 如果未找到顾客ID
            printf("未找到该顾客，请重新输入，按回车继续\n");
            while (getchar() != '\n')
                ;      // 清空输入缓冲区
            getchar(); // 等待用户按回车
        }
    }
}

void Admin_Modify_Purchase()
{
    // 打开purchaseInfo.txt文件，
    while (1)
    {
        system("cls");        // 清屏
        Print_PurchaseList(); // 显示所有进货信息
        // 获得purchaseInfo.txt中的第一列，即id，存储到数组中
        int purchase_id[1000];                         // 存储id的数组
        int count = 0;                                 // 记录id的数量
        FILE *fp = fopen("txt/purchaseInfo.txt", "r"); // 打开文件
        if (fp == NULL)
        { // 如果打开文件失败
            printf("文件打开失败！\n");
            exit(1); // 退出程序
        }
        while (1)
        {
            int result = fscanf(fp, "%d", &purchase_id[count]);
            if (result == EOF)
                break; // 到达文件末尾，退出循环
            else if (result == 0)
                while (fgetc(fp) != '\n' && !feof(fp))
                    ;
            else
                count++; // 成功读取一个整数，id数量加1
        }
        fclose(fp); // 关闭文件

        printf("已有的所有进货信息如上所示，供参考：\n");
        printf("请输入选择（0：退出，1：修改记录，2：删除记录，3：增加记录）：");
        int choice;
        scanf("%d", &choice); // 输入选择
        if (choice == 0)      // 如果输入0，退出循环
            break;
        else if (choice == 1)
        {
            printf("请输入要修改的记录id（输入'#'退出）：");
            char input[10];
            scanf("%s", input);
            if (strcmp(input, "#") == 0)
            {
                break;
            }
            int id = atoi(input);
            int found = 0;
            // 遍历id数组，查找id
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
                // 打开原文件用于读取
                FILE *fp = fopen("txt/purchaseInfo.txt", "r");
                if (fp == NULL)
                {
                    perror("文件打开失败");
                    continue;
                }
                // 打开临时文件用于写入
                FILE *temp_fp = fopen("txt/temp.txt", "w");
                if (temp_fp == NULL)
                {
                    perror("临时文件打开失败");
                    fclose(fp);
                    continue;
                }

                char line[256];
                int current_id;
                while (fgets(line, sizeof(line), fp) != NULL)
                {
                    // 从行中解析出第一个整数作为商品编号
                    if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
                    {
                        // 跳过要修改的记录
                        continue;
                    }
                    // 如果当前行不是要修改的记录，则写入临时文件
                    fputs(line, temp_fp);
                }
                fclose(fp);
                fclose(temp_fp);

                // 删除原文件
                remove("txt/purchaseInfo.txt");
                // 重命名临时文件为原文件名
                rename("txt/temp.txt", "txt/purchaseInfo.txt");

                // 输入新的记录信息
                printf("请输入新的记录信息：\n");
                char category[20], good_name[50], supplier[50];
                float cost_price;
                int quantity;
                printf("请输入商品类别：");
                scanf("%19s", category);
                printf("请输入商品名称：");
                scanf("%49s", good_name);
                printf("请输入商品进价：");
                scanf("%f", &cost_price);
                printf("请输入商品数量：");
                scanf("%d", &quantity);
                printf("请输入供应商：");
                scanf("%49s", supplier);

                // 重新打开文件以追加新记录
                fp = fopen("txt/purchaseInfo.txt", "a");
                if (fp == NULL)
                {
                    perror("文件打开失败");
                    continue;
                }

                // current_time与修改的id的那一列的时间一致
                char current_time[10]; // 定义变量

                // 假账id为0
                fprintf(fp, "%d %s %s %.2f %d %s %s\n", 0, category, good_name, cost_price, quantity, current_time, supplier);
                fclose(fp);

                printf("记录修改成功\n");
                printf("按回车键继续...\n");
                while (getchar() != '\n')
                    ;
                getchar();
            }
            else
            {
                printf("未找到该记录编号的进货记录！\n");
            }
        }
        else if (choice == 2)                                // 如果输入2，删除记录
        {                                                    // 清屏
            printf("请输入要删除的记录id（输入'#'退出）："); // 输入要删除的记录id
            char input[10];                                  // 定义输入变量
            scanf("%s", input);                              // 输入
            if (strcmp(input, "#") == 0)
                break;
            int id = atoi(input); // 将输入转换为整数
            int found = 0;
            // 遍历id数组，查找id
            for (int i = 0; i < count; i++)
                if (purchase_id[i] == id) // 如果找到id
                    found = 1;
            if (found) // 如果找到id
            {
                // 打开文件，将id为id的一整行删除
                FILE *fp = fopen("txt/purchaseInfo.txt", "r"); // 打开文件
                FILE *fp2 = fopen("txt/temp.txt", "w");        // 打开文件
                if (fp == NULL || fp2 == NULL)                 // 如果打开文件失败
                {                                              // 如果打开文件失败
                    printf("文件打开失败！\n");                // 输出
                    exit(1);                                   // 退出程序
                }
                char line[100];                               // 定义变量
                int current_id;                               // 用于临时存储从行中解析出的id
                while (fgets(line, sizeof(line), fp) != NULL) // 读取文件
                {
                    if (sscanf(line, "%d", &current_id) == 1 && current_id == id)
                    {
                        // 如果当前行的id等于要删除的id，则跳过该行
                        continue;
                    }
                    // 否则，将该行写入临时文件
                    fprintf(fp2, "%s", line);
                }
                fclose(fp);                                     // 关闭文件
                fclose(fp2);                                    // 关闭文件
                remove("txt/purchaseInfo.txt");                 // 删除文件
                rename("txt/temp.txt", "txt/purchaseInfo.txt"); // 重命名文件
                printf("记录删除成功\n");                       // 输出
                printf("按回车键继续...\n");                    // 输出
                while (getchar() != '\n')                       // 清空输入缓冲区
                    ;
                getchar();
            }
        }
        else if (choice == 3) // 如果输入3，增加记录
        {
            char category[20], good_name[50], supplier[50]; // 定义变量
            float cost_price;                               // 定义变量
            int quantity;                                   // 定义变量
            printf("请输入商品类别：");                     // 输入商品类别
            scanf("%19s", category);                        // 输入
            printf("请输入商品名称：");                     // 输入商品名称
            scanf("%49s", good_name);                       // 输入
            printf("请输入商品进价：");                     // 输入商品进价
            scanf("%f", &cost_price);                       // 输入
            printf("请输入商品数量：");                     // 输入商品数量
            scanf("%d", &quantity);                         // 输入
            printf("请输入供应商：");                       //
            scanf("%49s", supplier);                        // 输入
            printf("记录增加成功\n");                       // 输出
            printf("按回车键继续...\n");                    // 输出
            // 按照格式打印到文件最后一行
            FILE *fp = fopen("txt/purchaseInfo.txt", "a"); // 打开文件
            if (fp == NULL)                                // 如果打开文件失败
            {                                              // 如果打开文件失败
                printf("文件打开失败！\n");                // 输出
                exit(1);                                   // 退出程序
            }
            char current_time[20];
            GetCurrentTime(current_time);
            // 假账id为0
            fprintf(fp, "%d %s %s %.2f %d %s %s\n", 0, category, good_name, cost_price, quantity, current_time, supplier);
            fclose(fp); // 清空输入缓冲区
            while (getchar() != '\n')
                ;
            getchar();
        }
    }
}

// 管理员函数
void Admin()
{
    while (1)
    {
        system("cls");
        // 打印当前时间
        char current_time[20];
        GetCurrentTime(current_time);
        printf("当前时间：%ss\n", current_time);

        printf("【管理员】你好！\n");
        printf("请输入选择：\n");
        printf("0：退出\n");
        printf("1：商品管理&统计\n");
        printf("2：顾客信息管理\n");
        printf("3：进销记录管理&分析\n");
        printf("4：查询\n");
        printf("5：排序\n");
        printf("6：添加&删除账户\n");
        printf("7：备份&恢复密码\n\n");

        // 遍历all_good_list，进行库存提醒，存在商品库存小于50的，一星级提醒，
        // 存在商品库存小于25的，二星级提醒，存在商品库存小于10的，三星级提醒
        // 用五角星符号表示，空的位置用空五角星符号表示
        GoodNode *p = all_good_list->next; // 指向头结点的下一个节点
        int flag10 = 0, flag25 = 0, flag50 = 0, flag_sum;
        while (p != NULL)
        { // 遍历链表，查找商品ID
            if (p->stock < 50)
            {               // 如果找到商品ID
                flag50 = 1; // 库存不足
            }
            if (p->stock < 25)
            {               // 如果找到商品ID
                flag25 = 1; // 库存不足
            }
            if (p->stock < 10)
            {               // 如果找到商品ID
                flag10 = 1; // 库存不足
            }
            p = p->next; // 继续遍历下一个节点
        }
        flag_sum = flag10 + flag25 + flag50;
        switch(flag_sum)
        {
        case 0:
            printf("商品库存充足（紧急程度：☆ ☆ ☆）\n");
            break;
        case 1:
            printf("已有商品库存小于50，请前往处理（紧急程度：★ ☆ ☆）\n");
            break;
        case 2:
            printf("已有商品库存小于25，请前往处理（紧急程度：★ ★ ☆）\n");
            break;
        case 3:
            printf("已有商品库存小于10，请前往处理（紧急程度：★ ★ ★）\n");
            break;
        }

        int choice;
        int choice1;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            return;
            
            break; // 继续循环
        case 1:
            while (1)
            {
                int choice2;
                system("cls");
                printf("商品管理：\n");
                printf("0.退出\n");
                printf("1.进货\n");
                printf("2.查看商品信息\n");
                printf("3.修改商品价格\n");
                printf("4.修改商品促销信息\n");
                printf("5.删除商品信息\n");
                printf("6.查看已有商品类别\n");
                printf("7.调整商品类别\n");
                printf("8.删除某一个类别的所有商品\n");
                printf("9.统计某一个商品类别的商品个数\n");
                printf("10.添加商品描述\n");
                scanf("%d", &choice2);
                switch (choice2)
                {
                case 1: // 进货
                    system("cls");
                    while (1) // 不断进货，直到输入#退出
                    {
                        int choice2;
                        printf("请输入选择：（0：退出，1：手动输入进货，2：从文件导入进货（两种方法可同时使用））\n");
                        scanf("%d", &choice2);
                        if (choice2 == 1) // 手动输入进货
                        {
                            char category[20], good_name[50], supplier[50];
                            float cost_price;
                            int quantity;
                            printf("请输入商品类别（输入'#'退出）：");
                            scanf("%19s", category);
                            if (strcmp(category, "#") == 0)
                            {
                                break; // 输入'#'结束循环
                            }
                            printf("请输入商品名称：");
                            scanf("%49s", good_name);
                            printf("请输入商品进价：");
                            scanf("%f", &cost_price);
                            printf("请输入商品数量：");
                            scanf("%d", &quantity);
                            printf("请输入供应商：");
                            scanf("%49s", supplier);
                            printf("进货成功");
                            printf("\n\n");
                            Purchase(category, good_name, cost_price, quantity, supplier);
                        }
                        else if (choice2 == 2) // 从文件导入进货
                        {
                            // 读取source.txt文件，将文件中的进货信息导入到系统中
                            FILE *fp = fopen("txt/GoodSource.txt", "r");
                            if (fp == NULL)
                            {
                                printf("文件打开失败！\n");
                                break; // 打开文件失败，退出循环
                            }
                            char category[20], good_name[50], supplier[50];
                            float cost_price;
                            int quantity;

                            while (fscanf(fp, "%19s %49s %f %d %49s", category, good_name, &cost_price, &quantity, supplier) != EOF)
                            {
                                float discount;
                                // cost_price设置为文件GoodSource中第三栏进价的30%上下浮动
                                // discount = 0.3*sin(current_time*2*3.14/60)，sin函数的周期为60秒，振幅为0.3
                                float current_time_float = atof(current_time);
                                discount = 0.3 * sin(current_time_float * 2 * 3.14 / 60);
                                cost_price *= (1 + discount);
                                Purchase(category, good_name, cost_price, quantity, supplier);
                            }
                            fclose(fp); // 关闭文件
                            printf("进货成功\n");
                            printf("按回车键继续...\n");
                            while (getchar() != '\n')
                                ;      // 清除输入缓冲区
                            getchar(); // 等待用户按下回车键
                        }
                        else if (choice2 == 0) // 退出
                        {
                            break; // 退出循环
                        }
                    }
                    break;
                case 2:
                    system("cls");
                    printf("所有商品信息如下：\n");
                    // 按回车继续
                    Print_AllGoodList(all_good_list);
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                    break;
                case 3:
                    system("cls");
                    Print_AllGoodList(all_good_list);
                    printf("已存储的商品信息如上，供参考\n");
                    Set_Good_Price();
                    break;
                case 4:
                    system("cls");
                    Set_Good_Promotion_Info();
                    break;
                case 5:
                    Delete_Good_From_System(); // 函数内完成所有界面功能
                    break;
                case 6:
                    system("cls");
                    View_Good_Category();
                    break;
                case 7: // 调整商品类别
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
                    break; // 退出商品信息管理
                default:
                    printf("无效的选择，请重新输入！\n");
                    break;
                }
                if (choice2 == 0)
                    // 如果选择退出商品信息管理，则跳出循环
                    break;
            }
            break;
        case 2:
            while (1)
            {
                system("cls");
                printf("顾客信息管理：\n");
                printf("0.退出\n");
                printf("1.添加顾客信息\n");
                printf("2.调整顾客分类\n");
                printf("3.调整顾客手机号\n");
                printf("4.查看所有顾客信息\n");
                printf("5.删除顾客信息\n");

                scanf("%d", &choice1);
                switch (choice1)
                {
                case 1:
                    system("cls");
                    int choice4;
                    printf("请输入选择：（0：退出，1：手动输入顾客信息，2：从文件导入顾客信息（两种方法可同时使用））\n");
                    scanf("%d", &choice4);
                    if (choice4 == 1) // 手动输入顾客信息
                        Add_Customer_To_System();
                    else if (choice4 == 0) // 退出
                        break;
                    else if (choice4 == 2) // 从文件导入顾客信息
                    {
                        FILE *fp = fopen("txt/CustomerSource.txt", "r");
                        if (fp == NULL)
                        {
                            printf("文件打开失败！\n");
                            break; // 打开文件失败，退出循环
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
                        // 关闭文件
                        fclose(fp);
                        // 生成顾客信息文件
                        Create_CustomerInfo_File();
                        printf("顾客信息导入成功\n");
                        printf("按回车键继续...\n");
                        while (getchar() != '\n')
                            ;      // 清除输入缓冲区
                        getchar(); // 等待用户按下回车键
                    }
                    break;

                case 2:
                    system("cls");
                    Print_CustomerList(customer_list);
                    printf("已存储的顾客信息如上，供参考\n");
                    Adjust_Customer_Type();
                    break;
                case 3:                        // 调整顾客手机号
                    Adjust_Customer_Contact(); // 界面在内部实现
                    printf("按回车键继续...\n");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    break;
                case 4:
                    system("cls");
                    if (customer_list->next == NULL)
                    {
                        printf("顾客信息为空！\n");
                        printf("按回车键继续...");
                        while (getchar() != '\n')
                            ;      // 等待用户按下回车
                        getchar(); // 处理多余的换行符

                        break;
                    }
                    else
                        Print_CustomerList(customer_list);
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                    break;
                case 5:
                    system("cls");
                    Delete_Customer_From_System();
                    break;
                case 0:
                    break; // 退出顾客信息管理
                default:
                    printf("无效的选择，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                    break;
                }
                if (choice1 == 0)
                    // 如果选择退出顾客信息管理，则跳出循环
                    break;
            }
            break;
        case 3: // 进货记录与销售记录
            while (1)
            {
                system("cls");
                int choice2;
                printf("请输入选择：\n0：退出\n1：查看进货记录\n2：查看销售记录\n3：修改进货记录\n");
                scanf("%d", &choice2);
                if (choice2 == 1) // 打印purchaseInfo.txt的内容
                {
                    system("cls");
                    Print_PurchaseList();
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                else if (choice2 == 0)
                    break; // 退出

                else if (choice2 == 2) // 打印saleInfo.txt的内容
                {
                    system("cls");
                    Print_SaleList();
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                else if (choice2 == 3) // 修改进货记录
                {
                    // 仅仅从文件中修改而不影响真实的库存状态，好比做假账
                    Admin_Modify_Purchase();
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                else
                    printf("无效的选择，请重新输入！\n");
            }
            break;
        case 4:
            Admin_Search();
            break;
        case 5:
            Admin_Sort();
            break;
        case 6: // 添加&删除账户
            while (1)
            {
                system("cls");
                printf("请输入选择：（0：退出，1：添加管理员，2：添加售货员，3：删除管理员，4:删除售货员)\n");
                int choice2;
                while (scanf("%d", &choice2) != 1 || choice2 < 0 || choice2 > 4)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请输入选择：（0：退出，1：添加管理员，2：添加售货员，3：删除管理员，4:删除售货员)\n");
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
                    printf("请输入要删除的管理员用户名：");
                    scanf("%s", target);

                    if (delete_admin(&admin_list, target))
                    {
                        save_admin_list(admin_list, "txt/adminLogin.txt");
                        printf("管理员删除成功！\n");
                    }
                    else
                        printf("未找到该管理员！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符

                    free_admin_list(admin_list);
                }
                else if (choice2 == 4)
                {
                    AdminNode *admin_list = load_admin_list("txt/salespersonLogin.txt");
                    if (!admin_list)
                        return;
                    char target[50];
                    printf("请输入要删除的管理员用户名：");
                    scanf("%s", target);

                    if (delete_admin(&admin_list, target))
                    {
                        save_admin_list(admin_list, "txt/salespersonLogin.txt");
                        printf("管理员删除成功！\n");
                    }
                    else
                        printf("未找到该管理员！\n");

                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符

                    free_admin_list(admin_list);
                }
            }
            break;
        case 7: // 备份&恢复密码
            while (1)
            {
                int choice2;
                system("cls");

                printf("请输入选择：（0：退出，1:备份密码，2：恢复密码)\n");
                while (scanf("%d", &choice2) != 1 || choice2 < 0 || choice2 > 2)
                {
                    while (getchar() != '\n')
                        ;
                    printf("输入错误，请重新输入！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;
                    system("cls"); // 清屏
                    printf("请输入选择：（0：退出，1:备份密码，2：恢复密码)\n");
                }
                if (choice2 == 0)
                    break;
                else if (choice2 == 1)
                { // 备份
                    if (backup_admin_file("txt/adminLogin.txt", "txt/adminLogin_backup.txt") &&
                        backup_admin_file("txt/salespersonLogin.txt", "txt/salespersonLogin_backup.txt"))

                        printf("备份成功！\n");
                    else

                        printf("备份失败！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
                if (choice2 == 2)
                { // 恢复
                    if (restore_admin_file("txt/adminLogin_backup.txt", "txt/adminLogin.txt") &&
                        restore_admin_file("txt/salespersonLogin_backup.txt", "txt/salespersonLogin.txt"))
                        printf("恢复成功！\n");
                    else
                        printf("恢复失败！\n");
                    printf("按回车键继续...");
                    while (getchar() != '\n')
                        ;      // 等待用户按下回车
                    getchar(); // 处理多余的换行符
                }
            }
            break;
        default:
            printf("无效的选择，请重新输入，按回车键继续...\n");
            while (getchar() != '\n')
                ;      // 等待用户按下回车
            getchar(); // 处理多余的换行符
            break;
        }
    }
}

// 管理员登录函数
// 登录成功返回1，登录失败返回0
int admin_login()
{
    system("cls");
    char input_username[100];
    char input_password[100];

    // 读取文件中的内容，存储在两个二维数组中
    char usernames[100][100]; // 存储用户名
    char passwords[100][100]; // 存储密码
    int count = 0;            // 记录读取的行数

    FILE *fp = fopen("txt/adminLogin.txt", "r"); // 打开文件，只读模式
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return 0; // 打开文件失败，返回0
    }
    // 逐行读取文件内容，存储到数组中
    while (fscanf(fp, "%s %s", usernames[count], passwords[count]) != EOF)
        count++; // 行数加1
    fclose(fp);  // 关闭文件

    // 提示用户输入用户名和密码
    printf("请输入用户名：");
    scanf("%s", input_username); // 输入用户名
    printf("请输入密码：");
    scanf("%s", input_password); // 输入密码

    // 检查输入的用户名和密码是否与两个二维数组匹配
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(input_username, usernames[i]) == 0 && strcmp(input_password, passwords[i]) == 0)
        {
            printf("登录成功！\n"); // 登录成功
            printf("按回车键继续...\n");
            while (getchar() != '\n')
                ;      // 等待用户按下回车
            getchar(); // 处理多余的换行符
            return 1;  // 返回1
        }
    }
    printf("登录失败！用户名或密码错误。\n"); // 登录失败
    printf("按回车键继续...\n");
    while (getchar() != '\n')
        ;      // 等待用户按下回车
    getchar(); // 处理多余的换行符
    return 0;  // 返回0
}

int add_admin(const char *filename)
{
    char username[50];
    char password[50];
    printf("请输入用户名：");
    scanf("%s", username);

    // 检查是否重复
    FILE *fp = fopen(filename, "r");
    if (fp)
    {
        Adminster temp;
        while (fscanf(fp, "%s %s", temp.username, temp.password) != EOF)
        {
            if (strcmp(temp.username, username) == 0)
            {
                printf("该用户名已存在，不能重复添加！\n");
                printf("按回车键继续...\n");
                while (getchar() != '\n')
                    ;      // 等待用户按下回车
                getchar(); // 处理多余的换行符
                fclose(fp);
                return 0;
            }
        }
        fclose(fp);
    }

    printf("请输入密码：");
    scanf("%s", password);

    // 写入文件
    fp = fopen(filename, "a"); // 追加写入
    if (!fp)
    {
        printf("无法打开文件 %s\n", filename);
        printf("按回车键继续...\n");
        while (getchar() != '\n')
            ;      // 等待用户按下回车
        getchar(); // 处理多余的换行符
        return 0;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    if (strcmp(filename, "txt/adminLogin.txt") == 0)
        printf("管理员添加成功！\n");
    else if (strcmp(filename, "txt/salespersonLogin.txt") == 0)
        printf("售货员添加成功！\n");

    printf("按回车键继续...\n");
    while (getchar() != '\n')
        ;      // 等待用户按下回车
    getchar(); // 处理多余的换行符
    return 1;
}

AdminNode *load_admin_list(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("无法打开文件 %s\n", filename);
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

// 保存管理员链表
void save_admin_list(AdminNode *head, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("无法写入文件 %s\n", filename);
        return;
    }

    while (head)
    {
        fprintf(fp, "%s %s\n", head->data.username, head->data.password);
        head = head->next;
    }

    fclose(fp);
}

// 释放链表内存
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

// 删除管理员
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
            return 1; // 删除成功
        }
        prev = curr;
        curr = curr->next;
    }

    return 0; // 未找到
}

int backup_admin_file(const char *source, const char *backup)
{
    FILE *src = fopen(source, "r");
    if (!src)
    {
        printf("无法打开源文件：%s\n", source);
        return 0;
    }

    FILE *dest = fopen(backup, "w");
    if (!dest)
    {
        printf("无法创建备份文件：%s\n", backup);
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
        printf("无法打开备份文件：%s\n", backup);
        return 0;
    }

    FILE *dest = fopen(target, "w");
    if (!dest)
    {
        printf("无法写入目标文件：%s\n", target);
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
