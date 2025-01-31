/*
Noms :      ALI             AWISSOBA            LAWSON

Prenoms :   Farouk          Malibida            Late Jonathan

Nom du projet : Jeu de devinette

Code et intitule d'UE : INF 1329 - Projet Tuteuré 1

Parcours : Licence professionnelle Genie Logiciel

Professeur : Mr AKAKPO

Annee academique : 2024-2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pseudo.h"
#include "session.h"
#include "statistiques.h"

#define MAX_TENTATIVES 10

int main() {
    srand(time(NULL));

    char pseudo[50];
    int nombre_a_deviner, tentative, tentatives[MAX_TENTATIVES];
    int nombre_tentatives = 0;
    char choix;

    printf("Entrez votre pseudo : ");
    scanf("%s", pseudo);

    // Vérifier et enregistrer le pseudo
    if (verifier_pseudo(pseudo) == 0) {
        enregistrer_pseudo(pseudo);
    }

    do {
        int borne_max;
        printf("Entrez la borne maximale pour le nombre a deviner : ");
        scanf("%d", &borne_max);
        nombre_a_deviner = rand() % borne_max + 1;

        printf("Devinez le nombre entre 1 et %d.\n", borne_max);

        nombre_tentatives = 0;
        while (nombre_tentatives < MAX_TENTATIVES) {
            printf("Tentative %d : ", nombre_tentatives + 1);
            scanf("%d", &tentative);
            tentatives[nombre_tentatives] = tentative;
            nombre_tentatives++;

            if (tentative < nombre_a_deviner) {
                printf("Plus grand !\n");
            } else if (tentative > nombre_a_deviner) {
                printf("Plus petit !\n");
            } else {
                printf("Félicitations, vous avez trouvé en %d tentatives !\n", nombre_tentatives);
                break;
            }
        }

        if (nombre_tentatives == MAX_TENTATIVES) {
            printf("Vous avez épuisé vos tentatives. Le nombre était : %d\n", nombre_a_deviner);
        }

        // Calculer l'écart-type
        double ecart_type = calculer_ecart_type(tentatives, nombre_tentatives);

        // Enregistrer la session
        Session session;
        strcpy(session.pseudo, pseudo);
        time_t now = time(NULL);
        strftime(session.date_heure, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
        for (int i = 0; i < nombre_tentatives; i++) {
            session.tentatives[i] = tentatives[i];
        }
        session.ecart_type = ecart_type;
        enregistrer_session(&session);

        do {
            printf("Voulez-vous rejouer ? (O/N) : ");
            scanf(" %c", &choix);
            while (getchar() != '\n');

        } while (choix != 'O' && choix != 'o' && choix != 'N' && choix != 'n');

    } while (choix == 'O' || choix == 'o');
    // Afficher les archives
    do {
        printf("Voulez-vous consulter les archives ? (O/N) : ");
        scanf(" %c", &choix);
        while (getchar() != '\n');
    } while (choix != 'O' && choix != 'o' && choix != 'N' && choix != 'n');

    if (choix == 'O' || choix == 'o') {
        afficher_archives();
    }

    return 0;
}
