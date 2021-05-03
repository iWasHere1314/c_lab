#ifndef __KTV_H
#define __KTV_H
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
/*  */
void admin_draw_menu(){
    printf("\n================管理员模式================\n");
    printf("*****************功能列表*****************\n");
    printf("1.添加歌曲\n");
    printf("2.删除歌曲\n");
    printf("请输入对应序号选择功能，按回车键确认选择\n");
    printf("******************************************\n");
    printf("==========================================\n");
}
void admin_add_song(){
    FILE *songs_list = fopen("/home/professor/MyProgram/c_lab/src/ktv/songs", "r");
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
    songs_list = fopen("/home/professor/MyProgram/c_lab/src/ktv/songs", "a");
    if( !songs_list ){
        printf( "打开歌单出错，目前无法进行添加操作\n");
        return;
    }
    char directory[1024]="/home/professor/MyProgram/c_lab/src/ktv/";
    strcpy( directory+40, singer );
    *(directory+40+strlen(singer) ) = '_'; 
    strcpy( directory+40+strlen(singer)+1, name );
    FILE *song = fopen(directory, "w+");
    if( !song ){
        printf( "创建歌曲出错，目前无法进行添加操作\n");
        return;
    }
    printf( "请输入这首歌的歌词，歌词以由仅含有一个\'#\'的新一行为结束标志\n");
    char txt[512];
    while( scanf("%s",txt) && txt[0] != '#' ){
        fprintf(song, "%s\n", txt );
    }
    fprintf(songs_list, "%s %s\n", cur_name, cur_singer );
    printf( "歌曲添加成功" );

    fclose(songs_list);
    fclose( song );
    return;
}
void admin_delete_song(){

}
void admin( ){
    int choice;
    while(1){
        admin_draw_menu( );
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
void user( ){

}


void ktv_start( char user_level, const char *name ){
    if( user_level == 'a' ){
        FILE *admin_list = fopen( "/home/professor/MyProgram/c_lab/src/ktv/admin.txt", "r" );
        if( !admin_list ){
            printf("打开管理员列表失败，无法进行验证，程序结束运行。\n");
            return;
        }
        char buf[512];
        size_t name_sz = strlen(name);
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
        FILE *user_list = fopen( "/home/professor/MyProgram/c_lab/src/ktv/user.txt", "r" );
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