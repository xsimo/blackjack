#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void affiche(carte c)
{
  char* symbol = malloc((sizeof(char))*12);
  int k;
  k=(c.sorte)%4;
  if(k==0)
    symbol="PIQUE";
  if(k==1)
    symbol="COEUR";
  if(k==2)
    symbol="CARREAU";
  if(k==3)
    symbol="TREFLE";
  k = c.hauteur;
  if(k == 0)
    printf("As de %s  \n",symbol);
  if((k>0)&&(k<10))
    {printf("%d de %s  \n", k+1 , symbol);}
  if(k==10)
    printf("Valet de %s  \n",symbol);
  if(k==11)
    printf("Dame de %s  \n",symbol);
  if(k==12)
    printf("Roi de %s  \n",symbol);
  //  free(symbol);
}
