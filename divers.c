//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

#include "divers.h"
//#include "calcul.h"


//-----------------------------------------------------------------------------------------------------------------------------


struct maillon *insertMaillon(float nouvelleValeur,struct maillon *pliste,int taille_max)
{
    // On crée un nouvel élément
    struct maillon *nouveauMaillon = malloc(sizeof(struct maillon));
    int taille_liste=1;//au début la taille de la liste est de 1

    // On assigne la valeur au nouvel élément
    nouveauMaillon->val = nouvelleValeur;

    // On ajoute en fin, donc aucun élément ne va suivre
    nouveauMaillon->psuivant = NULL;

    if(pliste == NULL)
    {
        //Si la liste est videé il suffit de renvoyer l'élément créé
        return  nouveauMaillon;
    }
    else
    {
        // Sinon, on parcourt la liste à l'aide d'un pointeur temporaire et on
        //indique que le dernier élément de la liste est relié au nouvel élément
        struct maillon* temp=pliste;
        while(temp->psuivant != NULL)//tant qu'on est pas arrivé à la fin de la liste
        {
            temp = temp->psuivant;//on passe au maillon suivant
            taille_liste++;//on incrémente le compteur de position dans la liste
        }
        temp->psuivant = nouveauMaillon;//le nouveu maillon se place à la fin de la liste

        if(taille_liste<taille_max)//si la taille de la liste est inférieure à la taille max alors:
        {
            return pliste;//on retourne le pointeur sur le premier paramètre de la lste tel quel
        }

        else if(taille_liste>=taille_max)//sinon si la taille de la liste avec le nouveau maillon est supérieur à la taille max alors:
        {
            return pliste->psuivant;//le maillon de début de liste devient le 1 élément--> on coupe le 1er élément de la liste
            free(pliste);
        }
    }
}

float lireVal(struct maillon *pliste, int numero)
{
    int n=0;//on déclare la variable qui va nous permettre de nous déplacer dans la liste et on l'initialise à zéro
    while(n != numero)//tant qu'on est pas arrivé au numéro voulut
    {
        n++;//on ugment la variable de position
        if(pliste->psuivant == NULL)//si le pointeur suivant est null
        {
            return 0;//alors on retourne zéro
        }
        else//sinon on passe au maillon suivant
        {
            pliste=pliste->psuivant;
        }
    }
    return pliste->val;//quand on est arrivé au maillon voulut on retourne la valeure cob=ntenue dans celui-ci
}

