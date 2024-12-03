#include "consultmdp.h"

/*
// Fonction pour chiffrer le mot de passe en assurant des caractères imprimables
void encrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] ^ key[i % key_len]) % 94) + 33; // Assure des caractères imprimables
    }
}

// Fonction pour déchiffrer le mot de passe
void decrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] - 33 + 94) % 94) ^ key[i % key_len]; // Reconvertit en caractères originaux
    }
}

// Fonction : Consultation des mots de passe
void viewPasswords() {
    char masterPass[MAX_PASSWORD_LENGTH];
    char line[MAX_PASSWORD_LENGTH];

    printf("\n=== Consultation des Mots de Passe ===\n");
    printf("Entrez le mot de passe maitre : ");
    scanf("%s", masterPass);

    if (strcmp(masterPass, MASTER_PASSWORD) != 0) {
        printf("Mot de passe incorrect.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Aucun mot de passe sauvegarde.\n");
        return;
    }

    printf("\nListe des mots de passe:\n");
    printf("\nIdentifiant | Type de Login | Service | Mot de Passe\n");
    printf("----------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char identifier[MAX_PASSWORD_LENGTH], service[MAX_PASSWORD_LENGTH], password[MAX_PASSWORD_LENGTH];
        int type;
        sscanf(line, "%[^,],%[^,],%[^,],%s", identifier, &type, service, password);
            encrypt(password, -3);
            decrypt(password, -3); // Décrypter le mot de passe
            printf("%s | %s | %d | %s\n", identifier, type, service, password);
    }

    fclose(file);
}*/

// Fonction : Suppression d'un mot de passe retourne le mot de passe supprimé décrypté
char* deletePassword(int targetLine, char* masterPass) {
    char line[MAX_LINE];
    char lines[100][MAX_PASSWORD_LENGTH];
    int lineCount = 0;
    char password[MAX_PASSWORD_LENGTH +1];
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Aucun mot de passe sauvegarde.\n");
        return;
    }

    // Lecture des lignes du fichier
    while (fgets(line, sizeof(line), file)) {
        strcpy(lines[lineCount], line);
        lineCount++;
        printf("Hello %d\n", lineCount);
    }
    fclose(file);

    printf("Hello %d\n", lineCount);

    if (targetLine < 1 || targetLine > lineCount) {
        flushInputBuffer();
        printf("Entree invalide, il n'y a que %d ligne. Annulation de l'operation.\n", lineCount);
        return;
    }

    // Réécriture des lignes dans le fichier sans celle à supprimer
    file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        if (i != targetLine - 1) {
            fprintf(file, "%s", lines[i]);
        }else{
            sscanf(line[i],"%*s %s %*s %*s", password);
            decrypt(password, masterPass);
        }
    }
    fclose(file);
    return password;
}

// Fonction utilitaire : Vider le tampon d'entrée
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fonction pour chiffrer le mot de passe en assurant des caractères imprimables
void encrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] ^ key[i % key_len]) % 94) + 33; // Assure des caractères imprimables
    }
}

// Fonction pour déchiffrer le mot de passe
void decrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] - 33 + 94) % 94) ^ key[i % key_len]; // Reconvertit en caractères originaux
    }
}



// Fonction pour vérifier si le service existe déjà
int service_exists(const char *service_name) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return 0;
    }
    int nb_line = 1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char stored_service[100];
        sscanf(line, "%*s %*s %*s %s", stored_service); // Ignorer les trois premiers champs et lire le service_name
        if (strcmp(stored_service, service_name) == 0) {
            fclose(file);
            return nb_line; // Service trouvé
        }
        nb_line++;
    }

    fclose(file);
    return 0;
}

// Fonction pour afficher les mots de passe déchiffrés
char* viewPasswords(const char* key) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    // Allouer un buffer pour stocker toutes les lignes
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        return NULL;
    }
    buffer[0] = '\0'; // Initialiser le buffer

    // Ajouter l'en-tête
    strcat(buffer, "login\tpassword\tlogin_type\tservice\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char login[100], encrypted_password[100], login_type[100], service[100];
        sscanf(line, "%s\t%s\t%s\t%s", login, encrypted_password, login_type, service);

        // Déchiffrer le mot de passe
        decrypt(encrypted_password, key);

        // Afficher les informations déchiffrées
        char line[MAX_LINE];
        sprintf(line, "%s\t%s\t%s\t%s\n", login, encrypted_password, login_type, service);
        strcat(buffer, line);

        // Ajouter les informations déchiffrées au buffer
        /*size_t needed_size = strlen(buffer) + strlen(login) + strlen(encrypted_password) + strlen(login_type) + strlen(service) + 5;
        if (needed_size > buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (buffer == NULL) {
                perror("Erreur d'allocation mémoire");
                fclose(file);
                return NULL;
            }
        }
        strcat(buffer, login);
        strcat(buffer, "\t");
        strcat(buffer, encrypted_password);
        strcat(buffer, "\t");
        strcat(buffer, login_type);
        strcat(buffer, "\t");
        strcat(buffer, service);
        strcat(buffer, "\n");*/
    }

    fclose(file);
    return buffer;
}

// Fonction pour supprimer un mot de passe
/*char* deletePassword(const char* key, char* service_name, char* login) {
    FILE *file = fopen(MYFILE, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    //Creer une ligne temporaire pour stocker les informations
    char line[256];
    //Lire chaque ligne du fichier jusqu'à ce que le login et le service matchent
    while (fgets(line, sizeof(line), file)) {
        char stored_login[100], stored_encrypted_password[100], stored_login_type[100], stored_service[100];
        sscanf(line, "%s\t%s\t%s\t%s", stored_login, stored_encrypted_password, stored_login_type, stored_service);

        //Déchiffrer le mot de passe
        decrypt(stored_encrypted_password, key);

        //Si le login et le service correspondent, supprimer la ligne
        if (strcmp(stored_login, login) == 0 && strcmp(stored_service, service_name) == 0) {
            fclose(file);
            FILE *new_file = fopen("temp.txt", "w");
            if (new_file == NULL) {
                perror("Erreur lors de l'ouverture du fichier temporaire");
                return NULL;
            }

            //Réécrire toutes les lignes sauf celle à supprimer
            rewind(file);
            while (fgets(line, sizeof(line), file)) {
                char stored_login[100], stored_encrypted_password[100], stored_login_type[100], stored_service[100];
                sscanf(line, "%s\t%s\t%s\t%s", stored_login, stored_encrypted_password, stored_login_type, stored_service);

                //Déchiffrer le mot de passe
                decrypt(stored_encrypted_password, key);

                if (strcmp(stored_login, login) != 0 || strcmp(stored_service, service_name) != 0) {
                    fprintf(new_file, "%s\t%s\t%s\t%s\n", stored_login, stored_encrypted_password, stored_login_type, stored_service);
                }
            }

            fclose(file);
            fclose(new_file);
            remove(MYFILE);
            rename("temp.txt", MYFILE);
            return stored_encrypted_password;
        }
    }
    fclose(file);
    return "Mot de passe non trouvé";
}*/
