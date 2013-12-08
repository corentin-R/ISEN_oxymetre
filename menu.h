//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992


int menu();

void programmeEntier();

void testLecture();

void testCentrage();

void testFiltreFIR();

void testFiltreIIR();

void testCalcul();

void testAffichage();

void topMenu(int menu);
