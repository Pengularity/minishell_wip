
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Prototype des fonctions
char* expandVariables(const char *input);
char* appendVariableValue(char *result, const char *varName);
char* appendChar(char *result, char c);
char* extractVarName(const char **ptr);

// Fonction principale pour l'expansion des variables
char* expandVariables(const char *input) {
    const char *ptr = input;
    char *result = strdup("");

    while (*ptr) {
        if (*ptr == '$' && (isalpha(*(ptr + 1)) || *(ptr + 1) == '?')) {
            ptr++; // Passer le symbole '$'
            char *varName = extractVarName(&ptr);
            char *temp = appendVariableValue(result, varName);
            free(result);
            result = temp;
            free(varName);
        } else {
            char *temp = appendChar(result, *ptr);
            free(result);
            result = temp;
            ptr++;
        }
    }

    return result;
}

// Fonction pour extraire le nom de la variable
char* extractVarName(const char **ptr) {
    const char *start = *ptr;
    while (isalnum(**ptr) || **ptr == '_') {
        (*ptr)++;
    }
    return strndup(start, *ptr - start);
}

// Fonction pour ajouter la valeur de la variable au résultat
char* appendVariableValue(char *result, const char *varName) {
    char *varValue = getenv(varName);
    if (varValue) {
        size_t newLength = strlen(result) + strlen(varValue) + 1;
        char *newResult = malloc(newLength);
        strcpy(newResult, result);
        strcat(newResult, varValue);
        return newResult;
    }
    return strdup(result);
}

// Fonction pour ajouter un caractère au résultat
char* appendChar(char *result, char c) {
    size_t len = strlen(result);
    char *newResult = malloc(len + 2);
    strcpy(newResult, result);
    newResult[len] = c;
    newResult[len + 1] = '\0';
    return newResult;
}

int main() {
    // const char *input = "ici$bonjour coucou";
    // const char *input = "ici$USER coucou";
    const char *input = "ici$=USER coucou";
    char *expanded = expandVariables(input);

    printf("Avant l'expansion : %s\n", input);
    printf("Après l'expansion : %s\n", expanded);

    free(expanded);

    return 0;
}