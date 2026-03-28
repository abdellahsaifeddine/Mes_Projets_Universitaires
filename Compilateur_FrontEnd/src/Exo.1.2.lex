/*
 * Exo.1.2.lex
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Extension de Exo.1.1.lex : au lieu d'afficher chaque token,
 * on compte le nombre de concerts par commande et on affiche
 * le prenomNom ainsi que ce compteur en fin de traitement.
 *
 * Sortie attendue :
 *   ANNE-CLAIRE/BERGEY a achete des places de 3 concerts.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_concerts = 0;        /* Compteur de lignes concert */
char prenom_nom[256] = "";  /* Stockage du prenomNom pour l'affichage final */
int ligne = 0;              /* Numero de ligne courante pour identifier les sections */
%}

DOSSIER     [0-9]{8}
PRENOM_NOM  [A-Z][A-Z\-]*\/[A-Z][A-Z\-]*
CODE        [A-Z][A-Z0-9]*
NOM_CONCERT [A-Za-z][A-Za-z0-9]*
DATE        [0-9]{1,2}\/[0-9]{1,2}(\/[0-9]{2})?
HEURE       [0-9]{2}:[0-9]{2}
NB_PLACES   [1-9][0-9]?
PLACES      places
BLANC       [ \t]+
RC          \n

%%

{DOSSIER}       {
                    /* Ligne 1 : numero de dossier, on incremente la ligne */
                    ligne++;
                }

{PRENOM_NOM}    {
                    /* Ligne 2 : on sauvegarde le prenomNom pour l'affichage final */
                    strncpy(prenom_nom, yytext, sizeof(prenom_nom) - 1);
                }

{PLACES}        {
                    /*
                     * Le mot "places" apparait exactement une fois par ligne de concert.
                     * On l'utilise comme marqueur pour compter les concerts.
                     */
                    nb_concerts++;
                }

{DATE}          { /* token reconnu mais non affiche */ }
{HEURE}         { /* token reconnu mais non affiche */ }
{NB_PLACES}     { /* token reconnu mais non affiche */ }
{CODE}          { /* token reconnu mais non affiche */ }
{NOM_CONCERT}   { /* token reconnu mais non affiche */ }
{RC}            { /* retour chariot ignore */ }
{BLANC}         { /* blancs et tabulations ignores */ }

<<EOF>>         {
                    /* Affichage du bilan en fin de fichier */
                    printf("%s a achete des places de %d concerts.\n",
                           prenom_nom, nb_concerts);
                    return 0;
                }

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
