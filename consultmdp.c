#include "consultmdp.h"


// Fonction : Suppression d'un mot de passe retourne le mot de passe supprime decrypte
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

    // Reecriture des lignes dans le fichier sans celle supprimer
    file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        if (i != targetLine - 1) {
            fprintf(file, "%s", lines[i]);
        }else{
            sscanf(lines[i],"%*s %s %*s %*s", password);
            decrypt(password, masterPass);
        }
    }
    fclose(file);
    return password;
}

// Fonction utilitaire : Vider le tampon d'entree
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fonction pour chiffrer le mot de passe en assurant des caracteres imprimables
void encrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] ^ key[i % key_len]) % 94) + 33; // Assure des caracteres imprimables
    }
}

// Fonction pour d�chiffrer le mot de passe
void decrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] - 33 + 94) % 94) ^ key[i % key_len]; // Reconvertit en caracteres originaux
    }
}



// Fonction pour verifier si le service existe deja
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
            return nb_line; // Service trouv�
        }
        nb_line++;
    }

    fclose(file);
    return 0;
}

// Fonction pour afficher les mots de passe d�chiffr�s
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
        perror("Erreur d'allocation m�moire");
        fclose(file);
        return NULL;
    }
    buffer[0] = '\0'; // Initialiser le buffer

    // Ajouter l'en-t�te
    strcat(buffer, "login\tpassword\tlogin_type\tservice\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char login[100], encrypted_password[100], login_type[100], service[100];
        sscanf(line, "%s\t%s\t%s\t%s", login, encrypted_password, login_type, service);

        // D�chiffrer le mot de passe
        decrypt(encrypted_password, key);

        // Afficher les informations d�chiffr�es
        char line[MAX_LINE];
        sprintf(line, "%s\t%s\t%s\t%s\n", login, encrypted_password, login_type, service);
        strcat(buffer, line);

        // Ajouter les informations d�chiffr�es au buffer
        /*size_t needed_size = strlen(buffer) + strlen(login) + strlen(encrypted_password) + strlen(login_type) + strlen(service) + 5;
        if (needed_size > buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (buffer == NULL) {
                perror("Erreur d'allocation m�moire");
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
    //Lire chaque ligne du fichier jusqu'� ce que le login et le service matchent
    while (fgets(line, sizeof(line), file)) {
        char stored_login[100], stored_encrypted_password[100], stored_login_type[100], stored_service[100];
        sscanf(line, "%s\t%s\t%s\t%s", stored_login, stored_encrypted_password, stored_login_type, stored_service);

        //D�chiffrer le mot de passe
        decrypt(stored_encrypted_password, key);

        //Si le login et le service correspondent, supprimer la ligne
        if (strcmp(stored_login, login) == 0 && strcmp(stored_service, service_name) == 0) {
            fclose(file);
            FILE *new_file = fopen("temp.txt", "w");
            if (new_file == NULL) {
                perror("Erreur lors de l'ouverture du fichier temporaire");
                return NULL;
            }

            //R��crire toutes les lignes sauf celle � supprimer
            rewind(file);
            while (fgets(line, sizeof(line), file)) {
                char stored_login[100], stored_encrypted_password[100], stored_login_type[100], stored_service[100];
                sscanf(line, "%s\t%s\t%s\t%s", stored_login, stored_encrypted_password, stored_login_type, stored_service);

                //D�chiffrer le mot de passe
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
    return "Mot de passe non trouv�";
}*/
