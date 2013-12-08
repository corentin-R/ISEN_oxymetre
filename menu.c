//Chargement des librairies standard
#include <stdio.h>
#include <stdlib.h>
//Chargement de la librairie mathsh pour la puissance de 10
#include <math.h>
//Chargement de la librairie windows.h pour gérer les fichier en partie et la fonction sleep
#include <windows.h>

# define TAILLE_CHAINE_CHAR 21
# define ALPHA 0.992


#include "menu.h"
#include "divers.h"
#include "lecture.h"
#include "affichage.h"
#include "calcul.h"
#include "filtreFIR.h"
#include "filtreIIR.h"

#include "ftd2xx.h"


int menu()
{
    printf("\n PROJET INFORMATIQUE CSI3 2013 - OXYMETRE DE POULS - PERROT/RAOULT\n\n");//titre de la fenêtre
    printf("\t Choix de la fonction a tester:\n");
    printf("\t 1--> Programme entier\n");
    printf("\t 2--> Fonction Lecture et Centrage\n");
    printf("\t 3--> Filtre FIR\n");
    printf("\t 4--> Filtre IIR\n");
    printf("\t 5--> Fonction Calcul\n");
    printf("\t 6--> Fonction Affichage\n\n");
    printf("\t 0--> QUITTER\n");

    char touche;//on déclare la variable qui va stocker le code de la touche qui va être appuyée
    touche=getch();

    if(touche=='1')//si la touche appuyée est 1 alors:
    {
        system("cls");//on efface le terminal
        return 1;//on retourne 1
    }
    else if(touche=='2')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 2;//on return 2
    }
    else if(touche=='3')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 3;//on return 3
    }
    else if(touche=='4')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 4;//on return 4
    }
    else if(touche=='5')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 5;//on return 5
    }
    else if(touche=='6')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 6;//on return 6
    }
    else if(touche=='0')//si la touche appuyée est 2 alors:
    {
        system("cls");//on efface le terminal
        return 0;//on return 0
    }
    else// si la touche est autre que 1 ou 2
    {
        system("cls");// on efface le treminal
        return menu();//on réapplelle la fonction choixmode jusqu'à ce que la touche appuyée soit 1 ou 2
    }
}

//------------main----------------------------------------------------------------------------------------------------------
void programmeEntier()
{
    int n=0;
    int fin=0;
    int mode=choixMode();
    struct maillon *adressACr_brut= NULL;
    struct maillon *adressACir_brut= NULL;

    float *ac_fir=calloc(2,sizeof(float));
    float *ac_fir_iir=calloc(2,sizeof(float));
    float *ac_fir_prec=calloc(2,sizeof(float));
    float *ac_fir_iir_prec=calloc(2,sizeof(float));

    struct tab4 oxy;

    struct pointeurs *AC_R=malloc(4*sizeof(int)+4*sizeof(float));
    struct pointeurs *AC_IR=malloc(4*sizeof(int)+4*sizeof(float));

    AC_R->compteurPrecedent;
    AC_R->compteur=0;
    AC_R->passageZero=0;
    AC_R->ena_compteur=0;

    AC_R->maximum=0;
    AC_R->minimum=0;
    AC_R->maximum_prec=0;
    AC_R->minimum_prec=0;

    AC_IR->compteurPrecedent=0;
    AC_IR->compteur=0;
    AC_IR->passageZero=0;
    AC_IR->ena_compteur=0;

    AC_IR->maximum=0;
    AC_IR->minimum=0;
    AC_IR->maximum_prec=0;
    AC_IR->minimum_prec=0;

    float *dataBrut;

    //char *data_precedent=calloc(21, sizeof(char));

    FILE* fichier;

    FILE* fichier_c = fopen("test_c.dat", "w+");
    FILE* fichier_f1 = fopen("test_f1.dat", "w+");
    FILE* fichier_f2 = fopen("test_f2.dat", "w+");


    if(mode==1)
    {
        fichier = fopen("record1.dat", "r");
    }
    else if(mode ==2)
    {
        flux=FT_Open;
    }
    remove(".verrouData");//on supprime le fichier verroudata pour que l'interface graphique puisse lire le fichier data.txt

    while(fin != 1)
    {
        printf("%d\n",n);
        //
        dataBrut = Lecture(fichier , mode);
       fprintf (fichier_c,"%d,%d,%d,%d\n\n",(int)dataBrut[0],(int)dataBrut[1],(int)dataBrut[2],(int)dataBrut[3]);


        if ((int)dataBrut[1]==9999)
        {
            fin =1;
        }
        // printf(" %f,%f,%f,%f\n", dataBrut[0],dataBrut[1],dataBrut[2],dataBrut[3]);

        adressACr_brut=insertMaillon(dataBrut[0],adressACr_brut,51);// a corriger 51 et pas 50 !!!!
        adressACir_brut=insertMaillon(dataBrut[2],adressACir_brut,51);

        ac_fir = FlitreFIR(adressACr_brut,adressACir_brut);
        fprintf (fichier_f1,"%d,%d,%d,%d\n\n",(int)ac_fir[0],(int)dataBrut[1],(int)ac_fir[1],(int)dataBrut[3]);
        ac_fir_iir = FlitreIIR(ac_fir,ac_fir_prec, ac_fir_iir_prec);
        fprintf (fichier_f2,"%d,%d,%d,%d\n\n",(int) ac_fir_iir [0],(int)dataBrut[1],(int) ac_fir_iir[1],(int)dataBrut[3]);

        ac_fir_iir_prec = ac_fir_iir ;
        ac_fir_prec = ac_fir;

        // printf(" %f\t %f\n",ac_fir_iir[0],ac_fir_iir[1]);

        oxy.DCr=dataBrut[1];
        oxy.DCir=dataBrut[3];
        oxy.ACir_actuel=ac_fir_iir[1];
        oxy.ACr_actuel=ac_fir_iir[0];

        affichage(calcul(oxy,AC_R,AC_IR));

        oxy.ACr_prec=oxy.ACr_actuel;
        oxy.ACir_prec=oxy.ACir_actuel;

        // Sleep(2);

        n++;
    }

    printf(" Fini! \n Appuyer sur une touche pour revenir au menu\n");
    getch();
    system("cls");
    topMenu(menu());

    if(mode==1)
    {
        fclose(fichier);
    }

     fclose(fichier_c);
      fclose(fichier_f1);
       fclose(fichier_f2);

    //libération de la mémoire des pointeurs
    free(adressACir_brut);
    free(adressACr_brut);
    free(ac_fir);
    free(ac_fir_iir);
    free(ac_fir_prec);
    free(ac_fir_iir_prec);
    free(AC_R);
    free(AC_IR);

}

/*
void testLecture()
{
    FILE* fichier = fopen("record_test_lecture.dat", "r");
    FILE* fichier_resultat = fopen("record_test_lecture_resultat.dat", "w+");
    if( fichier == NULL)
    {
        printf("impossible d'ouvrire le fichier record_test_lecture.dat car il n'existe pas\n");
    }
    else
    {
        char *tab=NULL;
        float *tab_num=NULL;
        int fin=0;
        char * data_prec=calloc(21,sizeof(char));
        while(fin!=1)
        {
            tab=gestionErreurs(recupFichier(fichier),data_prec);
            tab_num = conversion(tab);
            if ((int)tab[1]==9999)
            {
                fin =1;
            }
            else
            {
                printf("resutat=%d,%d,%d,%d\n",(int)tab_num[0],(int)tab_num[1],(int)tab_num[2],(int)tab_num[3]);
                fprintf (fichier_resultat,"%d,%d,%d,%d\n",(int)tab[0],(int)tab[1],(int)tab[2],(int)tab[3]);
            }
            data_prec=tab;
        }

        free(tab);
        free(tab_num);
        free(data_prec);

    }
    printf("appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    fclose(fichier_resultat);
    system("cls");

    topMenu(menu());
}
*/
void testCentrage()
{
    FILE* fichier = fopen("record_test_centrage.dat", "r");
    FILE* fichier_resultat = fopen("record_test_centrage_resultat.dat", "w+");

    if( fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier record_test_centrage.dat car il n'existe pas\n");
    }
    else
    {
        float *tab=NULL;
        int fin=0;
       // char *data_precedent=calloc(21, sizeof(char));

        while(fin != 1)
        {
            Sleep(2);
            tab = Lecture(fichier,1);
            if ((int)tab[1]==9999)
            {
                fin =1;
            }
            else
            {
                printf("resultat=%d,%d,%d,%d\n",(int)tab[0],(int)tab[1],(int)tab[2],(int)tab[3]);
                fprintf (fichier_resultat,"%d,%d,%d,%d\n",(int)tab[0],(int)tab[1],(int)tab[2],(int)tab[3]);
            }
        }
    }
    printf("Appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    fclose(fichier_resultat);
    system("cls");

    topMenu(menu());
}

void testFiltreFIR()
{
    FILE* fichier = fopen("record_test_filreFIR.dat", "r");
    FILE* fichier_resultat = fopen("record_test_filreFIR_resultat.dat", "w+");

    if( fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier record_test_filtreFIR.dat car il n'existe pas\n");
    }
    else
    {
        float *tab=NULL;
        struct maillon *pliste=NULL;
        int nouvelleValeur;
        int n=0;

        while(fscanf(fichier, "%d", &nouvelleValeur) != EOF)
        {
            Sleep(2);
            printf("valeur lue = %d\n",nouvelleValeur);
            pliste = insertMaillon(nouvelleValeur,pliste,51);
            //bon normalement le filtre prend la liste chainée de ac-r et ac-ir mais là comme c'est un test je prend 2 fois la même
            tab=FlitreFIR(pliste,pliste);

            //pareil ici j'affiche que une valeure de sortie de mon filtre parce que l'autre c'est la même vu qu'on a les 2 mêmes listes chainées en entéres du FIR
            printf("resultat = %d\n",(int)tab[0]);
            fprintf (fichier_resultat,"%d\n\n",(int)tab[0]);
        }
    }
    printf("Appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    fclose(fichier_resultat);
    system("cls");

    topMenu(menu());
}

void testFiltreIIR()
{
    FILE* fichier = fopen("record_test_filreIIR.dat", "r");
    FILE* fichier_resultat = fopen("record_test_filreIIR_resultat.dat", "w+");

    if( fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier record_test_filtreIIR.dat car il n'existe pas\n");
    }
    else
    {

        float *tab=calloc(2,sizeof(float));
        struct maillon *pliste=NULL;
        float *val_fir=calloc(2,sizeof(float));
        float *val_fir_prec=calloc(2,sizeof(float));
        float *val_iir=calloc(2,sizeof(float));
        float *val_iir_prec=calloc(2,sizeof(float));
        int n=0;

        while(fscanf(fichier, "%f", &val_fir[0]) != EOF)
        {
            Sleep(2);
            printf("Valeur lue = %d\n",(int)val_fir[0]);

            //bon normalement le filtre prend la liste chainée de ac-r et ac-ir mais là comme c'est un test je prend 2 fois la même
            tab=FlitreIIR(val_fir,val_fir_prec,val_iir_prec);

            //pareil ici j'affiche que une valeure de sortie de mon filtre parce que l'autre c'est la même vu qu'on a les 2 mêmes listes chainées en entéres du FIR
            printf("Resultat = %f\n\n",tab[0]);
            fprintf (fichier_resultat,"%d\n\n",(int)tab[0]);

            val_fir_prec[0]=val_fir[0];
            val_iir_prec[0]=tab[0];
        }
    }
    printf("Appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    fclose(fichier_resultat);
    system("cls");

    topMenu(menu());
}

void testCalcul()
{

    FILE* fichier = fopen("record_test_calcul.dat", "r");
    FILE* fichier_resultat = fopen("record_test_calcul_resultat.dat", "w+");

    if( fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier record_test_calcul.dat car il n'existe pas\n");
    }
    else
    {
        int *tab=NULL;

        struct tab4 oxy;
        struct pointeurs *AC_R=malloc(4*sizeof(int)+4*sizeof(float));
        struct pointeurs *AC_IR=malloc(4*sizeof(int)+4*sizeof(float));

        AC_R->compteurPrecedent;
        AC_R->compteur=0;
        AC_R->passageZero=0;
        AC_R->ena_compteur=0;

        AC_R->maximum=0;
        AC_R->minimum=0;
        AC_R->maximum_prec=0;
        AC_R->minimum_prec=0;

        AC_IR->compteurPrecedent=0;
        AC_IR->compteur=0;
        AC_IR->passageZero=0;
        AC_IR->ena_compteur=0;

        AC_IR->maximum=0;
        AC_IR->minimum=0;
        AC_IR->maximum_prec=0;
        AC_IR->minimum_prec=0;

        while(fscanf(fichier, "%f,%f,%f,%f", &oxy.ACr_actuel, &oxy.DCr, &oxy.ACir_actuel, &oxy.DCir) != EOF)
        {
            Sleep(2);
            printf("Valeurs lues=%f,%f,%f,%f\n", oxy.ACr_actuel, oxy.DCr, oxy.ACir_actuel, oxy.DCir);

            tab=calcul(oxy,AC_R,AC_IR);

            oxy.ACr_prec=oxy.ACr_actuel;
            oxy.ACir_prec=oxy.ACir_actuel;

            printf("spo2=%d, bpm=%d\n",tab[0],tab[1]);
            fprintf(fichier_resultat,"spo2=%d, bpm=%d\n\n",tab[0],tab[1]);
        }
    }
    printf("Appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    fclose(fichier_resultat);
    system("cls");

    topMenu(menu());
}

void testAffichage()
{
    FILE* fichier = fopen("record_test_affichage.dat", "r");

    if( fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier record_test_affichage.dat car il n'existe pas\n");
    }
    else
    {
        int *valSortie=calloc(2,sizeof(int));
        int n=0;

        while(fscanf(fichier, "%d,%d", &valSortie[0], &valSortie[1]) != EOF)
        {
            Sleep(100);
            printf("Valeurs lues= %d,%d\t",valSortie[0],valSortie[1]);

            affichage(valSortie);
            n++;
        }
    }
    printf("Appuyer sur une touche pour revenir au menu\n");
    getch();

    fclose(fichier);
    system("cls");

    topMenu(menu());
}

/*void quitter()
{

    printf("voulez-vous quitter? [o/n]\n");
    char touche1;//on déclare la variable qui va stocker le code de la touche qui va être appuyée
    touche1=getch();

    if(touche1=='o')//si la touche appuyée est 1 alors:
    {
        system("cls");//on efface le terminal
    }
    else if(touche1=='n')//si la touche appuyée est 1 alors:
    {
        system("cls");//on efface le terminal
        menu();
    }
    else
    {
        system("cls");//on efface le terminal
        quitter();
    }
}
*/

void topMenu(int menu)
{
    switch(menu)
    {
    case 1:
        programmeEntier();
        break;

    case 2:
        testCentrage();
        break;

    case 3:
        testFiltreFIR();
        break;

    case 4:
        testFiltreIIR();
        break;

    case 5:
        testCalcul();
        break;

    case 6:
        testAffichage();
        break;

    case 0:
        break;

    default:
        programmeEntier();
        break;
    }
}
