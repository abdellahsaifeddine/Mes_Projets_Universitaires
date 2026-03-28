#include "save.h"


// Sauvegarde de la partie dans un fichier binaire
void sauvegarderPartieBinaire(TListePlayer p1, TListePlayer p2, int elixirPlayer1, int elixirPlayer2) {
    FILE *fichier = fopen("partiebin.clb", "wb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde binaire.\n");
        return;
    }

    // Écriture des données dans le fichier
    fwrite(&elixirPlayer1, sizeof(int), 1, fichier);
    fwrite(&elixirPlayer2, sizeof(int), 1, fichier);
    sauvegarderListePlayerBinaire(p1, fichier);
    sauvegarderListePlayerBinaire(p2, fichier);

    fclose(fichier);
}

// Chargement de la partie depuis un fichier binaire
void chargerPartieBinaire(TListePlayer *p1, TListePlayer *p2, int *elixirPlayer1, int *elixirPlayer2) {
    FILE *fichier = fopen("partiebin.clb", "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde binaire.\n");
        return;
    }

    // Lecture des données depuis le fichier
    fread(elixirPlayer1, sizeof(int), 1, fichier);
    fread(elixirPlayer2, sizeof(int), 1, fichier);
    *p1 = chargerListePlayerBinaire(fichier);
    *p2 = chargerListePlayerBinaire(fichier);

    fclose(fichier);
}

// Sauvegarde de la liste de joueurs dans un fichier binaire
void sauvegarderListePlayerBinaire(TListePlayer liste, FILE *fichier) {
    TListePlayer ptr = liste;
    while (ptr != NULL) {
        fwrite(&(ptr->pdata), sizeof(Tunite), 1, fichier);
        ptr = ptr->suiv;
    }
}

// Chargement de la liste de joueurs depuis un fichier binaire
TListePlayer chargerListePlayerBinaire(FILE *fichier) {
    TListePlayer liste = NULL;
    Tunite unite;
    while (fread(&unite, sizeof(Tunite), 1, fichier) == 1) {
        liste = ajoutEnFin(liste, unite);
    }
    return liste;
}

// Sauvegarde de la partie dans un fichier séquentiel
void sauvegarderPartieSequence(TListePlayer p1, TListePlayer p2, int elixirPlayer1, int elixirPlayer2) {
    FILE *fichier = fopen("partieseq.cls", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde séquentielle.\n");
        return;
    }

    // Écriture des données dans le fichier
    fprintf(fichier, "%d\n%d\n", elixirPlayer1, elixirPlayer2);
    sauvegarderListePlayerSequence(p1, fichier);
    sauvegarderListePlayerSequence(p2, fichier);

    fclose(fichier);
}

// Chargement de la partie depuis un fichier séquentiel
void chargerPartieSequence(TListePlayer *p1, TListePlayer *p2, int *elixirPlayer1, int *elixirPlayer2) {
    FILE *fichier = fopen("partieseq.cls", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde séquentielle.\n");
        return;
    }

    // Lecture des données depuis le fichier
    fscanf(fichier, "%d\n%d\n", elixirPlayer1, elixirPlayer2);
    *p1 = chargerListePlayerSequence(fichier);
    *p2 = chargerListePlayerSequence(fichier);

    fclose(fichier);
}

// Sauvegarde de la liste de joueurs dans un fichier séquentiel
void sauvegarderListePlayerSequence(TListePlayer liste, FILE *fichier) {
    TListePlayer ptr = liste;
    while (ptr != NULL) {
        fprintf(fichier, "%d %d %d %d\n", ptr->pdata->posX, ptr->pdata->posY, ptr->pdata->nom, ptr->pdata->pointsDeVie);
        ptr = ptr->suiv;
    }
}

// Chargement de la liste de joueurs depuis un fichier séquentiel
TListePlayer chargerListePlayerSequence(FILE *fichier) {
    TListePlayer liste = NULL;
    Tunite unite;
    while (fscanf(fichier, "%d %d %d %d\n", &unite.posX, &unite.posY, &unite.nom, &unite.pointsDeVie) == 4) {
        liste = ajoutEnFin(liste, unite);
    }
    return liste;
}
