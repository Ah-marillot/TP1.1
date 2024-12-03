#ifndef SAUVEGARDEMDP_H_INCLUDED
#define SAUVEGARDEMDP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int login_exists(const char *login);
void registerPass(const char *login, char *password, const char *key, const char *login_type, const char *service_name);

#endif // SAUVEGARDEMDP_H_INCLUDED
