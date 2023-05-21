#include "beolvas.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "debugmalloc.h"

/*A beolvas f�ggv�ny a forr�s f�jlt ellenorzi, ha l�tezik, akkor megnyitja �s elt�rolja a szavakat k�t dimenzi�s dinamikus t�mbbe a dintomb_atmeretez f�ggv�ny seg�ts�g�vel, majd bez�rja a f�jlt.*/

void beolvas(adat_elem **szotar, unsigned long *szavak_szama, int *leghosszabb_szo_karakter_szama)
{
    FILE *s = fopen("magyar_ascii.txt", "r");
    if (s == NULL)
    {
        printf("Nem sikerult megnyitni a fajlt.\n");
        exit(-1);
    }
    long sorok_szama = 0;
    char character;
    while (!feof(s))
    {
        fscanf(s, "%c", &character);
        if (character == '\n')
        {
            sorok_szama++;
        }
    }
    if (sorok_szama > 0)
    {
        sorok_szama--;
    }
    fclose(s);
    *szavak_szama = sorok_szama;
    debugmalloc_max_block_size(sorok_szama * sizeof(adat_elem));
    *szotar = (adat_elem*) malloc(sorok_szama * sizeof(adat_elem));
    if (*szotar == NULL)
    {
        printf("Nem sikerult memoriat foglalni.");
        exit(-1);
    }
    FILE *sz = fopen("magyar_ascii.txt", "r");
    if (sz == NULL)
    {
        printf("Nem sikerult megnyitni a fajlt.\n");
        exit(-1);
    }
    long i = 0;
    int vege = 0;
    while (vege != 1)
    {
        long j = 1;
        char *szo = (char*) malloc((1) * sizeof(char));
        if (szo == NULL)
        {
            printf("Nem sikerult memoriat foglalni.");
            exit(-1);
        }
        if (fscanf(sz, "%c", &character) == EOF)
        {
            vege = 1;
            free(szo);
            break;
        }
        while (character != '\n')
        {
            szo[j - 1] = character;
            j++;
            szo = dintomb_atmeretez(szo, j);
            fscanf(sz, "%c", &character);
            if (character == EOF)
            {
                vege = 1;
                break;
            }
        }
        (*szotar)[i].szo = szo;
        (*szotar)[i].hossza = strlen((*szotar)[i].szo);
        if (*leghosszabb_szo_karakter_szama < (*szotar)[i].hossza)
        {
            *leghosszabb_szo_karakter_szama = (*szotar)[i].hossza;
        }
        i++;
    }
    fclose(sz);
}
