#ifndef __QUICK_SORT_H
#define __QUICK_SORT_H

#include<malloc.h>

/*
 * 函数名称：swap
 * 函数功能：交换两个个指针指向的对象的内容
 * 参数: int *a( 操作数1 ), int *b( 操作数2 )
 * 返回值：void
 */
void swap( int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
    return;
}
/*
 * 函数名称：insertSort
 * 函数功能：插入排序
 * 参数: int nums[]( 待排序数组首地址 ), int start( 开始排序的位置 ), 
 *       int end( 结束排序的位置加1 )
 * 返回值：void
 */
void insertSort( int nums[], int start, int end){
    for( int i=start+1; i<end; i++ ){
        if( nums[i]<nums[i-1] ){
            int temp = nums[i];
            int j;
            for( j=i-1; j>=0; j-- ){
                if( nums[j]>temp ){
                    nums[j+1]=nums[j];
                }
                else{
                    break;
                }
            }
            nums[j+1] = temp;
        }
    }
}
/*
 * 函数名称：partiton
 * 函数功能：划分数组
 * 参数: int nums[]( 待划分数组首地址 ), int start( 开始划分的位置 ), 
 *       int end( 结束划分的位置加1 )
 * 返回值：int( 表示大小位于中间的数的位置 )
 */
int partiton( int nums[], int start, int end ){
    int mid= (start+end-1)/2;
    if( nums[start]>nums[end-1] ){
        swap( &nums[start], &nums[end-1] );
    }
    if( nums[mid]>nums[end-1] ){
        swap( &nums[end-1], &nums[mid] );
    }
    if( nums[mid]>nums[start] ){
        swap( &nums[start], &nums[mid] );
    }// 使得第一个元素是左中右中大小中等的, 这样有助于提升性能
    int flag = nums[start];
    int left=start;
    int right=end-1;
    while( left<right ){
        while( left<right && nums[right]>=flag ){ right--; }
        nums[left]=nums[right];
        while( left<right && nums[left]<=flag ){ left++; }
        nums[right]=nums[left];
    }//执行划分
    nums[left]=flag;//把首元素填入对应位置
    return left;
}
/*
 * 函数名称：quick_sort
 * 函数功能：快速排序
 * 参数: int nums[]( 待排序数组首地址 ), int start( 开始排序的位置 ), 
 *       int end( 结束排序的位置加1 )
 * 返回值：void
 */
void quick_sort( int nums[], int start, int end ){
   if( start<end-1){  
        if( end-start>10 ){
            // 若排序范围大于10, 则选择快速排序
            int mid = partiton( nums, start, end );//划分待排序列
            quick_sort( nums, start, mid);// 排序划分后的左半部分
            quick_sort( nums, mid+1, end);// 排序划分后的右半部分
        }
        else{
            // 否则选择插入排序
            insertSort( nums, start, end);
        }
    }
}

#endif