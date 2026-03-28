/*
 * Exo.2.3.yacc
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Extension de Exo.2.1.yacc pour reconnaitre les numeros de places
 * apres le mot cle "places" sur chaque ligne de concert.
 *
 * Modification de la grammaire :
 *   concert -> CODE NOM DATE HEURE ENTIER PLACES liste_numeros RC
 *   liste_numeros -> ENTIER | liste_numeros ENTIER
 *
 * On se contente de valider la syntaxe (valide / syntax error).
 * Les numeros de places sont des entiers non signes quelconques.
 */

%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

int yylex();
%}

%union {
    int entier;
}

%token <entier> TOKEN_DOSSIER
%token TOKEN_PRENOM_NOM
%token TOKEN_CODE
%token TOKEN_NOM
%token TOKEN_DATE
%token TOKEN_HEURE
%token TOKEN_PLACES
%token TOKEN_RC
%token <entier> TOKEN_ENTIER

%%

commande
    : TOKEN_DOSSIER TOKEN_RC
      TOKEN_PRENOM_NOM TOKEN_RC
      concerts
      {
          printf("La commande est valide\n");
      }
    ;

concerts
    : concert
    | concerts concert
    ;

/*
 * Un concert contient maintenant une liste de numeros de places
 * apres le mot cle "places". La liste doit contenir exactement
 * nb entiers (correspondant a TOKEN_ENTIER avant TOKEN_PLACES).
 * Ici on valide seulement la syntaxe sans compter.
 */
concert
    : TOKEN_CODE TOKEN_NOM TOKEN_DATE TOKEN_HEURE TOKEN_ENTIER TOKEN_PLACES liste_numeros TOKEN_RC
    ;

/*
 * liste_numeros : un ou plusieurs entiers non signes.
 * Regle recursive a gauche pour reconnaitre la suite de numeros.
 */
liste_numeros
    : TOKEN_ENTIER
    | liste_numeros TOKEN_ENTIER
    ;

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        extern FILE *yyin;
        FILE *f = fopen(argv[1], "r");
        if (!f) { perror("Erreur ouverture fichier"); return 1; }
        yyin = f;
    }
    yyparse();
    return 0;
}
