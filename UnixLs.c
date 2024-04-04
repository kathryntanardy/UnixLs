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

int main(){

    char message[MSG_MAX_LENGTH];
    char filepath[MSG_MAX_LENGTH];
    int command;
    int inode;
    int longlist; 
    int invalid;
    while(1){
        //Identify the commands by using strtok
        command = 0;
        inode = 0;
        longlist = 0;
        invalid = 0;
        filepath[0] = '\0';
        message[0] = '\0';
        fgets(message, MSG_MAX_LENGTH, stdin);
        
        size_t length = strlen(message);
        message[length-1] = '\0';
    
        char * token = strtok(message, " ");
        char * tokens[MSG_MAX_LENGTH];
        int count = 0;

        while(token != NULL){
            tokens[count++] = token;
            token = strtok(NULL, " ");
        }
    
        if(count <= 0){
            printf("No command specified.\n");
            continue;
        }

        if(strcmp(tokens[0], "UnixLs") == 0){
            command = 1;
        }

        for(int i = 1; i < count; i++){
            if(tokens[i][0] == '-'){
                for(int j = 1; tokens[i][j] != '\0'; j++){
                    if(tokens[i][j] == 'l')
                        longlist = 1;
                    else if (tokens[i][j] == 'i')
                        inode = 1;
                    else
                        invalid = 1;
                    }
            }else{
                strcpy(filepath, tokens[i]);
                break;
            }
        }  

        printf("command: %d\n", command);
        printf("inode: %d\n", inode);
        printf("longlist: %d\n", longlist);
        printf("filepath: %s\n", filepath);
        printf("invalid: %d\n", invalid);

        // if(strcmp(message, "UnixLs ") || strcmp(message, "UnixLs")){
        //     ls(".");
        // }
    }
    return 0;
}
