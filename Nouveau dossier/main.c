#include "generateur.h"
#include "consultmdp.h"
#include "sauvegardemdp.h"

const char* typeCompte[3] = {"Machine", "Messagerie", "Compte en ligne"};

// Fonction pour demander le mot de passe maitre, les demande 3 fois retourne 0 si le mot de passe est correct, 1 sinon
int askMasterPassword(char *masterPass) {
    for(int i = 0; i < 3; i++)
    {
        printf("Entrez le mot de passe maitre : ");
        scanf("%s", masterPass);
        flushInputBuffer();
        if(strcmp(masterPass, MASTER_PASSWORD) == 0)
        {
            return 0;
        }else{
            printf("Mot de passe maitre incorrect.\n");
        }
    }
    return 1;
}

// Fonction pour rentrer une valeur avec une avec confirmation
void enterValue(char *value, char *message) {
    char confirm;
    do {
        printf("%s", message);
        scanf("%s", value);
        flushInputBuffer();
        printf("Confirmez (O/N) : ");
        scanf("%c", &confirm);
        flushInputBuffer();
    } while (confirm != 'O' && confirm != 'o');
}

void menuprincipal()
{
    printf("=========================MENU PRINCIPAL=========================\n");
    printf("Faites votre choix pour acceder a une fonction du menu (1/2/3/4).\n");
    printf("1 : Generer un mot de passe\n");
    printf("2 : Consultation des mots de passe deja crees\n");
    printf("3 : Supprimer un mot de passe\n");
    printf("4 : Exit\n");
    printf("Votre choix : ");
}

int main() {

    char menu;
    char sousmenu;
    char password[MAX_PASSWORD_LENGTH];
    int length, lowercase, uppercase, digits;
   printf(" ________________________________________________________\n");
   printf("|                                                        |\n");
   printf("|                Gestionnaire de mot de passe            |\n");
   printf("|                                                        |\n");
   printf("|________________________________________________________|\n\n");

   do {
        menuprincipal();
    if (scanf("%d", &menu) != 1) {
            flushInputBuffer();
            printf("Entree invalide. Reessayez.\n");
        return 1;
    }
        switch (menu) {
        case 1:
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
                    //Demander le login et la confirmation à l'utilisateur que c'est le bon login
                    char login[MAX_PASSWORD_LENGTH];
                    enterValue(login, "Entrez le login : ");
                    char service[MAX_PASSWORD_LENGTH];
                    enterValue(service, "Entrez le service : ");
                    int type;
                    printf("Type de login (1: Machine, 2: Messagerie, 3: Compte en ligne) : ");
                    scanf("%d", &type);
                    //Demander le mot de passe maitre et verifier qu'il est correct avec 3 essais
                    if(askMasterPassword(password) == 0) {
                        registerPass(login, mdp, password, typeCompte[type-1], service);
                    }
                }
            }
            break;
        case 2:
            //Demander le mot de passe maitre et verifier qu'il est correct avec 3 essais pour afficher les mots de passes
            if(askMasterPassword(password) == 0)
            {
                printf("%s", viewPasswords(password));
            }
            break;
        case 3:
            //Demander le mot de passe maitre et verifier qu'il est correct avec 3 essais pour supprimer un mot de passe
            if(askMasterPassword(password) == 0){
                printf("%s", viewPasswords(password));
                printf("Entrer ligne a supprimer");
                int lineToDelete;
                scanf("%d", &lineToDelete);
                deletePassword(lineToDelete, password);
            }
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
