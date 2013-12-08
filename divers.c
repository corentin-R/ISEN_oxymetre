//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour g�rer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992

#include "divers.h"
//#include "calcul.h"


//-----------------------------------------------------------------------------------------------------------------------------


struct maillon *insertMaillon(float nouvelleValeur,struct maillon *pliste,int taille_max)
{
    // On cr�e un nouvel �l�ment
    struct maillon *nouveauMaillon = malloc(sizeof(struct maillon));
    int taille_liste=1;//au d�but la taille de la liste est de 1

    // On assigne la valeur au nouvel �l�ment
    nouveauMaillon->val = nouvelleValeur;

    // On ajoute en fin, donc aucun �l�ment ne va suivre
    nouveauMaillon->psuivant = NULL;

    if(pliste == NULL)
    {
        //Si la liste est vide� il suffit de renvoyer l'�l�ment cr��
        return  nouveauMaillon;
    }
    else
    {
        // Sinon, on parcourt la liste � l'aide d'un pointeur temporaire et on
        //indique que le dernier �l�ment de la liste est reli� au nouvel �l�ment
        struct maillon* temp=pliste;
        while(temp->psuivant != NULL)//tant qu'on est pas arriv� � la fin de la liste
        {
            temp = temp->psuivant;//on passe au maillon suivant
            taille_liste++;//on incr�mente le compteur de position dans la liste
        }
        temp->psuivant = nouveauMaillon;//le nouveu maillon se place � la fin de la liste

        if(taille_liste<taille_max)//si la taille de la liste est inf�rieure � la taille max alors:
        {
            return pliste;//on retourne le pointeur sur le premier param�tre de la lste tel quel
        }

        else if(taille_liste>=taille_max)//sinon si la taille de la liste avec le nouveau maillon est sup�rieur � la taille max alors:
        {
            return pliste->psuivant;//le maillon de d�but de liste devient le 1 �l�ment--> on coupe le 1er �l�ment de la liste
            free(pliste);
        }
    }
}

float lireVal(struct maillon *pliste, int numero)
{
    int n=0;//on d�clare la variable qui va nous permettre de nous d�placer dans la liste et on l'initialise � z�ro
    while(n != numero)//tant qu'on est pas arriv� au num�ro voulut
    {
        n++;//on ugment la variable de position
        if(pliste->psuivant == NULL)//si le pointeur suivant est null
        {
            return 0;//alors on retourne z�ro
        }
        else//sinon on passe au maillon suivant
        {
            pliste=pliste->psuivant;
        }
    }
    return pliste->val;//quand on est arriv� au maillon voulut on retourne la valeure cob=ntenue dans celui-ci
}

