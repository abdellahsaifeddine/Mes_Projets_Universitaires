/*
 * Exo.2.1.yacc
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Analyseur syntaxique pour une commande de billets de concert.
 * Affiche "La commande est valide" si la commande respecte la grammaire,
 * "syntax error" sinon (comportement par defaut de yacc).
 *
 * Grammaire :
 *   commande    -> TOKEN_DOSSIER TOKEN_RC TOKEN_PRENOM_NOM TOKEN_RC concerts
 *   concerts    -> concert | concerts concert
 *   concert     -> TOKEN_CODE TOKEN_NOM TOKEN_DATE TOKEN_HEURE TOKEN_ENTIER TOKEN_PLACES TOKEN_RC
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

/* Declaration des tokens */
%token TOKEN_DOSSIER
%token TOKEN_PRENOM_NOM
%token TOKEN_CODE
%token TOKEN_NOM
%token TOKEN_DATE
%token TOKEN_HEURE
%token TOKEN_PLACES
%token TOKEN_RC
%token <entier> TOKEN_ENTIER

%%

/*
 * Regle principale : une commande complete
 * Structure : dossier RC prenomNom RC liste_de_concerts EOF
 */
commande
    : TOKEN_DOSSIER TOKEN_RC
      TOKEN_PRENOM_NOM TOKEN_RC
      concerts
      {
          printf("La commande est valide\n");
      }
    ;

/* Une commande contient au moins un concert */
concerts
    : concert
    | concerts concert
    ;

/*
 * Un concert = codeConcert nomConcert date heure nb places RC
 */
concert
    : TOKEN_CODE TOKEN_NOM TOKEN_DATE TOKEN_HEURE TOKEN_ENTIER TOKEN_PLACES TOKEN_RC
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
