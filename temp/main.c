#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "generateur.h"
#include "consultmdp.h"

// Définir une longueur maximale pour le mot de passe
#define MAX_PASSWORD_LENGTH 128
#define MASTER_PASSWORD "password123"
#define FILE_NAME "passwords.txt"

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
    char *confirm;
    do {
        printf("%s", message);
        scanf("%s", value);
        flushInputBuffer();
        printf("Confirmez (O/N) : ");
        char confirm;
        scanf("%c", &confirm);
        flushInputBuffer();
    } while (confirm != 'O' && confirm != 'o');
}

// Fonction utilitaire : Vider le tampon d'entrée
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return;
}


void menuprincipal()
{
   printf("Faites votre sousmenu pour acceder a une fonction du menu (1/2/3/4).\n");
   printf("1 : Generer un mot de passe\n");
   printf("2 : Consultation des mots de passe deja crees\n");
   printf("3 : Sauvegarde du mot de passe\n");
   printf("4 : Supprimer un mot de passe\n");
   printf("5 : Exit\n");
   printf("Votre sousmenu : ");
}

// //Appel des fonctions
// void menuprincipal();
// void viewPasswords();
// void encrypt(char *password, const char *key);
// void decrypt(char *password, const char *key);
// void gen_mdp();
// void registerPass();
// void flushInputBuffer();

// Affiche le menu principal

int main() {

char menu;
char sousmenu;
char password[MAX_PASSWORD_LENGTH + 1];
char masterPass[MAX_PASSWORD_LENGTH + 1];

   printf(" ________________________________________________________\n");
   printf("|                                                        |\n");
   printf("|                Gestionnaire de mot de passe            |\n");
   printf("|                            Menu                        |\n");
   printf("|                                                        |\n");
   printf("|________________________________________________________|\n\n");

   do {
        menuprincipal();
    if (scanf("%c", &menu) != 1) {
            flushInputBuffer();
            printf("Entrée invalide. Réessayez.\n");
        return 1;
    }
        switch (menu) {
        case '1':
            printf("Vous entrez dans le module de creation de mot de passe\n");
            char* mdp[129];
            gen_mdp(mdp);
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
            break;
        case '2':
            //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
            for(int i = 0; i < 3; i++)
            {
                printf("Entrez le mot de passe maitre : ");
                char masterPass[MAX_PASSWORD_LENGTH];
                scanf("%s", masterPass);
                flushInputBuffer();
                if(strcmp(masterPass, MASTER_PASSWORD) == 0)
                {
                    viewPasswords(masterPass);
                    break;
                }else{
                    printf("Mot de passe maitre incorrect.\n");
                }
            }   
            break;
        case '3':
            break;
        case '4':
            //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
            if(askMasterPassword(masterPass) == 0)
            {
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
                printf("Le mot de passe %s à été supprimé", deletePassword(masterPass, service, login));
            }
            break;
        case '5':
            printf("Au revoir !\n");
            break;
        default:
            printf("Option invalide.\n");
        }
    } while (menu != '5');

    return 0;
}