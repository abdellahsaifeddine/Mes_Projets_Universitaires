#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;


typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;
    Tcible maposition;
    int pointsDeVie;
    float vitesseAttaque;
    int degats;
    int portee ;
    float vitessedeplacement;
    int posX, posY;
    int peutAttaquer;
    int coutEnElixir;
} Tunite;

typedef struct {
    int x;
    int y;
} couple;

float getATTS(Tunite* unite);
float getMS(Tunite* unite);


char unitecode(TuniteDuJeu data);

bool inRange(Tunite* unite, int X, int Y, int r);
void attack (Tunite* fighter, Tunite* ennemi);


long convertToNanoseconds(float attackSpeed);
void sleepNanoseconds(float attackSpeed);

int randm(int var);

