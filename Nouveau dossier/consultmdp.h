#ifndef CONSULTMDP_H_INCLUDED
#define CONSULTMDP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 128
#define MASTER_PASSWORD "password3A"
#define FILE_NAME "data.txt"
#define MAX_LINE 256


void encrypt(char *password, const char *key);
void decrypt(char *password, const char *key);
//void viewPasswords();
//void deletePassword();
void registerPass(const char *login, char *password, const char *key, const char *login_type, const char *service_name);

int service_exists(const char *service_name);
char* viewPasswords(const char* key);
char* deletePassword(int targetLine, char* masterPass);

#endif // CONSULTMDP_H_INCLUDED
