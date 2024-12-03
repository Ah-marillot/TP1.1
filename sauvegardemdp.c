#include "sauvegardemdp.h"
#include "consultmdp.h"

/*
// Fonction pour vérifier si le login existe déjà
int login_exists(const char *login) {
    FILE *file = fopen(MYFILE, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    char line[256];
    char file_login[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s", file_login);
        if (strcmp(file_login, login) == 0) {
            fclose(file);
            return 1; // Login trouvé
        }
    }

    fclose(file);
    return 0; // Login non trouvé
}

// Fonction pour enregistrer le login et le mot de passe chiffré
void Enregistrer(const char *login, char *password, const char *key) {
    if (login_exists(login)) {
        printf("Le login existe deja.\n");
        return;
    }

    printf("Enregistrement\n");
    // Chiffrer le mot de passe
    encrypt(password, key);

    // Ouvrir le fichier en mode append
    FILE *file = fopen(MYFILE, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le login et le mot de passe chiffré dans le fichier
    fprintf(file, "%s\t%s\n", login, password);

    // Fermer le fichier
    fclose(file);
}*/
// Fonction pour enregistrer le login, le mot de passe chiffré, le type de login et le nom du service
void registerPass(const char *login, char *password, const char *key, const char *login_type, const char *service_name) {
    if (login_exists(login)) {
        printf("Le login existe deja.\n");
        return;
    }

    printf("Enregistrement\n");
    // Chiffrer le mot de passe
    encrypt(password, key);

    // Ouvrir le fichier en mode append
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le login, le mot de passe chiffré, le type de login et le nom du service dans le fichier
    fprintf(file, "%s\t%s\t%s\t%s\n", login, password, login_type, service_name);

    // Fermer le fichier
    fclose(file);
}

// Fonction pour vérifier si le login existe déjà si oui retourne la ligne (attention si il existe plusieurs fois, la fonction ne retournera que la première ligne)
int login_exists(const char *login) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    int nb_line = 1;
    char line[256];
    char file_login[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s", file_login);
        if (strcmp(file_login, login) == 0) {
            fclose(file);
            return nb_line; // Login trouvé
        }
        nb_line++;
    }

    fclose(file);
    return 0; // Login non trouvé
}
