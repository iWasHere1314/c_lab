#include"bmp_zoom.h"
#include"stdio.h"
int main( int argc, char* argv[] ){
    if( argc != 4 ){
        printf("参数错误\n");
        return 0;
    } 
    char *src = argv[1];
    int percent = atoi( argv[2] );
    char *dst = argv[3];
    printf("%s", bmp_zoom( src, dst, percent )? "放缩成功\n":"放缩失败\n");
    return 0;
}