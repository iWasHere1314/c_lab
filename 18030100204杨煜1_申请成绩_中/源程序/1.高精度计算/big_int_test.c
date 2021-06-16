#include<stdio.h>
#include<stdbool.h>
#include"big_int.h"
int main(){
    int choice;
    big_int a, b, res;
    char t_a[512], t_b[512];
    bool is_end = false;
    while( !is_end ){
        printf("请选择功能\n");
        printf("1.加法\n2.减法\n3.退出程序\n");
        scanf("%d", &choice );
        switch( choice ){
            case 1:{
                printf("请输入两个操作数\n");
                scanf("%s %s", t_a, t_b );
                a = big_int_initialize(t_a);
                b = big_int_initialize(t_b);
                res = big_int_assign( big_int_add(a,b) );
                printf("结果为：%s\n", res );
                free( a );
                free( b );
                free( res );
                break;
            };
            case 2:{
                printf("请输入两个操作数\n");
                scanf("%s %s", t_a, t_b );
                a = big_int_initialize(t_a);
                b = big_int_initialize(t_b);
                res = big_int_assign( big_int_sub(a,b) );
                printf("结果为：%s\n", res );
                free( a );
                free( b );
                free( res );
                break;
            };
            case 3:{
                printf("退出程序\n");
                is_end = true;
                break;
            };
            default:{
                printf("不存在此选项,请重新输入\n");
                break;
            };
        }
    }

    return 0;
}