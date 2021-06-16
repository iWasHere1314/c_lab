#ifndef __KTV_H
#define __KTV_H
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
/* 管理员操作的相关模块 */

/*
 * 函数名称：admin_add_song
 * 函数功能：为ktv添加歌曲
 * 参数: 无
 * 返回值：void
 */
void admin_add_song(){ 
    FILE *songs_list = fopen("../src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行添加操作\n");
        return;
    }// 打开现有歌曲列表
    printf("\n=================添加歌曲=================\n");
    char name[512];// 输入的歌曲名
    char singer[512];// 输入的作者名
    char cur_name[512];// 现在遍历到的歌曲名
    char cur_singer[512];// 现在遍历到的作者名
    bool is_existed = false;// 表示该作者的该歌曲已经在系统中
    printf("请输入你要添加的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        // 与现存歌曲列表中的结果逐一比对
        // 若找到对应的歌曲, 则设置存在标志并退出比较
        if( strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0 ){
            is_existed = true;
            break;
        }
    }
    if( is_existed ){// 如果已经存在
        printf("该歌手的该歌曲已经存在曲库之中，无法重复添加\n");
        fclose( songs_list );
        return;
    }
    fclose( songs_list );
    songs_list = fopen("../src/ktv/songs", "a");
        // 以附加写入方式重新打开文件, 准备添加歌曲
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行添加操作\n");
        return;
    }
    char directory[1024]="../src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
        // 新添加的歌曲的歌词文件所存放的路径名
    //printf("%s\n", directory);
    FILE *song = fopen(directory, "w+");
    if( !song ){
        printf( "创建歌曲出错，目前无法进行添加操作\n");
        fclose( songs_list );
        return;
    }// 打开新歌曲的歌词文件
    printf( "请输入这首歌的歌词，歌词以由仅含有一个\'#\'的新一行为结束标志\n");
    char txt[512];
    while( scanf("%s",txt) && txt[0] != '#' ){
        fprintf(song, "%s\n", txt );
    }
    fprintf(songs_list, "%s %s\n", name, singer );
    printf( "歌曲添加成功\n" );

    fclose(songs_list);
    fclose( song );
    return;
}

/*
 * 函数名称：admin_delete_song
 * 函数功能：为ktv删除歌曲
 * 参数: 无
 * 返回值：void
 */
void admin_delete_song(){
    FILE *songs_list = fopen("../src/ktv/songs", "r");
        // 未执行删除时的歌曲列表
    FILE *new_song_list = fopen("../src/ktv/songs.temp", "w");
        // 执行删除后的歌曲列表
    if( !songs_list || !new_song_list ){
        printf( "打开歌单出错，目前无法进行删除操作\n");
        return;
    }
    printf("\n=================删除歌曲=================\n");
    char name[512];// 输入的歌曲名
    char singer[512];// 输入的作者名
    char cur_name[512];// 现在遍历到的歌曲名
    char cur_singer[512];// 现在遍历到的作者名
    printf("请输入你要删除的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        // 与现存歌曲列表中的结果逐一比对
        // 若找到对应的歌曲, 则不写入新的歌曲列表
        // 否则,写入新的歌曲列表
        if( strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0 ){
            continue;
        }
        fprintf(new_song_list, "%s %s\n", cur_name, cur_singer );
    }
    char directory[1024]="../src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
        // 删除的歌曲的歌词文件所存放的路径名
    fclose( songs_list );
    fclose( new_song_list );
    remove( "../src/ktv/songs" );// 移除旧歌曲列表
    remove( directory );// 移除要删除的歌曲文件的歌词文件
    rename( "../src/ktv/songs.temp", "../src/ktv/songs" );
        // 重命名新的歌曲列表的文件名
    printf("歌曲删除成功\n");
}

/*
 * 函数名称：admin
 * 函数功能：打开管理员模式
 * 参数: 无
 * 返回值：void
 */
void admin( ){
    int choice;// 表示用户所选操作
    while(1){
        printf("\n================管理员模式================\n");
        printf("*****************功能列表*****************\n");
        printf("1.添加歌曲\n");
        printf("2.删除歌曲\n");
        printf("3.退出系统\n");
        printf("请输入对应序号选择功能，按回车键确认选择\n");
        printf("******************************************\n");
        printf("==========================================\n");
        scanf( "%d", &choice );
        switch( choice ){
            case 1: admin_add_song(); break;
            case 2: admin_delete_song(); break;
            case 3: printf("管理员操作结束\n"); return; break;
            default: printf("输入选项不存在，请核对后重新选择\n"); break;
        }
    }
}

/* 用户操作的相关模块 */

/*
 * 函数名称：user_find_song_singer
 * 函数功能：查找某一歌手的所演唱的歌曲
 * 参数: 无
 * 返回值：void
 */
void user_find_song_singer(){
    FILE *songs_list = fopen("../src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行查询操作\n");
        return;
    }
    printf("\n=================查找歌曲=================\n");
    char singer[512];// 输入的作者名
    char cur_name[512];// 现在遍历到的歌曲名
    char cur_singer[512];// 现在遍历到的作者名
    printf("请输入你要查询的歌手的名称\n");
    scanf( "%s", singer );
    printf("****************查询结果****************\n");
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        // 与现存歌曲列表中的结果逐一比对
        // 若找到对应歌手的歌曲, 则予以显示
        // 否则, 不显示
        if( strcmp( cur_singer, singer ) == 0 ){
            printf("%s - %s\n", cur_name, cur_singer );
        }
    }
    printf("查询结束\n");
    fclose( songs_list );
}

/*
 * 函数名称：user_find_song_singer
 * 函数功能：查找同名的所有歌曲
 * 参数: 无
 * 返回值：void
 */
void user_find_song_name(){
    FILE *songs_list = fopen("../src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行查询操作\n");
        return;
    }
    printf("\n=================查找歌曲=================\n");
    char name[512];// 输入的歌曲
    char cur_name[512];// 现在遍历到的歌曲名
    char cur_singer[512];// 现在遍历到的作者名
    printf("请输入你要查询的歌曲的名称\n");
    scanf( "%s", name );
    printf("****************查询结果****************\n");
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        // 与现存歌曲列表中的结果逐一比对
        // 若找到对应歌名的歌曲, 则予以显示
        // 否则, 不显示
        if( strcmp( cur_name, name ) == 0 ){
            printf("%s - %s\n", cur_name, cur_singer );
        }
    }
    printf("查询结束\n");
    fclose( songs_list );
}

/*
 * 函数名称：user_find_song
 * 函数功能：用户查找歌曲选项的二级界面
 * 参数: 无
 * 返回值：void
 */
void user_find_song(){
    int choice;
    while(1){
        printf("\n================查找歌曲================\n");
        printf("*****************功能列表*****************\n");
        printf("1.按歌名查找\n");
        printf("2.按歌手查找\n");
        printf("3.返回上级\n");
        printf("请输入对应序号选择功能，按回车键确认选择\n");
        printf("******************************************\n");
        printf("==========================================\n");
        scanf( "%d", &choice );
        switch( choice ){
            case 1: user_find_song_name(); break;
            case 2: user_find_song_singer(); break;
            case 3: printf("正在返回上一级\n"); return; break;
            default: printf("输入选项不存在，请核对后重新选择\n"); break;
        }
    }
} 

/*
 * 函数名称：user_play_song
 * 函数功能：播放歌曲
 * 参数: 无
 * 返回值：void
 */
void user_play_song(){
    FILE *songs_list = fopen("../src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行点播操作\n");
        return;
    }
    printf("\n=================点播歌曲=================\n");
    char name[512];// 输入的歌曲名
    char singer[512];// 输入的作者名
    char cur_name[512];// 现在遍历到的歌曲名
    char cur_singer[512];// 现在遍历到的作者名
    printf("请输入你要点播的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    bool is_existed = false;// 是否存在对应的歌曲
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        // 与现存歌曲列表中的结果逐一比对
        // 若找到对应歌手的歌曲, 则设置存在标志
        if( strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0 ){
            is_existed = true;
            break;
        }
    }
    if( !is_existed ){
        printf("所点歌曲不在曲库中，点歌失败\n");
        fclose(songs_list);
        return;
    }
    char directory[1024]="../src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
        // 要播放的歌曲的歌词文件所存放的路径名
    FILE *song = fopen(directory, "r");
    if( !song ){
        printf( "无法打开该歌曲歌词，点歌失败\n");
        fclose( songs_list );
        return;
    }
    char buf[512];
    while( fgets(buf, 512,song ) != NULL ){
        printf( "%s", buf );
    }// 逐行显示歌词
    fclose( songs_list );
    fclose( song );
    printf("点歌成功\n");
}

/*
 * 函数名称：user
 * 函数功能：打开用户模式
 * 参数: 无
 * 返回值：void
 */
void user( ){
    int choice;
    while(1){
        printf("\n================用户模式================\n");
        printf("*****************功能列表*****************\n");
        printf("1.查找歌曲\n");
        printf("2.点播歌曲\n");
        printf("3.退出系统\n");
        printf("请输入对应序号选择功能，按回车键确认选择\n");
        printf("******************************************\n");
        printf("==========================================\n");
        scanf( "%d", &choice );
        switch( choice ){
            case 1: user_find_song(); break;
            case 2: user_play_song(); break;
            case 3: printf("用户操作结束\n"); return; break;
            default: printf("输入选项不存在，请核对后重新选择\n"); break;
        }
    }
}

/* 开始模块 */

/*
 * 函数名称：ktv_start
 * 函数功能：开始使用ktv
 * 参数: char user_level( 操作者的身份 ), const char *name( 操作者的姓名 )
 * 返回值：void
 */
void ktv_start( char user_level, const char *name ){
    if( user_level == 'a' ){// 管理员模式
        FILE *admin_list = fopen( "../src/ktv/admin", "r" );
        if( !admin_list ){
            printf("打开管理员列表失败，无法进行验证，程序结束运行。\n");
            return;
        }// 打开管理员名称列表, 准备进行验证
        char buf[512];// 临时缓冲区
        while( fscanf(admin_list,"%s", buf) != EOF ){
            // 与管理员列表中的名称逐一比对
            // 若发现该名管理员, 则开启管理员界面, 操作结束后退出系统
            if( strcmp( buf, name ) == 0 ){
                printf("验证通过，正在进入系统\n");
                admin();// 打开管理员操作界面
                printf("已退出系统，欢迎下次使用。\n");
                fclose(admin_list);
                return;
            }
        }
        printf("该管理员未登记入系统中，请核对名称后重试。\n");
        fclose(admin_list);
    }
    else if( user_level == 'u' ){// 用户模式
        FILE *user_list = fopen( "../src/ktv/user", "r" );
        if( !user_list ){
            printf("打开用户列表失败，无法进行验证，程序结束运行。\n");
            return;
        }// 打开用户名称列表, 准备进行验证
        char buf[512];
        while( fscanf(user_list,"%s", buf) != EOF ){
            // 与用户列表中的名称逐一比对
            // 若发现该名用户, 则开启用户界面, 操作结束后退出系统
            bool flag = strcmp( buf, name ) == 0;
            if( flag ){
                printf("验证通过，正在进入系统\n");
                user();// 打开用户操作界面
                printf("已退出系统，欢迎下次使用。\n");
                fclose(user_list);
                return;
            }
        }
        fclose(user_list);
        printf("该用户未登记入系统中，请核对名称后重试。\n");
    }
    else{// 若非以上两者, 说明存在错误
        printf("用户类型错误，请核对输入后重新启动程序。\n");
    }
    return;
}

#endif