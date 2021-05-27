#include <stdio.h>

void find1(char array[], char search, char **ppa) 
{ 
    int i; 
    for (i = 0; *(array + i) != 0; i++) 
    { 
        if ( *(array+i) == search){ 
            *ppa = array + i; 
            break; 
        } else if (*(array+i) == 0) { 
            *ppa = 0; 
            break; 
        } 
    } 
} 

int main() 
{ 
    // char str[] = {"afsdfsdfdf\0"}; /* 待查找的字符串 */ 
    // char a = 'd'; /* 设置要查找的字符 */ 
    // char *p = 0; /* 如果查找到后指针 p 将指向字符串中查找到的第 1 个字符的地址。 */ 
    // find1(str, a, &p); /* 调用函数以实现所要操作。 */ 
    // if (0 == p) 
    // { 
    //     printf("没找到！\n"); /* 如果没找到则输出此句 */ 
    // } 
    // else 
    // { 
    //     printf("找到了，p = %d", p); /* 如果找到则输出此句*/ 
    // } 
    printf("\a");
    int Case,If,While,Stop,stop;
    return 0; 
} 