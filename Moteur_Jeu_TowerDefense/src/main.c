/* =============================================================================
 * Projet : Moteur de Jeu Clash Loyal
 * Auteur : SAIFEDDINE Abdellah
 * Universite de Poitiers - L2 Informatique - 2024-2025
 * =============================================================================
 *
 * Point d'entree principal du jeu. J'initialise ici la fenetre SDL2, charge
 * tous les sprites BMP, cree les deux joueurs avec leurs unites de depart,
 * puis lance la boucle de jeu principale.
 *
 * La boucle gere chaque round : attaques, deplacements, achat d'unites,
 * ainsi que les sauvegardes/chargements en binaire et sequentiel via
 * les touches clavier S/D (sauvegarde) et C/V (chargement).
 * ============================================================================= */

#include "SDL.h"
#include "maSDL.h"      /* Fonctions d'affichage SDL adaptees au jeu */
#include "clashloyal.h"
#include "tester.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    /* --- Initialisation SDL et creation de la fenetre --- */
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    /*
     * La fenetre est dimensionnee dynamiquement selon LARGEURJEU et HAUTEURJEU
     * definis dans clashloyal.h (11 x 19 cases, chaque case = 40px).
     * Le titre rappelle les raccourcis clavier disponibles.
     */
    pWindow = SDL_CreateWindow(
        "ClashLoyal - ECHAP: quitter | S/D: sauvegarder | C/V: charger",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU * 40,
        HAUTEURJEU * 40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);

    /* --- Chargement des sprites BMP ---
     * Chaque sprite est indexe par son enum TuniteDuJeu dans TabSprite.
     * Les sprites de terrain (Eau, Herbe, Pont, Terre) ne font pas partie
     * de l'enum mais sont utilises pour afficher les cases vides du plateau.
     */
    SDL_Surface* pSpriteTour       = SDL_LoadBMP("./data/Tour.bmp");       /* indice 0 */
    SDL_Surface* pSpriteTourRoi    = SDL_LoadBMP("./data/TourRoi.bmp");    /* indice 1 */
    SDL_Surface* pSpriteArcher     = SDL_LoadBMP("./data/Archer.bmp");     /* indice 2 */
    SDL_Surface* pSpriteChevalier  = SDL_LoadBMP("./data/Chevalier.bmp");  /* indice 3 */
    SDL_Surface* pSpriteDragon     = SDL_LoadBMP("./data/Dragon.bmp");     /* indice 4 */
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); /* indice 5 */
    SDL_Surface* pSpriteEau        = SDL_LoadBMP("./data/Eau.bmp");        /* terrain  */
    SDL_Surface* pSpriteHerbe      = SDL_LoadBMP("./data/Herbe.bmp");      /* terrain  */
    SDL_Surface* pSpritePont       = SDL_LoadBMP("./data/Pont.bmp");       /* terrain  */
    SDL_Surface* pSpriteTerre      = SDL_LoadBMP("./data/Terre.bmp");      /* terrain  */

    /*
     * Tableau unifie des sprites : les 6 premieres entrees correspondent
     * aux unites (via leur enum), les 4 suivantes aux cases de terrain.
     * Ce tableau est passe a prepareAllSpriteDuJeu() pour le rendu complet.
     */
    SDL_Surface* TabSprite[10] = {
        pSpriteTour, pSpriteTourRoi, pSpriteArcher,
        pSpriteChevalier, pSpriteDragon, pSpriteGargouille,
        pSpriteEau, pSpriteHerbe, pSpritePont, pSpriteTerre
    };

    if (pSpriteTour) /* Si le premier sprite charge, on suppose que tous chargent */
    {
        /* --- Initialisation du plateau de jeu ---
         * Plateau 2D alloue dynamiquement (11 x 19) de pointeurs Tunite*.
         * Toutes les cases sont initialisees a NULL (aucune unite).
         */
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU, HAUTEURJEU);
        initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
        affichePlateauConsole(jeu, LARGEURJEU, HAUTEURJEU);
        prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
        maj_fenetre(pWindow);

        /* --- Creation des joueurs ---
         * Chaque joueur est une liste doublement chainee de Tunite*.
         * createplayer() positionne les tours et la tour roi de depart.
         * L'elixir de depart est fixe a 50 pour les deux joueurs.
         */
        TListePlayer p1, p2;
        TListePlayer apporte;
        initListe(&apporte);
        initListe(&p1);
        initListe(&p2);
        p1 = createplayer(p1, 1);
        p2 = createplayer(p2, 2);
        int elixirPlayer1 = 50, elixirPlayer2 = 50;
        bool check = false;

        srand(time(NULL)); /* Graine aleatoire pour l'achat d'unites */

        /* --- Tests initiaux (debug) ---
         * Ces appels verifient que les listes de joueurs sont bien formees
         * et que les operations de base (selection, tri) fonctionnent.
         */
        affichePtrPlayer(p1, "joueur 1 :");
        affichePtrPlayer(p2, "joueur 2 :");

        Tunite* ennemi = getPtrSelectData(p1, archer);
        affichePtrData(ennemi);
        printf("\n");

        apporte = apportePlayer(p2, ennemi);
        affichePtrPlayer(apporte, "apporte de ennemi");

        tri_selection_liste(&apporte);
        affichePtrPlayer(apporte, "apporte trie");

        printf("points de vie avant : %d\n", ennemi->pointsDeVie);
        printf("points de vie apres : %d\n", ennemi->pointsDeVie);

        Tunite* newunit = AcheteUnite(&elixirPlayer2, 2);
        affichePtrData(*newunit);

        /* =====================================================================
         * BOUCLE PRINCIPALE DU JEU
         *
         * Chaque iteration = 1 round. Ordre des operations :
         *   1. Positionnement des unites sur le plateau
         *   2. Tri par vitesse d'attaque (quicksort)
         *   3. Phase d'attaque : p1 attaque p2, puis p2 attaque p1
         *   4. Tri par vitesse de deplacement
         *   5. Phase de deplacement
         *   6. Achat d'une nouvelle unite pour chaque joueur
         *   7. Incrementation de l'elixir
         *   8. Reinitialisation des flags d'attaque
         *   9. Rendu graphique SDL
         *  10. Lecture des touches clavier (sauvegarde/chargement/quitter)
         * ===================================================================== */
        printf("\t\t************ GAME BEGIN ************\n");

        while (check == false) /* Condition de fin : tourRoi d'un joueur detruite */
        {
            SDL_PumpEvents();
            printf("\t\t************ New ROUND ************\n");

            PositionnePlayerOnPlateau(p1, jeu);
            PositionnePlayerOnPlateau(p2, jeu);

            /* Tri par vitesse d'attaque avant la phase combat */
            p1 = listQuickSort(p1, getATTS);
            p2 = listQuickSort(p2, getATTS);

            printf("\t\t************ player1 ATTAQUE ************\n");
            p2 = fight(p1, p2, jeu, check);
            printf("\t\t************ player2 ATTAQUE ************\n");
            p1 = fight(p2, p1, jeu, check);

            affichePtrPlayer(p1, "\t\t*** fin attaque player1 ***");
            affichePtrPlayer(p2, "\t\t*** fin attaque player2 ***");

            /* Tri par vitesse de deplacement avant la phase mouvement */
            p1 = listQuickSort(p1, getMS);
            p2 = listQuickSort(p2, getMS);

            moove(p1, p2, jeu);

            affichePtrPlayer(p1, "\t\t*** fin moove player1 ***");
            affichePtrPlayer(p2, "\t\t*** fin moove player2 ***");

            /* Achat d'une unite aleatoire selon l'elixir disponible */
            Tunite* newunit1 = AcheteUnite(&elixirPlayer1, 1);
            AjouterUnite(&p1, newunit1);
            Tunite* newunit2 = AcheteUnite(&elixirPlayer2, 2);
            AjouterUnite(&p2, newunit2);

            elixirPlayer1 += 1;
            elixirPlayer2 += 1;
            printf("\nelixir player1 : %d, elixir player2 : %d\n", elixirPlayer1, elixirPlayer2);

            affichePtrPlayer(p1, "\t\t*** fin achat player1 ***");
            affichePtrPlayer(p2, "\t\t*** fin achat player2 ***");

            p1 = resetAttack(p1);
            p2 = resetAttack(p2);

            /* --- Rendu graphique --- */
            efface_fenetre(pWinSurf);
            prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
            maj_fenetre(pWindow);
            SDL_Delay(1500);

            /* --- Gestion des touches clavier ---
             * S : sauvegarde binaire      | C : chargement binaire
             * D : sauvegarde sequentielle | V : chargement sequentiel
             * ECHAP : quitter
             */
            const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);

            if (pKeyStates[SDL_SCANCODE_S]) {
                sauvegarderPartieBinaire(p1, p2, elixirPlayer1, elixirPlayer2);
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if (pKeyStates[SDL_SCANCODE_C]) {
                chargerPartieBinaire(&p1, &p2, &elixirPlayer1, &elixirPlayer2);
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if (pKeyStates[SDL_SCANCODE_D]) {
                sauvegarderPartieSequence(p1, p2, elixirPlayer1, elixirPlayer2);
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if (pKeyStates[SDL_SCANCODE_V]) {
                chargerPartieSequence(&p1, &p2, &elixirPlayer1, &elixirPlayer2);
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu, LARGEURJEU, HAUTEURJEU, TabSprite, pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if (pKeyStates[SDL_SCANCODE_ESCAPE]) {
                check = true;
            }
        }

        /* Liberation des surfaces SDL */
        SDL_FreeSurface(pSpriteTour);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stderr, "Echec de chargement des sprites : %s\n", SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
