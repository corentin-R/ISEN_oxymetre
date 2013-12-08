//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992


typedef struct maillon
{
    float val;
    struct maillon *psuivant;
};

typedef struct tab4
{
    float DCr;
    float DCir;
    float ACr_actuel;
    float ACir_actuel;
    float ACr_prec;
    float ACir_prec;
};

typedef struct pointeurs
{
    int compteurPrecedent;
    int compteur;
    int passageZero;
    int ena_compteur;

    float maximum;
    float minimum;
    float maximum_prec;
    float minimum_prec;
};

//-----divers---------------------------------------------------------------------------------

struct maillon *insertMaillon(float nouvelleValeur,struct maillon *pliste,int taille_max);

float lireVal(struct maillon *pliste, int numero);
