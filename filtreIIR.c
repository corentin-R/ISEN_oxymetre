//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

//#include "filtreIIR.h"
#include "divers.h"





float *FlitreIIR(float *ac_fir,float *ac_fir_prec, float *ac_fir_iir_prec)
{
    float *tab=calloc(2,sizeof(float));

    tab[0]=ac_fir[0]-ac_fir_prec[0]+ALPHA*ac_fir_iir_prec[0];//calcul pour ac-r
    tab[1]=ac_fir[1]-ac_fir_prec[1]+ALPHA*ac_fir_iir_prec[1];//calcul pour ac-ir

    return tab;
}
