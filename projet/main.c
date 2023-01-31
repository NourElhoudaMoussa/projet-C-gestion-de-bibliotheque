#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define MAX_YR  9999
#define MIN_YR  1900
#define FILE_NAME "livre.bin"
#define FILE_NAME_L "login.bin"
#define FILE_NAME_ARTC "Article.bin"
#define FILE_NAME_MGZN "Magazine.bin"
#define FILE_NAME_ADHR "Adherent.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
int isFileExists(const char*path){
// Try to open file
FILE *fp = fopen(path, "rb");
int status = 0;
// If file does not exists
if (fp != NULL)
{
status = 1;
// File exists hence close file
fclose(fp);
}
 return status;
}
void init()
{
	   FILE *fad =NULL;
    FILE *fp = NULL;
    FILE *fa =NULL;
    FILE *fm =NULL;
    FILE *fl =NULL;
    int login = 0;
    int status = 0;
    int artc =0;
    int mgzn =0 ;
    int adhr=0;
    const char defaultUsername[] ="nour\n";
    const char defaultPassword[] ="nour\n";
    sFileHeader fileHeaderInfo = {0};
    login = isFileExists(FILE_NAME_L);
    status = isFileExists(FILE_NAME);
    artc= isFileExists(FILE_NAME_ARTC);
    mgzn= isFileExists(FILE_NAME_MGZN);
    adhr= isFileExists(FILE_NAME_ADHR);
    if(!login)
    {
        //create the binary file
        fl = fopen(FILE_NAME_L,"wb");
        if(fl != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fl);
            fclose(fl);
        }
    }
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
    }
    if(!artc)
    {
        //create the binary file
        fa = fopen(FILE_NAME_ARTC,"wb");
    }
    if(!mgzn)
    {
        //create the binary file
        fm = fopen(FILE_NAME_MGZN,"wb");
    }
    if(!adhr)
    {
        //create the binary file
        fad = fopen(FILE_NAME_ADHR,"wb");
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}
