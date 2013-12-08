//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

#include "ftd2xx.h"

//------fir-------------------------------------------------------------------------------
float *FlitreFIR(struct maillon *adressACr_brut,struct maillon *adressACir_brut);
