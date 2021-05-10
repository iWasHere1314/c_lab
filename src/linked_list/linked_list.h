#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H
#include<stdbool.h>
#include<malloc.h>

/* 
 * 链表从下标0开始计算下标,但下标为0的结点是用于代表链表的头结点,
 * 其值并无实际意义, 故有效的链表结点下标大于等于1
 */

typedef struct linked_list_node{
    int val;
    struct linked_list_node* next;
}linked_list_node, *linked_list;// 定义链表的结点

/*
 * 函数名称: linked_list_initialize
 * 函数功能: 初始化链表,即分配头结点
 * 参数: 无
 * 返回值: linked_list( 表示分配结果 )
 */
linked_list linked_list_initialize( ){
    linked_list temp =(linked_list)malloc( sizeof( linked_list_node ) );
    if( !temp ){
        return NULL;
    }
    return temp;
}

/*
 * 函数名称: linked_list_insert
 * 函数功能: 在链表的某一结点后插入一个结点
 * 参数: linked_list obj( 链表头结点 ) ,size_t loc( 要插入的位置的前一个结点的位置 ),
 *       int val( 新结点的值 )
 * 返回值: bool( 表示操作是否成功 )
 */
bool linked_list_insert( linked_list obj ,size_t loc, int val ){
    linked_list_node* cur = obj;
    size_t cnt=0;
    while( cur && cnt<loc ){
        cur = cur->next;
        ++cnt;
    }
    if( cnt<loc ){
        return false;
    }
    linked_list temp =(linked_list)malloc( sizeof( linked_list_node ) );
    if( !temp ){
        return false;
    }
    temp->val = val;
    cur->next = temp;
    return true;
}

/*
 * 函数名称: linked_list_delete
 * 函数功能: 删除链表的某一结点后的一个结点
 * 参数: linked_list obj( 链表头结点 ) ,size_t loc( 要删除的位置的前一个结点的位置 ),
 * 返回值: bool( 表示操作是否成功 )
 */
bool linked_list_delete( linked_list obj ,size_t loc ){
    if( !loc ){
        return false;
    }
    linked_list_node* cur = obj;
    size_t cnt=0;
    while( cur && cnt<loc-1 ){
        cur = cur->next;
        ++cnt;
    }
    if( cnt<loc || !cur->next ){
        return false;
    }
    linked_list_node* temp = cur->next->next;
    free( cur->next );
    cur->next = temp;
    return true;
}

/*
 * 函数名称: linked_list_print
 * 函数功能: 遍历链表并输出所有结点的值
 * 参数: linked_list obj( 链表头结点 )
 * 返回值: void
 */
void linked_list_print( linked_list obj ){
    linked_list_node* cur = obj->next;
    while( cur ){
        printf("%d ",cur->val);
        cur = cur->next;
    }
    printf("\n");
    return;
}
#endif