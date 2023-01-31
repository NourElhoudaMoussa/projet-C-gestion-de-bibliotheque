#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define MAX_YR  9999
#define MIN_YR  1900
#define FILE_NAME_MGZN "Magazine.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
// Add une magazine
void addMagazineInDataBase()
{
    int days;
    magazine addMagazineInfoInDataBase = {0};
    FILE *fm = NULL;
    int mgzn = 0;
    fm = fopen(FILE_NAME_MGZN,"ab+");
    if(fm == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("ADD UNE NOUVELLE MAGAZINE");//APPEL au fonction de centrage de titre
    printf("\n\n\tENTRER LES DETAILS ICI:");
    printf("\n\t-----------------------------------------------------------------\n");
    //donner le code unique dune magazine
    printf("\n\tCODE UNIQUE  = ");
    fflush(stdin);
    scanf("%u",&addMagazineInfoInDataBase.doc.code_unique);
    //donner le titre de la magazine
    do
    {
        printf("\n\tTITRE  = ");
        fflush(stdin);
        fgets(addMagazineInfoInDataBase.doc.titre,MAX_BOOK_NAME,stdin);
        mgzn = isNameValid(addMagazineInfoInDataBase.doc.titre);
        if (!mgzn)
        {
            printf("\n\tTitre contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    }
    while(!mgzn);
    //donner la localisation de la magazine
    printf("\n\tEntrer la localisation de la magazine en format(salle/rayon): ");
    fflush(stdin);
    scanf("%d/%d",&addMagazineInfoInDataBase.doc.localisation.salle,&addMagazineInfoInDataBase.doc.localisation.rayon);
    //donner le nombre d'exemplaires de la magazine
    printf("\n\tNombre d'exemplaires  = ");
    fflush(stdin);
    scanf("%u",&addMagazineInfoInDataBase.doc.nombre_exemplaire);
    //donner la frequence de parution de la magazine
    printf("\n\tFrequence de parution = ");
    fflush(stdin);
    scanf("%u",&addMagazineInfoInDataBase.frequence_parution);

    fwrite(&addMagazineInfoInDataBase,sizeof(addMagazineInfoInDataBase), 1, fm);
    fclose(fm);
}
// procedure pour rechercher une magazine a partir de son titre
void searchMagazine()
{
    int found = 0;
    char MagazineName[MAX_BOOK_NAME] = {0};
    magazine addMagazineInfoInDataBase = {0};
    FILE *fm = NULL;
    int mgzn = 0;
    fm = fopen(FILE_NAME_MGZN,"rb");
    if(fm == NULL)
    {
        printf("\n\tLe fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("RECHERCHER UNE MAGAZINE");//appel au fonction de centrage de titre
    if (fseek(fm,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fm);
        printf("\n\tProbleme de lecture du fichier\n");
        exit(1);
    }
    printf("\n\n\tEntrez le nom de la magazine a rechercher :");
    fflush(stdin);
    fgets(MagazineName,MAX_BOOK_NAME,stdin);
    while (fread (&addMagazineInfoInDataBase, sizeof(addMagazineInfoInDataBase), 1, fm))
    {
        if(!strcmp(addMagazineInfoInDataBase.doc.titre, MagazineName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
    				printf("\n\tCode unique          = %u\n",addMagazineInfoInDataBase.doc.code_unique);
        printf("\n\t\t\tTitre                = %s",addMagazineInfoInDataBase.doc.titre);
        printf("\n\tLocalisation         = (s%d/r%d)\n",addMagazineInfoInDataBase.doc.localisation.salle,
              addMagazineInfoInDataBase.doc.localisation.rayon);
        printf("\n\tNombre d'exemplaires = %u",addMagazineInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\tFrequence de parution= %u",addMagazineInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
    }
    else
    {
        printf("\n\tAucune Magazine");
    }
    fclose(fm);
    printf("\n\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    getchar();
}
// procedure pour la visualisation les magazines en detail
void viewMagazine()
{
    int found = 0;
    char MagazineName[MAX_BOOK_NAME] = {0};
    magazine addMagazineInfoInDataBase = {0};
    FILE *fm = NULL;
    int mgzn = 0;
    unsigned int countMagazine = 0;
    headMessage("VOIR LES MAGAZINE EN DETAIL");
    fm = fopen(FILE_NAME_MGZN,"rb");
    if(fm == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    if (fseek(fm,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fm);
        printf("Probleme de lecture du fichier\n");
        exit(1);
    }
    while (fread (&addMagazineInfoInDataBase, sizeof(addMagazineInfoInDataBase), 1, fm))
    {
    				printf("\n\tCode unique          = %u\n",addMagazineInfoInDataBase.doc.code_unique);
        printf("\n\tTitre                = %s",addMagazineInfoInDataBase.doc.titre);
        printf("\n\tLocalisation         = (s%d/r%d)\n",addMagazineInfoInDataBase.doc.localisation.salle,
              addMagazineInfoInDataBase.doc.localisation.rayon);
        printf("\n\tNombre d'exemplaires = %u",addMagazineInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\tFrequence de parution= %u",addMagazineInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
       
        found = 1;
        ++countMagazine;
    }
    	printf("\n\tNombre de magazines  = %d\n\n",countMagazine);
    	fclose(fm);
    if(!found)
    {
        printf("\n\tAucune Magazine");
    }
    	printf("\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    	fflush(stdin);
    	getchar();
}
// procedure pour supprimer une magazine a partir de son code unique
void deleteMagazine()
{
    int found = 0;
    int MagazineDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char MagazineName[MAX_BOOK_NAME] = {0};
    magazine addMagazineInfoInDataBase = {0};
    FILE *fm = NULL;
    FILE *tmpFp = NULL;
    int mgzn = 0;
    headMessage("Supprimer une magazine");
    fm = fopen(FILE_NAME_MGZN,"rb");
    if(fm == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fm);
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fm);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEntrer le code unique de la magazine. pour la suppression:");
    scanf("%d",&MagazineDelete);
    while (fread (&addMagazineInfoInDataBase, sizeof(addMagazineInfoInDataBase), 1, fm))
    {
        if(addMagazineInfoInDataBase.doc.code_unique != MagazineDelete)
        {
            fwrite(&addMagazineInfoInDataBase,sizeof(addMagazineInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\tMagazine supprime avec succes....."):printf("\n\tMagazine non trouve");
    fclose(fm);
    fclose(tmpFp);
    remove(FILE_NAME_MGZN);
    rename("tmp.bin",FILE_NAME_MGZN);
}
