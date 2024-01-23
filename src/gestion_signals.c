/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:14:12 by blax              #+#    #+#             */
/*   Updated: 2023/12/11 23:24:52 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Gestionnaire de signal pour SIGINT
void handle_sigint(int sig) {
    // Affiche un nouveau prompt sur une nouvelle ligne
    write(STDOUT_FILENO, "\n", 1);
    // Vous pouvez réafficher le prompt du shell ici si nécessaire
}

// Gestionnaire de signal pour SIGQUIT
void handle_sigquit(int sig) {
    // Ne fait rien pour ctrl-\
}

int main() {
    // Configurer les gestionnaires de signaux
    struct sigaction sa_int = {0}, sa_quit = {0};

    sa_int.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit;
    sigaction(SIGQUIT, &sa_quit, NULL);

    // Boucle principale du shell
    while (1) {
        // Afficher le prompt et lire l'entrée de l'utilisateur
        // ...

        // Si l'utilisateur tape ctrl-D (EOF), quittez le shell
        if (feof(stdin)) {
            printf("\n");
            exit(0);
        }

        // Exécuter la commande
        // ...
    }

    return 0;
}