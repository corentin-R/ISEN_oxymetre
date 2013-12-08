//chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
// chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992


//#include "filtreFIR.h"
#include "divers.h"

//--------------------------------------------------------------------------

float *FlitreFIR(struct maillon *adressACr_brut,struct maillon *adressACir_brut)
{
    float *tab=calloc(2,sizeof(float));//tab[0]-->ACr brut,  tab[1]-->ACir brut,

    int k;//déclaration de la variable qui va permettre de se déplacer dans la liste chainée contenant les 51 valeures précédentes des ac
    // déclaration du tableau contenant les 51 coefficient néccessaires au filtre fir
    float h[50] = {1.4774946e-019,1.6465231e-004,3.8503956e-004,7.0848037e-004,1.1840522e-003,
                   1.8598621e-003,2.7802151e-003,3.9828263e-003,5.4962252e-003,7.3374938e-003,
                   9.5104679e-003,1.2004510e-002,1.4793934e-002,1.7838135e-002,2.1082435e-002,
                   2.4459630e-002,2.7892178e-002,3.1294938e-002,3.4578348e-002,3.7651889e-002,
                   4.0427695e-002,4.2824111e-002,4.4769071e-002,4.6203098e-002,4.7081811e-002,
                   4.7377805e-002,4.7081811e-002,4.6203098e-002,4.4769071e-002,4.2824111e-002,
                   4.0427695e-002,3.7651889e-002,3.4578348e-002,3.1294938e-002,2.7892178e-002,
                   2.4459630e-002,2.1082435e-002,1.7838135e-002,1.4793934e-002,1.2004510e-002,
                   9.5104679e-003,7.3374938e-003,5.4962252e-003,3.9828263e-003,2.7802151e-003,
                   1.8598621e-003,1.1840522e-003,7.0848037e-004,3.8503956e-004,1.6465231e-004,
                   1.4774946e-019
                  };

    //on additionne une par une les 51 valeures de acr et acir avec leurs coefficient correspondant
    for(k=0; k<=50; k++)
    {
        tab[0]+=h[k]*lireVal(adressACr_brut,50-k);
        tab[1]+=h[k]*lireVal(adressACir_brut,50-k);
    }

    return tab;
}
