#include <stdio.h>
#include <time.h>
#include <string.h>
#include "struct.h"
#define MAX_YR  9999
#define MIN_YR  1900
#define FILE_NAME_ADHR "Adherent.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
// Add un adherent
void addAdherentInDataBase()
{
    int days;
    int a =0,b=0,c=0,d=0;
    adherent addAdherentInfoInDataBase = {0};
    FILE *fad = NULL;
    int adhr = 0;
    fad = fopen(FILE_NAME_ADHR,"ab+");
    if(fad == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("ADD UN NOUVEAU ADHERENT");//APPEL au fonction de centrage de titre
    printf("\n\n\tENTRER LES DETAILS ICI:");
    printf("\n\t-----------------------------------------------------------------\n");
    //donner l'identifiant de l'adherent
    printf("\n\tIDENTIFIANT  = ");
    fflush(stdin);
   scanf("%u",&addAdherentInfoInDataBase.identifiant);

    //donner le nom de l'adherent
    do
    {
        printf("\n\tNOM  	 = ");
        fflush(stdin);
        fgets(addAdherentInfoInDataBase.nom,MAX_NOM_PRENOM,stdin);
        adhr = isNameValid(addAdherentInfoInDataBase.nom);
        if (!adhr)
        {
            printf("\n\tNom contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    }
    while(!adhr);
    //donner le prenom de l'adherent
    do
    {
        printf("\n\tPRENOM 	 = ");
        fflush(stdin);
        fgets(addAdherentInfoInDataBase.prenom,MAX_NOM_PRENOM,stdin);
        adhr = isNameValid(addAdherentInfoInDataBase.prenom);
        if (!adhr)
        {
            printf("\n\tPrenom contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    }
    while(!adhr);
    //donner l'adresse de l'adherent
    printf("\n\tL'adresse de l'adherent");
    printf("\n\t\tNumero: ");
    fflush(stdin);
     scanf("%u",&addAdherentInfoInDataBase.adrs.numreo);
    do
    {
    printf("\n\t\tNom de la Rue   : ");
    fflush(stdin);
        fgets(addAdherentInfoInDataBase.adrs.rue,MAX_RUE,stdin);
        adhr = isNameValid(addAdherentInfoInDataBase.adrs.rue);
        if (!adhr)
        {
            printf("\n\tnom de la Rue contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    } while(!adhr);
	do
    {
    printf("\n\t\tVille           : ");
    fflush(stdin);
        fgets(addAdherentInfoInDataBase.adrs.ville,MAX_VILLE,stdin);
        adhr = isNameValid(addAdherentInfoInDataBase.adrs.ville);
        if (!adhr)
        {
            printf("\n\tnom de la Ville contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
    } while(!adhr);
 	printf("\n\t\tCode Postal: ");
    fflush(stdin);
    scanf("%u",&addAdherentInfoInDataBase.adrs.code_postal);
	
    
	//donner le type d'adherent
	  do
    {
        printf("\n\tTYPE ADHERENT(Etudiant/Enseignant/Visiteur)");
        fflush(stdin);
        fgets(addAdherentInfoInDataBase.type,MAX_TYPE,stdin);
        	 a=strcmp(addAdherentInfoInDataBase.type,"Etudiant");
        	 b=strcmp(addAdherentInfoInDataBase.type,"Enseignant");
        	 c=strcmp(addAdherentInfoInDataBase.type,"Visiteur");
        
        adhr = isNameValid(addAdherentInfoInDataBase.type);
        
        if (!adhr)
        {
            printf("\n\tType adherent contiennent un caractere non valide. Veuillez entrer a nouveau.");
        }
        if(!c||!b||!a)
        {
        	printf("le type d'adherent doit etre :Etudiant ou Enseignant ou Visiteur");
		}
    }
    while(!adhr&&!c&&!b&&!a);
    //nombre emprunt total effectues
    addAdherentInfoInDataBase.nbr_emprunts_effectues=0;
     //nombre emprunt en cours
    addAdherentInfoInDataBase.nbr_emprunts_cours=0;
     //nombre emprunt depasses
    addAdherentInfoInDataBase.nbr_emprunts_depasses=0;
    //remarque prend 1 si l'aderent et retardaire 0 si non par defaut lors de lacreation d'adherent remarque =0
    addAdherentInfoInDataBase.remarque=0;
    fwrite(&addAdherentInfoInDataBase,sizeof(addAdherentInfoInDataBase), 1, fad);
    printf("ajout avec succees");
    fclose(fad);
}
// procedure pour rechercher une magazine a partir de son titre

void searchAdherent()
{
    int found = 0;
    char AdherentName[MAX_NOM_PRENOM] = {0};
    adherent addAdherentInfoInDataBase = {0};
    FILE *fad = NULL;
    int adhr = 0;
    fad = fopen(FILE_NAME_ADHR,"rb");
    if(fad == NULL)
    {
        printf("\n\t\t\tLe fichier n’est pas ouvert\n");
        exit(1);
    }
    headMessage("RECHERCHER UN ADHERENT");//appel au fonction de centrage de titre
    if (fseek(fad,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fad);
        printf("\n\tProbleme de lecture du fichier\n");
        exit(1);
    }
    printf("\n\n\tEntrez le Prenom de l'adherent a rechercher :");
    fflush(stdin);
    fgets(AdherentName,MAX_NOM_PRENOM,stdin);
    while (fread (&addAdherentInfoInDataBase, sizeof(addAdherentInfoInDataBase), 1, fad))
    {
        if(!strcmp(addAdherentInfoInDataBase.prenom, AdherentName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
  						printf("\n\tIdentifiant          = %u\n",addAdherentInfoInDataBase.identifiant);
        printf("\n\tNom                  = %s",addAdherentInfoInDataBase.nom);
        printf("\n\tPrenom               = %s",addAdherentInfoInDataBase.prenom);
        printf("\n\tType                 = %s",addAdherentInfoInDataBase.type);
        printf("\n\tAdresse              ");
        printf("\n\t\tRue   :%u %s",addAdherentInfoInDataBase.adrs.numreo,addAdherentInfoInDataBase.adrs.rue);
								printf("\n\t\tVille :%u %s",addAdherentInfoInDataBase.adrs.code_postal,addAdherentInfoInDataBase.adrs.ville);
        printf("\n\tNombre d'emprunt effectues = %u",addAdherentInfoInDataBase.nbr_emprunts_effectues);
        printf("\n\tNombre d'emprunt en cours  = %u",addAdherentInfoInDataBase.nbr_emprunts_cours);
        printf("\n\tNombre d'emprunt depasses = %u",addAdherentInfoInDataBase.nbr_emprunts_depasses);
        printf("\n\tRemarque= %u",addAdherentInfoInDataBase.remarque);
        printf("\n\t*********************************************************************");

    }
    else
    {
        printf("\n\tAucun Adherent");
    }
    fclose(fad);
    printf("\n\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    getchar();
}
// procedure pour la visualisation les adherent en detail
void viewAdherent()
{
    int found = 0;
    char AdherentName[MAX_NOM_PRENOM] = {0};
    adherent addAdherentInfoInDataBase = {0};
    FILE *fad = NULL;
    int adhr = 0;
    unsigned int countAdherent = 0;
    headMessage("VOIR LES ADHERENTS EN DETAIL");
    fad = fopen(FILE_NAME_ADHR,"rb");
    if(fad == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    if (fseek(fad,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fad);
        printf("Probleme de lecture du fichier\n");
        exit(1);
    }
    while (fread (&addAdherentInfoInDataBase, sizeof(addAdherentInfoInDataBase), 1, fad))
    {
    				printf("\n\tIdentifiant          = %u\n",addAdherentInfoInDataBase.identifiant);
        printf("\n\tNom                  = %s",addAdherentInfoInDataBase.nom);
        printf("\n\tPrenom               = %s",addAdherentInfoInDataBase.prenom);
        printf("\n\tType                 = %s",addAdherentInfoInDataBase.type);
        printf("\n\tAdresse              ");
        printf("\n\t\tRue   :%u %s",addAdherentInfoInDataBase.adrs.numreo,addAdherentInfoInDataBase.adrs.rue);
								printf("\n\t\tVille :%u %s",addAdherentInfoInDataBase.adrs.code_postal,addAdherentInfoInDataBase.adrs.ville);
        printf("\n\tNombre d'emprunt effectues = %u",addAdherentInfoInDataBase.nbr_emprunts_effectues);
        printf("\n\tNombre d'emprunt en cours  = %u",addAdherentInfoInDataBase.nbr_emprunts_cours);
        printf("\n\tNombre d'emprunt depasses = %u",addAdherentInfoInDataBase.nbr_emprunts_depasses);
        printf("\n\tRemarque= %u",addAdherentInfoInDataBase.remarque);
        printf("\n\t*********************************************************************");
       
        found = 1;
        ++countAdherent;
    }
    	printf("\n\tNombre d'adherent  = %d\n\n",countAdherent);
    	fclose(fad);
    if(!found)
    {
        printf("\n\tAucun Adherent");
    }
    	printf("\n\n\tAppuyez sur n’importe quelle touche pour acceder au menu principal.....");
    	fflush(stdin);
    	getchar();
}
// procedure pour supprimer un adherent a partir de son code unique
void deleteAdherent()
{
    int found = 0;
    int AdherentDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char AdherentName[MAX_NOM_PRENOM] = {0};
    adherent addAdherentInfoInDataBase = {0};
    FILE *fad = NULL;
    FILE *tmpFp = NULL;/**/
    int adrh = 0;
    headMessage("Supprimer un adherent");
    fad = fopen(FILE_NAME_ADHR,"rb");
    if(fad == NULL)
    {
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fad);
        printf("Le fichier n’est pas ouvert\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fad);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\tEntrer l'identifiant de l'adherent. pour la suppression:");
    scanf("%d",&AdherentDelete);
    while (fread (&addAdherentInfoInDataBase, sizeof(addAdherentInfoInDataBase), 1, fad))
    {
        if(addAdherentInfoInDataBase.identifiant != AdherentDelete)
        {
            fwrite(&addAdherentInfoInDataBase,sizeof(addAdherentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\tAdherent supprime avec succes....."):printf("\n\tAdherent non trouve");
    fclose(fad);
    fclose(tmpFp);
    remove(FILE_NAME_ADHR);
    rename("tmp.bin",FILE_NAME_ADHR);
}
