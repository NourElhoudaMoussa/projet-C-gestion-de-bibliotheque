//procedure pour centrer un message donnée
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (68 - strlen(message))/2;
    printf("\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//procedure pour afficher l'entete de la page
void headMessage(const char *message)
{
    system("cls");
    printf("\t#################################################################");
    printf("\n\t#######                                                   #######");
    printf("\n\t#######      Projet de Gestion de Bibliotheque en C       #######");
    printf("\n\t#######                                                   #######");
    printf("\n\t#################################################################");
    printf("\n\t------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t------------------------------------------------------------------");
}
//procedure pour l'affichage du "welcome message"
void welcomeMessage()
{
    headMessage("Realiser par Nour Elhouda Moussa");
    printf("\n\n\n\n\n");
    printf("\n\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\t       =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t       =             BIENVENU DANS LE              =");
    printf("\n\t       =                 SYSTEME                   =");
    printf("\n\t       =                   DE                      =");
    printf("\n\t       =          GESTION DE BIBLIOTHEQUE          =");
    printf("\n\t       =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
