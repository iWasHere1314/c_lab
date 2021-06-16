#include"ktv.h"
#include<stdio.h>
#include<stdlib.h>
int main( int argc, char* argv[] ){
    if( argc != 3 ){
        printf("参数错误\n");
        return 0;
    }
    ktv_start( argv[1][1], argv[2] );
    return 0;
}