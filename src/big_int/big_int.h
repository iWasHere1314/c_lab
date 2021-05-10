#ifndef __BIG_INT_H
#define __BIG_INT_H
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
typedef char* big_int;// 采用字符数组存储大整数, 大整数首地址即字符指针
/*
 * 函数名称: big_int_initialize
 * 函数功能: 初始化一个大整数, 包括分配地址空间与初始赋值
 * 参数: big_int obj( 保存分配地址的指针 ), const char* val( 表示初始值得字符串 )
 * 返回值: big_int( 表示结果 )
 */
big_int big_int_initialize( const char* val ){
    size_t len = strlen( val ) + 1; // 字符数组需要多一个字符存储终结符
    bool flag = val[0] !='-' && val[0] != '+';// 标识初始值是否有符号
    if(  flag ){
        ++len;
    }// 如果输入的无符号, 则添加上'+', 从而数组长度需要加1
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return NULL;
    }// 分配空间, 若成功则继续执行, 失败则返回错误
    if( flag ){
        strcpy( temp+1, val );
        temp[0] = '+';
    }
    else{
        strcpy( temp, val );
    }// 初始输入确定拷贝起始位置
    return temp;
}  

/*
 * 函数名称: big_int_destory
 * 函数功能: 销毁一个大整数
 * 参数: big_int obj( 要销毁的大整数的首地址 )
 * 返回值: void
 */
void big_int_destory( big_int obj ){
    free( obj );
    return;
}

/*
 * 函数名称: big_int_assign
 * 函数功能: 为一个大整数赋值
 * 参数: big_int dst( 被赋值的数 ), const big_int src( 赋值来源 )
 * 返回值: big_int( 表示结果 )
 */
big_int big_int_assign( big_int dst, const big_int src ){
    size_t len = strlen( src )+1;// 多一位存储终结符
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return NULL;
    }   
    strcpy( temp, src );
    free( dst ); 
    return temp;
}

/*
 * 函数名称: big_int_unsigned_greater
 * 函数功能: 无符号大整数大于运算
 * 参数: const big_int a( 大于运算左侧操作数 ), const big_int b( 大于运算右侧操作数 )
 * 返回值: bool( 表示是否大于 )
 */
bool big_int_unsigned_greater( const big_int a, const big_int b ){
    size_t sz_a = strlen( a ), sz_b = strlen( b );
    if( sz_a != sz_b){
        return sz_a>sz_b;
    }// 长度不同时, 长度长的数字大
    for( size_t i=1; i<sz_a; --i ){
        if( a[i] != b[i] ){
            return a[i] > b[i];
        }
    }// 长度相同时, 最高不等位的比较结果即最终结果
    return false;// 每一位均相等, 即两数相等, 即不大于
}

/*
 * 函数名称: big_int_add
 * 函数功能: 大整数加法
 * 参数: big_int res( 存储运算结果的大整数 ), const big_int src1( 操作数1 ),
 *       const big_int src2( 操作数2 )
 * 返回值: big_int( 表示结果 )
 */
big_int big_int_add( const big_int src1, const big_int src2 ){
    size_t sz1 = strlen( src1 ), sz2 = strlen( src2 ),
        len = (sz1>sz2? sz1:  sz2) + 2;
        // 加法结果的位数不会超过两个操作数长度最大者加一
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return NULL;
    }
    temp[len-1] = '\0';// 添加终结符
    if( src1[0] == src2[0] ){
        // 两数符号相同时, 绝对值相加, 最后添上符号位即可
        int carry_in = 0;// 进位值
        size_t index1=sz1-1, index2=sz2-1, index = len-2;
        while( index1>=1 && index2>=1 ){
            // 从低位到高位按位相加
            int sum = ( src1[index1]-'0' ) + ( src2[index2]-'0' ) + carry_in;
            carry_in = sum/10;
            temp[index] = '0' + sum%10;
            --index1;
            --index2;
            --index;
        }

        // 将长度更长的数的剩余位和进位加到结果中
        while( index1>=1 ){
            int sum = ( src1[index1]-'0' ) + carry_in;
            carry_in = sum/10;
            temp[index] = '0' + sum%10;
            --index1;
            --index;
        }
        while( index2>=1 ){
            int sum = ( src2[index2]-'0' ) + carry_in;
            carry_in = sum/10;
            temp[index] = '0' + sum%10;
            --index2;
            --index;
        }
        if( carry_in ){
            temp[index] = '1';
            --index;
        }
        temp[index--] = src1[0];// 确定符号位
        size_t gap = index + 1;// 表示最终结果相对于首地址的偏移
        if( gap ){
            //若有空余空间, 填满空间的前端
            size_t f_len = len - gap;
            for( size_t i=0; i<f_len; ++i ){
                temp[i] = temp[i+gap];
            }
        }
        temp = ( big_int )realloc( temp, len - gap );// 释放需要的地址空间
        return temp;// 赋值并返回结果
    }
    else{
        // 两数符号不同时, 用绝对值大的数的绝对值减绝对值小的数的绝对值,
        // 结果符号位为绝对值大的数的符号位
        int carry_in = 0;// 借位值
        bool flag = big_int_unsigned_greater( src1+1, src2+1 );
            // 确定绝对值大的是哪一个操作数
        const big_int t_src1 = flag? src1:  src2;// 绝对值较大的数
        const big_int t_src2 = flag? src2:  src1;// 绝对值较小的数
        size_t t_sz1 = flag? sz1: sz2;
        size_t t_sz2 = flag? sz2: sz1;
        size_t index1=t_sz1-1, index2=t_sz2-1, index = len-2;
        while( index1>=1 && index2>=1 ){
            int sum = ( t_src1[index1]-'0' ) - ( t_src2[index2]-'0' ) - carry_in;
            carry_in = sum < 0;// 若结果小于0则表示不够减, 需要借位
            temp[index] = carry_in? sum+10+'0':  sum+'0';
            --index1;
            --index2;
            --index;
        }
        while( index1>=1 ){
            int sum = ( t_src1[index1]-'0' ) - carry_in;
            carry_in = sum < 0;// 若结果小于0则表示不够减, 需要借位
            temp[index] = carry_in? sum+10+'0':  sum+'0';
            --index1;
            --index;
        }
        while( index2>=1 ){
            int sum = ( t_src1[index2]-'0' ) - carry_in;
            carry_in = sum < 0;// 若结果小于0则表示不够减, 需要借位
            temp[index] = carry_in? sum+10+'0':  sum+'0';
            --index2;
            --index;
        }// 此运算规则下运算结果一定不会向比最高位更高的位借位
        temp[index--] = t_src1[0];
        size_t gap = index + 1;
        if( gap ){
            size_t f_len = len - gap;
            for( size_t i=0; i<f_len; ++i ){
                temp[i] = temp[i+gap];
            }
        }
        temp = ( big_int )realloc( temp, len - gap );
        return temp;
    }
}

/*
 * 函数名称: big_int_sub
 * 函数功能: 大整数减法
 * 参数: big_int res( 存储运算结果的大整数 ), const big_int src1( 被减数 ),
 *       const big_int src2( 减数 )
 * 返回值: bool( 表示是否成功进行了运算 )
 */
big_int big_int_sub( const big_int src1, const big_int src2 ){
    size_t len = strlen( src2 )+1;// 多一位用于存储终结符
    big_int temp = (big_int)malloc( sizeof(char)*(len) );
    if( !temp ){
        return NULL;
    }// 分配空间用于临时存储取反后的减数
    strcpy( temp, src2 );
    temp[0] = src2[0]=='+' ? '-':  '+';// 取反
    temp=big_int_add( src1, temp );// 减法相当于加上减数的相反数
    return temp;
}

#endif