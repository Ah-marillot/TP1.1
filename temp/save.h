#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définir la constante MYFILE
#define MYFILE "passwords.txt"

// Déclaration des fonctions
void decrypt(char *password, const char *key);
void encrypt(char *password, const char *key);
void registerPass(const char *login, char *password, const char *key, const char *login_type, const char *service_name);
int login_exists(const char *login);
int service_exists(const char *service_name);
char* viewPasswords(const char* key);
char* deletePassword(const char* key, char* service_name, char* login);
#endif // SAVE_H