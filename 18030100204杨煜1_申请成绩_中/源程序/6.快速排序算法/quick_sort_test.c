#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"quick_sort.h"

int main(){
    srand( time( NULL ) );
    int org_num[20];
    for( int i=0; i<5; ++i ){
        for( int j=0; j<20; ++j ){
            org_num[j] = rand();
        }// 获取20个随机数
        printf("未排序的序列为：\n");
        for( int j=0; j<20; ++j ){
            printf("%d ", org_num[j] );
        }// 显示未排序的序列
        printf("\n");
        quick_sort( org_num, 0, 20 );
        printf("排序后的序列为\n");
        for( int j=0; j<20; ++j ){
            printf("%d ", org_num[j] );
        }// 显示已排序的序列
        printf("\n\n");
    }
    return 0;
}