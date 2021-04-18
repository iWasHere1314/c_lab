#ifndef __BIG_INT_H
#define __BIG_INT_H
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
typedef char* big_int;
bool big_int_initialize( big_int obj, const char* val ){
    size_t len = strlen( val ) + 1;
    bool flag = val[0] !='-' && val[0] != '+';
    if(  flag ){
        ++len;
    }
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return false;
    }
    if( flag ){
        strcpy( temp+1, val );
        temp[0] = '+';
    }
    else{
        strcpy( temp, val );
    }
    obj = temp;
    return true;
}  

void big_int_destory( big_int obj ){
    free( obj );
    return;
}

bool big_int_assign( big_int dst, const big_int src ){
    size_t len = strlen( src )+1;
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return false;
    }   
    strcpy( temp, src );
    free( dst ); //
    dst = temp;
    return true;
}

bool big_int_unsigned_greater( const big_int a, const big_int b ){
    size_t sz_a = strlen( a ), sz_b = strlen( b ), 
        index_a = 0, index_b = 0;
    
}

bool big_int_add( big_int res, const big_int src1, const big_int src2 ){
    size_t sz1 = strlen( src1 ), sz2 = strlen( src2 ),
        len = (sz1>sz2? sz1: sz2) + 1;
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return false;
    }
    temp[len] = '\0';
    if( src1[0] == src2[0] ){
        int carry_in = 0;
        size_t index1=sz1-1, index2=sz2-1, index = len-2;
        while( index1>=1 && index2>=1 ){
            int sum = ( src1[index1]-'0' ) + ( src2[index2]-'0' ) + carry_in;
            carry_in = sum/10;
            temp[index] = '0' + sum%10;
            --index1;
            --index2;
            --index;
        }
        if( index1>=1 ){
            if( carry_in ){
                int sum = ( src1[index1]-'0' ) + carry_in;
                carry_in = sum/10;
                temp[index] = '0' + sum%10;
                --index1;
                --index;
            }
            while( index1>=1 ){
                temp[index] = src1[index1];
                --index1;
                --index;
            }
        }
        else if( index2>=1 ){
            if( carry_in ){
                int sum = ( src2[index2]-'0' ) + carry_in;
                carry_in = sum/10;
                temp[index] = '0' + sum%10;
                --index2;
                --index;
            }
            while( index2>=1 ){
                temp[index] = src2[index2];
                --index2;
                --index;
            }
        }
        else if( carry_in ){
            temp[index] = '1';
            --index;
        }
        temp[index--] = src1[0]; 
        size_t gap = index + 1;
        if( gap ){
            size_t f_len = len - gap;
            for( int i=0; i<f_len; ++i ){
                temp[i] = temp[i+gap];
            }
        }
        temp = ( big_int )realloc( temp, len - gap );
        return big_int_assign( res, temp );
    }
    else{
        int carry_in = 0;
        size_t index1=sz1-1, index2=sz2-1, index = len-2;
        bool flag = big_int_unsigned_greater( src1+1, src2+1 );
        const big_int t_src1 = flag? src1: src2;
        const big_int t_src2 = flag? src2: src1;
        while( index1>=1 && index2>=1 ){
            int sum = ( t_src1[index1]-'0' ) - ( t_src2[index2]-'0' ) - carry_in;
            carry_in = sum < 0;
            temp[index] = carry_in? sum+10+'0': sum+'0';
            --index1;
            --index2;
            --index;
        }
        if( index1>=1 ){
            if( carry_in ){
                int sum = ( t_src1[index1]-'0' ) - carry_in;
                temp[index] = '0' + sum;
                --index1;
                --index;
            }
            while( index1>=1 ){
                temp[index] = src1[index1];
                --index1;
                --index;
            }
        }
        else if( index2>=1 ){
            if( carry_in ){
                int sum = ( t_src2[index2]-'0' ) - carry_in;
                temp[index] = '0' + sum;
                --index2;
                --index;
            }
            while( index2>=1 ){
                temp[index] = src2[index2];
                --index2;
                --index;
            }
        }
        temp[index--] = t_src1[0];
        size_t gap = index + 1;
        if( gap ){
            size_t f_len = len - gap;
            for( int i=0; i<f_len; ++i ){
                temp[i] = temp[i+gap];
            }
        }
        temp = ( big_int )realloc( temp, len - gap );
        return big_int_assign( res, temp );
    }
}

bool big_int_sub( big_int res, const big_int src1, const big_int src2 ){
    size_t len = strlen( src2 )+1;
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return false;
    }   
    strcpy( temp, src2 );
    temp[0] = src2[0]=='+' ? '-': '+';
    bool res=big_int_add( res, src1, temp );
    free( temp );
    return res;
}

#endif