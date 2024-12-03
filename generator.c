#include "generator.h"

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128

void gen_mdp(char* mdp_out)
{
    const char *min,*maj,*chiffre,*c_sp;
    int nb_caracteres=0;
    int nb_maj=0;
    int nb_min=0;
    int nb_c_sp=0;
    int nb_chiffres=0;
    int i=0;
    int index = 0;

     // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    min = "abcdefghijklmnopqrstuvwxyz";
    chiffre = "0123456789";
    c_sp = "@!*#%$£:~";

    printf("*Bienvenue dans la gestion des mots de passe*\n");
    printf ("** combien voulez-vous de carateres(entre 8 et 128) :  \n");
    scanf ("%d", &nb_caracteres);

    if (nb_caracteres<MIN_PASSWORD_LENGTH || nb_caracteres>MAX_PASSWORD_LENGTH)
    {
        printf ("erreur, le nombre de caractere doit etre entre 8 et 128 ! \n");
        return 1 ;
    }
    else
    {
        // Demander combien de majuscules, minuscules, chiffres et caractères spéciaux
        printf("Combien de majuscules (maximum %d) ? ", nb_caracteres);
        scanf("%d", &nb_maj);

            if (nb_maj > nb_caracteres) {

                printf("Le nombre de majuscules ne peut pas depasser le total de caracteres.\n");
                return 1;
                                        }

        printf("Combien de minuscules (maximum %d) ? ", (nb_caracteres) - nb_maj);
        scanf("%d", &nb_min );

    if (nb_min > nb_caracteres - nb_maj)
    {
        printf("Le nombre de minuscules ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }

        printf("Combien de chiffres (maximum %d) ? ", (nb_caracteres) - nb_maj - nb_min);
        scanf("%d", &nb_chiffres);

    if (nb_chiffres > nb_caracteres - nb_maj - nb_min)
    {
        printf("Le nombre de chiffres ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }

        printf("Combien de caracteres speciaux (maximum %d) ? ", nb_caracteres - nb_maj - nb_min - nb_chiffres);
        scanf("%d", &nb_c_sp);

    if (nb_c_sp > nb_caracteres - nb_maj - nb_min - nb_chiffres)
    {
        printf("Le nombre de caracteres speciaux ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }
    int nb_restants = (nb_caracteres) - (nb_maj + nb_min + nb_chiffres + nb_c_sp); // ici on calcul le nombre de caractere

    if (nb_restants > 0)
        {
            printf("Le mot de passe sera complete avec %d caracteres aleatoires.\n", nb_restants);
            // que faire ???? a voir ...
        }
        // Allocation de mémoire pour le mot de passe
        char mdp[MAX_PASSWORD_LENGTH + 1];

        // Ajout des majuscules
        for (i = 0; i < nb_maj; i++)
        {
            mdp[index++] = maj[rand() % strlen(maj)]; // Selectionner un caratere dans la chaîne maj, et le stocker dans le tableau mdp (avec la position index), et on incrémente index pour avoir le ou les prochains caracteres

        }

        // Ajout des minuscules
        for (i = 0; i < nb_min; i++)
        {
            mdp[index++] = min[rand() % strlen(min)];
        }

        // Ajout des chiffres
        for (i = 0; i < nb_chiffres; i++)
        {
            mdp[index++] = chiffre[rand() % strlen(chiffre)];
        }

        // Ajout des caractères spéciaux
        for (i = 0; i < nb_c_sp; i++)
        {
            mdp[index++] = c_sp[rand() % strlen(c_sp)];
        }
        printf("index %d\n", index);
        //Tant que la boucle n'a pas atteint la longueur totale, on complete le mdp avec les caracteres aleatoires
        for (i = 0; i < nb_restants; i++)
        {
            int type = rand() % 4; // L'entier type va prendre une valeur aléatoire entre 0 et 3 à chaque execution de ces lignes

            if (type == 0)
            {
                mdp[index++] = maj[rand() % strlen(maj)];
            }

            else if (type == 1)
            {
                mdp[index++] = min[rand() % strlen(min)];
            }

            else if (type == 2)
            {
                mdp[index++] = chiffre[rand() % strlen(chiffre)];
            }

            else
            {
                mdp[index++] = c_sp[rand() % strlen(c_sp)];
            }
        }

        // melanger le mot de passe
        for (i = 0; i < nb_caracteres; i++) // on parcourt la ligne nb_caracteres
        {
            int j = rand() % nb_caracteres; // selectionner une position aleatoire entre et nb_caracteres -1
            char temp = mdp[i]; //Concatener deux tableaux pour mélanfer les caracteres
            mdp[i] = mdp[j];
            mdp[j] = temp;
        }
    printf("nb caractere %d\n", nb_caracteres);
    // Ajouter le caractere de fin de chaîne
    mdp[nb_caracteres] = '\0';
    printf("mdp %s\n", mdp);
    strcpy(mdp_out, mdp);
    printf("mdp_out %s\n", mdp_out);
    printf("Le mot de passe est genere\n");
    }
}