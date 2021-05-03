#ifndef __KTV_H
#define __KTV_H
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
/*  */
void admin_add_song(){
    FILE *songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行添加操作\n");
        return;
    }
    printf("\n=================添加歌曲=================\n");
    char name[512];
    char singer[512];
    char cur_name[512];
    char cur_singer[512];
    bool is_existed = false;
    printf("请输入你要添加的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        bool flag = strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0;
        if( flag ){
            is_existed = true;
            break;
        }
    }
    if( is_existed ){
        printf("该歌手的该歌曲已经存在曲库之中，无法重复添加\n");
        fclose( songs_list );
        return;
    }
    fclose( songs_list );
    songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "a");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行添加操作\n");
        return;
    }
    char directory[1024]="/home/yyang/MyProgram/c_lab/src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
    //printf("%s\n", directory);
    FILE *song = fopen(directory, "w+");
    if( !song ){
        printf( "创建歌曲出错，目前无法进行添加操作\n");
        fclose( songs_list );
        return;
    }
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
void admin_delete_song(){
    FILE *songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "r");
    FILE *new_song_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs.temp", "w");
    if( !songs_list || !new_song_list ){
        printf( "打开歌单出错，目前无法进行删除操作\n");
        return;
    }
    printf("\n=================删除歌曲=================\n");
    char name[512];
    char singer[512];
    char cur_name[512];
    char cur_singer[512];
    printf("请输入你要删除的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        bool flag = strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0;
        if( flag ){
            continue;
        }
        fprintf(new_song_list, "%s %s\n", cur_name, cur_singer );
    }
    char directory[1024]="/home/yyang/MyProgram/c_lab/src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
    fclose( songs_list );
    fclose( new_song_list );
    remove( "/home/yyang/MyProgram/c_lab/src/ktv/songs" );
    remove( directory );
    rename( "/home/yyang/MyProgram/c_lab/src/ktv/songs.temp", "/home/yyang/MyProgram/c_lab/src/ktv/songs" );
    printf("歌曲删除成功\n");
}
void admin( ){
    int choice;
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

/*  */
void user_find_song_singer(){
    FILE *songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行查询操作\n");
        return;
    }
    printf("\n=================查找歌曲=================\n");
    char singer[512];
    char cur_name[512];
    char cur_singer[512];
    printf("请输入你要查询的歌手的名称\n");
    scanf( "%s", singer );
    printf("****************查询结果****************\n");
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        bool flag = strcmp( cur_singer, singer ) == 0;
        if( flag ){
            printf("%s - %s\n", cur_name, cur_singer );
        }
    }
    printf("查询结束\n");
    fclose( songs_list );
}
void user_find_song_name(){
    FILE *songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行查询操作\n");
        return;
    }
    printf("\n=================查找歌曲=================\n");
    char name[512];
    char cur_name[512];
    char cur_singer[512];
    printf("请输入你要查询的歌曲的名称\n");
    scanf( "%s", name );
    printf("****************查询结果****************\n");
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        bool flag = strcmp( cur_name, name ) == 0;
        if( flag ){
            printf("%s - %s\n", cur_name, cur_singer );
        }
    }
    printf("查询结束\n");
    fclose( songs_list );
}
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
void user_play_song(){
    FILE *songs_list = fopen("/home/yyang/MyProgram/c_lab/src/ktv/songs", "r");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行点播操作\n");
        return;
    }
    printf("\n=================点播歌曲=================\n");
    char name[512];
    char singer[512];
    char cur_name[512];
    char cur_singer[512];
    printf("请输入你要点播的歌曲的名称\n");
    scanf( "%s", name );
    printf("请输入该歌曲的歌手名称\n");
    scanf( "%s", singer );
    bool is_existed = false;
    while( fscanf(songs_list, "%s", cur_name) != EOF && fscanf(songs_list, "%s", cur_singer )){
        bool flag = strcmp( cur_singer, singer ) == 0 && strcmp( cur_name, name ) == 0;
        if( flag ){
            is_existed = true;
            break;
        }
    }
    if( !is_existed ){
        printf("所点歌曲不在曲库中，点歌失败\n");
        fclose(songs_list);
        return;
    }
    char directory[1024]="/home/yyang/MyProgram/c_lab/src/ktv/";
    size_t pre_len = strlen( directory );
    strcpy( directory+pre_len, singer );
    *(directory+pre_len+strlen(singer) ) = '_'; 
    strcpy( directory+pre_len+strlen(singer)+1, name );
    FILE *song = fopen(directory, "r");
    if( !song ){
        printf( "无法打开该歌曲歌词，点歌失败\n");
        fclose( songs_list );
        return;
    }
    char buf[512];
    while( fgets(buf, 512,song ) != NULL ){
        printf( "%s", buf );
    }
    fclose( songs_list );
    fclose( song );
    printf("点歌成功\n");
}
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


void ktv_start( char user_level, const char *name ){
    if( user_level == 'a' ){
        FILE *admin_list = fopen( "/home/yyang/MyProgram/c_lab/src/ktv/admin", "r" );
        if( !admin_list ){
            printf("打开管理员列表失败，无法进行验证，程序结束运行。\n");
            return;
        }
        char buf[512];
        while( fscanf(admin_list,"%s", buf) != EOF ){
            bool flag = strcmp( buf, name ) == 0;
            if( flag ){
                printf("验证通过，正在进入系统\n");
                admin();
                printf("已退出系统，欢迎下次使用。\n");
                fclose(admin_list);
                return;
            }
        }
        printf("该管理员未登记入系统中，请核对名称后重试。\n");
        fclose(admin_list);
    }
    else if( user_level == 'u' ){
        FILE *user_list = fopen( "/home/yyang/MyProgram/c_lab/src/ktv/user", "r" );
        if( !user_list ){
            printf("打开用户列表失败，无法进行验证，程序结束运行。\n");
            return;
        }
        char buf[512];
        while( fscanf(user_list,"%s", buf) != EOF ){
            bool flag = strcmp( buf, name ) == 0;
            if( flag ){
                printf("验证通过，正在进入系统\n");
                user();
                printf("已退出系统，欢迎下次使用。\n");
                fclose(user_list);
                return;
            }
        }
        fclose(user_list);
        printf("该用户未登记入系统中，请核对名称后重试。\n");
    }
    else{
        printf("用户类型错误，请核对输入后重新启动程序。\n");
    }
    return;
}

#endif