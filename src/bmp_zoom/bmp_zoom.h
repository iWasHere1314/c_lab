#ifndef __BMP_ZOOM_H
#define __BMP_ZOOM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COLOR_WIDTH 3
#pragma pack(1) /* 必须在结构体定义之前使用,这是为了让结构体中各成员按1字节对齐*/
typedef struct tagBITMAPFILEHEADER {
    unsigned short bfType; //保存图片类型。 'BM'
    unsigned int bfSize; //位图文件的大小，以字节为单位（3-6字节，低位在前）
    unsigned short bfReserved1; //位图文件保留字，必须为0(7-8字节）
    unsigned short bfReserved2; //位图文件保留字，必须为0(9-10字节）
    unsigned int bfOffBits; // RGB数据偏移地址,位图数据的起始位置，以相对于位图（11-14字节，低位在前）
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    unsigned int biSize;  //本结构所占用字节数（15-18字节）
    unsigned int biWidth; //位图的宽度，以像素为单位（19-22字节）
    unsigned int biHeight; //位图的高度，以像素为单位（23-26字节）
    unsigned short biPlanes; //目标设备的级别，必须为1(27-28字节）
    unsigned short biBitCount; //每个像素所需的位数，必须是1（双色）（29-30字节）,4(16色），8(256色）16(高彩色)或24（真彩色）之一
    unsigned int biCompression; //位图压缩类型，必须是0（不压缩），（31-34字节）
        // 1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
    unsigned int biSizeImage; //位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
    unsigned int biXPelsPerMeter; //位图水平分辨率，每米像素数（39-42字节）
    unsigned int biYPelsPerMeter; //位图垂直分辨率，每米像素数（43-46字节)
    unsigned int biClrUsed; //位图实际使用的颜色表中的颜色数（47-50字节）
    unsigned int biClrImportant; //位图显示过程中重要的颜色数（51-54字节）
} BITMAPINFOHEADER;

/*
 * 函数名称：bmp_zoom
 * 函数功能：图片放大缩小
 * 参数: const char *src( 要被放缩的图片名称 ), const char *dst( 放缩结果的名称 ) ,
 *       int percent( 放缩的百分比 )
 * 返回值：bool( 表示操作是否存在成功 )
 */
bool bmp_zoom( const char *src, const char *dst , int percent ){
    FILE *fpsrc = fopen(src, "rb");// 打开源图片
    FILE *fpdst = fopen(dst, "wb");// 创建目标图片
    if( !fpsrc || !fpdst ){// 打开失败
        return false;
    }
    BITMAPFILEHEADER head;
    BITMAPINFOHEADER info;
    memset(&head,0,sizeof(BITMAPFILEHEADER));
	memset(&info,0,sizeof(BITMAPINFOHEADER));
    fread(&head, sizeof(BITMAPFILEHEADER), 1, fpsrc );
    fread(&info, sizeof(BITMAPINFOHEADER), 1, fpsrc );
        // 获取源图片文件头部信息
    unsigned int src_width = info.biWidth;   //获取原图片的宽
    unsigned int src_height = info.biHeight; //获取原图片的高

    //获取原图片的位图数据
    unsigned char *src_data = (unsigned char *)malloc(src_width * src_height * COLOR_WIDTH);
    fseek(fpsrc, 54, SEEK_SET);
    fread(src_data, src_width * src_height * COLOR_WIDTH, 1, fpsrc);   

    //修改原照片的宽高
    double scale = (double)percent/100;
    unsigned int dst_width = src_width * scale ;
    unsigned int dst_height = src_height * scale;
    double rate_y = (double)src_height/dst_height;
    double rate_x = (double)src_width/dst_width;
    head.bfSize = dst_width * dst_height * COLOR_WIDTH + 54;
    info.biWidth = dst_width;
    info.biHeight = dst_height;  
    //将修改过的头信息写进新照片
    fwrite(&head, sizeof(BITMAPFILEHEADER), 1, fpdst);
    fwrite(&info, sizeof(BITMAPINFOHEADER), 1, fpdst);

    unsigned char *dst_data = (unsigned char *)malloc(dst_width * dst_height * COLOR_WIDTH);
        //创建存储图片内容的缓冲区
    if( !dst_data ){
        return false;
    }

    //采用线性插值法进行图片放缩
    for(unsigned int dst_y = 0; dst_y<dst_height; ++dst_y){
        unsigned int src_y = (unsigned int)(rate_y * dst_y);
        for(unsigned int dst_x=0; dst_x<dst_width; ++dst_x){
            unsigned int src_x = (unsigned int)(rate_x * dst_x);  
            memcpy( dst_data+(dst_y*dst_width+dst_x)*COLOR_WIDTH, src_data+(src_y*src_width+src_x)*COLOR_WIDTH, COLOR_WIDTH );
        }
    }

    //结果写入文件
    fseek(fpdst, 54, SEEK_SET);
    fwrite(dst_data, dst_width * dst_height * 3, 1, fpdst);

    //释放堆空间
    free(dst_data);
    free(src_data);
    //关闭文件
    fclose(fpsrc);
    fclose(fpdst);
    
    return true;    
}

#endif