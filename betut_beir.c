#include "betut_beir.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "econio.h"

#include "debugmalloc.h"

/*A nincs_benne függvény kiválogatja azokat a szavakat, amelyek egyszersem tartalmazzák a tippelt betut és átmásolja azokat egy dinamikus tömbbe, a többi szót felszabadítja. Az új tömb pointerével felülírja a régi tömb pointerét.*/

void nincs_benne(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu,
                 int legkevesebb_betut_tartalmazo_szavak_szama, int legkevesebb_betu, int kitalalando_szo_hossza, char *kitalalando_szo)
{
    econio_clrscr();
    printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\n");
    printf("Nem talalt.\nA szo: ");
    for (int i = 0; i < kitalalando_szo_hossza; i++)
    {
        printf("%c ", kitalalando_szo[i]);
    }
    printf("\n");
    printf("Nem talalt tippek: ");
    nem_talalt_tippek[*nem_talalt_tippek_szama] = betu;
    (*nem_talalt_tippek_szama)++;
    for (int i = 0; i < *nem_talalt_tippek_szama; i++)
    {
        printf("%c ", nem_talalt_tippek[i]);
    }
    printf("\n");
    adat_elem *ujszotar = (adat_elem*) malloc(legkevesebb_betut_tartalmazo_szavak_szama * sizeof(adat_elem));
    if (ujszotar == NULL)
    {
        printf("'Nem sikerult memoriat foglalni.\n");
        exit(-1);
    }
    int j = 0;
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
        {
            memcpy(ujszotar + j, *szotar + i, sizeof(adat_elem));
            j++;
        }
        else
        {
            free((*szotar)[i].szo);
        }
    }
    free(*szotar);
    *szotar = ujszotar;
    *megfelelo_szavak_szama = j;
}

/*Az egyszer_fordul_elo függvény kiválogatja azokat a szavakat, amelyek csak egyszer tartalmazzák a tippelt betut, majd megnézi, hogy melyik indexen a leggyakoribb és oda arra az indexre beírja.
Ezután azokat a szavakat, amelyekben a leggyakoribb indexen szereplo betu csak egyszer fordul elo és megfelelo helyen van átmásolja egy dinamikus tömbbe, a többi szót felszabadítja. Az új tömb pointerével felülírja a régi tömb pointerét.*/

void egyszer_fordul_elo(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu, int legkevesebb_betu, char *kitalalando_szo,
                        char *talalt_tippek, int *kitalalt_betuk_szama, int kitalalando_szo_hossza)
{
    int legtobb_helyen[61] = {0};
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        int j = 0;
        if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
        {
            while ((*szotar)[i].szo[j] != '\0')
            {
                if ((*szotar)[i].szo[j] == betu)
                {
                    legtobb_helyen[j]++;
                }
                j++;
            }
        }
    }
    int legtobb_helyen_index = 0, legtobb_szama = -1;
    for (int i = 0; i < 61; i++)
    {
        if (legtobb_szama < legtobb_helyen[i])
        {
            legtobb_szama = legtobb_helyen[i];
            legtobb_helyen_index = i;
        }
    }
    kitalalando_szo[legtobb_helyen_index] = betu;
    talalt_tippek[*kitalalt_betuk_szama] = betu;
    (*kitalalt_betuk_szama)++;
    econio_clrscr();
    printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nTalalt.\n");
    printf("A szo: ");
    for (int i = 0; i < kitalalando_szo_hossza; i++)
    {
        printf("%c ", kitalalando_szo[i]);
    }
    printf("\nNem talalt tippek: ");
    for (int i = 0; i < *nem_talalt_tippek_szama; i++)
    {
        printf("%c ", nem_talalt_tippek[i]);
    }
    printf("\n");
    long j = 0;
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu && ((*szotar)[i].szo[legtobb_helyen_index] == betu))
        {
            j++;
        }
    }
    adat_elem *ujszotar = (adat_elem*) malloc(j * sizeof(adat_elem));
    if (ujszotar == NULL)
    {
        printf("'Nem sikerult memoriat foglalni.\n");
        exit(-1);
    }
    j = 0;
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu && ((*szotar)[i].szo[legtobb_helyen_index] == betu))
        {
            memcpy(ujszotar + j, *szotar + i, sizeof(adat_elem));
            j++;
        }
        else
        {
            free((*szotar)[i].szo);
        }
    }
    free(*szotar);
    *szotar = ujszotar;
    *megfelelo_szavak_szama = j;
}

/*A tobbszor_fordul_elo függvény kiválogatja azokat a szavakat, amelyekben a tippelt betu egynél többször, de a legkevesebbszer fordul elo.
Ezek közül egy random szót kiválaszt és megnézi, hogy mely indexen szerepel az adott számszor a tippelt betu, majd az összes olyan szót kiválogatja, amely ugyanott tartalmazza a betut.*/

void tobbszor_fordul_elo(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu, char *kitalalando_szo,
                         char *talalt_tippek, int *kitalalt_betuk_szama, int kitalalando_szo_hossza, int legkevesebb_betu)
{
    if (*megfelelo_szavak_szama == 1)
    {
        int talalt = 0;
        for (int i = 0; i < kitalalando_szo_hossza; i++)
        {
            if ((*szotar)[0].szo[i] == betu)
            {
                kitalalando_szo[i] = betu;
                talalt = 1;
            }
        }
        if (talalt)
        {
            econio_clrscr();
            printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nTalalt.\n");
            printf("A szo: ");
            for (int i = 0; i < kitalalando_szo_hossza; i++)
            {
                printf("%c ", kitalalando_szo[i]);
            }
            printf("\n");
            printf("Nem talalt tippek: ");
            for (int i = 0; i < *nem_talalt_tippek_szama; i++)
            {
                printf("%c ", nem_talalt_tippek[i]);
            }
            printf("\n");
            talalt_tippek[*kitalalt_betuk_szama] = betu;
            (*kitalalt_betuk_szama)++;
        }
        else
        {
            econio_clrscr();
            printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nNem talalt.\n");
            nem_talalt_tippek[*nem_talalt_tippek_szama] = betu;
            (*nem_talalt_tippek_szama)++;
            printf("Nem talalt tippek: ");
            for (int i = 0; i < *nem_talalt_tippek_szama; i++)
            {
                printf("%c ", nem_talalt_tippek[i]);
            }
            printf("\n\n");
            printf("A szo: ");
            for (int i = 0; i < kitalalando_szo_hossza; i++)
            {
                printf("%c ", kitalalando_szo[i]);
            }
            printf("\n");
        }
    }
    else
    {
        for (int i = 0; i < *megfelelo_szavak_szama; i++)
        {
            int betu_szama = 0;
            for (int j = 0; j < kitalalando_szo_hossza; j++)
            {
                if ((*szotar)[i].szo[j] == betu)
                {
                    betu_szama++;
                }
            }
            (*szotar)[i].szoban_elofordulo_betu_szama = betu_szama;
        }
        int szamlalo = 0;
        for (int i = 0; i < *megfelelo_szavak_szama; i++)
        {
            if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
            {
                szamlalo++;
            }
        }
        if (szamlalo == 1)
        {
            bool kilep = false;
            int i = 0;
            while (kilep != true)
            {
                if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
                {
                    for (int j = 0; j < kitalalando_szo_hossza; j++)
                    {
                        if ((*szotar)[i].szo[j] == betu)
                        {
                            kitalalando_szo[j] = betu;
                        }
                    }
                    kilep = true;
                }
                i++;
            }
            adat_elem *ujszotar = (adat_elem*) malloc(szamlalo * sizeof(adat_elem));
            for (int i = 0; i < *megfelelo_szavak_szama; i++)
            {
                if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
                {
                    memcpy(ujszotar + 0, *szotar + i, sizeof(adat_elem));
                }
                else
                {
                    free((*szotar)[i].szo);
                }
            }
           econio_clrscr();
            printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nTalalt.\n");
            free(*szotar);
            *szotar = ujszotar;
            *megfelelo_szavak_szama = szamlalo;
            //printf("\n\n");
            talalt_tippek[*kitalalt_betuk_szama] = betu;
            (*kitalalt_betuk_szama)++;
            printf("A szo: ");
            for (int i = 0; i < kitalalando_szo_hossza; i++)
            {
                printf("%c ", kitalalando_szo[i]);
            }
            printf("\nNem talalt tippek: ");
            for (int i = 0; i < *nem_talalt_tippek_szama; i++)
            {
                printf("%c ", nem_talalt_tippek[i]);
            }
            printf("\n");
        }
        else if (szamlalo > 1)
        {
            adat_elem *ujszotar = (adat_elem*) malloc(szamlalo * sizeof(adat_elem));
            if (ujszotar == NULL)
            {
                printf("'Nem sikerult memoriat foglalni.\n");
                exit(-1);
            }
            int j = 0;
            for (int i = 0; i < *megfelelo_szavak_szama; i++)
            {
                if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
                {
                    memcpy(ujszotar + j, *szotar + i, sizeof(adat_elem));
                    j++;
                }
                else
                {
                    free((*szotar)[i].szo);
                }
            }
            free(*szotar);
            *szotar = ujszotar;
            *megfelelo_szavak_szama = j;
            long random = rand() % *megfelelo_szavak_szama;
            for (int i = 0; i < kitalalando_szo_hossza; i++)
            {
                if ((*szotar)[random].szo[i] == betu)
                {
                    if (kitalalando_szo[i] == '_')
                    {
                        kitalalando_szo[i] = betu;
                    }
                }
            }
            int k = 0;
            for (int i = 0; i < *megfelelo_szavak_szama; i++)
            {
                int szamol = 0;
                for (int j = 0; j < kitalalando_szo_hossza; j++)
                {
                    if (kitalalando_szo[j] == betu && (*szotar)[i].szo[j] == betu)
                    {
                        szamol++;
                    }
                }
                if (szamol == legkevesebb_betu)
                {
                    k++;
                }
            }
            adat_elem *ujszotar2 = (adat_elem*) malloc(k * sizeof(adat_elem));
            if (ujszotar2 == NULL)
            {
                printf("'Nem sikerult memoriat foglalni.\n");
                exit(-1);
            }
            k = 0;
            for (int i = 0; i < *megfelelo_szavak_szama; i++)
            {
                int szamol = 0;
                for (int j = 0; j < kitalalando_szo_hossza; j++)
                {
                    if (kitalalando_szo[j] == betu && (*szotar)[i].szo[j] == betu)
                    {
                        szamol++;
                    }
                }
                if (szamol == legkevesebb_betu)
                {
                    memcpy(ujszotar2 + k, (*szotar) + i, sizeof(adat_elem));
                    k++;
                }
                else
                {
                    free((*szotar)[i].szo);
                }
            }
            free(*szotar);
            *szotar = ujszotar2;
            *megfelelo_szavak_szama = k;
            talalt_tippek[*kitalalt_betuk_szama] = betu;
            (*kitalalt_betuk_szama)++;
            econio_clrscr();
             printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nTalalt.\nA szo: ");
            for (int i = 0; i < kitalalando_szo_hossza; i++)
            {
                printf("%c ", kitalalando_szo[i]);
            }
            printf("\nNem talalt tippek: ");
            for (int i = 0; i < *nem_talalt_tippek_szama; i++)
            {
                printf("%c ", nem_talalt_tippek[i]);
            }
            printf("\n");
        }
    }
}

/*A betuket_beir függvény a tippelt betu szavakban lévo elofurdulási számának megfeleloen hívja meg a megfelelo függvényt.*/

void betuket_beir(adat_elem **szotar, long *megfelelo_szavak_szama, char betu, char *nem_talalt_tippek, int kitalalando_szo_hossza, int *kitalalt_betuk_szama, char *kitalalando_szo,
                  int *tippek_szama, char *talalt_tippek, int *nem_talalt_tippek_szama)
{
    int legkevesebb_betu = 1000; //biztosan legyen csere
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        long j = 0;
        (*szotar)[i].szoban_elofordulo_betu_szama = 0;
        while ((*szotar)[i].szo[j] != '\0')
        {
            if ((*szotar)[i].szo[j] == betu)
            {
                (*szotar)[i].szoban_elofordulo_betu_szama++;
            }
            j++;
        }
        if (legkevesebb_betu > (*szotar)[i].szoban_elofordulo_betu_szama)
        {
            legkevesebb_betu = (*szotar)[i].szoban_elofordulo_betu_szama;
        }
    }
    int legkevesebb_betut_tartalmazo_szavak_szama = 0;
    for (long i = 0; i < *megfelelo_szavak_szama; i++)
    {
        if ((*szotar)[i].szoban_elofordulo_betu_szama == legkevesebb_betu)
        {
            legkevesebb_betut_tartalmazo_szavak_szama++;
        }
    }
    if (legkevesebb_betu == 0)
    {
        nincs_benne(szotar, megfelelo_szavak_szama, nem_talalt_tippek, nem_talalt_tippek_szama, betu, legkevesebb_betut_tartalmazo_szavak_szama, 0, kitalalando_szo_hossza, kitalalando_szo);
    }
    else
    {
        if (legkevesebb_betu == 1)
        {
            egyszer_fordul_elo(szotar, megfelelo_szavak_szama, nem_talalt_tippek, nem_talalt_tippek_szama, betu, 1,
                               kitalalando_szo, talalt_tippek, kitalalt_betuk_szama, kitalalando_szo_hossza);
        }
        else
        {
            tobbszor_fordul_elo(szotar, megfelelo_szavak_szama, nem_talalt_tippek, nem_talalt_tippek_szama, betu, kitalalando_szo, talalt_tippek, kitalalt_betuk_szama, kitalalando_szo_hossza, legkevesebb_betu);
        }
    }
}
