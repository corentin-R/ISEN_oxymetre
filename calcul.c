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
#include "calcul.h"

//----calcul-----------------------------------------------------------------------------------------------------
int *calcul(struct tab4 oxy,struct pointeurs *AC_R,struct pointeurs *AC_IR)
//int *calcul (float *z,int *compteur, int *compteurPrecedent, int *passageZero,int *ena_compteur, float *zPrecedent, struct maillon *adressACr, struct maillon *adressACir )
{
    int *tab=calloc(2,sizeof(int));

    tab[0]=fmoyBPM(convertBPMRIR(compteurRIR(oxy,AC_R,0)),convertBPMRIR(compteurRIR(oxy,AC_IR,1)));

    tab[1]=convertSPO2(calculRsIR(ptpACRIR(oxy,AC_R,0),ptpACRIR(oxy,AC_IR,1),oxy.DCr, oxy.DCir));

    return tab;
}

int fmoyBPM (int bpmr,int bpmir)
{
    return ((bpmr+bpmir)*0.5);
}

int convertSPO2(float rsir)
{
    if(rsir<=1)
    {
        return 110-(25*rsir);
    }
    else if( rsir > 1)
    {
        return 121-(35.714*rsir);
    }
    else
    {
        return 0;
    }
}

int convertBPMRIR(int sCompteurRIR)
{
    return 60/(2e-3*sCompteurRIR)+1;
}

float calculRsIR(int ptpACr,int ptpACir, float dcr, float dcir)
{
    float r=((float)ptpACr/(float)dcr);
    float ir=((float)ptpACir/(float)dcir);

    return ((float)r/(float)ir);
}

int compteurRIR(struct tab4 oxy,struct pointeurs *AC_RIR, int choix)
{
    int sortie=AC_RIR->compteurPrecedent;

    float actuel, precedent;
    if(choix==0)
    {
        actuel=oxy.ACr_actuel;
        precedent=oxy.ACr_prec;
    }
    else if(choix==1)
    {
        actuel=oxy.ACir_actuel;
        precedent=oxy.ACir_prec;
    }

    if(AC_RIR->ena_compteur==1)
    {
        AC_RIR->compteur=AC_RIR->compteur+1;
    }
//   printf("prc->%f \t act->%f\n ",oxy.ACr_prec ,oxy.ACr_actuel);

    if((precedent >0 && actuel<=0) /*|| (oxy.ACr_prec  <0 && oxy.ACr_prec>=0)*/)
    {
        AC_RIR->passageZero=AC_RIR->passageZero+1;
        AC_RIR->ena_compteur=1;
        printf("---------------------------------------> passageZero=%d\n",AC_RIR->passageZero);
        if(AC_RIR->passageZero==2)
        {
            AC_RIR->compteurPrecedent=AC_RIR->compteur;
            sortie=AC_RIR->compteur;
            AC_RIR->compteur=0;
            AC_RIR->passageZero=1;

            AC_RIR->maximum_prec=AC_RIR->maximum;
            //  printf("max==%f\n",AC_RIR->maximum_prec);
            AC_RIR->minimum_prec=AC_RIR->minimum;
            AC_RIR->maximum=0;
            AC_RIR->minimum=0;
        }
    }
    return sortie;
}

float ptpACRIR(struct tab4 oxy,struct pointeurs *AC_RIR,int choix)
{

    float actuel;
    if(choix==0)
    {
        actuel=oxy.ACr_actuel;
    }
    else if(choix==1)
    {
        actuel=oxy.ACir_actuel;
    }

    if(actuel >= AC_RIR->maximum )
    {
        AC_RIR->maximum = actuel;
    }
    else if(actuel <= AC_RIR->minimum)
    {
        AC_RIR->minimum = actuel;
    }

    return AC_RIR->maximum_prec-AC_RIR->minimum_prec;
}




