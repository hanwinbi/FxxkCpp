#include <stdio.h>
#include <stdlib.h>

int main(){
	
	// int *p;
	// int count = 0;
	// p = (int *)malloc(sizeof(int) * 100);
	// free(p);
	// return 0;

	// 相邻两次malloc分配得到的空间是否连续
	// int *p,*q;
	// p = (int *)malloc(sizeof(int));
	// q = (int *)malloc(sizeof(int));
	// printf("p 的地址是%p\n", p);
	// printf("q 的地址是%p\n", q);
	// return 0;

	// 用数组表示连续的月份
	char *a[] = {"January","February","March","April", "May", "June", "July", "August","September","October","November","December" };
	for(int i = 0; i < 12; i++){
		printf("%s\n", a[i]);
	}
}
