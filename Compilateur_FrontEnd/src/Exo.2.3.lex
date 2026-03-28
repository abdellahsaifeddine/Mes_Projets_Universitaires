/*
 * Exo.2.3.lex
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Extension de Exo.2.2.lex pour reconnaitre les numeros de places
 * apres le mot cle "places" sur chaque ligne de concert.
 * Fonctionne en tandem avec Exo.2.3.yacc.
 *
 * Aucune modification majeure necessaire : les numeros de places
 * sont des entiers non signes, deja couverts par TOKEN_ENTIER.
 */

%{
#include <stdio.h>
#include "Exo.2.3.yacc.h"
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

{DOSSIER}       { yylval.entier = atoi(yytext); return TOKEN_DOSSIER; }
{PRENOM_NOM}    { return TOKEN_PRENOM_NOM; }
{DATE}          { return TOKEN_DATE; }
{HEURE}         { return TOKEN_HEURE; }
{PLACES}        { return TOKEN_PLACES; }
{NB_PLACES}     { yylval.entier = atoi(yytext); return TOKEN_ENTIER; }
{CODE}          { return TOKEN_CODE; }
{NOM_CONCERT}   { return TOKEN_NOM; }
{RC}            { return TOKEN_RC; }
{BLANC}         { /* ignore */ }

.               {
                    fprintf(stderr, "Erreur lexicale : caractere inconnu '%s'\n", yytext);
                }

%%

int yywrap() { return 1; }
