

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Prototypes des fonctions
char* expandVariables(const char *input);
char* appendVariableValue(char *result, const char *varName);
char* extractVarName(const char **ptr);
char* copyUntilChar(char *dest, const char *src, char delimiter);

// Fonction principale pour l'expansion des variables
char* expandVariables(const char *input) {
    const char *ptr = input;
    char *result = strdup("");
    char *temp;

    while (*ptr) {
        if (*ptr == '$' && (isalpha(*(ptr + 1)) || *(ptr + 1) == '?')) {
            ptr++; // Passer le symbole '$'
            char *varName = extractVarName(&ptr);
            temp = appendVariableValue(result, varName);
            free(result);
            result = temp;
            free(varName);
        } else {
            const char *nextDollar = strchr(ptr, '$');
            if (!nextDollar) nextDollar = ptr + strlen(ptr); // Si pas de '$', aller à la fin
            temp = copyUntilChar(result, ptr, *nextDollar);
            free(result);
            result = temp;
            ptr = nextDollar;
        }
    }

    return result;
}

// Fonction pour copier la chaîne jusqu'au caractère délimitateur
char* copyUntilChar(char *dest, const char *src, char delimiter) {
    size_t len = strlen(dest);
    size_t n = 0;
    const char *ptr = src;
    while (*ptr && *ptr != delimiter) {
        n++;
        ptr++;
    }
    char *newResult = malloc(len + n + 1);
    strcpy(newResult, dest);
    strncat(newResult, src, n);
    return newResult;
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

int main() {
    const char *input = "ici$USER coucou";
    char *expanded = expandVariables(input);

    printf("Avant l'expansion : %s\n", input);
    printf("Après l'expansion : %s\n", expanded);

    free(expanded);

    return 0;
}