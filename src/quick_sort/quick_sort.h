#ifndef __QUICK_SORT_H
#define __QUICK_SORT_H

#include<malloc.h>

void swap( int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
    return;
}
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
    }
    int flag = nums[start];
    int left=start;
    int right=end-1;
    while( left<right ){
        while( left<right && nums[right]>=flag ){ right--; }
        nums[left]=nums[right];
        while( left<right && nums[left]<=flag ){ left++; }
        nums[right]=nums[left];
    }
    nums[left]=flag;
    return left;
}
void qSort( int nums[], int start, int end ){
   if( start<end-1){  
        if( end-start>10 ){
            int mid = partiton( nums, start, end );
            qSort( nums, start, mid);
            qSort( nums, mid+1, end);
        }
        else{
            insertSort( nums, start, end);
        }
    }
}

#endif