#include<stdio.h>
#include<stdbool.h>
#include "linked_list.h"
int main(){
    int choice;
    linked_list obj = linked_list_initialize();
    bool is_end = false;
    while( !is_end ){
        printf("请选择功能\n");
        printf("1.插入节点\n2.删除节点\n3.遍历链表\n4.结束程序\n");
        scanf("%d", &choice );
        switch( choice ){
            case 1:{
                int loc, val;
                printf("请输入要在哪个位置后插入节点\n");
                scanf("%d", &loc );
                printf("请输入节点节点值\n");
                scanf("%d", &val );
                if( linked_list_insert(obj, loc, val ) ){
                    printf("插入成功\n");
                }
                else{
                    printf("插入失败\n");
                }
                break;
            };
            case 2:{
                int loc;
                printf("请输入要在哪个位置后删除节点\n");
                scanf("%d", &loc );
                if( linked_list_delete(obj, loc) ){
                    printf("删除成功\n");
                }
                else{
                    printf("删除失败\n");
                }
                break;
            };
            case 3:{
                printf("链表打印结果如下\n");
                linked_list_print( obj);
                break;
            }
            case 4:{
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
    linked_list_destory( obj );
    return 0;
}