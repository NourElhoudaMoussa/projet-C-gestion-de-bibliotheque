#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define MAX_YR  9999
#define MIN_YR  1900
#define FILE_NAME_ARTC "Article.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
// Add un livre dans une liste de livre
void addArticleInDataBase()
{
    int days;
    article addArticleInfoInDataBase = {0};
    FILE *fa = NULL;
    int artc = 0;
    fa = fopen(FILE_NAME_ARTC,"ab+");
    if(fa == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("ADD UN NOUVEAU ARTICLE");//APPEL au fonction de centrage de titre
    printf("\n\n\tENTRER LES DETAILS ICI:");
    printf("\n\t-----------------------------------------------------------------\n");
    //donner le code unique d'article
    printf("\n\tCODE UNIQUE  = ");
    fflush(stdin);
    scanf("%u",&addArticleInfoInDataBase.doc.code_unique);
    //donner le titre d'article
    do
    {
        printf("\n\tTITRE  = ");
        fflush(stdin);
        fgets(addArticleInfoInDataBase.doc.titre,MAX_BOOK_NAME,stdin);
        artc = isNameValid(addArticleInfoInDataBase.doc.titre);
        if (!artc)
        {
            printf("\n\tTitre contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    }
    while(!artc);
    //donner la localisation d'article
    printf("\n\tEntrer la localisation d'article en format(salle/rayon): ");
    fflush(stdin);
    scanf("%d/%d",&addArticleInfoInDataBase.doc.localisation.salle,&addArticleInfoInDataBase.doc.localisation.rayon);
    //donner le nombre d'exemplaires de l'article
    printf("\n\tNombre d'exemplaires  = ");
    fflush(stdin);
    scanf("%u",&addArticleInfoInDataBase.doc.nombre_exemplaire);
    //donner le nom d'auteur
	    do
	    {
	        printf("\n\tAUTEUR  = ");
	        fflush(stdin);
	        fgets(addArticleInfoInDataBase.auteur,MAX_AUTHOR_NAME,stdin);
	        artc = isNameValid(addArticleInfoInDataBase.auteur);
	        if (!artc)
	        {
	            printf("\n\tNom auteur contiennent un caractere non valide. Veuillez entrer a nouveau.");
	        }
	    }
	    while(!artc);
	
    //donner la date de publication de l'article
    	do
	    {
	        
	        printf("\n\tEntrer le date de publication en format (jour/mois/annee): ");
	        scanf("%d/%d/%d",&addArticleInfoInDataBase.date_publication.dd,&addArticleInfoInDataBase.date_publication.mm,&addArticleInfoInDataBase.date_publication.yyyy);
	        //verifier la validation de la date en utilisant la fonction isValidDate()
	        artc = isValidDate(&addArticleInfoInDataBase.date_publication);
	        if (!artc)
	        {
	            printf("\n\tSVP entre une date valide.\n");
	        }
	    }while(!artc);


    fwrite(&addArticleInfoInDataBase,sizeof(addArticleInfoInDataBase), 1, fa);
    fclose(fa);
}
// procedure pour rechercher un article a partir de son titre
void searchArticle()
{
    int found = 0;
    char ArticleName[MAX_BOOK_NAME] = {0};
    article addArticleInfoInDataBase = {0};
    FILE *fa = NULL;
    int artc = 0;
    fa = fopen(FILE_NAME_ARTC,"rb");
    if(fa == NULL)
    {
        printf("\n\tLe fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("RECHERCHER UN ARTICLE");//appel au fonction de centrage de titre
    if (fseek(fa,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fa);
        printf("\n\tProbleme de lecture du fichier\n");
        exit(1);
    }
    printf("\n\n\tEntrez le nom d'article a rechercher :");
    fflush(stdin);
    fgets(ArticleName,MAX_BOOK_NAME,stdin);
    while (fread (&addArticleInfoInDataBase, sizeof(addArticleInfoInDataBase), 1, fa))
    {
        if(!strcmp(addArticleInfoInDataBase.doc.titre, ArticleName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
    			 printf("\n\tCode unique          = %u\n",addArticleInfoInDataBase.doc.code_unique);
        printf("\n\tTitre                = %s",addArticleInfoInDataBase.doc.titre);
        printf("\n\tAuteur               = %s",addArticleInfoInDataBase.auteur);
        printf("\n\tLocalisation         = (s%d/r%d)\n",addArticleInfoInDataBase.doc.localisation.salle,
               addArticleInfoInDataBase.doc.localisation.rayon);
        printf("\n\tDate de publication  = (%d/%d/%d)\n",addArticleInfoInDataBase.date_publication.dd,
               addArticleInfoInDataBase.date_publication.mm, addArticleInfoInDataBase.date_publication.yyyy);
        printf("\n\tNombre d'exemplaires = %u",addArticleInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
    }
    else
    {
        printf("\n\tAucun Article");
    }
    fclose(fa);
    printf("\n\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    getchar();
}
// procedure pour la visualisation des articles en detail
void viewArticles()
{
    int found = 0;
    char ArticleName[MAX_BOOK_NAME] = {0};
    article addArticleInfoInDataBase = {0};
    FILE *fa = NULL;
    int artc = 0;
    unsigned int countArticle = 0;
    headMessage("VOIR LES ARTICLES EN DETAIL");
    fa = fopen(FILE_NAME_ARTC,"rb");
    if(fa == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    if (fseek(fa,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fa);
        printf("Probleme de lecture du fichier\n");
        exit(1);
    }
    while (fread (&addArticleInfoInDataBase, sizeof(addArticleInfoInDataBase), 1, fa))
    {
    				printf("\n\tCode unique          = %u\n",addArticleInfoInDataBase.doc.code_unique);
        printf("\n\tTitre                = %s",addArticleInfoInDataBase.doc.titre);
        printf("\n\tAuteur               = %s",addArticleInfoInDataBase.auteur);
        printf("\n\tLocalisation         = (s%d/r%d)\n",addArticleInfoInDataBase.doc.localisation.salle,
               addArticleInfoInDataBase.doc.localisation.rayon);
        printf("\n\tDate de publication  = (%d/%d/%d)\n",addArticleInfoInDataBase.date_publication.dd,
               addArticleInfoInDataBase.date_publication.mm, addArticleInfoInDataBase.date_publication.yyyy);
        printf("\n\tNombre d'exemplaires = %u",addArticleInfoInDataBase.doc.nombre_exemplaire);
        printf("\n\t********************************************************************");
       
        found = 1;
        ++countArticle;
    }
    	printf("\n\tNombre d'articles    = %d\n\n",countArticle);
    	fclose(fa);
    if(!found)
    {
        printf("\n\tAucun Article");
    }
    	printf("\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    	fflush(stdin);
    	getchar();
}
// procedure pour supprimer un article a partir de son code unique
void deleteArticle()
{
    int found = 0;
    int articleDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char articleName[MAX_BOOK_NAME] = {0};
    article addArticleInfoInDataBase = {0};
    FILE *fa = NULL;
    FILE *tmpFp = NULL;
    int artc = 0;
    headMessage("Supprimer un article");
    fa = fopen(FILE_NAME_ARTC,"rb");
    if(fa == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fa);
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fa);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEntrer le code unique de l'article. pour la suppression:");
    scanf("%d",&articleDelete);
    while (fread (&addArticleInfoInDataBase, sizeof(addArticleInfoInDataBase), 1, fa))
    {
        if(addArticleInfoInDataBase.doc.code_unique != articleDelete)
        {
            fwrite(&addArticleInfoInDataBase,sizeof(addArticleInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\tArticle supprime avec succes....."):printf("\n\tArticle non trouve");
    fclose(fa);
    fclose(tmpFp);
    remove(FILE_NAME_ARTC);
    rename("tmp.bin",FILE_NAME_ARTC);
}
