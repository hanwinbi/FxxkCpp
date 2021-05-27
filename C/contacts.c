/*
This is a small contact program for C language practice.
Author: hanwinbi

使用二进制形式存储数据
通讯录联系人数据结构定义姓名 电话 地址 邮箱
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//contact detail
typedef struct{
    char name[12];
    char phone_num[12];
    char address[100];
    char email[100];
}Contact;

//contacts is a link list,because we don't know how many contact will add to it.
typedef struct{
    Contact* head;
}Contacts;

enum eSearchType{by_index, by_key};//because I just wanna use enum datatype, I did this. but it actually not nesessarry.

void add();
FILE* OpenFile();
void SaveFile(Contact *contact);
int contact_num();
void ShowContact();
int Delete_contact();
void modify();
int init();

int main(){
    // printf("**********Contacts**********\n");
    // printf("*    1.查看通讯录          *\n");
    // printf("*    2.添加联系人          *\n");
    // printf("**********Contacts**********\n");
    // FILE *fp = OpenFile();
    // Contact someone;
    // add(&someone);
    // SaveFile(&someone);
    // add(&someone);
    // SaveFile(&someone);

    // ShowContact();
    // Delete_contact();
    // modify();
    int end = 0;
    while(1){
        if(!end){
            end = init();
        }else{
            break;
        }
    }
    
    return 0;

}

int init(){
    printf("**********Contacts**********\n");
    printf("*                         *\n");
    printf("*    1.查看通讯录          *\n");
    printf("*    2.添加联系人          *\n");
    printf("*    3.修改联系人          *\n");
    printf("*    4.删除联系人          *\n");
    printf("*                         *\n");
    printf("**********Contacts**********\n");

    printf("输入操作编号：");
    int op;
    scanf("%d", &op);
    Contact someone;
    switch (op)
    {
    case 1:
        system("clear");
        ShowContact();
        break;
    case 2:
        add(&someone);
        SaveFile(&someone);
        break;
    case 3:
        ShowContact();
        modify();
        break;
    case 4:
        Delete_contact();
        break;
    default:
        return 1;
        break;
    }
    return 0;
}

//count of contact
int contact_num(){
    FILE *fp = fopen("data.in","r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    int num = size / sizeof(Contact);
    fclose(fp);
    return num;
}

//open file of contact, I use this function just for use encapsulation
FILE* OpenFile(){
    FILE *fp = fopen("data.in", "r");
    
    if(fp){
        return fp;
    }else{
        printf("通讯录文件打开失败！");
    }
    return NULL;
}

//save modified file
void SaveFile(Contact *contact){
    FILE *fp = fopen("data.in","a");
    if(fp){
        fwrite(contact, sizeof(Contact), 1, fp);
        fclose(fp);
    }else{
        printf("通讯录文件打开失败！");
    }
}

//show all contact detail
void ShowContact(){
    FILE *fp = fopen("data.in","r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    int num = size / sizeof(Contact);   
    printf("we have %d contact\n", num);
    
    if(fp){
        for(int i = 0; i < num; ++i){
            fseek(fp, i*sizeof(Contact), SEEK_SET);
            Contact someone;
            fread(&someone, sizeof(Contact), 1, fp);
            printf("%d. ", i);
            printf("姓名：%s\t", someone.name);
            printf("电话号码：%s\t", someone.phone_num);
            printf("地址：%s\t", someone.address);
            printf("邮箱：%s\t", someone.email);
            printf("\n");
        }
        fclose(fp);
    }else{
        printf("通讯录文件打开失败！");
    }
}

//add contact
void add(Contact *contact){
    printf("请输入姓名：");
    scanf("%s", contact->name);
    printf("请输入电话号码：");
    scanf("%s", contact->phone_num);
    printf("请输入地址：");
    scanf("%s", contact->address);
    printf("请输入邮箱：");
    scanf("%s", contact->email);
}

//delete contact by phone num or name
//C can not delete piece of file and save, do this function by copy all file to the another
int Delete_contact(){
    ShowContact();
    FILE *fpsrc = fopen("data.in", "r");
    FILE *fpdst = fopen("data.out", "w");

    fseek(fpsrc, 0, SEEK_END);
    long size = ftell(fpsrc);
    int num = size / sizeof(Contact);

    Contact someone;
    printf("1. 输入标号删除\n");
    printf("2. 输入姓名删除\n");
    int input;
    scanf("%d", &input);

    if(input == 1){
        fseek(fpsrc, 0, SEEK_SET);
        int index;
        char null[10];
        printf("输入要删除联系人的编号：");
        scanf("%d", &index);
        
        if(num == 1 && index == 0){
            remove("data.in");
            rename("data.out", "data.in");
            return 0;
        }else{
            for(int i = 0; i < num; ++i){
                Contact temp;
                if(i != index){
                    fseek(fpsrc, i*sizeof(Contact), SEEK_SET);
                    fread(&temp, sizeof(Contact), 1, fpsrc);
                    fwrite(&temp, sizeof(Contact), 1, fpdst);
                }
            }
        }
        
    }
    else if(input == 2){
        char key[12];
        printf("输入要删除联系人的姓名：");
        scanf("%s", key);
        for(int i = 0; i < num; ++i){
            Contact temp;
            fseek(fpsrc, i*sizeof(Contact), SEEK_SET);
            fread(&temp, sizeof(Contact), 1, fpsrc);
            if(num == 1 && i == 0){
                remove("data.in");
                fclose(fpdst);
                rename("data.out", "data.in");
                return 0;
            }
            if(temp.name != key){
                printf("%d", key == temp.name);
                printf("key:%s name:%s\n", key, temp.name);
                fwrite(&temp, sizeof(Contact), 1, fpdst);
            }
        }
    }
    else{
        printf("输入错误，请重新输入!(0退出)\n");
        scanf("%d", &input);
    }
    fclose(fpsrc);
    fclose(fpdst);
    remove("data.in");
    rename("data.out", "data.in");
    return 1;
}

//modify contact detail, only available for index
void modify(){
    FILE *fp = fopen("data.in", "w");
    int index;
    printf("请输入要修改的联系人编号：");
    scanf("%d", &index);
    Contact someone;
    fseek(fp, index*sizeof(Contact), SEEK_SET);
    printf("请输入姓名：");
    scanf("%s", someone.name);
    printf("请输入电话号码：");
    scanf("%s", someone.phone_num);
    printf("请输入地址：");
    scanf("%s", someone.address);
    printf("请输入邮箱：");
    scanf("%s", someone.email);
    fwrite(&someone, sizeof(Contact), 1, fp);
    fclose(fp);
}
