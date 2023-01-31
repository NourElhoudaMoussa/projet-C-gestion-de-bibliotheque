#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define FILE_NAME_L "login.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//login password
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME_L,"rb");
    if(fp == NULL)
    {
        printf("Le fichier n'est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\tUtilisateur: ");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\tMot de passe: ");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\tEchec de la connexion Saisir a nouveau le nom d'utilisateur et le mot de passe\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\tDesole, utilisateur inconnu.");
        getch();
        system("cls");
    }
}
//modification de login et mot de passe
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Mettre a jour les justificatifs d’identite");
    fp = fopen(FILE_NAME_L,"rb+");
    if(fp == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\tProbleme de mise a jour du mot de passe\n");
        exit(1);
    }
    printf("\n\n\tNouveau nom d'utilisateur :");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\tNouveau mot de passe:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\tVotre mot de passe a ete modifie avec succes");
    printf("\n\treconnecte");
    fflush(stdin);
    getchar();
    exit(1);
}
