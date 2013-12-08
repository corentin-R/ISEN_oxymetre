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
#include "lecture.h"




float *Lecture(FILE* fichier, int mode)
{
    char* tab=NULL;
    int *nombres=NULL;
    int i;

    if(mode==1)
    {
        //  printf("test\n");
        //  printf("prec=%s\n",data_precedent);
        //  printf("tab=%s\n",*tab);

        tab=recupFichier(fichier);

        /*    for(i=0;i<20;i++)
            {
                *data_precedent=*tab;
            }
        */
        nombres=centrerAC(conversion(tab));

        return nombres;

        //free(data_precedent);
        free(tab);
        free(nombres);

    }
    else if(mode==2)
    {
        return centrerAC(conversion(recupUSB()));
    }
}

// convertie la chaine de 21 caractères en tableau de 4 entiers coorespondant
float *conversion(char *donnee)
{
    // on alloue la mémoire du tableau qui va contenir acr, dcr, acir, dcir (4 entiers) et on remplit par des zéros
    float *tab= calloc(4,sizeof(float));

    int i;// variable temporaire pour se placer dans la chine de caractère d'entée
    int j=0;// variable temporaire pour se placer dans le tableau d'entier de sortie
    int k=0;// variable pour stocker la puissance de 10 correspondant à la place du caractère correspondant

    for(i=0; i<=21; i++)//on parcourt la chaine de caractère
    {
        if(donnee[i]==',')//si le cractère lu est une virgule
        {
            j++;//on change de case dans le tableau de sortie
            k=0;
        }
        else if (donnee[i]>47 && donnee[i]<58)// si le caractère lu est un nombre
        {
            //on convertit le caractère ascii en entier et on le multiplit pr la puissance de 10 correspondante
            tab[j]+=(donnee[i]-48)*pow(10,3-k);

            k++;//on fait descendre la puissance de 10 (3-k => k augmente => la puissance de 10 diminue)
        }
    }

    return tab;// on retourne le tableau de 4 flottants
}

// centre le signal sinu
float  *centrerAC(float *donnee)
{
    // on soustrait dc à ac car dc pour le centrer en zéro est l moyenne de ac
    //normalement on recoupe dc à ac mais pour d'obscures raison on prend 2048
    donnee[0]=donnee[0]-2048;//donnee[1]->pour acr
    donnee[2]=donnee[2]-2048;//donnee[3]->pour acir
    // printf("int=%f,%f,%f,%f\n",donnee[0],donnee[1],donnee[2],donnee[3]);
    return donnee;
}

char *recupFichier(FILE* fichier)
{
    //FILE* fichier = NULL;
    char* chaineSortie= malloc(TAILLE_CHAINE_CHAR *sizeof(char));
    int n=0;


    if (fichier != NULL) // On peut lire et écrire dans le fichier
    {
        // On lit maximum TAILLE_CHAINE_CHR caractères du fichier, on stocke le tout dans "chaineSortie"
        do
        {
            chaineSortie[n]=fgetc(fichier);
            //printf("%c",chaineSortie[n]);
            if(chaineSortie[n]==EOF)
            {
                printf("fin fichier\n");
                return "9999,9999,9999,9999\n";
            }
            n++;

        }
        while((int)chaineSortie[n-1]!=10);
        // printf("\n");
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier record1.dat\n");
        return "error";
    }

    return chaineSortie;//on retourne la chaine de 21 caractères en sortie
}

int choixMode()
{
    printf("\n \t choix du mode\n");//titre de la fenêtre
    printf("\t 1----> lecture des donnees dans fichier data\n");//lit dans les fichiers qui doivent êtres placés dans le même répertoire que l'ecxecutable
    printf("\t 2----> lecture du flux de données USB\n");//lit le blux usb en live (4 donées toutes les 2 ms normalement)

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
    else// si la touche est autre que 1 ou 2
    {
        system("cls");// on efface le treminal
        return choixMode();//on réapplelle la fonction choixmode jusqu'à ce que la touche appuyée soit 1 ou 2
    }
}

char *recupUSB()
{
    char* chaineSortie= malloc(TAILLE_CHAINE_CHAR *sizeof(char));
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;

    char RxBuffer[20];
    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK)
    {
        // FT_Open failed
     //   return error_status_t;
    }
    FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (RxBytes > 0)
    {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived);

        if (ftStatus == FT_OK)
        {
          chaineSortie=RxBytes;
        }
        else
        {
            // FT_Read Failed
        }
    }
    FT_Close(ftHandle);

    return chaineSortie;

}

/*
char *gestionErreurs(char *data_c, char *data_precedent)
{
    int i=0;
   // Sleep(3000);
  //    printf("%s",data_c);
     printf("dataprec=%s\n",*data_precedent);
    for(i=0; i<=20; i++)
    {
        // printf("%d-->",i);
        //  printf("%c\n",data_c[i]);
        if(i==4 || i==9 || i==14)
        {

            if(data_c[i] != ',')//si ce n'est pas une virgule
            {
                printf("test 1\n");
                return data_precedent;
            }
        }
        else if(i!=4 && i!=9 && i!=14 && i!=19 && i != 20)
        {
            //  printf("i=%d-->",i);
            // printf("%d,",(int)data_c[i]);
            if((int)data_c[i]<47 || (int)data_c[i]>58)// si data_c[i] n'est pas un nombre
            {
                printf("test 2\n");
                return data_precedent;
            }
        }
        //printf("test 3\n");
        /* else if( i==20)
         {
             if(data_c[i] != 10)//lf
             {
                 return data_precedent;
             }
         }
         else if( i==21)
         {

             if(data_c[i] != 13)//cr
             {
                 return data_precedent;
             }

         }

    }
    // printf("test_f\n");

    return data_c;

}

*/
