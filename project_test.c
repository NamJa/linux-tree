#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include <pwd.h>
#include <grp.h>

void ShowTree(char* pos,int gap);
void FilePerm(mode_t file_mode);

char list[20]; //permission

int main()
{
    char* position;
    position = getcwd(position, 255);
    printf("\n");
    ShowTree(position,0);        
    exit(0);
}
void ShowTree(char* pos,int gap)
{  
    DIR *dir;                 
    struct dirent *direntp;     
    struct stat stat;
    struct passwd *myPwd;
    char userName[255];
    mode_t file_mode;
    if( (dir=opendir(pos)) == NULL)
    {
        perror("Not exist directory \n");
        exit(0);
    }
    chdir(pos);   
    while(direntp = readdir(dir))
    {
        memset(&stat, 0, sizeof(struct stat));
        lstat(direntp->d_name,&stat); 
	    file_mode = stat.st_mode;
        myPwd = getpwuid(stat.st_uid);
        lstat(direntp->d_name,&stat);  
        if(S_ISDIR(stat.st_mode))
        {  
            if(!strcmp(".",direntp->d_name) || !strcmp("..",direntp->d_name))
                continue;
            //get ownerName
            // myPwd = getpwuid(stat.st_uid);
            lstat(direntp->d_name,&stat); 
            file_mode = stat.st_mode; // get file permission
            FilePerm(file_mode);
            printf("%*s┣━━━[%ld %ld %s %s  %6d]     %c[34m%s%c[0m\n",gap,"", stat.st_ino, stat.st_dev, list, myPwd->pw_name, (int)stat.st_size, 27,direntp->d_name,27);

            ShowTree(direntp->d_name,gap+4); 
            chdir("..");
        }
        else if (S_ISREG(stat.st_mode))
        {
                        lstat(direntp->d_name,&stat); 
            file_mode = stat.st_mode; // get file permission
            FilePerm(file_mode);
            // 간격, inode, 디바이스 번호 권한 소유자 파일사이즈 파일이름으로 출력
            // 간격, inode, 디바이스 번호,권한 소유자          파일이름 구현완료
            printf("%*s┣━━━[%ld %ld %s %s  %6d]      %s\n",gap,"", stat.st_ino, stat.st_dev, list, myPwd->pw_name, (int)stat.st_size, direntp->d_name);
        }
	
    }
    closedir(dir);
}
// void line(int gap)
// {
//     int i;
//     printf("┃  ");
//     for ()
// }

void FilePerm(mode_t file_mode)
{
    int i=0;
    if (S_ISDIR(file_mode))
    {
        list[i++] = 'd';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IRUSR)
    {
        list[i++] = 'r';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IWUSR)
    {
        list[i++] = 'w';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IXUSR)
    {
        list[i++] = 'x';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IRGRP)
    {
        list[i++] = 'r';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IWGRP)
    {
        list[i++] = 'w';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IXGRP)
    {
        list[i++] = 'x';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IROTH)
    {
        list[i++] = 'r';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IWOTH)
    {
        list[i++] = 'w';
    }
    else
        list[i++] = '-';
    if (file_mode & S_IXOTH)
    {
        list[i++] = 'x';
    }
    else
        list[i++] = '-';
    return;
}
