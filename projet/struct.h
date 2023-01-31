// les constantes relative à login
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
// Les constantes relatives à un document
#define MAX_BOOK_NAME   50
#define MAX_AUTHOR_NAME 50
#define MAX_PUBLISHEE_NAME 50
//les constantes realative à une adresse
#define MAX_RUE 100
#define MAX_VILLE 20
//les constantes relative à un adherent
#define MAX_NOM_PRENOM 50
#define MAX_TYPE 15
//*******************************les structures************************************//
//structure date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

//structure login
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

//structure localisation d'un document
typedef struct
{
	int salle;
	int rayon;
}location;

//structure document
typedef struct
{   
	unsigned int code_unique; 
    char titre[MAX_BOOK_NAME];
    location localisation;
    unsigned int nombre_exemplaire;
}document;

//structure livre
typedef struct
{
    document doc;
    char auteur[MAX_AUTHOR_NAME];
    char editeur[MAX_PUBLISHEE_NAME];
    Date date_edition;
}livre;

//structure article
typedef struct
{
    document doc;
    char auteur[MAX_AUTHOR_NAME];
    Date date_publication;
}article;

//structure magazine
typedef struct
{
    document doc;
    unsigned int frequence_parution;
}magazine;
//structure adresse
typedef struct
{
	unsigned int numreo;
	char rue[MAX_RUE];
	char ville[MAX_VILLE];
	unsigned int code_postal;
}adresse;
//structure adherent
typedef struct
{
	unsigned int identifiant; 
	char nom[MAX_NOM_PRENOM];
	char prenom[MAX_NOM_PRENOM];
	adresse adrs;
	char type[MAX_TYPE];
	unsigned int nbr_emprunts_effectues; 
 unsigned int nbr_emprunts_cours;
 unsigned int nbr_emprunts_depasses;
	unsigned int remarque;
}adherent;
//structure emprunt
typedef struct{
	unsigned int code_unique;
	char type_doc[MAX_TYPE];
	Date date_sortir;
	Date date_retour;
}emprunt;
//structure fiche_Emprunt
typedef struct
{
	unsigned int idfiche;
	unsigned int identifiant;
	emprunt *tab[];

}fiche_emprunt; 
