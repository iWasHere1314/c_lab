#include"bmp_zoom.h"
#include"stdio.h"
int main(){
    bmp_zoom( "/home/professor/MyProgram/c_lab/test.bmp", "/home/professor/MyProgram/c_lab/bigger.bmp", 400 );
    bmp_zoom( "/home/professor/MyProgram/c_lab/test.bmp", "/home/professor/MyProgram/c_lab/smaller.bmp", 50 );
    return 0;
}