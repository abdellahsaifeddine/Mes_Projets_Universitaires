/*
 * Exo.2.2.yacc
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Analyseur syntaxique qui calcule et affiche le nombre total de places
 * concernees par un dossier de commande.
 *
 * Sortie attendue :
 *   Le dossier 12345678 concerne 17 places
 *
 * La valeur semantique du token TOKEN_DOSSIER (l'entier 8 chiffres) est
 * propagee jusqu'a la regle commande via $1.
 * Chaque concert contribue son nombre de places ($5) au total.
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

/* Les non-terminaux concerts et concert ont une valeur semantique entiere */
%type <entier> concerts concert

%%

/*
 * commande : recupere le numero de dossier ($1) et le total de places
 * accumule dans concerts ($5) pour l'affichage final.
 */
commande
    : TOKEN_DOSSIER TOKEN_RC
      TOKEN_PRENOM_NOM TOKEN_RC
      concerts
      {
          printf("Le dossier %d concerne %d places\n", $1, $5);
      }
    ;

/*
 * concerts : accumule les places de tous les concerts.
 * Valeur semantique = somme des places de tous les concerts.
 */
concerts
    : concert               { $$ = $1; }
    | concerts concert      { $$ = $1 + $2; }
    ;

/*
 * concert : retourne le nombre de places ($5 = TOKEN_ENTIER).
 * Les autres tokens sont consommes sans valeur semantique utile.
 */
concert
    : TOKEN_CODE TOKEN_NOM TOKEN_DATE TOKEN_HEURE TOKEN_ENTIER TOKEN_PLACES TOKEN_RC
      { $$ = $5; }
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
