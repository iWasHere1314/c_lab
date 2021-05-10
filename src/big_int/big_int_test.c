#include<stdio.h>
#include"big_int.h"
int main(){
    big_int a, b;
    a = big_int_initialize( "12345678912345678912345678912345" );
    b = big_int_initialize( "-98765432198765432198765432198765");
    big_int add_res, sub_res;
    add_res = big_int_add( a, b );
    sub_res = big_int_sub( a, b );
    printf("%s\n", a );
    printf("%s\n", b );
    printf("%s\n", add_res );
    printf("%s\n", sub_res );
    big_int_destory(a);
    big_int_destory(b);
    big_int_destory(add_res);
    big_int_destory(sub_res);
    return 0;
}