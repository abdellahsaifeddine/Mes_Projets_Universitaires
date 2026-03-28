#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clashloyal.h"


void sauvegarderPartieBinaire(TListePlayer p1, TListePlayer p2, int elixirPlayer1, int elixirPlayer2);
void chargerPartieBinaire(TListePlayer *p1, TListePlayer *p2, int *elixirPlayer1, int *elixirPlayer2);
void sauvegarderListePlayerBinaire(TListePlayer liste, FILE *fichier);
TListePlayer chargerListePlayerBinaire(FILE *fichier);
void sauvegarderPartieSequence(TListePlayer p1, TListePlayer p2, int elixirPlayer1, int elixirPlayer2);
void chargerPartieSequence(TListePlayer *p1, TListePlayer *p2, int *elixirPlayer1, int *elixirPlayer2);
void sauvegarderListePlayerSequence(TListePlayer liste, FILE *fichier);
TListePlayer chargerListePlayerSequence(FILE *fichier);
