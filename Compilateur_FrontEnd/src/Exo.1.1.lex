/*
 * Exo.1.1.lex
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Analyseur lexical pour une commande de billets de concert.
 * Reconnait chaque token et l'affiche, en eliminant blancs et tabulations.
 *
 * Format attendu :
 *   - Ligne 1 : dossier (entier 8 chiffres)
 *   - Ligne 2 : prenomNom (PRENOM/NOM en majuscules avec tirets possibles)
 *   - Lignes suivantes : codeConcert nomConcert date heure nb places
 *   - Fin de fichier
 */

%{
#include <stdio.h>
#include <stdlib.h>

/* Compteur de concerts pour l'exercice 1.2 */
int nb_concerts = 0;
%}

/* --- Definitions des fragments reguliers --- */

/* Un dossier est un entier de exactement 8 chiffres */
DOSSIER     [0-9]{8}

/* prenomNom : lettres majuscules, tirets, slash separant prenom et nom */
PRENOM_NOM  [A-Z][A-Z\-]*\/[A-Z][A-Z\-]*

/* Code concert : lettre(s) suivie(s) de chiffres */
CODE        [A-Z][A-Z0-9]*

/* Nom de concert : commence par une majuscule, peut contenir minuscules/chiffres */
NOM_CONCERT [A-Za-z][A-Za-z0-9]*

/* Date : DD/MM, DD/M, DD/MM/YY ou DD/M/YY */
DATE        [0-9]{1,2}\/[0-9]{1,2}(\/[0-9]{2})?

/* Heure : HH:MM */
HEURE       [0-9]{2}:[0-9]{2}

/* Nombre de places : entier entre 1 et 99 */
NB_PLACES   [1-9][0-9]?

/* Mot cle "places" en minuscules */
PLACES      places

/* Separateurs (ignores) */
BLANC       [ \t]+

/* Retour chariot */
RC          \n

%%

{DOSSIER}       { printf("dossier\n"); }
{PRENOM_NOM}    { printf("prenomNom\n"); }
{DATE}          { printf("date\n"); }
{HEURE}         { printf("heure\n"); }
{NB_PLACES}     { printf("nb\n"); }
{PLACES}        { printf("places\n"); }
{CODE}          { printf("codeConcert\n"); }
{NOM_CONCERT}   { printf("nomConcert\n"); }
{RC}            { printf("RC\n"); }
{BLANC}         { /* on ignore les blancs et tabulations */ }
<<EOF>>         { printf("FinFichier\n"); return 0; }

.               {
                    fprintf(stderr, "Erreur lexicale : caractere inconnu '%s'\n", yytext);
                }

%%

int yywrap() { return 1; }

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) { perror("Erreur ouverture fichier"); return 1; }
        yyin = f;
    }
    yylex();
    return 0;
}
