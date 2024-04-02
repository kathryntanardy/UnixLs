#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define MSG_MAX_LENGTH 100

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

int main(){

    while(1){
        char message[MSG_MAX_LENGTH];
        fgets(message, MSG_MAX_LENGTH, stdin);
        
        size_t length = strlen(message);
        message[length-1] = '\0';

        if(strcmp(message, "UnixLs ") || strcmp(message, "UnixLs")){
            ls(".");
        }
    }
    return 0;
}
