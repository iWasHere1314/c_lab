#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H
#include<stdbool.h>
#include<malloc.h>
typedef struct linked_list_node{
    int val;
    struct linked_list_node* next;
}linked_list_node, *linked_list;

bool linked_list_initialize( linked_list obj){
    linked_list temp =(linked_list)malloc( sizeof( linked_list_node ) );
    if( !temp ){
        return false;
    }
    obj = temp;
    return true;
}
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