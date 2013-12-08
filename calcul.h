//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

//#ifndef "calcul.h"
//#define "calcul.h"
//----calcul-------------------------------------------------------------------------------

int *calcul(struct tab4 oxy,struct pointeurs *AC_R,struct pointeurs *AC_RIR);

int fmoyBPM (int bpmr,int bpmir);

int convertSPO2(float rsir);

int convertBPMRIR(int sCompteurRIR);

float calculRsIR (int ptpACr,int ptpACir, float dcr, float dcir);

int compteurRIR(struct tab4 oxy,struct pointeurs *AC_RIR, int choix);

float ptpACRIR(struct tab4 oxy,struct pointeurs *AC_RIR, int choix);


//#endif
