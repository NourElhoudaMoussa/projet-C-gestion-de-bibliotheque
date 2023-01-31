//menu principal
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MENU PRINCIPAL");
        printf("\n\n\n\t1.Ajouter un livre");
        printf("\n\t2.Rechercher un livre");
        printf("\n\t3.Afficher les livres");
        printf("\n\t4.Supprimer un livre");
        printf("\n\t5.Ajouter un article");
        printf("\n\t6.Rechercher un article");
        printf("\n\t7.Afficher les article");
        printf("\n\t8.Supprimer un article");
        printf("\n\t9.Ajouter une magazine");
        printf("\n\t10.Rechercher une magazine");
        printf("\n\t11.Afficher les magazines");
        printf("\n\t12.Supprimer une magazine");
        printf("\n\t13.Ajouter un adherent");
        printf("\n\t14.Rechercher un adherent");
        printf("\n\t15.Afficher les adherents");
        printf("\n\t16.Supprimer un adherent");
        printf("\n\t17.Mettre a jour le nom d'utilisateur et le mot de passe");
        printf("\n\t0.Exit");
        printf("\n\n\n\tSaisir votre choix => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            deleteBooks();
            break;
        case 5:
            addArticleInDataBase();
            break;
        case 6:
            searchArticle();
            break;
        case 7:
            viewArticles();
            break;
        case 8:
            deleteArticle();
            break;
        case 9:
            addMagazineInDataBase();
            break;
        case 10:
            searchMagazine();
            break;
        case 11:
            viewMagazine();
            break;
        case 12:
            deleteMagazine();
            break;
        case 13:
        	addAdherentInDataBase();
            break;
        case 14:
        	searchAdherent();
            break;
        case 15:
        	viewAdherent();
            break;
        case 16:
        	deleteAdherent();
            break;
        case 17:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\tMerci!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\tINVALID INPUT!! Reessayez...");
        }                                           
    }
    while(choice!=0);                                       
}

