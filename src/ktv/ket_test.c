#include"ktv.h"
#include<stdio.h>
#include<stdlib.h>
int main(){
    ktv_start( 'a', "yyang" );
    ktv_start( 'a', "nihao" );
    ktv_start( 'a', "ma" );
    ktv_start( 'u', "yyang" );
    ktv_start( 'u', "nihao" );
    ktv_start( 'u', "ma" );
    ktv_start( 'a', "abcd" );
    ktv_start( 'u', "abcd" );
    ktv_start( 'x', "abcd" );
    ktv_start( 'y', "abcd" );
    ktv_start( 'z', "abcd" );
}