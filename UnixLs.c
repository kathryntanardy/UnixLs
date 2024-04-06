#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>


#define MSG_MAX_LENGTH 300

void ls(const char* filepath){
    DIR* dir = opendir(filepath);
    if (dir == NULL){
        printf("opendir() not successful.\n");
        return;
    }

    struct dirent* entry;
    entry = readdir(dir);
    while(entry != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ){
            entry = readdir(dir);
            continue;
        }
        printf("%s  ",entry->d_name);
        entry = readdir(dir);
    }
    printf("\n");
    closedir(dir);
}

int main(int argc, char *argv[]){


    // char message[MSG_MAX_LENGTH];
    char filepath[MSG_MAX_LENGTH];
    int command = 0;
    int inode = 0;
    int longlist = 0;
 
    filepath[0] = '\0';

    if(strcmp(argv[0], "UnixLs") == 0){
        command = 1;
    }
   
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            for(int j = 1; argv[i][j] != '\0'; j++){
                if(argv[i][j] == 'l')
                    longlist = 1;
                else if (argv[i][j] == 'i')
                    inode = 1;
                else
                    strcpy(filepath, argv[i]);
            }       
        }else{
            strcpy(filepath, argv[i]);
            break;
        }
    }  



    // printf("command: %d\n", command);
    // printf("inode: %d\n", inode);
    // printf("longlist: %d\n", longlist);
    // printf("filepath: %s\n", filepath);
    return 0;
}
