#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define MAX_YR  9999
#define MIN_YR  1900
#define FILE_NAME  "livre.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
// Add un livre dans une liste de livre
void addBookInDataBase()
{
    int days;
    livre addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("ADD UN NOUVEAU LIVRE");//APPEL au fonction de centrage de titre
    printf("\n\n\tENTRER LES DETAILS ICI:");
    printf("\n\t-----------------------------------------------------------------\n");
    //donner le code unique du livre
    printf("\n\tCODE UNIQUE  = ");
    fflush(stdin);
    scanf("%u",&addBookInfoInDataBase.doc.code_unique);
    //donner le titre du livre
    do
    {
        printf("\n\tTITRE  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.doc.titre,MAX_BOOK_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.doc.titre);
        if (!status)
        {
            printf("\n\tTitre contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    }
    while(!status);
    //donner la localisation du livre
    printf("\n\tEntrer la localisation du livre en format(salle/rayon): ");
    fflush(stdin);
    scanf("%d/%d",&addBookInfoInDataBase.doc.localisation.salle,&addBookInfoInDataBase.doc.localisation.rayon);
    //donner le nombre d'exemplaires du livre
    printf("\n\tNombre d'exemplaires  = ");
    fflush(stdin);
    scanf("%u",&addBookInfoInDataBase.doc.nombre_exemplaire);
    //donner le nom d'auteur
	    do
	    {
	        printf("\n\tAUTEUR  = ");
	        fflush(stdin);
	        fgets(addBookInfoInDataBase.auteur,MAX_AUTHOR_NAME,stdin);
	        status = isNameValid(addBookInfoInDataBase.auteur);
	        if (!status)
	        {
	            printf("\n\tNom auteur contiennent un caractère non valide. Veuillez entrer a nouveau.");
	        }
	    }
	    while(!status);
	    
    //donner le nom d'editeur du livre
	    do
	    {
	        printf("\n\tEDITEUR  = ");
	        fflush(stdin);
	        fgets(addBookInfoInDataBase.editeur,MAX_PUBLISHEE_NAME,stdin);
	        status = isNameValid(addBookInfoInDataBase.editeur);
	        if (!status)
	        {
	            printf("\n\tNom editeur contiennent un caractère non valide. Veuillez entrer a nouveau.");
	        }
	    }
	    while(!status);
	
    //donner la date d'edition du livre
    	do
	    {
	        
	        printf("\n\tEntrer le date d'edition en format (jour/mois/annee): ");
	        scanf("%d/%d/%d",&addBookInfoInDataBase.date_edition.dd,&addBookInfoInDataBase.date_edition.mm,&addBookInfoInDataBase.date_edition.yyyy);
	        //check date validity
	        status = isValidDate(&addBookInfoInDataBase.date_edition);
	        if (!status)
	        {
	            printf("\n\tSVP entre une date valide.\n");
	        }
	    }while(!status);


    fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}
// procedure pour rechercher un livre a partire de son titre
void searchBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    livre addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\tLe fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("RECHERCHER UN LIVRE");//appel au fonction de centrage de titre
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\tProbleme de lecture du fichier\n");
        exit(1);
    }
    printf("\n\n\tEntrez le nom du livre a rechercher :");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(addBookInfoInDataBase.doc.titre, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
    	printf("\n\tCode unique          = %u\n",addBookInfoInDataBase.doc.code_unique);
        printf("\n\tTitre                = %s",addBookInfoInDataBase.doc.titre);
        printf("\n\tAuteur               = %s",addBookInfoInDataBase.auteur);
        printf("\n\tEditeur              = %s",addBookInfoInDataBase.editeur);
        printf("\n\tLocalisation         = (s%d/r%d)\n",addBookInfoInDataBase.doc.localisation.salle,
               addBookInfoInDataBase.doc.localisation.rayon);
        printf("\n\tDate d'edition       = (%d/%d/%d)\n",addBookInfoInDataBase.date_edition.dd,
               addBookInfoInDataBase.date_edition.mm, addBookInfoInDataBase.date_edition.yyyy);
        printf("\n\tNombre d'exemplaires = %u",addBookInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
    }
    else
    {
        printf("\n\tAucun Livre");
    }
    fclose(fp);
    printf("\n\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    getchar();
}
// procedure pour la visualisation des livre en detail
void viewBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    livre addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 0;
    headMessage("VOIR LES LIVRES EN DETAIL");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Probleme de lecture du fichier\n");
        exit(1);
    }
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        printf("\n\tCode unique          = %u\n",addBookInfoInDataBase.doc.code_unique);
        printf("\n\tTitre                = %s",addBookInfoInDataBase.doc.titre);
        printf("\n\tAuteur               = %s",addBookInfoInDataBase.auteur);
        printf("\n\tEditeur              = %s",addBookInfoInDataBase.editeur);
        printf("\n\tLocalisation         = (%d/%d)\n",addBookInfoInDataBase.doc.localisation.salle,
               addBookInfoInDataBase.doc.localisation.rayon);
        printf("\n\tDate d'edition       = (%d/%d/%d)\n",addBookInfoInDataBase.date_edition.dd,
               addBookInfoInDataBase.date_edition.mm, addBookInfoInDataBase.date_edition.yyyy);
        printf("\n\tNombre d'exemplaires = %u",addBookInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
       
        found = 1;
        ++countBook;
    }
    	printf("\n\tNombre de livres     = %d\n\n",countBook);
    	fclose(fp);
    if(!found)
    {
        printf("\n\tAucun Livre");
    }
    	printf("\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    	fflush(stdin);
    	getchar();
}
// procedure pour supprimer un livre a partir de son code unique
void deleteBooks()
{
    int found = 0;
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    livre addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Supprimer un livre");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEntrer le code unique du livre. pour la suppression:");
    scanf("%d",&bookDelete);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.doc.code_unique != bookDelete)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\tLivre supprime avec succes....."):printf("\n\tLivre non trouve");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
