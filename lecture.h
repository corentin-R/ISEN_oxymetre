//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992



//-----lecture-------------------------------------------------------------------------------------------------------------------------

float *Lecture(FILE* fichier,int mode);

float *conversion(char *donnee);

float *centrerAC(float *donnee);

//char *gestionErreurs(char *data_c, char *data_precedent);

char *recupFichier(FILE* fichier);

char *recupUSB();

int choixMode();
