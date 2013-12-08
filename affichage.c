//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

#include "affichage.h"
#include "divers.h"


//----affichage--------------------------------------------------------------------------------------------------------------------

void affichage(int *valSortie)
{
    printf("-----> bpm=%d   spo2=%d %%\n",valSortie[0], valSortie[1]);//on affiche les valeurs de bpm et spo2 dans le terminal


    if((INT_PTR)GetFileAttributesA(".verrouData") > 0)//si le fichier verroudata existe
    {
        //on affiche dans le terminal la raison pour laquelle on ne peut écrire dans data.txt
        printf("imposible d'écrire dans data.txt car .verrouData existe\n");
    }
    else // si le fichier verrou data  n'existe pas
    {
        FILE* fichier = NULL;
        FILE* verrou = NULL;

        fichier = fopen("data.txt", "w+");//on ouvre data et on efface son contenu
        verrou = fopen(".verrouData", "r");//créer le fichier .verrouData

        if (fichier != NULL) // On peut lire et écrire dans le fichier
        {
            if(valSortie[1]>100 || valSortie[1]<0 )//si spo2 > 100 ou <0 alors on écrit - dans le ficjier data.txt
            {
                fprintf(fichier, "%c\n", '-');
            }
            else//sinon on affiche la vraie valeure de spo2
            {
                fprintf(fichier, "%d\n", valSortie[1]);
            }

            if(valSortie[0]>255 || valSortie[0]<30)//si bpm > 255 ou <0 alors on écrit - dans le ficjier data.txt
            {
                fprintf(fichier, "%c\n", '-');
            }
            else//sinon on affiche la vraie valeure de bpm
            {
                fprintf(fichier, "%d\n", valSortie[0]);
            }

            fclose(fichier);//on ferme le fichier data.txt
            fclose(verrou);
            // DeleteFile(".verrouData");
            remove(".verrouData");//on supprime le fichier verroudata pour que l'interface graphique puisse lire le fichier data.txt
        }
    }
}
