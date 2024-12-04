#ifndef GENERATEUR_H_INCLUDED
#define GENERATEUR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 128

int gen_mdp(char* mdp_out);

#endif // GENERATEUR_H_INCLUDED
