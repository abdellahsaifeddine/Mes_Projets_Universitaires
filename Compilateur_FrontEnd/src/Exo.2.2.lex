/*
 * Exo.2.2.lex
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 *
 * Meme lexer que Exo.2.1.lex, adapte pour Exo.2.2.yacc.
 * Fonctionne en tandem avec Exo.2.2.yacc pour compter les places totales.
 */

%{
#include <stdio.h>
#include "Exo.2.2.yacc.h"
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
