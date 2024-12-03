#include "generateur.h"
#include "consultmdp.h"
#include "sauvegardemdp.h"


void menuprincipal()
{
   printf("Faites votre choix pour acceder a une fonction du menu (1/2/3/4).\n");
   printf("1 : Generer un mot de passe\n");
   printf("2 : Consultation des mots de passe deja crees\n");
   printf("3 : Supprimer un mot de passe\n");
   printf("4 : Exit\n");
   printf("Votre choix : ");
}

//Appel des fonctions
void menuprincipal();
void flushInputBuffer();

// Affiche le menu principal

int main() {

char menu;
char sousmenu;
char password[] = "password123";
int length, lowercase, uppercase, digits;

   printf(" ________________________________________________________\n");
   printf("|                                                        |\n");
   printf("|                Gestionnaire de mot de passe            |\n");
   printf("|                            Menu                        |\n");
   printf("|                                                        |\n");
   printf("|________________________________________________________|\n\n");

   do {
        menuprincipal();
    if (scanf("%d", &menu) != 1) {
            flushInputBuffer();
            printf("Entrée invalide. Réessayez.\n");
        return 1;
    }
        switch (menu) {
        case 1:
            /*
            printf("Vous entrez dans le module de creation de mot de passe\n");
            char* mdp[129];
            char masterPass[MAX_PASSWORD_LENGTH];
            gen_mdp(mdp);
            scanf("%c", &sousmenu);
            printf("Votre choix : %c\n", sousmenu);
            if (sousmenu == 'O' || sousmenu == 'o')
            {
                //Demander le login à registerPass et demander la confirmation à l'utilisateur que c'est le bon login
                char login[MAX_PASSWORD_LENGTH];
                do {
                    printf("Entrez le login : ");
                    scanf("%s", login);
                    flushInputBuffer();
                    printf("Confirmez le login (O/N) : ");
                    scanf("%c", &sousmenu);
                    flushInputBuffer();
                } while (sousmenu != 'O' && sousmenu != 'o');
                //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
                    printf("Entrez le mot de passe maitre : ");
                    scanf("%s", masterPass);


    printf("Mot de passe genere : %s\n", mdp);

    printf("Voulez-vous sauvegarder ce mot de passe ? (o/n) : ");
    getchar();
    char save;
    scanf("%c", &save);

if (save == 'o' || save == 'O') {
        char identifier[128], service[128];
        int type;

        printf("Identifiant associé : ");
        scanf("%s", identifier);
        printf("Nom du service : ");
        scanf("%s", service);
        printf("Type de login (1: Machine, 2: Messagerie, 3: Compte en ligne) : ");
        scanf("%d", &type);

        FILE *file = fopen(FILE_NAME, "a");
        if (!file) {
            printf("Erreur : Impossible d'ouvrir le fichier.\n");
            return;
        }
        fprintf(file, "%s;%s;%d;%s\n", identifier, service, type, password);
        fclose(file);
        printf("Mot de passe sauvegarde avec succes.\n");
    }


    if (strcmp(masterPass, MASTER_PASSWORD) != 0) {
        printf("Mot de passe incorrect.\n");
        return;
    }
               // }
            }*/
            printf("Vous entrez dans le module de creation de mot de passe\n");
            char* mdp[129];
            if(gen_mdp(mdp)==0){
                printf("Votre mot de passe est le: %s\n", mdp);
                printf("Voulez-vous enregister ce mot de passe ? (O/N) : \n");
                flushInputBuffer();
                scanf("%c", &sousmenu);
                printf("Votre choix : %c\n", sousmenu);
                if (sousmenu == 'O' || sousmenu == 'o')
                {
                    //Demander le login à registerPass et demander la confirmation à l'utilisateur que c'est le bon login
                    char login[MAX_PASSWORD_LENGTH];
                    do {
                        printf("Entrez le login : ");
                        scanf("%s", login);
                        flushInputBuffer();
                        printf("Confirmez le login (O/N) : ");
                        scanf("%c", &sousmenu);
                        flushInputBuffer();
                    } while (sousmenu != 'O' && sousmenu != 'o');
                    char service[MAX_PASSWORD_LENGTH];
                    do {
                        printf("Entrez le service : ");
                        scanf("%s", service);
                        flushInputBuffer();
                        printf("Confirmez le service (O/N) : ");
                        scanf("%c", &sousmenu);
                        flushInputBuffer();
                    } while (sousmenu != 'O' && sousmenu != 'o');
                    //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
                    for(int i = 0; i < 3; i++)
                    {
                        printf("Entrez le mot de passe maitre : ");
                        char masterPass[MAX_PASSWORD_LENGTH];
                        scanf("%s", masterPass);
                        flushInputBuffer();
                        // unsigned char masterPassHash[SHA256_DIGEST_LENGTH];
                        // hash_password(masterPass, masterPassHash);
                        // if(*masterPassHash == MASTER_PASSWORD_HASH)
                        if(strcmp(masterPass, MASTER_PASSWORD) == 0)
                        {
                            registerPass(login, mdp, masterPass, "user", service);
                            break;
                        }else{
                            printf("Mot de passe maitre incorrect.\n");
                        }
                    }
                }
            }
            break;
        case 2:
            printf("%s", viewPasswords(MASTER_PASSWORD));
            break;
        case 3:
            printf("%s", viewPasswords(MASTER_PASSWORD));
            printf("Entrer ligne a supprimer");
            int lineToDelete;
            scanf("%d", &lineToDelete);
            deletePassword(lineToDelete, MASTER_PASSWORD);
            break;
        case 4:
            printf("Au revoir !\n");
            break;
        default:
            printf("Option invalide.\n");
        }
    } while (menu != 4);

    return 0;
}
