#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

#define MSG_MAX_LENGTH 300

void getAndPrintUserName(uid_t uid) {

  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw) {
    printf("%s ", pw->pw_name);
  } else {
    perror("Hmm not found???");
    printf("No name found for %u\n", uid);
  }
}

void getAndPrintGroup(gid_t grpNum) {
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
    printf("%s ", grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}

void printOutput(const char* filepath, const int* inode, const int* longlist, const int* command){
    if(*command == 1){
        printf("Command not recognized\n");
        return;
    }

    DIR* dir = opendir(filepath);
    if (dir == NULL){
        printf("Invaild directory: %s\n", filepath);
        return;
    }

    struct dirent* entry;
    struct stat st;

    entry = readdir(dir);
    while(entry != NULL){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.'){
            entry = readdir(dir);
            continue;
        }
        char newpath[MSG_MAX_LENGTH];
        sprintf(newpath, "%s/%s", filepath, entry->d_name);
        if(lstat(newpath, &st) == 0){
            if(*inode == 1)
                printf("%10lu ", st.st_ino);
            
            if(*longlist == 1){
                if(S_ISDIR(st.st_mode))
                    printf("d");
                else if(S_ISLNK(st.st_mode))
                    printf("l");
                else
                    printf("-");
                
                if(st.st_mode & S_IRUSR)
                    printf("r");
                else
                    printf("-");

                if(st.st_mode & S_IWUSR)
                    printf("w");
                else
                    printf("-");

                if(st.st_mode & S_IXUSR)
                    printf("x");
                else
                    printf("-");

                if(st.st_mode & S_IRGRP)
                    printf("r");
                else
                    printf("-");  

                if(st.st_mode & S_IWGRP)
                    printf("w");
                else
                    printf("-");  
                
                if(st.st_mode & S_IXGRP)
                    printf("x");
                else
                    printf("-");  

                if(st.st_mode & S_IROTH)
                    printf("r");
                else
                    printf("-"); 

                if(st.st_mode & S_IWOTH)
                    printf("w");
                else
                    printf("-"); 

                if(st.st_mode & S_IXOTH)
                    printf("x");
                else
                    printf("-"); 

                printf(" %lu ",st.st_nlink);
                getAndPrintUserName(st.st_uid);
                getAndPrintGroup(st.st_gid);
                printf("%5lu ", st.st_size);
                
                char timeString[MSG_MAX_LENGTH];
                time_t time = st.st_mtime;
                struct tm time_s;
                localtime_r(&time, &time_s);
                strftime(timeString, sizeof(timeString), "%b %-d %Y %H:%M", &time_s);
                printf("%s ", timeString); 
            }
            
            //For formatting purposes only
            printf("%s ",entry->d_name);
           

            if(*longlist == 1 && S_ISLNK(st.st_mode)){
                char realFile[MSG_MAX_LENGTH];
                ssize_t len = readlink(newpath, realFile, sizeof(realFile) -1);
                if (len != -1){
                    realFile[len] = '\0';
                    printf("-> %s", realFile);
                }
            }else{
                printf(" ");
            }

            if(*longlist == 1 || *inode == 1){
                printf("\n");
            }
           
        }
        
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

    if (argc == 1){
        strcpy(filepath, ".");
        printOutput(filepath, &inode, &longlist, &command);
        return 0;
    }
    int flag = 0;   
    for(int i = 1; i < argc; i++){  
        if(argv[i][0] == '-'){
            for(int j = 1; argv[i][j] != '\0'; j++){
                if(argv[i][j] == 'l')
                    longlist = 1;
                else if (argv[i][j] == 'i')
                    inode = 1;
            }  
            if ((i+1) == argc){
                filepath[0] = '.';
                filepath[1] = '\0';
            }    
        }
        else{
            strcpy(filepath, argv[i]);
        
            if(filepath[0] == '\0')
            {
            filepath[0] = '.';
            filepath[1] = '\0';
            }
        }
        
            
        if (filepath[0] != '\0'){
            if ((argc - i) > 1 || flag == 1){
                printf ("%s:\n", filepath);
                flag = 1;
            }
            printOutput(filepath, &inode, &longlist, &command);
        }
        
    }  

    //If filepath 

    // printf("command: %d\n", command);
    // printf("inode: %d\n", inode);
    // printf("longlist: %d\n", longlist);
    // printf("filepath: %s\n", filepath);
    return 0;
}